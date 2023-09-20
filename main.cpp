#include <array>
#include <iostream>
#include <set>
#include <vector>

constexpr size_t SIDES = 2;

struct Move {
    size_t x;
    size_t y;
};

void print_board(std::array<std::array<char, SIDES>, SIDES> const &board) {
    for (auto arr: board) {
        for (auto e: arr) {
            std::cout << e << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

std::vector<Move> generate_moves(std::array<std::array<char, SIDES>, SIDES> const &board) {
    std::vector<Move> all_possible_moves = {};

    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[i].size(); ++j) {
            if (board[i][j] != ' ') {
                all_possible_moves.push_back({i, j});
            }
        }
    }
}

int main() {
    std::array<std::array<char, SIDES>, SIDES> board = {};
    std::array<char, SIDES>                    players = {'x', 'o'};
    size_t                                     player_index = 0;

    std::set<std::array<std::array<char, SIDES>, SIDES>> tree_set;

    for (auto &arrs: board) {
        arrs.fill(' ');
    }

    std::cout << "starting to get all combination\n";
    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[i].size(); ++j) {
            board[i][j] = players[player_index];
            player_index++;
            player_index %= players.size();
            tree_set.insert(board);
        }
    }
    std::cout << "all combination found\n";

    std::cout << "there are a total of " << tree_set.size() << " combinations for\n";
    std::cout << "a tic-tac-toe game with a dimension " << SIDES << 'x' << SIDES << '\n';

    return 0;
}