//
// Author: Ammar Vora
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <time.h>
#include <unistd.h>

int currentScore = 0;

char COMPUTER;
char PLAYER;

void printBoard(char board[][26], int n)
{
    printf("  ");
    // print the abcd s
    for (int letter = 0; letter < n; letter++)
    {
        printf("%c", (char)(97 + letter));
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("%c ", 97 + i);
        for (int j = 0; j < n; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void getOpposite(char *tile, char *opposite)
{
    if (*tile == 'W')
        *opposite = 'B';
    else
        *opposite = 'W';
}

bool positionInBounds(int n, int row, int col)
{
    if (row >= n || col >= n || row < 0 || col < 0)
        return false;

    return true;
}

bool isLegalInDirection(char board[][26], int n, int row, int col,
                        char tile, int deltaRow, int deltaCol)
{
    char opposite;
    getOpposite(&tile, &opposite);

    // Next one has to be the opposite tile
    if (board[row += deltaRow][col += deltaCol] == opposite)
    {
        int score = 0;
        // Check if the same color comes again.
        while (positionInBounds(n, row, col))
        {
            // End of sequence
            if (board[row][col] == tile)
            {
                currentScore += score;
                return true;
            }
            // Break in the sequence
            else if (board[row][col] == 'U')
            {
                return false;
            }
            score++;

            row += deltaRow;
            col += deltaCol;
        }
    }

    return false;
}

bool isValidAndFlip(char board[][26], int size, int row, int col, char tile, bool flip, bool score)
{
    // Use this variable to see if move is valid.
    bool isLegal = false;

    // Check in directions
    for (int deltaRow = -1; deltaRow < 2; deltaRow++)
    {
        for (int deltaCol = -1; deltaCol < 2; deltaCol++)
        {

            // Skip over the center direction
            if (deltaRow != 0 || deltaCol != 0)
            {

                // Check if the direction is valid
                if (positionInBounds(size, row + deltaRow, col + deltaCol))
                {

                    bool legal =
                        isLegalInDirection(board, size, row, col,
                                           tile, deltaRow, deltaCol);

                    if (legal)
                    {
                        // When you don't want to flip, or are not counting
                        // score. When counting score, have to go through all
                        // directions, and therefore, cannot return true after
                        // single confirmation
                        if (!flip && !score)
                            return true;
                        else if (!flip && score)
                            isLegal = true;
                        else
                        {
                            isLegal = true;

                            char opposite;
                            getOpposite(&tile, &opposite);

                            // Flip until you can't
                            for (int rowDummy = row + deltaRow, colDummy = col + deltaCol;
                                 board[rowDummy][colDummy] == opposite;
                                 rowDummy += deltaRow, colDummy += deltaCol)
                            {
                                board[rowDummy][colDummy] = tile;
                            }
                        }
                    }
                }
            }
        }
    }
    return isLegal;
}

bool moveExists(char board[][26], int size, char tile)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == 'U')
                if (isValidAndFlip(board, size, i, j, tile, false, false))
                    return true;
    return false;
}

// ***NEED TO TEST THIS OUT*** {{DONE}}
int calculateScore(char board[][26], int size, int tile)
{
    int score = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == tile)
            {
                score++;
            }
            else if (board[i][j] == 'U')
                continue;
            else
            {
                score--;
            }
        }
    }

    return score;
}

// ***NEED TO TEST THIS OUT*** {{DONE}}
int calculate(char board[][26], int size, char tile)
{
    int score = 0;
    char opposite;
    getOpposite(&tile, &opposite);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == tile)
                score++;
            else if (board[i][j] == 'U')
            {
                continue;
            }
            else
                score--;
        }
    }

    // If the opponent has corners, don't take corner edges
    if (board[0][0] == opposite)
    {
        score -= 50;
        if (board[0][1] == tile)
            score -= 60;
        if (board[1][0] == tile)
            score -= 60;
        if (board[1][1] == tile)
            score -= 60;
    }

    if (board[0][size - 1] == opposite)
    {
        score -= 50;
        if (board[0][size - 2] == tile)
            score -= 60;
        if (board[1][size - 2] == tile)
            score -= 60;
        if (board[1][size - 1] == tile)
            score -= 60;
    }

    if (board[size - 1][0] == opposite)
    {
        score -= 50;
        if (board[size - 2][0] == tile)
            score -= 60;
        if (board[size - 2][1] == tile)
            score -= 60;
        if (board[size - 1][1] == tile)
            score -= 60;
    }

    if (board[size - 1][size - 1] == opposite)
    {
        score -= 50;
        if (board[size - 1][size - 2] == tile)
            score -= 60;
        if (board[size - 2][size - 2] == tile)
            score -= 60;
        if (board[size - 2][size - 1] == tile)
            score -= 60;
    }

    // If the corners are empty, don't take corner edges
    if (board[0][0] == 'U')
    {
        if (board[0][1] == tile)
            score -= 10;
        if (board[1][0] == tile)
            score -= 10;
        if (board[1][1] == tile)
            score -= 10;
    }

    if (board[0][size - 1] == 'U')
    {
        if (board[0][size - 2] == tile)
            score -= 10;
        if (board[1][size - 2] == tile)
            score -= 10;
        if (board[1][size - 1] == tile)
            score -= 10;
    }

    if (board[size - 1][0] == 'U')
    {
        if (board[size - 2][0] == tile)
            score -= 10;
        if (board[size - 2][1] == tile)
            score -= 10;
        if (board[size - 1][1] == tile)
            score -= 10;
    }

    if (board[size - 1][size - 1] == 'U')
    {
        if (board[size - 1][size - 2] == tile)
            score -= 10;
        if (board[size - 2][size - 2] == tile)
            score -= 10;
        if (board[size - 2][size - 1] == tile)
            score -= 10;
    }

    // If you have corners, and the opponent has corner edges.
    if (board[0][0] == tile)
    {
        score += 20;

        // check for edge sequences
        int index = 1;
        while (board[index][0] == tile && index < size)
        {
            score += 10;
            index++;
        }
        index = 1;
        while (board[0][index] == tile && index < size)
        {
            score += 10;
            index++;
        }

        if (board[0][1] == opposite)
            score += 5;
        if (board[1][0] == opposite)
            score += 5;
        if (board[1][1] == opposite)
            score += 5;
    }

    if (board[0][size - 1] == tile)
    {
        score += 20;
        int index = size - 2;
        while (board[0][index] == tile && index > 0)
        {
            score += 10;
            index--;
        }
        index = 1;
        while (board[index][size - 1] == tile && index > size)
        {
            score += 10;
            index++;
        }
        if (board[0][size - 2] == opposite)
            score += 5;
        if (board[1][size - 2] == opposite)
            score += 5;
        if (board[1][size - 1] == opposite)
            score += 5;
    }

    if (board[size - 1][0] == tile)
    {
        score += 20;
        int index = size - 2;
        while (board[index][0] == tile && index > 0)
        {
            score += 10;
            index--;
        }
        index = 1;
        while (board[size - 1][index] == tile && index < size)
        {
            score += 10;
            index++;
        }
        if (board[size - 2][0] == opposite)
            score += 5;
        if (board[size - 2][1] == opposite)
            score += 5;
        if (board[size - 1][1] == opposite)
            score += 5;
    }

    if (board[size - 1][size - 1] == tile)
    {
        score += 20;

        int index = size - 2;
        while (board[size - 1][index] == tile && index > 0)
        {
            score += 10;
            index--;
        }
        index = size - 2;
        while (board[index][size - 1] == tile && index > 0)
        {
            score += 10;
            index--;
        }
        if (board[size - 1][size - 2] == opposite)
            score += 5;
        if (board[size - 2][size - 2] == opposite)
            score += 5;
        if (board[size - 2][size - 1] == opposite)
            score += 5;
    }

    return score;
}

void makeBoardCopy(const char board[][26], char boardCopy[][26], int size)
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            boardCopy[row][col] = board[row][col];
        }
    }
}

void freeBoard(char **boardCopy, int size)
{
    for (int index = 0; index < size; index++)
        free(boardCopy[index]);
    free(boardCopy);
    boardCopy = NULL;
}

int minimax(char board[][26], int size, char tile, int depth, bool computer, int alpha, int beta)
{
    if (depth > 13)
    {
        return calculate(board, size, tile) - depth;
    }
    else
    {
        // Maximizer
        if (computer)
        {
            int bestScore = -1000000;
            bool checked = false;
            bool done = false;
            for (int i = 0; i < size && !done; i++)
            {
                for (int j = 0; j < size && !done; j++)
                {
                    if (board[i][j] == 'U')
                    {
                        // make the move and then call minimax to make the next move
                        // and calculate score

                        // copy the board into dummy ***NEED TO TEST THIS*** {{DONE}}
                        char boardCopy[size][26];
                        makeBoardCopy(board, boardCopy, size);

                        if (isValidAndFlip(boardCopy, size, i, j, tile, true, false))
                        {
                            boardCopy[i][j] = tile;
                            checked = true;
                            int currentScore = minimax(boardCopy, size, tile, ++depth, !computer, alpha, beta);

                            bestScore = fmax(bestScore, currentScore);

                            alpha = fmax(bestScore, alpha);
                            if (beta <= alpha)
                                done = true;

                            // no need to undo move as a copy of the board was
                            // used.
                        }
                    }
                }
            }

            // If no new move was made, end the minimax recursion and return
            // the score.

            // Multiply the score by a "bad move" factor
            if (!checked)
            {
                return (calculate(board, size, tile) - depth) - 50;
            }

            return bestScore;
        }
        // The minimizer
        else
        {
            int bestScore = 1000000;
            bool checked = false;
            bool done = false;
            for (int i = 0; i < size && !done; i++)
            {
                for (int j = 0; j < size && !done; j++)
                {
                    if (board[i][j] == 'U')
                    {

                        // Make the move for the opposite tile
                        char opposite;
                        getOpposite(&tile, &opposite);

                        // Make a copy of the board
                        char boardCopy[size][26];
                        makeBoardCopy(board, boardCopy, size);

                        if (isValidAndFlip(boardCopy, size, i, j, opposite, true, false))
                        {
                            boardCopy[i][j] = opposite;
                            checked = true;
                            int currentScore = minimax(boardCopy, size, tile, ++depth, !computer, alpha, beta);

                            bestScore = fmin(bestScore, currentScore);

                            beta = fmin(bestScore, beta);
                            if (beta <= alpha)
                                done = true;
                        }
                    }
                }
            }

            if (!checked)
            {
                // Multiply the score by a "good move" factor
                return (calculate(board, size, tile) - depth) + 40;
            }

            return bestScore;
        }
    }
}

// If the depth after minimax is 0, there are no possible moves for that place
// Then set row and col to -1 as there are no moves, and return 0

int makeMove(const char board[][26], int n, char turn, int *row, int *col)
{

    int bestScore = -10000000;

    // make a copy of board and pass into minimax
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 'U')
            {

                char boardCopy[n][26];
                makeBoardCopy(board, boardCopy, n);

                if (isValidAndFlip(boardCopy, n, i, j, turn, true, false))
                {
                    boardCopy[i][j] = turn;
                    int currentScore = minimax(boardCopy, n, turn, 0, false, -10000000, 10000000);
                    if (currentScore > bestScore)
                    {
                        bestScore = currentScore;
                        *row = i;
                        *col = j;
                    }
                }
            }
        }
    }

    // No moves found
    if (bestScore == -10000000)
        return 0;

    return 1;
}

bool playerMove(char board[][26], int size, char tile)
{

    if (!moveExists(board, size, tile))
        return false;

    char input[3];
    printf("Enter move for colour %c (RowCol): ", tile);
    scanf("%s", input);

    bool legal = isValidAndFlip(board, size, input[0] - 'a', input[1] - 'a', tile, true, false);
    if (legal)
    {
        board[input[0] - 'a'][input[1] - 'a'] = tile;
    }
    else
    {
        printf("Invalid move.\n%c player wins.", COMPUTER);
        exit(0);
    }

    return true;
}
void printWinner(char board[][26], int size)
{
    int wCount = 0, bCount = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == 'W')
                wCount++;
            else if (board[i][j] == 'B')
                bCount++;
        }
    }

    if (wCount > bCount)
        printf("W player wins.");
    else if (bCount > wCount)
        printf("B player wins.");
    else
        printf("Draw.");
}

bool isFull(char board[][26], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[i][j] == 'U')
                return false;
        }
    }

    return true;
}

int main(void)
{

    int size;
    printf("Enter the board dimension: ");
    scanf("%d", &size);

    char board[size][26];

    // Set the initial tiles
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            board[i][j] = 'U';
        }
    }

    board[(size / 2) - 1][(size / 2) - 1] = 'W';
    board[(size / 2)][(size / 2)] = 'W';
    board[(size / 2) - 1][(size / 2)] = 'B';
    board[(size / 2)][(size / 2) - 1] = 'B';

    char input[2];
    char PLAYER;
    printf("Computer plays (B/W): ");
    scanf("%s", input);

    COMPUTER = input[0];
    getOpposite(&COMPUTER, &PLAYER);

    printBoard(board, size);

    // Main loop

    bool done = false;

    // To see who is supposed to move first.
    // If move is 0, then COMPUTER plays, else PLAYER plays
    int move = 0;
    if (PLAYER < COMPUTER)
        move = 1;

    // For testing purpose
    int count = 0;
    bool moves[2] = {true, true};
    while (!done)
    {

        if (isFull(board, size))
        {
            // Find winner
            printWinner(board, size);
            done = true;
        }
        // Computer goes first
        else if (move == 0)
        {

            // call computer plays
            // moves[0] = computerMove(board, size, COMPUTER);
            int row, col;

            clock_t start, end;
            double cpu_time_used;
            start = clock();

            moves[0] = makeMove(board, size, COMPUTER, &row, &col);

            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

            printf("Computation took: %lfs\n", cpu_time_used);
            if (moves[0])
            {
                isValidAndFlip(board, size, row, col, COMPUTER, true, false);

                board[row][col] = COMPUTER;
                printf("Computer places %c at %c%c.\n", COMPUTER, 'a' + row, 'a' + col);
                printBoard(board, size);
                int score = calculateScore(board, size, COMPUTER);
                printf("Score for computer: %d\n", score);
            }
            else
                printf("%c player has no valid move.\n", COMPUTER);

            move = 1;
            count++;
        }
        else
        {
            // call player plays

            moves[1] = playerMove(board, size, PLAYER);
            if (moves[1])
                printBoard(board, size);
            else
                printf("%c player has no valid move.\n", PLAYER);

            move = 0;
            count++;
        }

        // No one played, therefore game is ending
        if (!moves[0] && !moves[1])
        {
            // Find winner
            printWinner(board, size);
            done = true;
        }
    }
    return 0;
}