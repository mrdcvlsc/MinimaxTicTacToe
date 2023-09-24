/* A program to get the total reachable tic-tac-toe board
   states in a tic-tac-toe game "ASSUMING NORMAL GAMEPLAY" */

#include <cstddef>
#include <ios>
#include <iostream>
#include <chrono>
#include <limits>
#include <random>
#include <ratio>

#include "TicTacToe.hpp"

int main() {
    std::mt19937_64 engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<size_t> rng(std::numeric_limits<size_t>::min(), std::numeric_limits<size_t>::max());

    size_t RUN_ID = 0;
    for (size_t i = 0; i < 1'000'000'000; ++i) {
        RUN_ID += rng(engine);
    }
    std::cout << "board 2x2 UID : " << std::hex << RUN_ID << std::dec << '\n';

    auto              start2x2 = std::chrono::high_resolution_clock::now();
    ttt::TicTacToe<2> board2x2;
    board2x2.get_computer_move(2 * 2 + 1);
    std::cout << "Total reachable 2x2 Tic-Tac-Toe board positions achievable through normal play : "
              << board2x2.tree_table.size() << '\n';
    auto end2x2 = std::chrono::high_resolution_clock::now();
    auto dur2x2 = std::chrono::duration_cast<std::chrono::microseconds>(end2x2 - start2x2);
    std::cout << "Time took : " << dur2x2.count() << " microseconds\n\n";
    board2x2.new_game();

    RUN_ID = 0;
    for (size_t i = 0; i < 100'000'000; ++i) {
        RUN_ID += rng(engine);
    }
    std::cout << "board 3x3 UID : " << std::hex << RUN_ID << std::dec << '\n';

    auto              start3x3 = std::chrono::high_resolution_clock::now();
    ttt::TicTacToe<3> board3x3;
    board3x3.get_computer_move(3 * 3 + 1);
    std::cout << "Total reachable 3x3 Tic-Tac-Toe board positions achievable through normal play : "
              << board3x3.tree_table.size() << '\n';
    auto end3x3 = std::chrono::high_resolution_clock::now();
    auto dur3x3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3x3 - start3x3);
    std::cout << "Time took : " << dur3x3.count() << " milliseconds\n\n";
    board3x3.new_game();

    RUN_ID = 0;
    for (size_t i = 0; i < 100'000'000; ++i) {
        RUN_ID += rng(engine);
    }
    std::cout << "board 4x4 UID : " << std::hex << RUN_ID << std::dec << '\n';

    auto              start4x4 = std::chrono::high_resolution_clock::now();
    ttt::TicTacToe<4> board4x4;
    board4x4.get_computer_move(4 * 4 + 1);
    std::cout << "Total reachable 4x4 Tic-Tac-Toe board positions achievable through normal play : "
              << board4x4.tree_table.size() << '\n';
    auto end4x4 = std::chrono::high_resolution_clock::now();
    auto dur4x4 = std::chrono::duration_cast<std::chrono::seconds>(end4x4 - start4x4);
    std::cout << "Time took : " << dur4x4.count() << " seconds\n\n";
    board4x4.new_game();

    RUN_ID = 0;
    for (size_t i = 0; i < 100'000'000; ++i) {
        RUN_ID += rng(engine);
    }
    std::cout << "board 5x5 UID : " << std::hex << RUN_ID << std::dec << '\n';

    auto              start5x5 = std::chrono::high_resolution_clock::now();
    ttt::TicTacToe<5> board5x5;
    board5x5.get_computer_move(5 * 5 + 1);
    std::cout << "Total reachable 5x5 Tic-Tac-Toe board positions achievable through normal play : "
              << board5x5.tree_table.size() << '\n';
    auto end5x5 = std::chrono::high_resolution_clock::now();
    auto dur5x5 = std::chrono::duration_cast<std::chrono::seconds>(end5x5 - start5x5);
    std::cout << "Time took : " << dur5x5.count() << " seconds\n\n";
    board5x5.new_game();

#ifdef DISPLAY_ALL_BOARD_STATES
    for (auto board: board2x2.tree_table) {
        for (auto row: board.first) {
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