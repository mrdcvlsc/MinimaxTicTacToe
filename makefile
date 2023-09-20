CXX:=clang++
CXX_STANDARD:=-std=c++20
WARNING_FLAGS:=-Wall -Wextra -Wpedantic


debug:
	$(CXX) $(CXX_STANDARD) TicTacToeConsole.cpp -o main.out $(WARNING_FLAGS) -g3 -fsanitize=address

release:
	$(CXX) $(CXX_STANDARD) TicTacToeConsole.cpp -o ttt-cli.out $(WARNING_FLAGS) -O3

test:
	$(CXX) $(CXX_STANDARD) tests.cpp -o tests.out $(WARNING_FLAGS) -g3 -fsanitize=address

comb:
	$(CXX) $(CXX_STANDARD) combinations.cpp -o comb.out $(WARNING_FLAGS) -O3

combd:
	$(CXX) $(CXX_STANDARD) combinations.cpp -o comb.out $(WARNING_FLAGS) -g3 -fsanitize=address

style:
	clang-format -i -style=file *.hpp *.cpp