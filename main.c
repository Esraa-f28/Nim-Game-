#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

struct node         // create node
{
    char data;
    int stones_in_row;      //number of stones in each row
    struct node* next;
};
typedef struct node node;

int num_rows,row,stones,choice;
int begin=0;
int i,j;                //counters
int player = 0;
char y;
node** head; // pointer to array of pointers
node* top;
/* function to create game which contains number of rows (choose by users ) with number of stones in each row depend on the row's number */
void create_game(int num_rows)
{
    for(i=0; i< num_rows ; i++)
    {
        node* newnode = (node*)malloc(sizeof(node));
        head[i] = newnode;
        newnode -> stones_in_row = (i*2 + 1); // number of stones in row
        top = newnode;
        newnode -> data = '#';
        newnode -> next = NULL;
        for(j=0; j< i*2 ; j++)
        {
            node* newnode = (node*)malloc(sizeof(node));
            newnode -> data = '#';
            newnode -> next = NULL;
            top -> next = newnode;
            top = newnode;
        }
    }
}
/*Displays the game state with the available number of stones in each row */
void display()
{

   for(i = 0;i < num_rows;i++) {
        printf("\t  Row %d : stones %d ---> \t", i + 1, head[i]->stones_in_row);
        for(j = 1;j < num_rows - i;j++) {
            printf("   ");
        }
        for(j = 0;j < head[i]->stones_in_row ;j++) {
            printf("%c  ", head[i]->data);
        }
        printf("\n");
    }
        printf("\n*************************************************************************************************\n\n");

}
//  function to delete stone from a given row
void pop(int row)
{
    top = head[row];
    head[row] -> next-> stones_in_row = (head[row] -> stones_in_row) -1;
    head[row] = head[row]->next;
    free(top);
    top = NULL;
}
void play( int row , int stones )
{
    if (stones == head[row]-> stones_in_row)
    {
        head[row]-> stones_in_row = 0;
        head[row]-> next = NULL;
        head[row]-> data = NULL;
    }
    else
    {
    for( i=0; i<stones; i++)
    {
        pop(row);
    }
    }
}
/* function to check if the game end (there is stones or not) */
bool check_win()
{

    for(i=0;i< num_rows;i++)
    {
        if (head[i]-> stones_in_row > 0 )
            return false ;

    }
        return true ;
}
/*
    * To enable 2 player mode for Nim Game
    * Each player enters a row number and the number of stones to be removed
    * A player has to enter valid number or rows/stones  to play or -1 to exit the game
    * Else the flow keeps on looping at the same position asking the user for a valid input
    * When a player quits the game or when there are no further moves, winner is declared
*/
void playwithfriend()
{
    // choose the player who it's turn
    while(!check_win()){
     if ( player ==0 )
            {
            printf("player %d\n", player+1);
            player++;
            }
        else
            {
            printf("player %d\n", player+1);
            player--;
            }
    //  player = (player == 1)? 2 : 1;
        printf("choose the row: "); // choose the row want to remove from
        scanf("%d",&row);
          if(row == -1) // if one of player want to quit
        {
            break;
        }
        printf("choose the stones: "); // choose number of stones want to remove from chosen row
        scanf("%d",&stones);
          if(stones == -1) // if one of player want to quit
        {
            break;
        }
        while( (row > num_rows) || (stones >  head[row -1] -> stones_in_row) ) // check valid input and if not valid take another valid input
        {
            printf("wrong input\n");
            printf("choose the row: ");
            scanf("%d",&row);
              if(row == -1)
            {
            break;
            }
            printf("choose the stones: ");
            scanf("%d",&stones);
              if(stones == -1)
            {
            break;
            }
        }
            play(row-1,stones); // remove stones from chosen row
            display();


    }

                printf("player %d lost!!!\n ",(!player--)+1); // the player who remove the last stone is the loser
}
/*
    * function to implement the logic of computer Play
    * This logic makes computer  move intelligently and gives the most chances to win the game
*/

void pc_play(int* row ,int* stones)
{
    int zeroes = 0;
    int oneRows = 0;
    int targetRow = 0;
    int maxCount = 0;
    int temp;
    int index = 0;

    for(i = 0;i < num_rows; i++) {

        int temp = head[i]-> stones_in_row;

        if(head[i]->stones_in_row == 0) {        // FINDS THE NO. OF ROWS CONTAINING ZERO OBJECTS
            zeroes++;
        }
        if(head[i]->stones_in_row > maxCount) {    // FINDS THE MAX AMONG THE ROWS
            maxCount = head[i]->stones_in_row;
            targetRow = i;
        }
        if(head[i]->stones_in_row == 1) {        //  FINDS THE NUMBER OF ROWS CONTAINING '1' OBJECT
            oneRows++;
        }
        }
        int bitcolumn=(log(2* num_rows-1)/ log(2))+1;
        //printf("bitcolumn = %d\n ",bitcolumn);
        int** bitArray = (int**)malloc(num_rows * sizeof(int*));
        for (i = 0; i < num_rows; i++)
            bitArray[i] = (int*)malloc(bitcolumn * sizeof(int));
        for (i = 0; i < num_rows; i++)
            for (j = 0; j < bitcolumn; j++)
                bitArray[i][j] = 0;
        int* powersCount = (int*)calloc(bitcolumn,sizeof(int));
        /* THIS GETS THE COUNT OF POWERS OF 2 IN EACH NUM
         EG: 7 = 111 IN BASE2. SO IT HAS ONE 4, ONE 2 AND ONE 1
         EG: 5 = 101. IT HAS ONE 4 AND ONE 1*/

        for(i = 0;i < num_rows; i++) {
        temp = head[i]-> stones_in_row;
        int j =(log(2* num_rows-1)/ log(2));
// printf(" log2(stones) = %d\n",j);

        while(temp != 0)
        {
            if(temp >= pow(2,j))
            {
            bitArray[i][j] = 1;
            temp -= pow(2,j);
            powersCount[j]++;
           // printf("bitArray[%d][%d] = %d\t",i,j, bitArray[i][j]);
            }

            j--;
        }
       // printf("\n");
        }

    /*TO FIND WHICH POWER OF 2 HAS ODD COUNT STARTING FROM 4
     INDEX IS ALREADY ZERO, SO IF NONE OF 4 NOR 2 IS ODD IT TAKES INDEX 0
    THE BASE RULE IS THAT ONE OF POWERS OF 2  MUST BE ODD ACCORDING TO THE LOGIC*/
    int power = bitcolumn-1;
   while(power){
    //printf("powersCount[%d]= %d\n",power,powersCount[power]);
    if( powersCount[power] % 2) {

        index = power;
       // printf("index= %d\n",index);
        break;
    }
     power--;
   }
    i = -1;
    while(i == -1){
    for(i = num_rows - 1;i >= 0;i--) {
            //printf("bitArray22[%d][%d] = %d\n",i,index,bitArray[i][index]);
        if(bitArray[i][index] == 1) {
            targetRow = i;
            bitArray[i][index] = 0;
            powersCount[index]--;
            index--;
            break;
        }
    }
    if(i== -1)
    index++;
    }


    while(index >= 0) {
        if(powersCount[index] % 2) {
            bitArray[targetRow][index] = !bitArray[targetRow][index];
        }
        index--;
    }

    *stones = head[targetRow]->stones_in_row;
 //   printf(" stones1 : %d \n",*stones);
 //   printf(" array : %d\t%d\t%d\t \n",bitArray[i][0],bitArray[i][1],bitArray[i][2]);
    int stonesAfter = 0;
    while(bitcolumn > 0){
    stonesAfter += bitArray[i][bitcolumn-1] * pow(2,bitcolumn-1);
    bitcolumn--;
    }
   // printf(" stonesAfter : %d \n",stonesAfter);
    if(maxCount == 1 && stonesAfter != 1) {
        oneRows--;
    } else if(stonesAfter == 1) {
        oneRows++;
    }
    if(stonesAfter == 0) {
        zeroes++;
    }

    if((zeroes + oneRows) == num_rows && oneRows % 2 == 0 && maxCount != 1) {
        stonesAfter== 0 ? ++(stonesAfter) : --(stonesAfter);
    }

    // SENDING BACK THE TARGETROW AND NUMBER OF OBJECTS REMOVED
    //printf(" stonesAfter2 : %d \n",stonesAfter);
    *stones -= stonesAfter;
    //printf(" stones2 : %d \n",*stones);
    *row = targetRow;
    printf("computer's play ----->   row:%d \t stones : %d \n\n",(*row)+1,*stones);
}
/*
    * function to play with computer
    * This function is written such that computer plays intelligently
*/
void playwith_pc()
{
    printf("1 for PC to start \n0 for you to start \n");
    scanf("%d",&player);
    while(!check_win()){
    if (player  == 0)
        {
        printf("choose the row: ");
        scanf("%d",&row);
        if(row == -1) // if player want to quit
        {
            player =1;
            break;
        }
        printf("choose the stones: ");
        scanf("%d",&stones);
          if(stones == -1)
        {
            player=1;
            break;
        }
        while( (row > num_rows) || (stones >  head[row -1] -> stones_in_row) )
        {
            printf("wrong input\n");
            printf("choose the row: ");
            scanf("%d",&row);
            printf("choose the stones: ");
            scanf("%d",&stones);
        }
            play(row-1,stones);
            display();
            player = 1;
        }
        else
        {
            pc_play(&row,&stones);
            play(row,stones);
            display();
            player=0;
        }

}
    if(player==1)
    printf("player %d lost!!! \n ",player);
    else
    printf("computer lost!!! \n ");
    printf("\n");
}

void display_Home()
{
    printf("\n\n\n\t*Let's start !!!");
    printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t*    1. Play against a friend     *");
    printf("\n\t*    2. Play against computer      *");
    printf("\n\t*    3. Exit                      *");
    printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void display_instructions()
{
    printf("\n\t*NIM Game Instructions:\n");
    printf("\t*************************\n");

    printf("\n\t* You have number of rows and few stones in each row");
    printf("\n\t* You select a row with stones available");
    printf("\n\t* You choose how many stones you want to remove from that row");
    printf("\n\t* in one turn, you have to remove stones from only one row");
    printf("\n\t* you have to remove at least one stone in each of your turns");
    printf("\n\t* This continues till there are no objects in any row");
    printf("\n\t* The one who removes the last object loses and the other player wins!");
    printf("\n\t* Any moment you want to quit the game and go back, give -1 as input");
    printf("\n\t* The one who quit the game is declared as to lose the game and the other one - Winner!");
    printf("\n\t******************************************************************************************");

}



int main()
{
    clock_t t;
   t = clock();
    display_instructions();
    display_Home();
    printf("\n\tEnter your choice: ");
    scanf("%d",&choice);
    if (choice ==3)
        return 0;
    system("cls");
    printf("enter num of rows: ");
    scanf("%d",&num_rows);
    printf("\n");
    head=(node**)malloc(sizeof(node*)*num_rows);
    create_game(num_rows);
    display();

        switch(choice){
        case 1:
            playwithfriend();
            break;
        case 2:

            playwith_pc();
            break;
    }

   t = clock() - t;
   double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
   printf("The execution  time with the program= %f \n ", time_taken);
    return 0;
}
