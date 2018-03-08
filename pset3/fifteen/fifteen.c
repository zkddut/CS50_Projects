/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(int d, int board[DIM_MAX][DIM_MAX]);
void draw(int d, int board[DIM_MAX][DIM_MAX]);
bool move(int tile, int d, int board[DIM_MAX][DIM_MAX]);
bool won(int d, int board[DIM_MAX][DIM_MAX]);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init(d, board);

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw(d, board);

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won(d, board))
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile, d, board))
        {
            printf("\nIllegal move.\n");
            usleep(50000);
        }

        // sleep thread for animation's sake
        usleep(50000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(int d, int board[DIM_MAX][DIM_MAX])
{
    int i, j;
    int count = (d*d -1);
    int tmp;
    for (i = 0; i < d; i++){
        for (j = 0; j < d; j++){
            board[i][j] = count--;
        }
    }
    if (d%2 == 0) {
        tmp = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = tmp;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(int d, int board[DIM_MAX][DIM_MAX])
{
    int i, j;
    for (i = 0; i < d; i++){
        for (j = 0; j < d; j++){
            if (board[i][j] == 0) {
                printf("_ ");
            }else{
                printf("%d ",board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile, int d, int board[DIM_MAX][DIM_MAX])
{
    int i, j;
    int tmp;
    for (i = 0; i < d; i++){
        for (j = 0; j < d; j++){
            if (board[i][j] == tile) {
                if (((i-1) >=0) & (board[i-1][j] ==0)) {
                    tmp = board[i][j];
                    board[i][j] = board[i-1][j];
                    board[i-1][j] = tmp;
                    return true;
                }
                if (((j-1) >=0) & (board[i][j-1] ==0)) {
                    tmp = board[i][j];
                    board[i][j] = board[i][j-1];
                    board[i][j-1] = tmp;
                    return true;
                }
                if (((i+1) <d) & (board[i+1][j] ==0)) {
                    tmp = board[i][j];
                    board[i][j] = board[i+1][j];
                    board[i+1][j] = tmp;
                    return true;
                }
                if (((j+1) <d) & (board[i][j+1] ==0)) {
                    tmp = board[i][j];
                    board[i][j] = board[i][j+1];
                    board[i][j+1] = tmp;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(int d, int board[DIM_MAX][DIM_MAX])
{
    int i, j;
    int count = 1;
    for (i = 0; i < d; i++){
        for (j = 0; j < d; j++){
            if ((board[i][j] == count) | (((i == d-1) & (j == d-1)) & (board[i][j] == 0)))  {
                count++;
            }else{
                return false;
            }
        }
    }
    return true;
}
