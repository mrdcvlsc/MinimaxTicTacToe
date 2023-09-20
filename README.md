# MinimaxTicTacToe

![Tests](https://github.com/mrdcvlsc/MinimaxTicTacToe/actions/workflows/tests.yml/badge.svg)

This is another implementation of a minimax Tic-Tac-Toe program.

I have optimized this version in C++, building upon my previous implementation in JavaScript, which you can find here: [minimax-tic-tac-toe](https://github.com/mrdcvlsc/minimax-tic-tac-toe).

I have employed this program to enumerate all possible board states of a Tic-Tac-Toe game achievable through "normal play." In this context, "normal play" refers to two players taking turns placing 'X' and 'O' on an empty square on the Tic-Tac-Toe board until someone wins or the board is filled without a winner.

Current Results:

- Surprisingly, for a small **2x2** Tic-Tac-Toe game, there appear to be a total of **28** possible positions achievable through normal play, excluding the empty board state.

- In the case of a **3x3** Tic-Tac-Toe game, there are a total of **5,477** positions achievable through normal play, excluding the empty board state.

- Conversely, a **4x4** Tic-Tac-Toe game seems to have a total of **9,772,010** positions achievable through normal play, excluding the empty board state.

- For other boards sizes greater than or equal to **5x5**... well there's a lot.