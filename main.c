#include <stdio.h>
#include <stdlib.h>
#include <time.h>
///TIP:
///Have a look at this site for tips on maze algorithms http://www.astrolog.org/labyrnth/algrithm.htm
//typedefs
typedef enum boolean {fals,tru}; //Bool data type fals=0, tru=1
//SETTINGS
char printWhileSolving =        fals;   //Lets you see what the recBacktracker does
char compactPrinting =          fals;   //Prints the maze more compact (for huge mazes)
char cleanMazeAfterSolving =    fals;   //Cleans the maze from the '.' the recBacktracker leaves behind
char waitBeforeSolving =        fals;   //Waits after maze is generated so you can try to solve it first
char solutionPathCharacter =    '+' ;   //Not allowed are '.' , '#' , ' ', 'F'
char maze                   [7][4];   //Size of Maze to be generated can be scaled however you like: example [62][111]
                ///Minimum is [3][4] or [4][3] otherwise the generation fails
//Rnd Methods
void initRnd()//initializes Random
{
    srand((unsigned)time(NULL));
}
int Rnd(int min,int max)//Gives a random number between min - max
{
    return ((rand() % (max-min+1 )) + min);
}
//Print Method
void print()//prints the maze
{
    if(printWhileSolving==tru)
        system("cls");
    for(int z=0; z<sizeof(maze)/sizeof(maze[0]); z++)
    {
        for(int i=0; i< sizeof(maze[0])/sizeof(maze[0][0]); i++)
        {
            if(compactPrinting==fals)
                printf(" %c",maze[z][i]);
            else
                printf("%c",maze[z][i]);
        }
        printf("\n");
    }
}
//Solving Methods
int solve(char y, char x)//solves the maze with recursive backtracking
{
    if(printWhileSolving==tru)
        print();
    if(maze[y][x]=='#'||maze[y][x]=='.')    //If hit wall or prev visited spot
    {
        return fals;
    }
    else if(maze[y][x]=='F')                //If hit Finish
    {
        return tru;
    }
    maze[y][x]='.';                         //Mark as visited
    if(solve(y+1,x)==tru)                   //If down
    {
        maze[y][x]=solutionPathCharacter;
        return tru;
    }
    else if(solve(y-1,x)==tru)              //If Up
    {
        maze[y][x]=solutionPathCharacter;
        return tru;
    }
    else if(solve(y,x+1)==tru)              //If Right
    {
        maze[y][x]=solutionPathCharacter;
        return tru;
    }
    else if(solve(y,x-1)==tru)              //If Left
    {
        maze[y][x]=solutionPathCharacter;
        return tru;
    }
    else
        return fals;


}
void cleanup()//cleans the maze from the '.' after solving
{
    for(int z=0; z<sizeof(maze)/sizeof(maze[0]); z++)
    {
        for(int i=0; i< sizeof(maze[0])/sizeof(maze[0][0]); i++)
        {
            if(maze[z][i]=='.')
            {
                maze[z][i]=' ';
            }
        }
    }
    print();
}
//Maze Creation Methods
void buildWall(int y, int x,int orientation)//build a Wall at y,x in given direction with random Lenth
{
    int adjC;
    int WallLength = Rnd(1,sizeof(maze)/sizeof(maze[0]))/2;
    switch(orientation)
    {
    case 0:
        for(int z=1; z<WallLength; z++)
        {
            adjC=0;
            if(maze[y+1+z][x]=='#')
                adjC++;
            if(maze[y+1+z][x+1]=='#')
                adjC++;
            if(maze[y+1+z][x-1]=='#')
                adjC++;
            if(maze[y-1+z][x]=='#')
                adjC++;
            if(maze[y-1+z][x+1]=='#')
                adjC++;
            if(maze[y-1+z][x-1]=='#')
                adjC++;
            if(maze[y+z][x+1]=='#')
                adjC++;
            if(maze[y+z][x-1]=='#')
                adjC++;
            if(adjC==1)
            {
                maze[y+z][x]='#';
            }
        }
        break;
    case 1:
        for(int z=1; z<WallLength; z++)
        {
            adjC=0;
            if(maze[y+1-z][x]=='#')
                adjC++;
            if(maze[y+1-z][x+1]=='#')
                adjC++;
            if(maze[y+1-z][x-1]=='#')
                adjC++;
            if(maze[y-1-z][x]=='#')
                adjC++;
            if(maze[y-1-z][x+1]=='#')
                adjC++;
            if(maze[y-1-z][x-1]=='#')
                adjC++;
            if(maze[y-z][x+1]=='#')
                adjC++;
            if(maze[y-z][x-1]=='#')
                adjC++;
            if(adjC==1)
            {
                maze[y-z][x]='#';
            }
        }
        break;
    case 2:
        for(int z=1; z<WallLength; z++)
        {
            adjC=0;
            if(maze[y+1][x+z]=='#')
                adjC++;
            if(maze[y+1][x+z+1]=='#')
                adjC++;
            if(maze[y+1][x+z-1]=='#')
                adjC++;
            if(maze[y-1][x+z]=='#')
                adjC++;
            if(maze[y-1][x+z+1]=='#')
                adjC++;
            if(maze[y-1][x+z-1]=='#')
                adjC++;
            if(maze[y][x+1+z]=='#')
                adjC++;
            if(maze[y][x-1+z]=='#')
                adjC++;
            if(adjC==1)
            {
                maze[y][x+z]='#';
            }
        }
        break;
    case 3:
        for(int z=1; z<WallLength; z++)
        {
            adjC=0;
            if(maze[y+1][x-z]=='#')
                adjC++;
            if(maze[y+1][x-z+1]=='#')
                adjC++;
            if(maze[y+1][x-z-1]=='#')
                adjC++;
            if(maze[y-1][x-z]=='#')
                adjC++;
            if(maze[y-1][x-z+1]=='#')
                adjC++;
            if(maze[y-1][x-z-1]=='#')
                adjC++;
            if(maze[y][x+1-z]=='#')
                adjC++;
            if(maze[y][x-1-z]=='#')
                adjC++;
            if(adjC==1)
            {
                maze[y][x-z]='#';
            }
        }
        break;
    }
}
void addWall()//adds ONE Wall if it fails it retries 50 times at different positions
{
    for(int y=0; y<50; y++)
    {
        for(int z=Rnd(1,sizeof(maze)/sizeof(maze[0])); z<sizeof(maze)/sizeof(maze[0])-1; z++)
        {
            for(int i=Rnd(1,sizeof(maze[0])/sizeof(maze[0][0])); i<sizeof(maze[0])/sizeof(maze[0][0])-1; i++)
            {
                int adjC;
                if(maze[z][i]==' ')
                {
                    adjC=0;
                    if(maze[z+1][i]=='#')
                        adjC++;
                    if(maze[z+1][i+1]=='#')
                        adjC++;
                    if(maze[z+1][i-1]=='#')
                        adjC++;
                    if(maze[z-1][i]=='#')
                        adjC++;
                    if(maze[z-1][i+1]=='#')
                        adjC++;
                    if(maze[z-1][i-1]=='#')
                        adjC++;
                    if(maze[z][i+1]=='#')
                        adjC++;
                    if(maze[z][i-1]=='#')
                        adjC++;
                    if(adjC==1&&(maze[z+1][i+1]==' '&&maze[z+1][i-1]==' '&&maze[z-1][i+1]==' '&&maze[z-1][i-1]==' '))
                    {
                        maze[z][i]='#';
                        buildWall(z,i,Rnd(0,3));
                        return;
                    }
                    else if(adjC==2&&(maze[z+1][i]=='#'||maze[z-1][i]=='#'||maze[z][i+1]=='#'||maze[z][i-1]=='#')&&(maze[z+1][i+1]=='#'||maze[z+1][i-1]=='#'||maze[z-1][i+1]=='#'||maze[z-1][i-1]=='#'))
                    {
                        maze[z][i]='#';
                        buildWall(z,i,Rnd(0,3));
                        return;
                    }
                    else if(adjC==3&&(z==1||z==sizeof(maze)/sizeof(maze[0])-2||i==1||i==sizeof(maze[0])/sizeof(maze[0][0])-2))
                    {
                        maze[z][i]='#';
                        buildWall(z,i,Rnd(0,3));
                        return;
                    }
                }
            }
        }
    }
}
void addFrame()//adds the '#' to the maze
{
    for(int z=0; z<sizeof(maze)/sizeof(maze[0]); z++)
    {
        for(int i=0; i< sizeof(maze[0])/sizeof(maze[0][0]); i++)
        {
            if(z==0||i==0||z==sizeof(maze)/sizeof(maze[0])-1||i==sizeof(maze[0])/sizeof(maze[0][0])-1)
            {
                maze[z][i]='#';
            }
        }
    }
}
void placeF()//randomly places the finish on an empty space not [1][1]
{
    while(1==1)
    {
        for(int z=0; z<sizeof(maze)/sizeof(maze[0]); z++)
        {
            for(int i=0; i< sizeof(maze[0])/sizeof(maze[0][0]); i++)
            {
                if(maze[z][i]==' '&&(z!=1||i!=1)&&Rnd(0,sizeof(maze)/sizeof(maze[0])*sizeof(maze[0])/sizeof(maze[0][0])*10)==0)
                {
                    maze[z][i]='F';
                    return;
                }
            }
        }
    }

}
void cleanDiag()//Is usually obsoletebut there is a bug somewhere ^^ this take care of that issue and removes diagonal blocks
{
    for(int z=1; z<sizeof(maze)/sizeof(maze[0])-1; z++)
    {
        for(int i=1; i< sizeof(maze[0])/sizeof(maze[0][0])-1; i++)
        {
            if(maze[z+1][i+1]=='#'&&maze[z+1][i]==' '&&maze[z][i+1]==' ')
            {
                maze[z][i]=' ';
            }
            else if(maze[z+1][i-1]=='#'&&maze[z+1][i]==' '&&maze[z][i-1]==' ')
            {
                maze[z][i]=' ';
            }
            else if(maze[z-1][i+1]=='#'&&maze[z-1][i]==' '&&maze[z][i+1]==' ')
            {
                maze[z][i]=' ';
            }
            else if(maze[z-1][i-1]=='#'&&maze[z-1][i]==' '&&maze[z][i-1]==' ')
            {
                maze[z][i]=' ';
            }
        }
    }
}
void initMaze()//initializes the maze
{
    for(int z=0; z<sizeof(maze)/sizeof(maze[0]); z++)
    {
        for(int i=0; i< sizeof(maze[0])/sizeof(maze[0][0]); i++)
        {
            maze[z][i]=' ';
        }
    }
}
unsigned int PercentFull()//Return % of the maze drawspace that is filled with walls use to prevent BS EZ PZ mazes
{
    unsigned int count=0;
    for(int z=1; z<sizeof(maze)/sizeof(maze[0])-1; z++)
    {
        for(int i=1; i< sizeof(maze[0])/sizeof(maze[0][0])-1; i++)
        {
            if(maze[z][i]=='#')
                count++;
        }
    }
    return 100*(double)count/((sizeof(maze)/sizeof(maze[0])-1)*(sizeof(maze[0])/sizeof(maze[0][0])-1));
}
void genMaze()//generates a maze
{
    printf("Please by patient while your maze is beeing generated.");
    initRnd();
    initMaze();
    addFrame();
    int tries=0;
    do{
    int wallCount = Rnd(sizeof(maze)/sizeof(maze[0])+sizeof(maze[0])/sizeof(maze[0][0]),sizeof(maze)/sizeof(maze[0])*sizeof(maze[0])/sizeof(maze[0][0]));
    for(int z=0; z<wallCount; z++)
    {
        addWall();
    }
    cleanDiag();
    tries++;
    }while(PercentFull()<42&&tries<5);
    placeF();
    system("cls");
}
//MAIN
int main()//controls the program
{
    genMaze();
    if(waitBeforeSolving==tru)//Wait with solving so User can try to find solution first
        {print();char c;printf("Input a char to solve: ");scanf("%c",&c);system("cls");}
    if(solve(1,1)==fals)
        printf("Maze cannot be solved!\n");
    if(cleanMazeAfterSolving==tru)
        cleanup();
    else if(printWhileSolving==fals)
        print();
    return PercentFull();
}
