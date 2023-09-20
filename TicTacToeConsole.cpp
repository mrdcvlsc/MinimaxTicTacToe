#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>

#include "TicTacToe.hpp"

static constexpr std::uint32_t GRID = 3;

void player_input(ttt::TicTacToe<GRID> &board, std::uint32_t &row, std::uint32_t &col);
void check_game_result(std::uint32_t game_status);

int main() {
    std::cout << "Pick Piece [input a number] | 0 => x | 1 => o | : ";
    std::uint32_t player;
    std::cin >> player;

    if (!(player == ttt::PLAYER1 || player == ttt::PLAYER2)) {
        std::cerr << "Invalid Player\n";
        return 1;
    }

    ttt::TicTacToe<GRID> board;
    board.print_board();

    constexpr std::uint32_t depth = 10;
    std::uint32_t           game_status = ttt::ONGOING, row, col;

    if (player == 0) {
        // ========================================================================================
        //                                 PLAYING AS 'x'
        // ========================================================================================
        while (true) {
            // -------------------------------------------------------------------
            //                         player's turn
            // -------------------------------------------------------------------

            player_input(board, row, col);
            game_status = board.make_move(row, col);

            if (game_status == ttt::INVALID_MOVE) {
                std::cout << "\nThat is an invalid move, pick another move...\n\n";
                continue;
            }

            board.print_board();
            check_game_result(game_status);

            // -------------------------------------------------------------------
            //                         computer's turn
            // -------------------------------------------------------------------

            std::cout << "computer moving...\n";

            ttt::Move com = board.get_computer_move(depth);
            game_status = board.make_move(com.i, com.j);
            board.print_board();

            if (game_status == ttt::INVALID_MOVE) {
                throw std::runtime_error("get_computer_move() was not supposed to return ttt::INVALID_MOVE");
            }

            check_game_result(game_status);
            std::cout << "computer move done.\n";
        }
    } else if (player == 1) {
        // ========================================================================================
        //                                 PLAYING AS 'o'
        // ========================================================================================
        while (true) {
            // -------------------------------------------------------------------
            //                         computer's turn
            // -------------------------------------------------------------------
            if (game_status != ttt::INVALID_MOVE) {
                std::cout << "computer moving...\n";

                if (board.ply == -1) {
                    // random computer first move
                    std::mt19937 engine(std::chrono::steady_clock::now().time_since_epoch().count());
                    std::uniform_int_distribution<std::uint32_t> rng(0, GRID - 1);

                    auto a = rng(engine);
                    auto b = rng(engine);

                    game_status = board.make_move(a, b);
                } else {
                    ttt::Move com = board.get_computer_move(depth);
                    game_status = board.make_move(com.i, com.j);
                }

                board.print_board();

                if (game_status == ttt::INVALID_MOVE) {
                    throw std::runtime_error("get_computer_move() was not supposed to return ttt::INVALID_MOVE");
                }

                check_game_result(game_status);
                std::cout << "computer move done.\n";
            }

            // -------------------------------------------------------------------
            //                         player's turn
            // -------------------------------------------------------------------

            player_input(board, row, col);
            game_status = board.make_move(row, col);

            if (game_status == ttt::INVALID_MOVE) {
                std::cout << "\nThat is an invalid move, pick another move...\n\n";
                continue;
            }

            board.print_board();
            check_game_result(game_status);
        }
    }

    return 0;
}

void player_input(ttt::TicTacToe<GRID> &board, std::uint32_t &row, std::uint32_t &col) {
    std::cout << "Player Turn : " << ttt::PIECES[board.current_player] << '\n';
    std::cout << "Input the row & column : ";
    std::cin >> row >> col;
}

void check_game_result(std::uint32_t game_status) {
    if (game_status == ttt::DRAW) {
        std::cout << "Game ended in a draw\n";
        std::exit(0);
    }

    if (game_status != ttt::EMPTY && game_status != ttt::ONGOING) {
        std::cout << "Player : " << ttt::PIECES[game_status] << " already won\n";
        std::exit(0);
    }
}