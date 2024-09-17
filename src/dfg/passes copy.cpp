#include "passes.h"

#define NUM_PASSES 6

void remove_unnecessary_nodes()
{
    std::vector<struct Node*> stk;
    std::map<struct Node*, int> out_deg_map;
    for (int i = 0; i < all_nodes.size(); i++) {
        if ((!all_nodes[i]->outs.size()) && all_nodes[i]->op != OP_ID::ID_STORE) {
            stk.push_back(all_nodes[i]);
        }
    }
    while (!stk.empty()) {
        struct Node* n = stk.back();
        stk.pop_back();
        assert(n->outs.size() == 0);
        for (int i = 0; i < n->ins.size(); i++) {
            for (int j = 0; j < n->ins[i].node->outs.size(); j++) {
                if (n->ins[i].node->outs[j].node == n) {
                    n->ins[i].node->outs.erase(n->ins[i].node->outs.begin() + j);
                    j--;
                    if (n->ins[i].node->outs.size() == 0) {
                        stk.push_back(n->ins[i].node);
                    }
                }
            }
        }
        for (int i = 0; i < all_nodes.size(); i++) {
            if (all_nodes[i] == n) {
                all_nodes.erase(all_nodes.begin() + i);
                i--;
            }
        }
        n->ins.clear();
        delete n;
    }
}

int get_sched_out_deg(struct Node* n)
{
    int out_deg = 0;
    for (struct Out_Conn out : n->outs) {
        if (out.attr == Edge_Attr::ATTR_IN_VALID || out.attr == Edge_Attr::ATTR_ORDER) {
            out_deg++;
        }
    }
    return out_deg;
}

int max_schedule = 0;

void print_schedule()
{
    for (int t = 0; t < max_schedule + 1; t++) {
        printf("schedule time = %d: ", t);
        for (struct Node* n : all_nodes) {
            if (n->op != OP_ID::ID_CONST && n->schedule == t) {
                printf("%s,", n->name.c_str());
            }
        }
        printf("\n");
    }
}

void Schedule_ALAP()
{
    std::vector<struct Node*> stack;
    std::map<struct Node*, int> out_deg_map;
    max_schedule = 0;

    for (struct Node* n : all_nodes) {
        if (n->op != OP_ID::ID_CONST) {
            out_deg_map[n] = get_sched_out_deg(n);
            if (out_deg_map[n] == 0) {
                n->schedule = 0;
                stack.push_back(n);
            }
        }
    }

    while (stack.size()) {
        struct Node* n = stack.back();
        stack.pop_back();
        for (struct In_Conn in : n->ins) {
            if (in.attr == Edge_Attr::ATTR_IN_VALID || in.attr == Edge_Attr::ATTR_ORDER) {
                out_deg_map[in.node]--;
                if (out_deg_map[in.node] == 0) {
                    stack.push_back(in.node);
                    for (struct Out_Conn out : in.node->outs) {
                        if (out.attr == Edge_Attr::ATTR_IN_VALID || out.attr == Edge_Attr::ATTR_ORDER) {
                            if (out.node->schedule + 1 > in.node->schedule) {
                                in.node->schedule = out.node->schedule + 1;
                            }
                        }
                    }
                    if (in.node->schedule > max_schedule) {
                        max_schedule = in.node->schedule;
                    }
                }
            }
        }
    }

    for (auto out_deg : out_deg_map) {
        if (out_deg.second != 0) {
            printf("Topology sort un-successful, there may be circle in the graph without reverse edge!");
            exit(1);
        }
    }
    for (struct Node* n : all_nodes) {
        if (n->op != OP_ID::ID_CONST) {
            n->schedule = -(n->schedule - max_schedule);
        }
    }
    // print_schedule();
}
int get_sched_in_deg(struct Node* n)
{
    int in_deg = 0;
    for (struct In_Conn in : n->ins) {
        if (in.attr == Edge_Attr::ATTR_IN_VALID || in.attr == Edge_Attr::ATTR_ORDER) {
            in_deg++;
        }
    }
    return in_deg;
}
int get_min_sche(struct Node* n)
{
    int max_in_sche = -1, tmp_n;
    if (get_sched_in_deg(n) > 0) {
        for (struct In_Conn in : n->ins) {
            if (in.attr == Edge_Attr::ATTR_IN_VALID || in.attr == Edge_Attr::ATTR_ORDER) {
                if (in.node->schedule > max_in_sche) {
                    max_in_sche = in.node->schedule;
                }
            }
        }
        return max_in_sche + 1;
    }
    return n->schedule;
}

void indent_schedule()
{
    std::vector<struct Node*> stack;
    for (struct Node* n : all_nodes) {
        if (n->op != OP_ID::ID_CONST) {
            if (n->schedule > get_min_sche(n)) {
                stack.push_back(n);
            }
        }
    }
    while (stack.size()) {
        struct Node* n = stack.back();
        stack.pop_back();
        n->schedule = get_min_sche(n);
        for (struct Out_Conn out : n->outs) {
            if (out.node->schedule > get_min_sche(out.node)) {
                stack.push_back(out.node);
            }
        }
    }
    // print_schedule();
}
int get_max_sche(struct Node* n)
{
    int min_out_sche = max_schedule, tmp_n;
    if (get_sched_out_deg(n) > 0 && n->op != OP_ID::ID_STORE) {
        for (struct Out_Conn out : n->outs) {
            if (out.attr == Edge_Attr::ATTR_IN_VALID || out.attr == Edge_Attr::ATTR_ORDER) {
                if (out.node->schedule < min_out_sche) {
                    min_out_sche = out.node->schedule;
                }
            }
        }
        return min_out_sche - 1;
    }
    return n->schedule;
}
void down_schedule()
{
    std::vector<struct Node*> stack;
    for (struct Node* n : all_nodes) {
        if (n->op != OP_ID::ID_CONST) {
            if (n->schedule < get_max_sche(n)) {
                stack.push_back(n);
            }
        }
    }
    while (stack.size()) {
        struct Node* n = stack.back();
        stack.pop_back();
        n->schedule = get_max_sche(n);
        for (struct In_Conn in : n->ins) {
            if (in.node->schedule < get_max_sche(in.node)) {
                stack.push_back(in.node);
            }
        }
    }
    // print_schedule();
}

void insert_routs()
{
    for (struct Node* n : all_nodes) {
        if (n->op != OP_ID::ID_CONST) {
            int max_next = -1;
            for (struct Out_Conn out : n->outs) {
                if (out.attr == Edge_Attr::ATTR_IN_VALID && out.node->schedule > max_next) {
                    max_next = out.node->schedule;
                }
            }
            struct Node* rout_n = nullptr;
            for (int i = n->schedule + 1; i < max_next; i++) {
                if (rout_n == nullptr) {
                    rout_n = create_node(OP_ID::ID_ROUT, "", {n});
                } else {
                    rout_n = create_node(OP_ID::ID_ROUT, "", {rout_n});
                }
                rout_n->schedule = i;
                for (int j = 0; j < n->outs.size(); j++) {
                    if (n->outs[j].attr == Edge_Attr::ATTR_IN_VALID && n->outs[j].node->schedule == i + 1) {
                        rout_n->outs.push_back(n->outs[j]);
                        for (int k = 0; k < n->outs[j].node->ins.size(); k++) {
                            if (n->outs[j].node->ins[k].node == n) {
                                n->outs[j].node->ins[k].node = rout_n;
                            }
                        }
                        n->outs.erase(n->outs.begin() + j);
                        j--;
                    }
                }
            }
        }
    }
    // print_schedule();
}

bool is_same_node(struct Node* n_1, struct Node* n_2)
{
    if (                    
        n_1->op == n_2->op && 
        n_1->op != OP_ID::ID_CONST &&
        n_1->ins.size() == n_2->ins.size()
    ) {
        int i, j;
        switch (n_1->op) {
            // ops that operand order doesn't matter
            case OP_ID::ID_ADD:
            case OP_ID::ID_MUL:
            case OP_ID::ID_AND:
            case OP_ID::ID_OR:
            case OP_ID::ID_XOR:
            case OP_ID::ID_EQ:
                for (i = 0; i < n_1->ins.size(); i++) {
                    for (j = 0; j < n_2->ins.size(); j++) {
                        if (n_1->ins[i].node == n_2->ins[j].node) {
                            break;
                        }
                    }
                    if (j == n_2->ins.size()) {
                        return false;
                    }
                }
                break;
            default:
                for (i = 0; i < n_1->ins.size(); i++) {
                    for (j = 0; j < n_2->ins.size(); j++) {
                        if (
                            n_1->ins[i].node == n_2->ins[j].node &&
                            n_1->ins[i].operand == n_2->ins[j].operand
                        ) {
                            break;
                        }
                    }
                    if (j == n_2->ins.size()) {
                        return false;
                    }
                }
        }
        return true;
    }
    return false;
}

void merge_same_node()
{
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < all_nodes.size(); i++) {
            for (int j = i + 1; j < all_nodes.size(); j++) {
                if (is_same_node(all_nodes[i], all_nodes[j])) {
                    changed = true;
                    for (int k = 0; k < all_nodes[j]->outs.size(); k++) {
                        for (int l = 0; l < all_nodes[j]->outs[k].node->ins.size(); l++) {
                            if (all_nodes[j]->outs[k].node->ins[l].node == all_nodes[j]) {
                                all_nodes[j]->outs[k].node->ins[l].node = all_nodes[i];
                                all_nodes[i]->outs.push_back(all_nodes[j]->outs[k]);
                            }
                        }
                    }
                    for (int k = 0; k < all_nodes[j]->ins.size(); k++) {
                        for (int l = 0; l < all_nodes[j]->ins[k].node->outs.size(); l++) {
                            if (all_nodes[j]->ins[k].node->outs[l].node == all_nodes[j]) {
                                all_nodes[j]->ins[k].node->outs.erase(all_nodes[j]->ins[k].node->outs.begin() + l);
                                l--;
                            }
                        }
                    }
                    all_nodes.erase(all_nodes.begin() + j);
                    j--;
                }
            }
        }
    }
}

void (*pass_func[NUM_PASSES])() = {
    remove_unnecessary_nodes,
    merge_same_node,
    Schedule_ALAP,
    // ALAP will schecdule order edge as late as possible, but they can be stored earlier instead of add a rout node
    // example as follow
    /*
        add->store0
        add->neg0
        add->abs0
        abs->store1
        store0->store1[order edge]

        by order edge, store1 must be saved before store1
        ALAP will schedule store1 at time 3, and store1 at time 2, add at time 0
        If this is followed, there had to be an rout between add and store
        indent will indent store0 back to time 1, and avoid adding the rout node
    */
    indent_schedule,
    /*
        mapping will start from stores, which has the latest schedules
        rout node in late schedule that mapped into global register will create 
        big amount of extra divergencies of search
    */
    down_schedule,
    insert_routs
};

void run_all_passes()
{
    for (int i = 0; i < sizeof(pass_func) / 8; i++) {
        if (pass_func[i] != nullptr) {
            pass_func[i]();
        }
    }
}