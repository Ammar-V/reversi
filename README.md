
# Reversi in C

The Reversi board game implemented in C. This was done for the APS105 course at the University of Toronto.

The goal of this project was to allow a player to compete against an AI in the terminal. As an extension, student AI's were put up against one another and the algorithms were ranked on a leaderboard. Students were given two weeks to code and improve their algorithm.

With my implementation, I ranked **4th** place with a score of **2489** 🥳.

## How does Reversi work?

The standard Reversi board is an 8 x 8 where two players - white tiles and black tiles - try to cover the board with their color. The black tile plays first. 

The initial setup looks like this:

![image](https://user-images.githubusercontent.com/81657185/170308910-30f856e0-0b3b-4d42-a30c-9d564dd9bc08.png)


At the center, 4 tiles are placed in a pattern. To make a valid move, a player has to surround (or flank) the opponents tile with two of their own. For exaple: W B W.
This pattern can take place in any direction on the board. The games ends when there are no valid moves or when the board is full.


## AI for Reversi

For the AI, I used the minimax algorithm with alhpa-beta pruning. Minimax revolves around the idea that if a player could try all possible moves in a turn and knew the outcome of the board n-turns into the future, they can make a well informed decision as where to place their tile. The constraints of the competition required the AI's move to take no longer than 1 second. In this time period, my implemenation allow the computer to search the game tree 13 moves into the future. 

The name minimax is derived from the idea of finding the maximum score on the player's turn and the minimum score during the computer's turn. The function <code>minimax</code> is a recursive function. The first call originates from trying out all the possible moves for the computer. Inside the minimax function, a copy of the board is made is made for each move. After trying a move, <code>minimax</code> is called again with a simple change - now it is the player's turn. The minimax function is called n times, where each turn is flipped between the computer and the player. Once reaching the n-th turn, The herusitic score of the board is calculated. This score is passed up the call stack and then evaluated against the best score. If the call originated from the maximizer's turn, the <code>fmax(bestScore, currentScore)</code> is reassigned to <code>bestScore</code>. If the call originated from the minimizer's turn, the <code>fmin(bestScore, currentScore)</code> is saved instead.
