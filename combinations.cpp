/* A program to get the total reachable tic-tac-toe board
   states in a tic-tac-toe game "ASSUMING NORMAL GAMEPLAY" */

#include <cstddef>
#include <iostream>
#include <chrono>
#include <ratio>

#include "TicTacToe.hpp"

int main() {
    auto              start2x2 = std::chrono::high_resolution_clock::now();
    ttt::TicTacToe<2> board2x2;
    board2x2.get_computer_move(2 * 2 + 1);
    std::cout << "Total reachable 2x2 Tic-Tac-Toe board positions achievable through normal play : "
              << board2x2.tree_table.size() << '\n';
    auto end2x2 = std::chrono::high_resolution_clock::now();
    auto dur2x2 = std::chrono::duration_cast<std::chrono::microseconds>(end2x2 - start2x2);
    std::cout << "Time took : " << dur2x2.count() << " microseconds\n\n";
    board2x2.new_game();

    auto              start3x3 = std::chrono::high_resolution_clock::now();
    ttt::TicTacToe<3> board3x3;
    board3x3.get_computer_move(3 * 3 + 1);
    std::cout << "Total reachable 3x3 Tic-Tac-Toe board positions achievable through normal play : "
              << board3x3.tree_table.size() << '\n';
    auto end3x3 = std::chrono::high_resolution_clock::now();
    auto dur3x3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3x3 - start3x3);
    std::cout << "Time took : " << dur3x3.count() << " milliseconds\n\n";
    board3x3.new_game();

    auto              start4x4 = std::chrono::high_resolution_clock::now();
    ttt::TicTacToe<4> board4x4;
    board4x4.get_computer_move(4 * 4 + 1);
    std::cout << "Total reachable 4x4 Tic-Tac-Toe board positions achievable through normal play : "
              << board4x4.tree_table.size() << '\n';
    auto end4x4 = std::chrono::high_resolution_clock::now();
    auto dur4x4 = std::chrono::duration_cast<std::chrono::seconds>(end4x4 - start4x4);
    std::cout << "Time took : " << dur4x4.count() << " seconds\n\n";
    board4x4.new_game();

    // auto              start5x5 = std::chrono::high_resolution_clock::now();
    // ttt::TicTacToe<5> board5x5;
    // board5x5.get_computer_move(5 * 5 + 1);
    // std::cout << "Total reachable 5x5 Tic-Tac-Toe board positions achievable through normal play : "
    //           << board5x5.tree_table.size() << '\n';
    // auto end5x5 = std::chrono::high_resolution_clock::now();
    // auto dur5x5 = std::chrono::duration_cast<std::chrono::seconds>(end5x5 - start5x5);
    // std::cout << "Time took : " << dur5x5.count() << " seconds\n\n";
    // board5x5.new_game();

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