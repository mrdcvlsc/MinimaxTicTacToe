// WHEN A BUG IS FOUND, PLEASE ADD THE TEST HERE FIRST THEN FIX IT
// DON'T REMOVE PREVIOUS TEST CASES, ONLY UPDATE IT IF THERE'S INTERNAL CHANGES

#include <iostream>
#include <assert.h>

#include "TicTacToe.hpp"

int main() {
    ttt::TicTacToe<3> board;
    std::uint32_t     game_status = ttt::ONGOING;

    // ==========================================================================
    // row win test 1
    board.make_move(0, 0);
    board.make_move(1, 1);
    board.make_move(0, 1);
    board.make_move(2, 2);
    game_status = board.make_move(0, 2);

    assert(game_status == ttt::PLAYER1);
    assert(game_status != ttt::PLAYER2);
    board.new_game();

    // ==========================================================================
    // row win test 2
    board.make_move(0, 0);
    board.make_move(1, 1);
    board.make_move(0, 1);
    board.make_move(1, 2);
    board.make_move(2, 2);
    game_status = board.make_move(1, 0);

    assert(game_status != ttt::PLAYER1);
    assert(game_status == ttt::PLAYER2);
    board.new_game();

    // ==========================================================================
    // row win test 3
    board.make_move(2, 0);
    board.make_move(1, 0);
    board.make_move(2, 1);
    board.make_move(1, 1);
    game_status = board.make_move(2, 2);

    assert(game_status == ttt::PLAYER1);
    assert(game_status != ttt::PLAYER2);
    board.new_game();

    // ==========================================================================
    // col win test 1
    board.make_move(1, 1);
    board.make_move(0, 0);
    board.make_move(2, 2);
    board.make_move(1, 0);
    board.make_move(0, 2);

    game_status = board.make_move(2, 0);

    assert(game_status != ttt::PLAYER1);
    assert(game_status == ttt::PLAYER2);
    board.new_game();

    // ==========================================================================
    // col win test 2
    board.make_move(0, 0);
    board.make_move(0, 1);
    board.make_move(0, 2);
    board.make_move(1, 1);
    board.make_move(1, 2);
    game_status = board.make_move(2, 1);

    assert(game_status != ttt::PLAYER1);
    assert(game_status == ttt::PLAYER2);
    board.new_game();

    // ==========================================================================
    // col win test 3
    board.make_move(2, 0);

    board.make_move(2, 2);
    board.make_move(2, 1);
    board.make_move(1, 2);
    board.make_move(0, 1);
    game_status = board.make_move(0, 2);

    assert(game_status != ttt::PLAYER1);
    assert(game_status == ttt::PLAYER2);
    board.new_game();

    // ==========================================================================
    // left diag win test
    board.make_move(0, 1);
    board.make_move(0, 0);
    board.make_move(0, 2);
    board.make_move(1, 1);
    board.make_move(2, 0);
    game_status = board.make_move(2, 2);

    assert(game_status != ttt::PLAYER1);
    assert(game_status == ttt::PLAYER2);
    board.new_game();

    // ==========================================================================
    // right diag win test
    board.make_move(0, 2);
    board.make_move(0, 0);
    board.make_move(1, 1);
    board.make_move(0, 1);
    game_status = board.make_move(2, 0);

    assert(game_status == ttt::PLAYER1);
    assert(game_status != ttt::PLAYER2);
    board.new_game();

    // ==========================================================================
    // bug 1

    board.make_move(0, 1);
    board.make_move(0, 2);
    board.make_move(0, 0);
    board.make_move(1, 1);

    ttt::Move minimax_move1 = board.minimax(ttt::PLAYER1, 25);

    assert(minimax_move1.player == ttt::PLAYER1);
    assert(minimax_move1.player != ttt::PLAYER2);
    assert(minimax_move1.i == 2);
    assert(minimax_move1.j == 0);

    board.make_move(minimax_move1.i, minimax_move1.j);
    board.new_game();

    // ==========================================================================
    // bug 2

    board.make_move(1, 1); // x
    board.make_move(0, 0); // o
    board.make_move(0, 1); // x
    board.make_move(2, 1); // o
    board.make_move(0, 2); // x
    board.make_move(2, 0); // o
    board.make_move(2, 2); // x

    std::uint32_t winner = board.check_winning_last_move();
    assert(winner == ttt::EMPTY);
    board.new_game();

    // ==========================================================================
    // bug 3

    board.make_move(0, 2);                         // x
    board.make_move(1, 0);                         // o
    auto bug3Move = board.get_computer_move(1000); // x

    assert(bug3Move.player == ttt::PLAYER1);
    assert(bug3Move.player != ttt::PLAYER2);
    assert(bug3Move.i == 0);
    assert(bug3Move.j == 0);
    board.new_game();

    // ==========================================================================
    // bug 4

    ttt::TicTacToe<5> ttt5x5board;

    ttt5x5board.make_move(0, 3);
    ttt5x5board.make_move(0, 0);
    ttt5x5board.make_move(1, 3);
    ttt5x5board.make_move(0, 1);
    ttt5x5board.make_move(3, 0);
    ttt5x5board.make_move(0, 2);
    ttt5x5board.make_move(3, 1);
    ttt5x5board.make_move(0, 4);
    ttt5x5board.make_move(4, 3);
    ttt5x5board.make_move(1, 0);
    ttt5x5board.make_move(3, 4);
    ttt::Move ttt5x5MBbug1 = ttt5x5board.get_computer_move(4);

    assert(ttt5x5MBbug1.i == 2);
    assert(ttt5x5MBbug1.j == 3);

    std::cout << "ALL TESTS PASSED\n";

    return 0;
}