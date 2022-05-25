
# Reversi in C

The Reversi board game implemented in C. This was done for the APS105 course at the University of Toronto.

The goal of this project was to allow a player to compete against an AI in the terminal. As an extension, student AI's were put up against one another and the algorithms were ranked on a leaderboard. Students were given two weeks to code and improve their algorithm.

With my implementation of the minimax algorithm, I ranked **4th** place with a score of **2489** 🥳.

## How does Reversi work?

The standard Reversi board is an 8 x 8 where two players - white tiles and black tiles - try to cover the board with their color. The black tile plays first. 

The initial setup looks like this:

![image](https://user-images.githubusercontent.com/81657185/170308910-30f856e0-0b3b-4d42-a30c-9d564dd9bc08.png)


At the center, 4 tiles are placed in a pattern. To make a valid move, a player has to surround (or flank) the opponents tile with two of their own. For exaple: W B W.
This pattern can take place in any direction on the board. The games ends when there are no valid moves or when the board is full.


## AI for Reversi

For the AI, I used the minimax algorithm with alhpa-beta pruning. The name minimax is derived from the idea that from each players perspective, they would want to maximize their score. The term 'mini' comes from the idea that maximizing the opponents score is minimzing your own score. Minimax assumes that the player would make the best move possible for them, so that the computer can avoid a move that would lead to that board position. If the computer could try all possible moves in a turn and knew the outcome of the board n-turns into the future, it can make a well informed decision as where to place the tile. The constraints of the competition required the AI's move to take no longer than 1 second. In this time period, my implemenation allow the computer to search the game tree 13 turns into the future. 

The function <code>minimax</code> is a recursive function. The first call originates from trying out all the possible moves for the computer. Inside the minimax function, a copy of the board is made is made for each move. After trying a move, <code>minimax</code> is called again with a simple change - now it is the player's turn. The minimax function is called n times, where each turn is flipped between the computer and the player. Once reaching the n-th turn, The herusitic score of the board is calculated, always with respect to the computer. This score is passed up the call stack and then evaluated against the best score. If the call originated from the maximizer's turn, the <code>fmax(bestScore, currentScore)</code> is reassigned to <code>bestScore</code>. If the call originated from the minimizer's turn, the <code>fmin(bestScore, currentScore)</code> is saved instead.

### My throughts on Minimax

My first view of minimax was that it stores the location of the best move for every turn and then the computer would execute said moves. Although, this assumes that the player would always make their best move, which is not the case. Instead, minimax works by executing one valid move and then evaluating the outcome of that move n-turns into the future. It repeats this for all valid moves in a given turn. Therefore, <code>minimax</code> is called at every turn the computer has and for each turn, it evalues the board 13 turns into the future. Due to the recursive nature of the function, the deeper the game tree (n -turns), the more resources are utilized. Inceasing the number of turns from 13 to 14 caused the program to exceed the 1 second time constraint.

### Minimax with Alpha-Beta pruning

### Evaluating the board

Previously, I mentioned that at the end of each minimax call, the score is calculated to get a sense of how good the origin move is. One simple and greedy way of evaluating the board, from the computer's perspective, is to <code>+1</code> for every computer tile and <code>-1</code> for every player tile. Although, Reversi is a complex game inovlving strategy where board positions are important to the outcome of a game. For example, a single move might flip over 3 of the opponents tiles which seems promising. However, that board position may allow the opponent to flip over 8 of your own tiles. A move might seem rewarding in the current turn but it may allow the opponent to gain an upper hand in future moves.

To combat this, the board needs to be evaluated in a heuristic sense where certain positions are valued more than others, even if they sacrifice points in the short run. For example, in Reversi, it is crucial to capture the corners as the opponent can never re-claim that for themseleves.
