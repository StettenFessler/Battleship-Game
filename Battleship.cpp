#include <iostream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

const int col = 10;
const int row = 10;
const int MAX = 10;

// Specification C1- OOP
class Ship  // class to hold ship arrays and functions to set ships in each battlemap
  {
    public: 
      char destroyer[2];
      char submarine[3];
      char cruiser[3];
      char battleship[4];
      char carrier[5];
      void randShip(char map[row][col], char ship[], int size);
      void shipSize();
  };

int win, PCwin;
char grid[row][col];
char pcgrid[row][col];

void gridSet(char set[row][col]);
void displayPlayer(char disp[row][col]);
void getInput();
void hitSetter(char graph[row][col], int x, int y);
void pchitSetter(char graph[row][col], int x, int y); 
void sinkCheck(char check[row][col], int x, int y);
void pcsinkCheck(char check[row][col], int x, int y);
void victory();
void PCvictory();
void mysteryKey();
void menu();
void randomAI();
void displaypcfrompc();

void victory()
{
  cout << "Congrats! You won!! Game over, exiting program..." << endl;
  exit(0);
}
void PCvictory()
{
  cout << "Better luck next time, the PC won! Exiting program" << endl;
  exit(0);
}
void gridSet(char set[row][col])
{
	for (int i = 0; i < row; i++)
	{	
		for (int x = 0; x < col; x++)
		{
			set[i][x] = '.';
		}
	}
}

// Displays the player's battlemap
void displayer(char disp[row][col])
{
  cout << "\n===============================" << endl;
  cout << "Your Battlemap: " << endl;
  cout << "===============================";
  cout << "   \n   A  B  C  D  E  F  G  H  I  J " << endl;

	for (int i = 0; i < row; i++)
	{ 
    cout << i << "| "; 
	  for (int x = 0; x < col; x++)
		{
      cout << disp[i][x] << "  ";
		}
		cout << endl;
	}
 
}
// Specification B3- Random Start
void randShip(char map[row][col], char ship[], int size)
{
  
  int hSet, vSet, hORv;

  Reset:
    do
    {
      hSet = rand()%MAX; //rand # 0-9
      vSet = rand()%MAX;
      hORv = rand()%2;  // rand # 0-1
    }
    while(map[hSet][vSet] == '$');

    // sets ship randomly in horizontal orientation
    if (hORv == 0) 
    {
      while (vSet + size >= MAX) // gets new random # if out of battlemap range
      {
        vSet = rand()%col;
      }
      for (int x = vSet; x < vSet + size; x++)
      {
        // if a ship is already at the selected coordinates, reset and get new coordinates to place ship
        if (map[hSet][x] == '$')      
          goto Reset;
        if (map[hSet - 1][x] == '$')
          goto Reset;
        if (map[hSet + 1][x] == '$')
          goto Reset;
        if (map[hSet][x -1] == '$')
          goto Reset;
        if (map[hSet][x + 1] == '$')
          goto Reset;
      }
      for (int z = vSet; z < vSet + size; z++)
      {
        for (int c = 0; c < size; c++)
        {
        map[hSet][z] = ship[c];
        }
      }
    }

    // sets ship randomly in vertical orientation
    if (hORv == 1)       
    {
      while (hSet + size >= MAX)
      {
        hSet = rand()%row;
      }
      for (int x = hSet; x < hSet + size; x++)
      {
        // if a ship is already at the selected coordinates, reset and get new coordinates to place ship
        if (map[x][vSet] == '$')
          goto Reset;
        if (map[x-1][vSet] == '$')
          goto Reset;
        if (map[x+1][vSet] == '$')
          goto Reset;
        if (map[x][vSet-1] == '$')
          goto Reset;
        if (map[x][vSet + 1] == '$')
          goto Reset;
      }
      for (int z = hSet; z < hSet + size; z++)
      {
        for (int n = 0; n < size; n++)
        {
        map[z][vSet] = ship[n];
        }
      }
    }
}

// Displays the PC battlemap
void displaypc()
{
  cout << "\n===============================" << endl;
  cout << "PC Battlemap: " << endl;
  cout << "===============================";
  cout << "   \n   A  B  C  D  E  F  G  H  I  J " << endl;

	for (int i = 0; i < row; i++)
	{ 
    cout << i << "| "; 
	  for (int x = 0; x < col; x++)
		{
      if (pcgrid[i][x] != '$')
      {
        cout << pcgrid[i][x] << "  ";
      }
      else 
      {
        cout << ".  ";
      }
			
		}
		cout << endl;
	}  
  randomAI();
}

void getInput()
{ 
  char colGet;
  int colIn;
  int rowIn;
Retry:
  cout << "\nEnter column letter (A,B,C,D,E,F,G,H,I,J)" << endl;
  
    cin >> colGet;
    // Converts alphabetical input to numerical
    if (colGet == 'A' || colGet == 'a')
      colIn = 0;
    else if (colGet == 'B' || colGet == 'b')
      colIn = 1;
    else if (colGet == 'C' || colGet == 'c')
      colIn = 2;
    else if (colGet == 'D' || colGet == 'd')
      colIn = 3;
    else if (colGet == 'E' || colGet == 'e')
      colIn = 4;
    else if (colGet == 'F' || colGet == 'f')
      colIn = 5;
    else if (colGet == 'G' || colGet == 'g')
      colIn = 6;
    else if (colGet == 'H' || colGet == 'h')
      colIn = 7;
    else if (colGet == 'I' || colGet == 'i')
      colIn = 8;
    else if (colGet == 'J' || colGet == 'j')
      colIn = 9;
    else if (colGet == '?')
      mysteryKey();
// Specification B1- Validate Input
    else 
    {
    cout << "Invalid input" << endl;
    goto Retry;
    }
Redo:
    cout << "Enter row number" << endl;
    cin >> rowIn; 

    if (rowIn != 0 && rowIn != 1 && rowIn != 2 &&rowIn != 3 && rowIn != 4 && rowIn != 5 && rowIn != 6 && rowIn != 7 && rowIn != 8 && rowIn != 9)
    {
      cout << "Invalid input" << endl;
      goto Redo;
    }
    // If a point has already been fired upon, player must try again
    if (pcgrid[rowIn][colIn] == 'o' || pcgrid[rowIn][colIn] == '!' || pcgrid[rowIn][colIn] == '%')
    {
      cout << "----------------------------------------" << endl;
      cout << "Error: You already fired upon that point" << endl;
      cout << "----------------------------------------" << endl;
      goto Retry;
    }

  hitSetter(pcgrid, rowIn, colIn);
}

// Entering "?" as the column input allows the player to see where the PC's ships are! 
void mysteryKey()
{
  cout << "\nSecret key pressed!\n " << endl;
  cout << "===============================================" << endl;
  cout << "Your battlemap from the computer's perspective: " << endl;
  cout << "===============================================" << endl;
  cout << "   \n   A  B  C  D  E  F  G  H  I  J " << endl;
  for (int i = 0; i < row; i++)
	{ 
    cout << i << "| "; 
	  for (int x = 0; x < col; x++)
		{
      if (grid[i][x] != '$')
      {
        cout << grid[i][x] << "  ";
      }
      else 
      {
        cout << ".  ";
      }
    }
		cout << endl;
    
	}  
  cout << "====================================================" << endl;
  cout << "\nThe computer's battlemap from it's own perspective: " << endl;
  cout << "====================================================" << endl;
  cout << "   \n   A  B  C  D  E  F  G  H  I  J " << endl;
  for (int i = 0; i < row; i++)
	{ 
    cout << i << "| "; 
	  for (int x = 0; x < col; x++)
		{
      cout << pcgrid[i][x] << "  ";
		}
		cout << endl;
	}
  getInput();
}
// The PC randomly chooses points to fire at
void randomAI()
{
  cout << "\nThe PC is going now..." << endl;
Set:
  int x = rand()%MAX;
  int y = rand()%MAX;
// If the PC has already fired upon a point, retry with different points
  if (grid[x][y] == '!' && grid [x][y] == 'o' && grid[x][y] == '%')
    goto Set;
  
  cout << "The coordinates the PC guessed are: " << y + 1 << " and " << x << endl;
  
  pchitSetter(grid, x, y);
}
void menu()
{
  int decision;
Wrong:
  cout << "\n====================================================" << endl;
  cout << "KEY:" << endl;
  cout << " '.' = unhit point" << endl;
  cout << " '!' = hit point" << endl;
  cout << " '!' changed to '%' = entire ship sunk" << endl;
  cout << " 'o' = missed point" << endl;
  cout << "Enter '?' as your column input to cheat and see where the PC's ships are!" <<endl;
  cout << "\nWhat do you want to do next?" << endl;
  cout << "1. Input coordinates to fire at" << endl;
  cout << "2. Exit program" << endl;
  cout << "=======================================================" << endl;
    cin >> decision;
  if (decision == 1)
    getInput();
  else if (decision == 2)
  {
	cout << "exiting program" << endl;
    exit(0);
  }
  else 
  {
    cout << "Incorrect input, enter 1 or 2" << endl;
    goto Wrong;
  }
}

// Checks if input coordinates are a hit
void hitSetter(char graph[row][col], int x, int y)
{
  if (graph[x][y] == '$')
  {
    cout << "\n*************" << endl;
    cout << "That's a hit!" << endl;
    cout << "*************" << endl;
    graph[x][y] = '!';
    sinkCheck(graph, x, y);
    displayer(grid);
    displaypc();
  }
  else if (graph[x][y] == '.')
  {
    cout << "\n**************" << endl;
    cout << "That's a miss!" << endl;
    cout << "**************" << endl;
    graph[x][y] = 'o';
    displayer(grid);
    displaypc();
    randomAI();
  }
}

// Each ship has a predetermined size
void Ship::shipSize()
{
  
  for (int i = 0; i < 2; i++)
  {
    destroyer[i] = '$';
  }

  for (int i = 0; i < 3; i++)
  {
    submarine[i] = '$';
    cruiser[i] = '$';
  }

  for (int i = 0; i < 4; i++)
  {
    battleship[i] = '$';
  }

  for (int i = 0; i < 5; i++)
  {
    carrier[i] = '$';
  }
}

// Checks if a ship has been sunk
void sinkCheck(char check[row][col], int x, int y)
{ 
  bool sinker = false;

  // Checks every point around the ship for '$'
  if (check[x-1][y] == '$') 
          sinker = false;
  else if (check[x+1][y] == '$')
          sinker = false;
  else if (check[x][y-1] == '$')
          sinker = false;
  else if (check[x][y + 1] == '$')
          sinker = false; 
  else
  // Ff there aren't any $'s, then the ship is sunk
  sinker = true;          
  
  // If a ship has been sunk, check if 5 ships have been sunk
  if (sinker)
  {
    
    check[x][y] = '%';
    cout << "You sunk that ship!" << endl;
    win++;
    // If 5 ships have been sunk, then the game is over
    if(win == 5)
    {
    victory();
    }
    displayer(grid);
    displaypc();
    randomAI();
     
  }
  
  // If the point has not been changed to a '%', then the ship is not sunk yet
  else 
  {
    cout << "The ship isn't sunk yet!" << endl;
    displayer(grid);
    displaypc();
    randomAI();
  }
}
 
// Checks if player has a ship at PC's selected points
void pchitSetter(char graph[row][col], int x, int y)
{
  if (graph[x][y] == '$')
  {
    cout << "\n*******************" << endl;
    cout << "The PC hit your ship!" << endl;
    cout << "*********************" << endl;
    graph[x][y] = '!';
    sinkCheck(graph, x, y);
    displayer(grid);
    displaypcfrompc();
  }
  else if (graph[x][y] == '.')
  {
    cout << "\n**************" << endl;
    cout << "The PC missed!" << endl;
    cout << "**************" << endl;
    graph[x][y] = 'o';
    displayer(grid);
    displaypcfrompc();
    menu();
  }
}

void pcsinkCheck(char check[row][col], int x, int y)
{ 
  bool sinker = false;
  
  
  if (check[x-1][y] == '$') // checks every point around the ship for '$'
          sinker = false;
  else if (check[x+1][y] == '$')
          sinker = false;
  else if (check[x][y-1] == '$')
          sinker = false;
  else if (check[x][y + 1] == '$')
          sinker = false; 
  else
  sinker = true;          // if there aren't any $'s, then the ship is sunk

  if (sinker)
  {
    check[x][y] = '%';
    cout << "The PC sunk that ship!" << endl;
    PCwin++;
    if(PCwin == 5)
    {
    PCvictory();
    }
    displayer(grid);
    displaypcfrompc();
    menu();
     
  }
  else 
  {
    cout << "The ship the pc hit isn't sunk yet!" << endl;
    displayer(grid);
    displaypcfrompc();
    menu();
  }
}

// Display's where the PC's ships are
void displaypcfrompc()
{
  cout << "\n===============================" << endl;
  cout << "PC Battlemap: " << endl;
  cout << "===============================";
  cout << "   \n   A  B  C  D  E  F  G  H  I  J " << endl;

	for (int i = 0; i < row; i++)
	{ 
    cout << i << "| "; 
	  for (int x = 0; x < col; x++)
		{
      if (pcgrid[i][x] != '$')
      {
        cout << pcgrid[i][x] << "  ";
      }
      else 
      {
        cout << ".  ";
      }
			
		}
		cout << endl;
	}  
  menu();
}

 int main()
{
  Ship start;
  srand(time(NULL));
  
  cout << "\nWelcome to Battleship! Your ships are currently being set..." << endl;
  cout << "Press any key to continue." << endl;
  
  cin.ignore();

  // player battlemap set
  gridSet(grid);
  start.shipSize();
  randShip(grid, start.destroyer, 2);   // sets destroyer on player grid
  randShip(grid, start.submarine, 3);
  randShip(grid, start.cruiser, 3);     
  randShip(grid, start.battleship, 4);  
  randShip(grid, start.carrier, 5);     
  displayer(grid);
  
  // ai battlemap set
  gridSet(pcgrid);
  randShip(pcgrid, start.destroyer, 2);   // sets destroyer on pc grid
  randShip(pcgrid, start.submarine,3);    
  randShip(pcgrid, start.cruiser, 3);     
  randShip(pcgrid, start.battleship,4);   
  randShip(pcgrid, start.carrier,5);
  displaypcfrompc();      
  menu();
}	
