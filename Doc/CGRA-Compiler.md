[TOC]

# DFG生成

## 基本假设

该模块负责从C语言到由算子组成的DFG的生成，对C语言本身有如下限制：

1. 目标代码需包含在确定次数的循环内
2. 目标代码不能包含循环上限不确定的循环
3. 目标代码的语法仅包含if，循环，赋值和表达式
4. 不含子循环（后续可支持）
5. 不含循环依赖（暂时mapper不支持）
6. 无函数调用
7. 不含`return`

## 去除循环（后续计划）

### `while`，`do while`等价`for`表述

`while`等价于不含`step`和`init`的`for`循环，即对于如下循环

```c
while (exp) {
    <s_1>;
    <s_2>
    ...
}
```

应变为如下等价表述

```c
for(;exp;) {
    <s_1>;
    <s_2>
    ...
}
```

同理`do while`仅是第一次必须运行，故对于如下循环

```c
do {
    <s_1>;
    <s_2>
    ...
} while (exp);
```

应变为如下等价表述

```c
<s_1>;
<s_2>;
...
for(;exp;) {
    <s_1>;
    <s_2>;
    ...
}
```

### 去除`for`循环

`for`循环在AST中一般由以下四个元素组成
1. `init`即循环开始前需要运行的语句
2. `step`即每次循环结束后需要运行的语句
3. `cond`即每次循环开始前需要判断的表达式，为真则
4. `body`即循环内部语句

根据[上一步](#whiledo-while等价for表述)可得任意循环语句均可，定义后缀`_in`为内部循环，`_out`为外部循环，主要步骤如下：
1. 设置`break_sig`来判定是否循环停止
2. 外层循环次数调整为`for(int k=0;k<m*(n_1+n_2+...))`，其中`n_i`为内部第`i`个循环的上限
3. 循环开始前运行`init`，并通过`cond`判断赋值`break_sig`
4. 循环`body`结束后运行`step`，并通过`cond`判断赋值`break_sig`
5. 定义`n_0 = 0`则通过`k%m`的值来判断：
   1. `k%m == 0`则运行外层循环代码
   2. `(n_i <= k%m) && (k%m < n_i+n_{i+1})`则运行第`i+1`个循环的代码

则对于如下循环：

```c
for (<init_out>;<step_out>;<cond_out>) {
    <s_out_1>;
    <s_out_2>;
    ...
    <s_out_n>;
    for(<init_in_1>;<step_in_1>;<cond_in_1>) {
        <s_in_1_1>;
        <s_in_1_2>;
        ...
    }
    <s_out_{n+1}>;
    ...
    <s_out_m>;
    for(<init_in_2>;<step_in_2>;<cond_in_2>) {
        <s_in_2_1>;
        <s_in_2_2>;
        ...
    }
    <s_out_{m+1}>;
    ...
    <s_out_o>;
}
```

设三个内部循环的最大循环次数依次为`n_1,n_2,n_3`，外部循环最大次数为`m`则变换后

```c
int break_out, break_in_1, break_in_2, break_in_3;
// 外部循环准备
<init_out>；
if (<cond_out>) {
    break_out = 0;
} else {
    break_out = 1;
}
for (int k = 0;k < m*(n_1 + n_2 + n_3);k++) {
    if ((k % (n_1 + n_2 + n_3) == 0) && (!break_out)) {
        <s_out_1>;
        <s_out_2>;
        ...
        <s_out_n>;
        // 第一个内部循环准备
        <init_in_1>;
        if (<cond_in_1>) {
            break_in_1 = 0;
        } else {
            break_in_1 = 1;
        }
    }
    if ((!break_in_1) && (k % m < n_1) && (k % m >= 0)) {
        <s_in_1_1>;
        <s_in_1_2>;
        ...
        // 运行完`body`后运行`step`并判断是否终止循环
        <step_in_1>;
        if (<cond_in_1>) {
            break_in_1 = 0;
        } else {
            break_in_1 = 1;
        }
    }
    if ((k % (n_1 + n_2 + n_3) == 0) && (!break_out)) {
        <s_out_{n+1}>;
        ...
        <s_out_m>;
        // 第二个内部循环准备
        <init_in_2>;
        if (<cond_in_2>) {
            break_in_2 = 0;
        } else {
            break_in_2 = 1;
        }
    }
    if ((!break_in_2) && (k % m < n_1 + n_2) && (k % m >= n_1)) {
        <s_in_2_1>;
        <s_in_2_2>;
        ...
        // 运行完`body`后运行`step`并判断是否终止循环
        <step_in_1>;
        if (<cond_in_2>) {
            break_in_1 = 0;
        } else {
            break_in_1 = 1;
        }
    }
    if ((k % (n_1 + n_2 + n_3) == 0) && (!break_out)) {
        <s_out_{m+1}>;
        ...
        <s_out_o>;
        // 运行完`body`后运行`step`并判断是否终止循环
        <step_out>;
        if (<cond_out>) {
            break_out = 0;
        } else {
            break_out = 1;
        }
    }
}
```

### 主要流程

1. 将所有`while`以及`do while`循环转化为`for`循环
2. 自内向外，递归消除所有`for`循环

## 生成DFG

针对满足[基本假设](#基本假设)且不含内部循环（根据[上一步](#去除循环后续计划)可去除）的C代码生成DFG

即此时的C代码仅包含条件语句和赋值语句

### 基本流程

1. 根据控制流（br语句）深度优先访问各个block并执行：
   1. 记录所有`phi`、`store`以及输出到外部的指令
   2. 根据`br`计算访问到时的条件，并记录
   3. 对每一条**不是**`br`或`phi`的指令生成dfg
   4. 若是`phi`，则生成空节点
   5. 若是`br`则根据`br`生成`struct BB_Info`
2. 根据每个block访问到的条件进行简化（可省略，在第一步中建立）
3. 对记录的指令：
   1. 若为`phi`，则根据其标注的前驱block记录的条件生成相应的select算子
   2. 若为`store`
      1. 若所处block为任意控制流均会执行，则不做任意处理
      2. 若不是，则生成`sel`算子满足当前block被执行的情况下存储到目标地址，否则则存储到`dump`地址（避免不同分支存储地址相同产生冲突）
   3. 若为输出到外部的指令
      1. 生成输出地址
      2. 同样生成`sel`算子选择上一步的输出地址或`dump`地址
      3. 根据之前生成的结果生成`store`算子

### 代码描述

#### 变量与类型定义

```c++
struct In_Conn {
    int             node;
    enum Edge_Attr  attr;
    int             operand;
};

struct Out_Conn {
    int             node;
    enum Edge_Attr  attr;
};

struct Node {
    char*               name;
    int                 schedule;
    enum OP_ID          op;
    int                 in_degree;
    int                 out_degree;
    int                 val;
    struct In_Conn*     ins;
    struct Out_Conn*    outs;
};

struct BB_Info {
    struct Node* cond = NULL;
    struct Node* br_true = NULL;
    struct Node* br_false = NULL;
    BasicBlock* next_true = NULL;
    BasicBlock* next_false = NULL;
    BasicBlock* next_uncondi = NULL;
    int visit_cnt = 0;
    int num_preds = -1;
};

std::vector<Instruction*> delay_I;
std::vector<struct Node*> store_stack;
std::map<Instruction*, struct Node*> I_map_Node;
std::map<Constant*, struct Node*> const_map_Node;
std::map<Argument*, struct Node*> arg_map_Node;
std::map<BasicBlock*, BB_Info> BB_map_Info;
std::vector<struct Node*> all_nodes;
std::set<BasicBlock*> un_condi_BB;
Loop* target_L;
BasicBlock* preheader;
```

#### 功能函数

```c++
void add_out_edge(struct Node* in, struct Node* out, int operand, enum Edge_Attr attr);

bool is_inside_BB(BasicBlock* trg_BB)
{
    for (const BasicBlock * BB : target_L->getBlocks()) {
        if (trg_BB == BB) {
            return true;
        }
    }
    return false;
}
bool is_input(Instruction I)
{
    if (is_inside_BB(I->getParent())) {
        return false;
    }
    return true;
}
bool is_output(Instruction I)
{
    for (const Use &U : I->uses()) {
        const Instruction *I = cast<Instruction>(U.getUser());
        if (!is_inside_BB(I->getParent())) {
            return true;
        }
    }
    return false;
}
struct Node* find_or_create_V_node(Value v, enum Edge_Attr* attr = NULL)
{
    if (Constant* C = dyn_cast<Constant>(v)) {
        if (const_map_Node.count(C)) {
            if (attr != NULL) {
                *attr = ATTR_CONST;
            }
            all_nodes.push_back(node);
            return const_map_Node[C];
        }
        ...
        all_nodes.push_back(node);
        return node;
    } else if (Argument* A = dyn_cast<Argument>(v)) {
        if (arg_map_Node.count(A)) {
            if (attr != NULL) {
                *attr = ATTR_CONST;
            }
            all_nodes.push_back(node);
            return arg_map_Node[A];
        }
        ...
        all_nodes.push_back(node);
        return node;
    } else if (Instruction* I = dyn_cast<Instruction>(I->getOperand(r))) {
        if (attr != NULL) {
            *attr = ATTR_IN_VALID;
        }
        if (is_input(I)) {
            ...
        }
        all_nodes.push_back(node);
        return I_map_Node[I];
    }
    printf("unknow type of value");
    exit(1);
}
struct Node* find_or_create_I_node(Instruction I)
{
    if (I_map_Node.count(I)) {
        return I_map_Node[I];
    }
    if(isa<CastInst>(I)) {
        Instruction* pre = dyn_cast<Instruction>(I->getOperand(0));
        I_map_Node[I] = I_map_Node[pre];
        return I_map_Node[I];
    } 
    struct Node* node = ...;
    unsigned int num_operands = I->getNumOperands();
    for(unsigned int r = 0; r < num_operands; r++) {
        enum Edge_Attr attr;
        add_out_edge(node, find_or_create_V_node(I->getOperand(r), &attr), r, attr);
    }
    all_nodes.push_back(node);
    return node;
}
int get_num_preds(BasicBlock *BB)
{
    unsigned int numPreds = 0;

    for (BasicBlock *pred : predecessors(BB)) {
        ++numPreds;
    }
    return numPreds;
}

struct Node* create_not_node(struct Node* n);
struct Node* create_and_node(struct Node* n_1, struct Node* n_2);
struct Node* create_or_node(struct Node* n_1, struct Node* n_2);
struct Node* create_load_node(struct Node* addr);
struct Node* create_sel_node(struct Node* cond, struct Node* true, struct Node* false);
struct Node* create_store_node(struct Node* addr, struct Node* val);
void insert_between(struct Node* n1, struct Node* n2, struct Node* inserted);
void replace_node(struct Node* old_n, struct Node* new_n)
{
    ...
    I_map_Node[I] = new_n;
};
struct Node* get_output_addr();
struct Node* get_dump_addr();
```
#### block递归访问

```c++
void visitor(BasicBlock* BB, struct Node* cond)
{
    // collect conditions
    BB_map_Info[BB].visit_cnt++;
    if (BB_map_Info[BB].num_preds == -1) {
        BB_map_Info[BB].num_preds = get_num_preds(BB);
    }
    if (!un_condi_BB.count(BB)) {
        if (BB_map_Info[BB].cond == NULL) {
            BB_map_Info[BB].cond = cond;
        } else {
            BB_map_Info[BB].cond = create_or_node(cond, BB_map_Info[BB].cond);
        }
    }
    if (BB_map_Info[BB].visit_cnt < BB_map_Info[BB].num_preds) {
        return;
    }
    // visit instructions
    Instruction* I =  NULL;
    std::vector<struct Node*> store_nodes;
    for (BasicBlock::iterator i = (*bb)->begin(), e = (*bb)->end(); i != e; ++i) {
        I = i;
        if (I->getOpcode() == Instruction::Call) {
            printf("Cannot support opkind: %s", I->getOpcodeName());
            exit(1);
        } else if (I->getOpcode() == Instruction::Br) {
            continue;
        } else if (I->getOpcode() == Instruction::PHI) {
            I_map_Node[I] = create_empty_node();
            delay_I.push_back(I);
        } else if (I->getOpcode() == Instruction::Store) {
            I_map_Node[I] = create_I_node(I);
            store_nodes.push_back(I_map_Node[I])
            delay_I.push_back(I);
        } else {
            I_map_Node[I] = create_I_node(I);
            if (is_output(I)) {
                delay_I.push_back(I);
            }
        }
    }
    // visit next BB
    if (BranchInst* br = dyn_cast<BranchInst>(I)) {
        // handle store order
        for (int i = 0; i < store_nodes.size(); i++) {
            for (int j = 0; j < store_stack.size(); j++) {
                add_out_edge(store_stack[j], store_stack[i], 0, ATTR_ORDER)
            }
            store_stack.push_back(store_nodes[i]);
        }
        if (br->isUnconditional()) {
            if (BasicBlock* next_BB = dyn_cast<BasicBlock>(I->getOperand(0))) {
                if (next_BB != preheader && is_inside_BB(next_BB)) {
                    if (un_condi_BB.count(BB)) {
                        un_condi_BB.insert(next_BB);
                    }
                    visit(next_BB, cond);
                }
            } else {
                printf("first operand of unconditional br is not block");
                exit(1);
            }
        } else {
            struct Node* next_cond = find_or_create_V_node(I->getCondition());
            if (BasicBlock* next_BB = dyn_cast<BasicBlock>(I->getOperand(1))) {
                if (next_BB != preheader && is_inside_BB(next_BB)) {
                    BB_map_Info[BB].next_true = next_BB;
                    if (cond != NULL) {
                        BB_map_Info[BB].br_true = create_and_node(cond, br_cond);
                    } else {
                        BB_map_Info[BB].br_true = br_cond;
                    }
                    visit(next_BB, BB_map_Info[BB].br_true);
                }
            } else {
                printf("second operand of conditional br is not block");
                exit(1);
            }
            if (BasicBlock* next_BB = dyn_cast<BasicBlock>(I->getOperand(2))) {
                if (next_BB != preheader && is_inside_BB(next_BB)) {
                    BB_map_Info[BB].next_true = next_false;
                    if (cond != NULL) {
                        BB_map_Info[BB].br_false = create_and_node(cond, create_not_node(br_cond));
                    } else {
                        BB_map_Info[BB].br_false = br_cond;
                    }
                    visit(next_BB, BB_map_Info[BB].br_false);
                }
            } else {
                printf("third operand of conditional br is not block");
                exit(1);
            }
        }
        // handle store order
        for (int i = 0; i < store_nodes.size(); i++) {
            store_stack.pop_back();
        }
    } else {
        printf("last instruction of basic block is opkind: %s", I->getOpcodeName());
        exit(1);
    }
}
```

#### 特殊指令处理

```c++
void handle_phi(PHINode* phi)
{
    struct Node* node = NULL;
    Value* out_Val = NULL;
    for (unsigned i = 0; i < phi->getNumIncomingValues(); ++i) {
        BasicBlock* BB = phi->getIncomingBlock(i);
        if (!is_inside_BB(BB)) {
            if (out_Val == NULL) {
                out_Val = phi->getIncomingValue(i);
            } else {
                // for loop, only pre-header block will have one out side predecessor
                printf("phi instruction has more than one outside incoming BBs");
                exit(1);
            }
        }
    }
    if (out_BB != NULL) {
        node = find_or_create_V_node(out_val)
    } 
    for (unsigned i = 0; i < phi->getNumIncomingValues(); ++i) {
        BasicBlock* BB = phi->getIncomingBlock(i);
        Value* val = phi->getIncomingValue(i);
        if (val == out_Val) {
            continue;
        }
        if (node == NULL) {
            node = find_or_create_V_node(val);
        } else {
            if (BB_map_Info[BB].next_true == I->getParent()) {
                node = create_sel_node(BB_map_Info[I->getParent()].br_ture, find_or_create_V_node(val), node);
            } else {
                node = create_sel_node(BB_map_Info[I->getParent()].br_false, find_or_create_V_node(val), node);
            }
        }
    }
    replace_node(I_map_Node[I],node);
}

void handle_store(Instruction* I)
{
    if (!un_condi_BB.count(I->getParent())) {
        struct Node* store_addr = find_or_create_V_node(I->getOperand(1));
        struct Node* sel_addr = create_sel_node(BB_map_Info[I->getParent()].cond, store_addr, get_dump_addr());
        replace_node(store_addr, sel_addr);
    }
}
void handle_output(Instruction* I)
{
    if (un_condi_BB.count(I->getParent())) {
        create_store_node(get_output_addr(), I_map_Node[I])
    } else {
        struct Node* addr = get_output_addr();
        struct Node* sel_addr = create_sel_node(BB_map_Info[I->getParent()].cond, addr, get_dump_addr());
        create_store_node(sel_addr, I_map_Node[I]);
    }
}

void handle_delay_I()
{
    for (int i = 0; i < delay_I.size(); i++) {
        Instruction* I = delay_I[i];
        if (PHINode* phi = dyn_cast<PHINode>(I)) {
            handle_phi(phi)；
            if (is_output(I)) {
                handle_output(I);
            }
        } else if (I->getOpcode() == Instruction::Store) {
            handle_store(I);
        } else {
            handle_output(I);
        }
    }
}
```

#### 主调度程序

```c++
virtual bool runOnLoop(Loop *L, LPPassManager &LPM)
{
    target_L = L;
    un_condi_BB.insert(L->block_begin());
    visitor(L->block_begin(), NULL);
    handle_delay_I();
    return true;
}

```


### 定义与定理

#### 前提假设

1. 任意指令中用到的任意输入`%n`：
   1. 或在运行到该指令前被指令赋值；
   2. 或为外部输入（在目标代码外部被复制/函数入参）不在目标代码内被赋值；
2. 任意变量`%n`只被一条指令赋值，即任意[条件](#前提定义) $c\in C$ 在目标代码中仅被赋值一次（ssa假设）
3. 任意基本快的最后一条指令：
   1. 或为`ret`
   2. 或为有条件`br`（`br i1 %18, label %26, label %19`）
   3. 或为无条件`br`（`br label %36`）
4. 有条件`br`仅有真，假两个后继基本快，即每个基本快最多可有两个后继
5. 任意代码块在[控制流](#控制流)中至多出现1次（无内部循环）
6. 目标代码的任意指令 $I$ 在其所有外部以来固定的情况下，其运行结果亦固定

#### 前提定义

1. $B=\{b_1,b_2,...,b_n\}$ 为目标代码中基本块
2. $b^*\in B$ 为入口块
3. $F\subset B$ 为出口快，即存在 $b^*$ 或目标代码外的代码块作为其可能后继
4. $C=\{c_1,c_2,...,c_m\}$ 为所有`br`指令中的`cond`
5. 定义函数 $f_K:C\to\{1,0\}$ 对于任意 $c_i\in C$ 有：
   1. $K$ 为 $b^*$ 开始被运行时目标代码所有的外部依赖，以及 $b^*$ 中的`phi`节点取值，即入参
   2. 若存在唯一指令 $I$ 为 $c$ 赋值，则 $f_K(c_i)$ 为目标代码入参为 $K$ 的时候指令 $I$ 的值
   3. 若 $c$ 是不被修改的外部依赖，则 $f_K(c_i)$ 为 $c$ 作为入参的值
   4. 根据[假设](#前提定义)可得指令 $I$ 唯一，易证 $f_K(c_i)$ 是函数
   5. 若无法评估（存在未被赋值的输入），则 $f_K(c_i)=\phi$ （后续证明不考虑，控制流下不存在该情况）
6. 定义函数 $\eta:B\to C\cup\{\epsilon\}$ 
   1. 若 $\eta(b)\in C$ 则表示基本块 $b$ 最后是有条件`br`且条件为 $c$
   2. 若 $\eta(b)=\epsilon$ 则表示基本块 $b$ 最后是无条件`br`
7. 定义函数 $\delta:B\times \{1,0\}\to B\cup\{\varnothing\}$ 满足 $\delta(b,\tau)=\begin{cases}b_1&\eta(b)\ne\epsilon\\b_2&\eta(b)=\epsilon\land\tau=1\\\varnothing&else\end{cases}$ 其中 $b_1\in B,b_2\in B$ 

#### 控制流

若有序集 $s=\left<\delta(b_1,\tau_1),...,\delta(b_k,\tau_k)\right>$ 在特定入参 $K$ 下满足：

1. $k<\infty$ 且对于任意 $i>1$ 均有 $b_i\ne b^*$
2. $b_1=b^*\in B$ 即有唯一入口基本快
3. $b_{i+1}=\delta(b_i,\tau_i)\land b_{i+1}\in B$
4. 若 $\eta(b_i)=\epsilon$ 则 $\tau_i=1$

则称 $\left<\delta(b_1,\tau_1),...,\delta(b_k,\tau_k)\right>$ 是目标代码的一个控制流

其中 $\tau_i$ 表示在参数 $K$ 下 $\eta(b_i)$ 运行到 $b_i$ 最后一条指令时的值（仅为真/假），若 $\eta(b_i)=\epsilon$ 则 $\tau_i=1$

#### 引理1

在入参不变（恒为 $K$ ）的情况下运行[控制流](#控制流) $s=\left<\delta(b_1,\tau_1),...,\delta(b_k,\tau_k)\right>$ 其任意基本快中的任意指令的运算结果不变

##### 证明

定义 $\gamma$ 为指令 $I$ 的参数在[控制流](#控制流)中引用指令的层数，则根据下列证明已经数学归纳法可挣得

###### 当 $\gamma=0$ 时

此时 $I$ 中的所有参数均直接引用外部入参，即在 $K$ 中

若 $I$ 不是`phi`节点，则根据 $K$ 不变可得指令 $I$ 的计算结果不变

若 $I$ 是`phi`节点，设其位于 $b_i$ 中，若 $b_i=b^*$ 则 $I$ 属于 $K$ 显然不变

否则，由于[控制流](#控制流) $s$ 已知，故 $I$ 的前置基本快为 $b_{i-1}$ 确定，即指令 $I$ 仅选择前置为 $b_{i-1}$ 对应的参数为计算结果

又根据 $\gamma=0$ 可得其对应的结果属于 $K$ ，故 $I$ 的计算结果不变

###### 归纳假设

对于任意 $\gamma<n$ 的 $I$ 若属于 $s$ 中，则在入参为 $K$ 的情况下其计算结果不变

###### 当 $\gamma=n$ 时

若 $I$ 不是`phi`节点，根据 $\gamma=n$ 可得其用到的参数或为 $K$ 中提供，根据条件不变

或为其他 $\gamma<n$ 的指令的计算结果。根据[前提假设](#前提假设)这些指令：
1. 必须在控制流中
2. 在 $I$ 之前被计算赋值
3. 只被赋值一次，即赋值后不被修改

故根据归纳假设可得这些指令的计算结果亦不变，即 $I$ 的参数在运行中不被改变。故 $I$ 的计算结果亦不被改变

若 $I$ 是`phi`节点，由于 $s$ 确定可得前置基本快确定，同上可证 $I$ 的计算结果不变

#### 引理2

入参 $K$ 下的[控制流](#控制流) $s=\left<\delta(b_1,\tau_1),...,\delta(b_k,\tau_k)\right>$ 若运行到 $b_i$ 时若 $\eta(b_i)\ne\epsilon$ 则有 $f_K(\eta(b_i))=\tau_i$

##### 证明

根据[假设](#前提假设)：
1. $\eta(b_i)$ 是不被修改的外部依赖，或存在唯一的指令 $I$ 为其赋值
2. 若存在 $I$ ，则控制流 $s$ 运行到 $b_i$ 的最后一条指令时 $\eta(b_i)$ 必被 $I$ 赋值
3. $I$ 在运行时可被评估，即 $f(\eta(b_i))\ne\phi$

根据[定义](#控制流)可得 $\tau_i$ 为控制流运行到 $b_i$ 最后一条指令时 $\eta(b_i)$ 的值

则若 $\eta(b_i)$ 是不被修改的外部依赖，则其值在控制流运行期间恒等于 $f_K(\eta(b_i))$ 故有 $f_K(\eta(b_i))=\tau_i$

若 $\eta(b_i)$ 是目标代码块中的指令 $I$ ，则根据[定义](#前提定义)可得 $f_K(\eta(b_i))$ 为 $K$ 入参下指令 $I$ 的值

且当运行到 $b_i$ 的最后一条指令时 $\eta(b_i)$ 已被 $I$ 赋值并在此之后不被修改，且根据[引理1](#引理1)可得入参为 $K$ 的情况下 $I$ 的运行结果不变

故有 $f_K(\eta(b_i))=\tau_i$

#### 引理3

对于任意入参为 $K$ 的控制流 $s_1,s_2$ 其中一个必是另一个的前段（即对于任意 $1\leq i\leq\min(|s_1|,|s_2|)$ 均有 $b_i=b'_i$）

##### 证明

设 $s_1=\left<\delta(b_1,\tau_1),...,\delta(b_k,\tau_k)\right>，s_2=\left<\delta(b'_1,\tau'_1),...,\delta(b'_l,\tau'_l)\right>$

不妨设 $k\leq l$ 则假设 $s_1$ 不是 $s_2$ 的前段，则必存在 $\{b_{i_1},...,b_{i_p}\},i_j\leq l$ 满足 $b_i\ne b'_i$ 

取 $i=\min(b_{i_1},...,b_{i_p})$ 由于 $b_1=b^*=b'_1$ 故 $i\geq 2$

由于 $b_i$ 最小，故对于任意 $u<i$ 均有 $b_u=b'_u$ ，由于 $\delta(b_u,\tau_u)=b_{u+1}$ 易证:
1. 任意 $u<i-1$ 均有 $\tau_u=\tau'_u$
2. $\tau_{i-1}\ne\tau'_{i-1}$

又根据[引理2](#引理2)有 $\tau_{i-1}=f_K(\eta(b_{i-1}))=f_K(\eta(b'_{i-1}))=\tau'_{i-1}$ 矛盾，故假设不成立，即 $s_1$ 是 $s_2$ 的前段

#### 引理4

若有入参为 $K$ [控制流](#控制流) $s_1=\left<\delta(b_1,\tau_1),...,\delta(b_k,\tau_k)\right>$ ，对于任意其他入参 $K'$ 若满足对于任意 $\eta(b_i)\ne\epsilon$ 有 $f_{K'}(\eta(b_i))=\tau_i$

则存在入参为 $K'$ 的[控制流](#控制流)比 $s_1$ 长

##### 证明

由于 $|B|<\infty$ 且根据[假设](#前提假设)每个 $b\in B$ 在[控制流](#控制流)中只出现一次，故根据[引理3](#引理3)易证参数 $K'$ 下存在最长[控制流](#控制流)

定义最长控制流为 $s_2=\left<\delta(b'_1,\tau'_1),...,\delta(b'_l,\tau'_l)\right>$ ，假设 $l<k$

则取 $s'_1=\left<\delta(b_1,\tau_1),...,\delta(b_l,\tau_l)\right>$ 根据[定理1](#定理1)可得 $s'_1$ 是 $s_2$ 的前段，根据 $|s'_1|=|s_2|$ 有 $s'_1$ 与 $s_2$ 相等

则有 $\delta(b_l,\tau_l)=\delta(b'_l,\tau'_l)$ 又根据 $l<k$ 故有 $\delta(b_l,\tau_l)=b_{l+1}$ 以及 $\eta(b_{l+1})=\eta(b'_{l+1})$

若 $\eta(b_{l+1})=\eta(b'_{l+1})=\epsilon$ 则 $\tau_{l+1}=1$

否则根据[引理2](#引理2)可得 $f_K(\eta(b_{l+1}))=\tau_{l+1}$ 又根据条件有 $f_{K'}(\eta(b_{l+1}))=\tau_{l+1}=f_K(\eta(b_{l+1}))$

综上所述，易证 $\left<\delta(b'_1,\tau'_1),...,\delta(b'_l,\tau'_l),\delta(b'_{l+1},\tau_{l+1})\right>$ 是参数 $K'$ 下的控制流，与 $l$ 是最长控制流矛盾

故假设不成立，即 $l\geq k$ 

#### 定理1

若有入参为 $K$ [控制流](#控制流) $s_1=\left<\delta(b_1,\tau_1),...,\delta(b_k,\tau_k)\right>$ ，对于任意其他入参为 $K'$ 的[控制流](#控制流) $s_2=\left<\delta(b'_1,\tau'_1),...,\delta(b'_l,\tau'_l)\right>$ 若满足：
1. 对于任意 $\eta(b_i)\ne\epsilon$ 有 $f_{K'}(\eta(b_i))=\tau_i$
4. $l\geq k$
   
则有 $s_1$ 必为 $s_2$ 的前段（即对于任意 $1\leq i\leq k$ 均有 $b_i=b'_i\land\tau_i=\tau'_i$）

##### 证明

根据 $|s_1|<\infty$ ，以下证明以及数学归纳法可得 $s_1$ 是 $s_2$ 的前段

<a id="MK1"></a> 

###### 当 $k=1$ 时

此时显然 $|s_2|\geq|s_1|$ 且 $s_1=\left<\delta(b_1,\tau_1)\right>$ 根据[控制流定义](#控制流)可得 $b_1=b'_1=b^*$ ，根据[定义](#前提定义)可得 $\eta(b_1)=\eta(b^*)=\eta(b'_1)$ 

当 $\eta(b_1)=\eta(b'_1)=\epsilon$ 时根据[控制流定义](#控制流)可得 $\tau_1=\tau'_1=1$

否则，根据条件有 $\eta(b_1)=\eta(b'_1)$ 又根据[引理2](#引理2)有 $\tau_1=f_{K'}(\eta(b_1))=f_{K'}(\eta(b'_1))=\tau'_1$

综上所述，有 $b'_1=b_1,\tau'_1=\tau_1$ 即 $s_1$ 是 $s_2$ 的前段

###### 归纳假设

对于任意 $k<m$ 的情况引理均成立

###### 当 $k=m$ 时

取 $s'_1=\left<\delta(b_1,\tau_1),...,\delta(b_{k-1},\tau_{k-1})\right>$ 显然 $|s_1|<m$ 

又根据条件 $s_2=\left<\delta(b'_1,\tau'_1),...,\delta(b'_l,\tau'_l)\right>$ 满足对于任意 $s_1$ 的 $\eta(b_i)\ne\epsilon$ 存在 $j$ 满足 $\eta(b_i)=\eta(b'_j)$ 以及 $\tau'_j=\tau_i$

则对于 $s'_1$ 同样满足上述条件，即可得 $s'_1$ 是 $s_2$ 的前段，即有 $b_{k-1}=b'_{k-1},\tau_{k-1}=\tau'_{k-1}$ 

故 $\delta(b_{k-1},\tau_{k-1})=\delta(b'_{k-1},\tau'_{k-1})$ ，根据[定义](#控制流)可得 $b_k=\delta(b_{k-1},\tau_{k-1})=\delta(b'_{k-1},\tau'_{k-1})=b'_k$ 即有 $\eta(b_k)=\eta(b'_k)$ 

当 $\eta(b_k)=\epsilon$ 时根据[控制流定义](#控制流)可得 $\tau_k=\tau'_k=1$

当 $\eta(b_k)\ne\epsilon$ 时根据[引理2](#引理2)有 $\tau_k=f_{K'}(\eta(b_k))=f_{K'}(\eta(b'_k))=\tau'_k$

综上所述，根据 $s'_1$ 是 $s_2$ 的前段以及 $b_k=b'_k,\tau_k=\tau'_k$ 可得 $s_1$ 是 $s_2$ 的前段

#### 定理2

若有入参为 $K$ [控制流](#控制流) $s_1=\left<\delta(b_1,\tau_1),...,\delta(b_k,\tau_k)\right>$ 若有入参 $K'$ 满足对于任意 $\eta(b_i)\ne\epsilon$ 有 $f_{K'}(\eta(b_i))=\tau_i$

则 $K'$ 的最长控制流一定经过 $b_k$

##### 证明

根据[引理4](#引理4)可得 $K'$ 下存在控制流 $s_2=\left<\delta(b'_1,\tau'_1),...,\delta(b'_l,\tau'_l)\right>$ 满足 $l\geq k$

则根据[定理1](#定理1)可得 $s_1$ 是 $s_2$ 的前段，故有 $b_k=b'_k$

# mapper

# CGRA汇编语法

```bison
INTEGER = [-+]?[0-9]+ /*正则表达式，整数*/

INPUT = 
    "pe_left" |
    "pe_up" |
    "pe_right" |
    "pe_down" |
    "left_LSU" |
    "up_LSU" |
    "right_LSU" |
    "down_LSU" |
    "lr[0]" |
    "lr[1]" |
    "lr[2]" |
    "imm_reg[0]" |
    "imm_reg[1]" |  
    "imm_reg[2]" |
    "gr"
;

RELATION = 
    "<" |
    "<=" |
    "=="
;

CONDI = 
    INPUT RELATION INPUT |
    INPUT RELATION "1"
;

INPUT_OR_BOOL = 
    INPUT |
    "1" |
    "0"
;

IF = "%if" CONDI "," INPUT_OR_BOOL "," INPUT_OR_BOOL;

ROUT = "%rout" INPUT;

ARITH = 
    "%sadd" INPUT "," INPUT|
    "%ssub" INPUT "," INPUT|
    "%sabs" INPUT|
    "%sneg" INPUT|
    "%smul" INPUT "," INPUT|
    "%smod" INPUT "," INPUT|
    "%smac" INPUT "," INPUT
;

LOGIC = 
    "%and" INPUT "," INPUT|
    "%or" INPUT "," INPUT|
    "%not" INPUT|
    "%xor" INPUT
;

SHIFT = 
    "%sra" INPUT "," INPUT|
    "%srl" INPUT "," INPUT|
    "%sll" INPUT "," INPUT
;

IMM = "imm" INTEGER "," INPUT /*save integer into INPUT*/

OP_INSTR =
    IF |
    ROUT |
    ARITH |
    LOGIC |
    SHIFT |
    IMM
;

OUTPUTS = 
    “out=” INTEGER |
    OUTPUTS "|" “out=” INTEGER

INSTR_PRE = "//iteration_cycle=" INTEGER "|start_cycle=" INTEGER "|II=" INTEGER "|" OUTPUTS;

INSTR = INSTR_PRE "\n" OP_INSTR;

INSTRS = 
    INSTR |
    INSTRS "\n" INSTR
;

INTEGER_OR_X = 
    INTEGER |
    "x"
;

PE_INSTR = 
    "PE[" INTEGER "]" "\n"
    "%TOP CP_index_=" INTEGER_OR_X "|CP_num=" INTEGER_OR_X "|Instruction_num=" INTEGER "\n"
    INSTRS
;

PE_INSTRS = 
    PE_INSTR | 
    PE_INSTRS "\n" PE_INSTR
;
```
