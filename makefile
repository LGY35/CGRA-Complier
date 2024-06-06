PHONY =			# 用于存储所有伪目标（非文件目标）的列表。
BRANCH = $(shell git symbolic-ref --short HEAD)
# test ===================================================================================
run_test: src/mapper/mapper.out src/dfg/dfg.out  # 依赖于这两个out文件，存在时执行下面两个py脚本
	python3 ./test/dfg/run_test.py	
	python3 ./test/mapper/run_test.py

PHONY += run_test								# 将 run_test 添加到伪目标列表中。
# build ==================================================================================
src/mapper/mapper.out:							# 调用 make 命令进入./src/mapper/ 目录并并行执行构建 mapper.out 目标。 -C：（1）改变当前工作目录到指定目录。（2）在该目录中执行 Makefile。
	make -C ./src/mapper/ -j8 mapper.out	  
src/dfg/dfg.out:
	make -C ./src/dfg/ -j6 dfg.out

PHONY += src/dfg/dfg.out src/mapper/mapper.out	# 将这两个构建目标添加到伪目标列表中。
# Clean ==================================================================================
clean_mapper:
	make -C ./src/mapper/ clean
clean_dfg:
	make -C ./src/dfg/ clean
clean_test:
	- rm ./test/dfg/output/*
	- rm ./test/mapper/output/*
clean: clean_mapper clean_dfg clean_test

PHONY += clean_mapper clean_dfg clean clean_test
# git ====================================================================================
pull: 
	git pull
commit:
	git add -A
	@echo "Please type in commit comment: "; \
	read comment; \
	git commit -m"$$comment"
sync: sub_pull commit
	git push -u origin $(BRANCH)
list_branch:
	git branch -a
reset_hard:
	git fetch && git reset --hard origin/$(BRANCH)

PHONY += commit sync sub_pull pull reset_hard list_branch
# ========================================================================================
.PHONY: $(PHONY)  # 伪目标声明：这行确保所有在 PHONY 变量中的目标都是伪目标（即使有同名文件存在，也会执行目标规则）。