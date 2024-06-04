PHONY =
BRANCH = $(shell git symbolic-ref --short HEAD)
# test ===================================================================================
run_test: src/mapper/mapper.out src/dfg/dfg.out
	python3 ./test/dfg/run_test.py
	python3 ./test/mapper/run_test.py

PHONY += run_test
# build ==================================================================================
src/mapper/mapper.out:
	make -C ./src/mapper/ -j8 mapper.out
src/dfg/dfg.out:
	make -C ./src/dfg/ -j6 dfg.out

PHONY += src/dfg/dfg.out src/mapper/mapper.out
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
.PHONY: $(PHONY)