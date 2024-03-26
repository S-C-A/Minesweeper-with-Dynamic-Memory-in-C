// -10: 0, -9: bomb -1 to -8: unrevealed mark
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void minesweeper(int **, char **);
void print_screen(char **, int **);
void check_bomb(int, int, int**, char **);
int* reveal(int **, char **);
void auto_reveal(int **, char **, int, int);
void flag(int **, char **);
int game_status(int **, char **);

int main(){

    srand(time(NULL));
    int bomb, row = 0, column = 0;
    printf("How many bombs do you want to add: ");
    scanf("%d", &bomb);
    int **background;
    background = (int **)calloc(10,(sizeof(int *)));
    for (int i = 0; i < 10; i++)
    {
        background[i] = (int *)calloc(10,(sizeof(int)));
    }

    char **screen;
    screen = (char **)calloc(10,(sizeof(char *)));
    for (int i = 0; i < 10; i++)
    {
        screen[i] = (char *)calloc(10,(sizeof(char)));
    }

    for (int i = 0; i < 10; i++) 
    {
        for (int t = 0; t < 10; t++)
        {
            screen[i][t] = '0';
        }
    }        
    

    while (bomb > 0)
    {
        row = rand() % 10;
        column = rand() % 10;
        if (background[row][column] == 0)
        {
            background[row][column] = -9;
            screen[row][column] = 'B';
            bomb--;
        }        
    }

    for (int i = 0; i < 10; i++) 
    {
        for (int t = 0; t < 10; t++)
        {
            if (background[i][t] != -9)
            {
                check_bomb(i,t,background,screen);
            }
            
        }
    }        
    

    minesweeper(background,screen);

}

void minesweeper(int **background, char **screen){

    int *location = (int*)malloc(2*(sizeof(int)));
    int choice;

    print_screen(screen, background);
    printf("1 for REVEALING A SPOT\n2 for A FLAG\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        location = reveal(background, screen);
        if(background[location[0]-1][location[1]-1] == 0){
            auto_reveal(background, screen, location[0], location[1]);
        }
    }    
    else if (choice == 2)
    {
        flag(background, screen);
    }
    if (game_status(background, screen) == 1)
    {
        return;
    }
    
    free(location);
    minesweeper(background,screen); 
}

void print_screen(char **screen, int **background){

    printf("                   ");  
    for (int i = 0; i < 10; i++)
    {      
        printf("   %d    ", i+1);
    }
    printf("\n");   
    printf("\n");

    for (int i = 0; i < 10; i++) 
    {
        if (i != 9)
        {
            printf("                %d |", i+1);
        }
        else
        {
            printf("               %d |", i+1);
        }
        
        for (int t = 0; t < 10; t++)
        {
        printf("   %c   |",(background[i][t] > -1 || background[i][t] < -10)  ? screen[i][t]: '?');
        }
        printf("\n");
        printf("                   -------------------------------------------------------------------------------");
        printf("\n");
    }


}

void check_bomb(int row, int column, int **background, char **screen){


    for (int i = row-1; i < row+2; i++) 
    {
        for (int t = column-1; t < column+2; t++)
        {
            if (i<0 || i>9 || t<0 || t>9 || (column == t && row == i))
            {
                continue;
            }
            else if (background[i][t] == -9)
            {
                background[row][column]--;
            }
        }
    }        
        
    if (background[row][column] != 0)
    {
        screen[row][column] = '0' - background[row][column];
    }
    else if (background[row][column] == 0)
    {
        background[row][column] = -10;
    }
}

int* reveal(int **background, char **screen){

    int *location = (int*)malloc(2*(sizeof(int)));
    printf("Enter your move: ");
    scanf("%d %d", &location[0], &location[1]);

    if (background[location[0]-1][location[1]-1] == -10)
    {
        background[location[0]-1][location[1]-1] = 0;
    }   
    else if (background[location[0]-1][location[1]-1] < 0)
    {
        background[location[0]-1][location[1]-1] += -2*(background[location[0]-1][location[1]-1]) ;

    }

    return location;
    
}

void auto_reveal(int **background, char **screen, int row, int column){

    for (int i = row-1; i < row+2; i++) 
    {
        for (int t = column-1; t < column+2; t++)
        {
            if (i<0 || i>9 || t<0 || t>9 || (column == t && row == i))
            {
                continue;
            }
            else if (background[i][t] == -10)
            {
                background[i][t] = 0;
                auto_reveal(background, screen, i, t);
            }
        }
    }        


}

void flag(int **background, char **screen){

    int row, column;
    printf("Enter your move: ");
    scanf("%d %d", &row, &column);

    if(background[row-1][column-1] < 0){
        if (background[row-1][column-1] > -11)
        {
            screen[row-1][column-1] = 'F';
            background[row-1][column-1] -= 10;
        }
        else if (background[row-1][column-1] < -10)
        {
            background[row-1][column-1] += 10;
            if (background[row-1][column-1] == -10)
            {
                screen[row-1][column-1] = '0';
            }
            else if(background[row-1][column-1] != -9){
                screen[row-1][column-1] = '0' - background[row-1][column-1];
            }
            else if (background[row-1][column-1] == -9)
            {
                screen[row-1][column-1] = 'B';
            }
            
        }    
    }

}

int game_status(int **background, char **screen){

    int end = 1;

    for (int i = 0; i < 10; i++) 
    {
        for (int t = 0; t < 10; t++)
        {
            if (background[i][t] == 9)
            {
                    for (int i = 0; i < 10; i++) 
                    {
                        for (int t = 0; t < 10; t++)
                        {
                            background[i][t] = 50; 
     
                        }
                    }       
                print_screen(screen, background);     
                printf("YOU'VE STRUCK A BOMB");
                return 1;
            }
            if (background[i][t] == -9 || (screen[i][t] == 'F' && background[i][t] != -19))
            {
                end = 0;
            }            
        }
    }
    if (end == 1)
    {
        for (int i = 0; i < 10; i++) 
        {
            for (int t = 0; t < 10; t++)
            {
                background[i][t] = 50; 
     
            }
        }     
        print_screen(screen, background);
        printf("YOU'VE FLAGGED ALL THE BOMBS!");
        return 1;
    }
            
}