
# Reversi in C

The Reversi board game implemented in C. This was done for the APS105 course at the University of Toronto.

The goal of this project was to allow a player to compete against an AI in the terminal. As an extension, student AI's were put up against one another and the algorithms were ranked on a leaderboard. Students were given two weeks to code and improve their algorithm.

With my implementation, I ranked **4th** place with a score of **2489** 🥳.

## How does Reversi work?

The standard Reversi board is an 8 x 8 where two players - white tiles and black tiles - try to cover the board with their color. The black tile plays first. 

The initial setup looks like this:


  a b c d e f g h  
a U U U U U U U U   
b U U U U U U U U   
c U U U U U U U U   
d U U U W B U U U   
e U U U B W U U U   
f U U U U U U U U   
g U U U U U U U U   
h U U U U U U U U   

At the center, 4 tiles are placed in a pattern. To make a valid move, a player has to surround (or flank) the opponents tile with two of their own. For exaple: W B W.
This pattern can take place in any direction on the board. The games ends when there are no valid moves or when the board is full.


## AI for Reversi

For the AI, I used the minimax algorithm with alhpa-beta pruning. Minimax revolves around the idea that if a player knew the outcome of the board n-moves into the future, they can make a well informed decision as where to place their tile.
