/* A program to get the total reachable tic-tac-toe board
   states in a tic-tac-toe game "ASSUMING NORMAL GAMEPLAY" */

#include "TicTacToe.hpp"
#include <cstddef>
#include <iostream>

int main() {
    constexpr size_t     GRID = 2;
    ttt::TicTacToe<GRID> board;

    board.get_computer_move(GRID * GRID + 1);
    std::cout << "Total Reachable Board Combinations : " << board.tree_table.size() << '\n';

#ifdef DISPLAY_ALL_BOARD_STATES
    for (auto board_state: board.tree_table) {
        for (auto row: board_state) {
            for (auto e: row) {
                std::cout << e << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "--------\n";
    }
#endif

    return 0;
}