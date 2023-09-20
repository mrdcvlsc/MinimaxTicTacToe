# MinimaxTicTacToe

![tests](https://github.com/mrdcvlsc/MinimaxTicTacToe/actions/workflows/tests.yml/badge.svg)

Just another minimax TicTacToe program

An optimized C++ version of my minimax program that I have recently written in
javascript : [minimax-tic-tac-toe](https://github.com/mrdcvlsc/minimax-tic-tac-toe)

I used this program to get all of the possible board state of a tic-tac-toe game that
is reachable through "**normal play**". The _normal play_ here means two players alternately
putting 'x' and 'o' on an empty square in the tic-tac-toe board until someone wins, or draw
by filling the empty square in the board without a player winning.

Current Results:
- For a **3x3** tic-tac-toe game, it seems that there is a total of **5,477** positions
though normal play excluding the empty board state.

- On the other hand, a **4x4** tic-tac-toe game seems to have a total of **9,772,010** positions
achiveable though normal play (excluding the empty board state).
