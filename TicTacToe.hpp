#ifndef MRDCVLSC_CXX_TIC_TAC_TOE_MINIMAX_CLASS
#define MRDCVLSC_CXX_TIC_TAC_TOE_MINIMAX_CLASS

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <limits>
#include <stddef.h>
#include <stdexcept>
#include <utility>
#include <vector>

#include <map>

/// Tic-Tac-Toe game namespace.
namespace ttt {
    using uchar = unsigned char;

    static constexpr std::array<uchar, 2> PIECES = {
        static_cast<uchar>('x'),
        static_cast<uchar>('o'),
    };

    static constexpr std::uint32_t PLAYER1 = 0u, PLAYER2 = 1u;
    static constexpr std::uint32_t DRAW = static_cast<uchar>('d');
    static constexpr std::uint32_t ONGOING = static_cast<uchar>('p');
    static constexpr std::uint32_t EMPTY = static_cast<uchar>('.');
    static constexpr std::uint32_t INVALID_MOVE = static_cast<uchar>('i');

    struct Move {
        std::uint32_t i;
        std::uint32_t j;
        std::uint32_t player;
        float         score;
    };

    template <std::uint32_t grid_n>
    struct TicTacToe {
        std::uint32_t                                                  current_player;
        std::int32_t                                                   ply;
        std::uint32_t                                                  status;
        std::array<std::array<uchar, grid_n>, grid_n>                  board;
        std::array<Move, grid_n * grid_n>                              move_history;
        std::map<std::array<std::array<uchar, grid_n>, grid_n>, float> tree_table;

        TicTacToe() : current_player(PLAYER1), ply(-1), status(ONGOING), board{}, move_history{} {
            for (auto &row: board) {
                row.fill(static_cast<uchar>(EMPTY));
            }
            tree_table.clear();
        }

        void new_game() {
            current_player = PLAYER1;
            ply = -1;
            status = ONGOING;

            for (auto &row: board) {
                row.fill(static_cast<uchar>(EMPTY));
            }
            tree_table.clear();
        }

        void force_make_move(std::uint32_t i, std::uint32_t j) {
            board[i][j] = PIECES[current_player];

            ply++;
            move_history[static_cast<std::uint32_t>(ply)] = {i, j, current_player, 0.f};

            current_player++;
            current_player %= PIECES.size();
        }

        void force_unmake_move() {
            current_player--;
            current_player %= PIECES.size();

            Move move = move_history[static_cast<std::uint32_t>(ply)];
            board[move.i][move.j] = static_cast<uchar>(EMPTY);

            ply--;
        }

        /// \brief Places a piece for the current player in the board.
        ///
        /// \returns `PLAYER1` if player 1 already won.
        /// \returns `PLAYER2` if player 2 already won.
        /// \returns `DRAW`    if the game ended with a draw.
        /// \returns `ONGOING` if there is still no winner but the game haven't ended yet.
        /// \returns `INVALID_MOVE` if the choosen square is already occupied.
        ///
        /// \note checks the board first if a player already won, and if there is none yet,
        /// proceed to make the move, then checks the board again if the last move wins the game.
        ///
        std::uint32_t make_move(std::uint32_t i, std::uint32_t j) {
            if (i >= grid_n || j >= grid_n) {
                return INVALID_MOVE;
            }

            auto win_status = check_winning_last_move();
            if (win_status == PLAYER1 || win_status == PLAYER2 || win_status == DRAW) {
                return win_status;
            }

            if (board[i][j] == static_cast<uchar>(EMPTY)) {
                force_make_move(i, j);
                win_status = check_winning_last_move();

                if (win_status == PLAYER1 || win_status == PLAYER2 || win_status == DRAW) {
                    return win_status;
                }
            } else {
                return INVALID_MOVE;
            }

            return ONGOING;
        }

        Move get_computer_move(std::uint32_t scan_depth) {
            std::uint32_t computer_player = current_player;
            Move          best_move = minimax(current_player, scan_depth);
            best_move.player = computer_player;
            return best_move;
        }

        Move minimax(std::uint32_t maximizing_player, std::uint32_t depth) {
            std::vector<Move> moves = generate_moves();
            Move              best_move = {EMPTY, EMPTY, maximizing_player, 0};

            std::uint32_t winner = check_winning_last_move();
            std::uint32_t remaining_turns = (grid_n * grid_n) - 1 - ply;

            // evaluation for player winners should always come first before the depth checks to prevent returning 0
            // score moves at leaf nodes since my depth == 0 conditions returns 0 score moves

            if (winner == PLAYER1) {
                best_move.score = 1.f * (remaining_turns == 0 ? 1.f : static_cast<float>(remaining_turns));
                return best_move;
            }

            if (winner == PLAYER2) {
                best_move.score = -1.f * (remaining_turns == 0 ? 1.f : static_cast<float>(remaining_turns));
                return best_move;
            }

            // if leaf node : return heuristic value | But since I don't implement a way to evaluate the board's
            // "non-leaf nodes" so I'm just returning a zero score.
            if (depth == 0 || moves.size() == 0) {
                return {0, 0, EMPTY, 0};
            }

            // recursive minimax search

            if (maximizing_player == PLAYER1) {
                best_move.score = -std::numeric_limits<float>::max();
                for (auto &move: moves) {

                    force_make_move(move.i, move.j);
                    auto iter = tree_table.find(board);
                    if (iter == tree_table.end()) {
                        float evaluation_score = minimax(PLAYER2, depth - 1).score;
                        move.score = evaluation_score;
                        if (evaluation_score > best_move.score) {
                            best_move.score = evaluation_score;
                            best_move.i = move.i;
                            best_move.j = move.j;
                        }
                        tree_table.emplace(board, evaluation_score);
                    } else {
                        float saved_score = iter->second;
                        if (saved_score > best_move.score) {
                            best_move.score = saved_score;
                            best_move.i = move.i;
                            best_move.j = move.j;
                        }
                    }
                    force_unmake_move();
                }
            } else {
                best_move.score = std::numeric_limits<float>::max();
                for (auto &move: moves) {

                    force_make_move(move.i, move.j);
                    auto iter = tree_table.find(board);
                    if (iter == tree_table.end()) {
                        float evaluation_score = minimax(PLAYER1, depth - 1).score;
                        move.score = evaluation_score;
                        if (evaluation_score < best_move.score) {
                            best_move.score = evaluation_score;
                            best_move.i = move.i;
                            best_move.j = move.j;
                        }
                        tree_table.emplace(board, evaluation_score);
                    } else {
                        float saved_score = iter->second;
                        if (saved_score < best_move.score) {
                            best_move.score = saved_score;
                            best_move.i = move.i;
                            best_move.j = move.j;
                        }
                    }
                    force_unmake_move();
                }
            }

            return best_move;
        }

        /// \brief Get all of the possible moves for the current state of the tic-tac-toe board.
        ///
        std::vector<Move> generate_moves() {
            // std::vector<Move> generate_moves() const {
            std::vector<Move> all_possible_moves(0);
            all_possible_moves.reserve(grid_n * grid_n - ply);

            for (std::uint32_t i = 0; i < board.size(); ++i) {
                for (std::uint32_t j = 0; j < board[i].size(); ++j) {
                    if (board[i][j] == static_cast<uchar>(EMPTY)) {
                        all_possible_moves.push_back({i, j, PIECES.size(), 0});
                    }
                }
            }

            return all_possible_moves;
        }

        /// \brief Checks the last move for winning conditions.
        ///
        /// \returns `EMPTY` if there is no winner yet.
        /// \returns `DRAW` if the game already end and there's no winner.
        /// \returns `PLAYER1` if last move `x` formed a straight line.
        /// \returns `PLAYER2` if last move `o` formed a straight line.
        ///
        std::uint32_t check_winning_last_move() const {
            if (ply < 0) {
                return EMPTY;
            }

            Move last_move = move_history[static_cast<std::uint32_t>(ply)];

            // vertical check
            std::uint32_t same_piece = 1;
            for (std::uint32_t i = 0; i < grid_n - 1; ++i) {
                uchar piece = board[i][last_move.j];
                if (piece != static_cast<uchar>(EMPTY) && piece == board[i + 1][last_move.j]) {
                    same_piece++;
                    if (same_piece == grid_n) {
                        return last_move.player;
                    }
                } else {
                    same_piece = 1;
                }
            }

            // horizontal check
            same_piece = 1;
            for (std::uint32_t i = 0; i < grid_n - 1; ++i) {
                uchar piece = board[last_move.i][i];
                if (piece != static_cast<uchar>(EMPTY) && piece == board[last_move.i][i + 1]) {
                    same_piece++;
                    if (same_piece == grid_n) {
                        return last_move.player;
                    }
                } else {
                    same_piece = 1;
                }
            }

            // left diagonal check
            same_piece = 1;
            for (std::uint32_t i = 0; i < grid_n - 1; ++i) {
                uchar piece = board[i][i];
                if (piece != static_cast<uchar>(EMPTY) && piece == board[i + 1][i + 1]) {
                    same_piece++;
                    if (same_piece == grid_n) {
                        return last_move.player;
                    }
                } else {
                    same_piece = 1;
                }
            }

            // right diagonal check
            same_piece = 1;
            for (std::uint32_t i = 0; i < grid_n - 1; ++i) {
                uchar piece = board[i][grid_n - 1 - i];
                if (piece != static_cast<uchar>(EMPTY) && piece == board[i + 1][grid_n - 2 - i]) {
                    same_piece++;
                    if (same_piece == grid_n) {
                        return last_move.player;
                    }
                } else {
                    same_piece = 1;
                }
            }

            if (ply == grid_n * grid_n - 1) {
                return DRAW;
            }

            return EMPTY;
        }

        void print_board() const {
            for (auto arr: board) {
                for (auto e: arr) {
                    std::cout << e << ' ';
                }
                std::cout << '\n';
            }
            std::cout << '\n';
        }
    };
} // namespace ttt

#endif