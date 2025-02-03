#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// #include <string.h>
#include <math.h>

//  Proto types :
void Transpose(int board[4][4]);
int moveUp(int board[4][4], int back_board[4][4]);
int moveDown(int board[4][4], int back_board[4][4]);
int moveRight(int board[4][4], int back_board[4][4], int signal);
int moveLeft(int board[4][4], int back_board[4][4], int signal);
int printBoard(int board[4][4], int back_board[4][4]);
void initializeBoard(int board[4][4]);
void addRandom(int board[4][4]);
int calculateScore(int board[4][4]);
int is_win(int board[4][4]);
int is_loose(int board[4][4]);
void new_start(int board[4][4], int back_board[4][4]);
void back_move(int board[4][4], int back_board[4][4]);
int compare_arrays(int board_1[4][4], int board_2[4][4]);
void memmory_copy(int *mem1, int *mem2, int size);
void create_string(char *white_spaces, int count);
int is_exist_move(int board[4][4]);
int readInput(int board[4][4],int back_board[4][4],char move);


int main()
{
    int board[4][4] = {0};
    int back_board[4][4] = {0};
    initializeBoard(board);
    printBoard(board, back_board);
    char move;
    while (1)
    {
        scanf(" %c", &move);
        getchar();
        if(readInput(board,back_board,move)==1) break;
    }
    return 0;
}
int readInput(int board[4][4],int back_board[4][4],char move)
{
    if (is_loose(board))
        {
            printf("You Lost \n");
            return 1 ; 
        }
        if (is_win(board))
        {
            printf("You finally win! Congrats!\n");
            return 1 ; 
        }

        
        int move_status = 0;
        if (move == 'Q' || move == 'q')
        {
            printf("You choose to quit the game\n");
            return 1 ; 
        }
        // first move then add random to the board then print the board
        else if (move == 'B' || move == 'b')
        {
            back_move(board, back_board);
            printBoard(board, back_board);
        }
        else if (move == 'L' || move == 'l')
        {
            move_status = moveLeft(board, back_board, 0);

            if (move_status == 1)
                addRandom(board);
            printBoard(board, back_board);
        }
        else if (move == 'R' || move == 'r')
        {
            move_status = moveRight(board, back_board, 0);
            if (move_status == 1)
                addRandom(board);
            printBoard(board, back_board);
        }
        else if (move == 'U' || move == 'u')
        {
            move_status = moveUp(board, back_board);
            if (move_status == 1)
                addRandom(board);
            printBoard(board, back_board);
        }
        else if (move == 'D' || move == 'd')
        {
            move_status = moveDown(board, back_board);
            if (move_status == 1)
                addRandom(board);
            printBoard(board, back_board);
        }
        else if (move == 'N' || move == 'n') new_start(board, back_board);
        else
        {
            printf("Invalid move\n");
            printBoard(board, back_board);
        }
}

int is_win(int board[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 2048)
                return 1;
        }
    }
    return 0;
}


int is_loose(int board[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
                return 0;
        }
    }
    if(is_exist_move(board)==0) return 0 ;
    return 1;
}

void create_string(char *white_spaces, int count)
{
    for (int i = 0; i < count; i++)
    {
        white_spaces[i] = ' ';
    }
    white_spaces[count] = '\0';
}

// for phase 1 project
int printBoard(int board[4][4], int back_board[4][4])
{
    printf("*****************************\n");
    printf("Your score is : %d\n", calculateScore(board));

    char white_spaces[5];

    printf("-----------------------------\n");

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
                printf("|    ");
            else
            {
                int count_digit = 1;
                if (board[i][j] == 0)
                    count_digit = 0;
                else
                    count_digit = log10(board[i][j]) + 1;
                create_string(white_spaces, 4 - count_digit);
                printf("|%s%d", white_spaces, board[i][j]);
            }
        }
        printf("|\n");
    }

    printf("------------------------------\n");
    printf("Move(L/R/U/D) or Quite(Q) New Start(N) Back(B)\n");
    printf("*****************************\n");

    return calculateScore(board);
}
// for phase 1 project
void initializeBoard(int board[4][4])
{

    srand(time(0));

    for (int i = 1; i <= 2; i++)
    {
        int rand_num = (rand() % 2 == 0) ? 2 : 4;
        int rand_index;

        do
        {
            rand_index = rand() % 16;
        } while (board[rand_index / 4][rand_index % 4] != 0);

        board[rand_index / 4][rand_index % 4] = rand_num;
        // (*filled_index)++;
    }
}
// for phase 1 project
void addRandom(int board[4][4])
{
    int empty_tiles[16];
    int empty_count = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
            {
                empty_tiles[empty_count++] = i * 4 + j;
            }
        }
    }

    if (empty_count == 0)
        return; // terminate the function

    int rand_index = rand() % empty_count;
    int position = empty_tiles[rand_index];
    int number = (rand() % 2 == 0) ? 2 : 4;

    board[position / 4][position % 4] = number;
}
// for phase 1 project
int calculateScore(int board[4][4])
{ // add all tiles
    int score = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            score += board[i][j];
        }
    }
    return score;
}
int compare_arrays(int board_1[4][4], int board_2[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board_1[i][j] != board_2[i][j])
                return 1;
        }
    }
    return 0; // if two arrays diffrent to each other it return 1 otherwise return 0
    // it is usefull when we want to know if the move is change nothing we do not add random number
}

int is_exist_move(int board[4][4])
{ // it checks can make shift left right up and down
    int tmp[4][4];
    memmory_copy((int *)tmp, (int *)board, 16);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == board[i][j + 1])
            {
                return 0;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j > 0; j--)
        {
            if (board[i][j] == board[i][j - 1])
            {
                return 0;
            }
        }
    }
    Transpose(tmp);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tmp[i][j] == tmp[i][j + 1])
            {
                return 0;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j > 0; j--)
        {
            if (tmp[i][j] == tmp[i][j - 1])
            {
                return 0;
            }
        }
    }
    return 1 ; 
}
int moveLeft(int board[4][4], int back_board[4][4], int signal) // for phase 1 project
{
    // if(signal==0) memcpy(back_board,board,sizeof(int)*16);
    int tmp[4][4];
    memmory_copy((int *)tmp,(int *)board,16);
    int g = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
            {
                g++;
            }
            else
            {
                if (g > 0)
                {
                    board[i][j - g] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
        g = 0;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == board[i][j + 1])
            {
                board[i][j] *= 2;
                board[i][j + 1] = 0;
            }
        }
    }

    g = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
            {
                g++;
            }
            else
            {
                if (g > 0)
                {
                    board[i][j - g] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
        g = 0;
    }
    if (signal == 0&&compare_arrays(board,tmp))
        memmory_copy((int *)back_board, (int *)tmp, 16);

    return compare_arrays(board, tmp);
}

int moveRight(int board[4][4], int back_board[4][4], int signal)
{
    // if (signal==0) memcpy(back_board,board,sizeof(int)*16);
    int tmp[4][4];
    memmory_copy((int *)tmp,(int *)board,16);
    int g = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j >= 0; j--)
        {
            if (board[i][j] == 0)
            {
                g++;
            }
            else
            {
                if (g > 0)
                {
                    board[i][j + g] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
        g = 0;
    } // move it to  right

    for (int i = 0; i < 4; i++)
    { // double the value
        for (int j = 3; j > 0; j--)
        {
            if (board[i][j] == board[i][j - 1])
            {
                board[i][j] *= 2;
                board[i][j - 1] = 0;
            }
        }
    }

    g = 0; // move it to right again
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j >= 0; j--)
        {
            if (board[i][j] == 0)
            {
                g++;
            }
            else
            {
                if (g > 0)
                {
                    board[i][j + g] = board[i][j];
                    board[i][j] = 0;
                }
            }
        }
        g = 0;
    }
    if (signal == 0&&compare_arrays(board,tmp))
        memmory_copy((int *)back_board, (int *)tmp, 16);

    return compare_arrays(board, tmp);
}

void Transpose(int board[4][4])
{ 
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            int temp = board[i][j];
            board[i][j] = board[j][i];
            board[j][i] = temp;
        }
    }
}

int moveDown(int board[4][4], int back_board[4][4])
{
    // memcpy(back_board,board,sizeof(int)*16);

    int tmp[4][4];
    memmory_copy((int *)tmp,(int *)board,16);
    Transpose(board);
    moveRight(board, back_board, 1);
    Transpose(board);
    if(compare_arrays(board,tmp)==1) memmory_copy((int *)back_board, (int *)tmp, 16); 
    return compare_arrays(board, tmp);
}

int moveUp(int board[4][4], int back_board[4][4])
{ // transpose this to make easy
    // memcpy(back_board,board,sizeof(int)*16);
    int tmp[4][4];
    memmory_copy((int *)tmp,(int *)board,16);
    Transpose(board);
    moveLeft(board, back_board, 1);
    Transpose(board);
    if(compare_arrays(board,tmp)==1) memmory_copy((int *)back_board, (int *)tmp, 16); 
    return compare_arrays(board, tmp);
}
void memmory_copy(int *mem1, int *mem2, int size)
{
    for (int i = 0; i < size; i++)
    {
        *(mem1 + i) = *(mem2 + i);
    }
}
void new_start(int board[4][4], int back_board[4][4]) // make board 0 and then initialize the board then we have new game
{
    memmory_copy((int *)back_board, (int *)board, 16);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = 0;
        }
    }
    initializeBoard(board);
    printBoard(board, back_board);
}
void back_move(int board[4][4], int back_board[4][4])
{
    // memcpy(board,back_board,sizeof(int)*16);
    memmory_copy((int *)board, (int *)back_board, 16); // coping the board at the first of any move function and when we hit B for back we copy the back board in to board
}
