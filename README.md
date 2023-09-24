# MinimaxTicTacToe

![Tests](https://github.com/mrdcvlsc/MinimaxTicTacToe/actions/workflows/tests.yml/badge.svg)

Just another implementation of Tic-Tac-Toe with minimax algorithm.

I have optimized this version in C++, building upon my previous implementation in JavaScript, which you can find here: [minimax-tic-tac-toe](https://github.com/mrdcvlsc/minimax-tic-tac-toe).

A standard tic-tac-toe board has a total of **(N x N)!** (_factorial_) **possible overall board states/configurations** (_without considering board rotations, flips, or mirrors that would result in a similar board state configuration_). However, most of these positions are unattainable in a typical game of tic-tac-toe.

I have employed this program to **enumerate all possible board states** of a Tic-Tac-Toe game **achievable through "normal play"**, In this context, "normal play" refers to two players taking turns placing 'x' and 'o' on an empty square on the Tic-Tac-Toe board until someone wins or the board is filled without having a winner (_draw_).

### Current Results:

_Again all of these results does not consider board rotations, flips, or mirrors that would result in a similar board state configuration, each variation is considered different from each other_.

- Surprisingly, for a small **2x2** Tic-Tac-Toe game, there appears to be a total of **28** possible positions achievable through normal play.

    **[Time took : ~23 microseconds]**

- In the case of a **3x3** Tic-Tac-Toe game, there are a total of **5,477** positions achievable through normal play.

    **[Time took : ~7 milliseconds]**

- Conversely, a **4x4** Tic-Tac-Toe game seems to have a total of **9,722,010** positions achievable through normal play.

    **[Time took : ~32 seconds, Memory usage : 500+ MB]**