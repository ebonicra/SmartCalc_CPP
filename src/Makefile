.PHONY: all  clean tests gcov_report rebuild linter leaks

CC						= g++ -std=c++17
WFLAGS 					= -Wall -Wextra -Werror
GCOVFLAGS 				= --coverage
CLEAN					= rm -rf

NAME					= SmartCalc2

SRC_DIR					= ./model
TEST_FILE				= $(NAME)_test
TEST_FILE_COV			= $(TEST_FILE)_cov
SOURCE					= $(SRC_DIR)/*.cc
TEST 					= ./test/$(TEST_FILE).cc
BUILD_DIR 				= ../build
DOCUMENT				= documentation
DIST_NAME 				= $(NAME)-1.0

OC := $(shell uname)
ifeq ($(OC),Darwin)
	LEAKS 				= CK_FORK=no leaks --atExit --
	CHECKFLAGS 			= -lcheck -lm -lpthread -lgtest
	OPEN 				= open
	APP					= $(NAME).app
else
	LEAKS 				= valgrind --leak-check=full --track-origins=yes -s
	CHECKFLAGS			= -lgtest -lgtest_main -lm -lstdc++ -lpthread
	OPEN 				= xdg-open
	APP					= $(NAME)
endif


all: install

install: uninstall
	qmake CONFIG+=release -o $(BUILD_DIR)/Makefile $(NAME).pro
	-cd $(BUILD_DIR); make -C $(BUILD_DIR) > /dev/null
	-cd $(BUILD_DIR); make clean
	$(CLEAN) $(BUILD_DIR)/Makefile
	$(CLEAN) $(BUILD_DIR)/.qmake.stash
	$(CLEAN) $(BUILD_DIR)/qmake_qmake_qm_files.qrc
	$(CLEAN) $(BUILD_DIR)/.qm

clean:
	$(CLEAN) $(TEST_FILE) $(TEST_FILE_FOR_LEAKS) $(TEST_FILE_COV) .clang-format
	$(CLEAN) *.o *.a *.gcno *.gcda *.info *.out *.gch *.dSYM report
	$(CLEAN) ../$(DIST_NAME).tar.gz ../$(DIST_NAME)
	$(CLEAN) ../$(DOCUMENT)
	$(CLEAN) report*

tests: $(SOURCE) $(TEST)
	$(CC) $(WFLAGS) $(SOURCE) $(TEST) -o $(TEST_FILE) $(CHECKFLAGS)
	./$(TEST_FILE)

rebuild: clean all

gcov_report: $(SOURCE) $(TEST)
	$(CC) $(WFLAGS) $(GCOVFLAGS) $(SOURCE) $(TEST) -o $(TEST_FILE_COV) $(CHECKFLAGS)
	./$(TEST_FILE_COV)
	lcov -t "$(TEST_FILE_COV)" -o $(TEST_FILE_COV).info -c -d . --no-external
	genhtml -o report $(TEST_FILE_COV).info

open_report:
	-$(OPEN) report/index.html

uninstall: clean
	$(CLEAN) $(BUILD_DIR)	

dvi:
	makeinfo -o ../$(DOCUMENT) --html --no-warn --no-validate --force $(DOCUMENT).texi
	-$(OPEN) ../$(DOCUMENT)/index.html

run:
	open ../build/SmartCalc2.app

dist:
	make clean
	cd ..; $(CLEAN) $(DIST_NAME).tar.gz
	$(CLEAN) ../$(DIST_NAME)
	cd ..; cp -r src $(DIST_NAME)
	cd ..; tar -cvf $(DIST_NAME).tar.gz $(DIST_NAME)
	$(CLEAN) ../$(DIST_NAME)

linter:
	clang-format -n -style=google model/*.cc model/*.h
	clang-format -n -style=google view/*.cc view/*.h
	clang-format -n -style=google controller/*.cc controller/*.h
	clang-format -n -style=google main.cc

linter_wow:
	clang-format -i -style=google model/*.cc model/*.h
	clang-format -i -style=google view/*.cc view/*.h
	clang-format -i -style=google controller/*.cc controller/*.h
	clang-format -i -style=google main.cc

leaks: $(TEST_FILE)
	$(LEAKS) ./$(TEST_FILE)
