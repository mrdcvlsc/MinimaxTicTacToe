CC:=gcc
CXX:=g++
OS:=$(shell uname)

LINKING:=-static

CXX_STANDARD:=-std=c++20
CXXFLAGS:=-Wall -Wextra -g3
WARNING_FLAGS:=-Wall -Wextra -Wpedantic

# disable asan if compiler is an arm compiler
IS_ARM_COMPILER:=$(findstring arch,$(CC))$(findstring arm,$(CC))

# disable asan if on a windows operating system
IS_ON_WINDOWS:=$(findstring MSYS_NT,$(OS))$(findstring win,$(OS))$(findstring Win,$(OS))$(findstring WIN,$(OS))

ENABLE_SANITIZER:=$(if $(strip $(IS_ARM_COMPILER)$(IS_ON_WINDOWS)),noasan)

SANITIZER:=
ifneq ($(ENABLE_SANITIZER),noasan)
SANITIZER+=-fsanitize=address
endif

debug:
	$(CXX) $(CXX_STANDARD) TicTacToeConsole.cpp -o main.out $(WARNING_FLAGS) -g3 $(SANITIZER)

release:
	$(CXX) $(CXX_STANDARD) $(LINKING) TicTacToeConsole.cpp -o ttt-cli.out $(WARNING_FLAGS) -O3

test:
	$(CXX) $(CXX_STANDARD) tests.cpp -o tests.out $(WARNING_FLAGS) -g3 $(SANITIZER)

comb:
	$(CXX) $(CXX_STANDARD) $(LINKING) combinations.cpp -o comb.out $(WARNING_FLAGS) -O3

combd:
	$(CXX) $(CXX_STANDARD) combinations.cpp -o comb.out $(WARNING_FLAGS) -g3 $(SANITIZER)

style:
	clang-format -i -style=file *.hpp *.cpp