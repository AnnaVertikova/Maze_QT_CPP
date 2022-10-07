.PHONY: all build install uninstall dvi dist distdir clean test gcov_report gcov_open leaks main

# ========================================================================================================================== #

CXX = g++
FLAGS = --std=c++17 #-ggdb3 
WFLAGS = -Wall -Werror -Wextra
GCOV = --coverage
LCOV = lcov --no-external -t
OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBS = -lgtest -pthread -lm -lsubunit
	LEAKS = valgrind --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(TESTEXE)
	OPEN = xdg-open
else
	LIBS = -lgtest -lstdc++ 
	LEAKS = CK_FORK=no leaks --atExit -- ./$(TESTEXE)
	OPEN = open
endif

FILES = controller/*.cpp \
				model/*.cpp
MAN = ./manual/
TESTFILES = ./*_test.cpp
TESTEXE = test
GCOVFILES = gcov_report.info
REPORTDIR = report
REPORTFILES = index.html
QTBUILDDIR = ../build-Maze-Desktop_x86_darwin_generic_mach_o_64bit-Debug \
						 ../build-Maze-Qt_6_2_3_for_macOS-Debug
BUILDDIR = ../build/
DVIFILE = ./manual/Manual.html
DISTNAME = Maze
DISTDIR = $(HOME)/Applications/Maze/
APP = $(BUILDDIR)Maze.app
APPDIR = $(HOME)/Applications/Maze/

TAR = tar -cf
COMPRESS = gzip -9f
DEL_DIR = rm -rf
DEL_FILE = rm -f
COPY_DIR = cp -f -R

# ========================================================================================================================== #

all: build 

build: clean
	@ mkdir $(BUILDDIR)
	@cd $(BUILDDIR) && qmake ../src/Maze.pro
	@make -C $(BUILDDIR)
	@cd $(BUILDDIR) && $(DEL_DIR) *.c *.h *.cpp *.ui *.o

install: build 
	@mkdir $(APPDIR)
	@cp -rf $(APP) $(APPDIR)
	@make clean

uninstall: 
	@$(DEL_DIR) $(BUILDDIR)
	@$(DEL_DIR) $(APPDIR)

dvi:
	@$(OPEN) $(DVIFILE)

dist: distdir
	@(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) 
	@$(DEL_DIR) $(DISTDIR)

distdir: build
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	@$(COPY_DIR) $(BUILDDIR) $(DISTDIR)/
	@$(COPY_DIR) $(MAN) $(DISTDIR)/

clean:
	@$(DEL_FILE) *.o *.a *.gcno *.gcda *.info *.out *.h.gch *.log *.pro.user $(TESTEXE) $(HOME)/Applications/Maze.tar.gz ./datasets/save_*.txt
	@$(DEL_DIR) ./$(REPORTDIR) ./$(BUILDDIR) ./$(QTBUILDDIR) $(DISTDIR) *.dSYM

test:
	@clear
	@$(CXX) -g $(FLAGS) $(WFLAGS) $(GCOV) $(FILES) $(TESTFILES) $(LIBS) -o $(TESTEXE)
	@./$(TESTEXE)

gcov_report:
	@clear
	@$(LCOV) "$(TESTEXE)" -o $(GCOVFILES) -c -d .
	@genhtml -o $(REPORTDIR) $(GCOVFILES)

gcov_open:
	@$(OPEN) ./$(REPORTDIR)/$(REPORTFILES)

leaks: test
	@$(LEAKS)
	@make clean

main: clean
	@$(CXX) $(FLAGS) -g main.cpp cave.cpp
	@./a.out
