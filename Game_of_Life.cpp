// GameOfLife.cpp
// by Ben Van de Brooke
// On 10/16/16
// Editor: X-Code
// Compiler: GCC
// Description: Simulation of the Game of Life using my own AssociativeArray

#include <iostream>
#include "VandeBrookeBenAssociativeArray.h"
#include "VandeBrookeBenAssociativeArray.h"
#include <string>
#include <sstream>

using namespace std;

struct orderedPair
{
  int X;
  int Y;
  
  bool operator == (orderedPair otherPair)
  {
    return (X == otherPair.X && Y == otherPair.Y);
  }

};


void InitializeGrid(AssociativeArray<orderedPair, char>& currentGen,string input)
{
  orderedPair aPair;
  vector<int> coordiates;
  
  //deletes the pair of -1 from the string
  for(int i = 0; i < 6; i++)
  {
    input.pop_back();
  }
  
  int x = 0;
  stringstream ss(input);
  
  while(ss >> x)
  {
    coordiates.push_back(x);
    if( ss.peek() == ' ')
    {
      ss.ignore();
    }
  }
  
  //sets the elements to * based on ordered pairs
  for( int i = 0; i < coordiates.size(); i++)
  {
    aPair.X = coordiates.at(i);
    aPair.Y = coordiates.at(++i);
    
    currentGen[aPair] = '*';
  }
}


void Print(const AssociativeArray<orderedPair, char>& currentGen)
{

  
  orderedPair pair;
  
  const int xMax = 10, xMin = -10, yMax = 10, yMin = -10;
  
  for(int y = yMax; y >= yMin; y--)
  {
    for(int x = xMin; x <= xMax; x++)
    {
      
      pair.X = x;
      pair.Y = y;
    
      if(currentGen.ContainsKey(pair))
      {
        cout << currentGen[pair];
      }
      else
      {
        cout << ".";
      }
    }
    cout << endl;
  }
}

int countAdj(AssociativeArray<orderedPair, char>& currentGen, orderedPair center)
{
  int adj = 0;

  orderedPair above, below, left ,right, upperLeft, upperRight, lowerLeft, lowerRight;
  vector<orderedPair> adjacentElements;
  
  above.Y = center.Y + 1;
  above.X = center.X;
  adjacentElements.push_back(above);
  
  below.Y = center.Y - 1;
  below.X = center.X;
  adjacentElements.push_back(below);
  
  right.Y = center.Y;
  right.X = center.X + 1;
  adjacentElements.push_back(right);
  
  left.Y = center.Y;
  left.X = center.X - 1;
  adjacentElements.push_back(left);
  
  
  upperLeft.Y = center.Y + 1;
  upperLeft.X = center.X - 1;
  adjacentElements.push_back(upperLeft);
  
  
  upperRight.Y = center.Y + 1;
  upperRight.X = center.X + 1;
  adjacentElements.push_back(upperRight);
  
  lowerLeft.Y = center.Y - 1;
  lowerLeft.X = center.X - 1;
  adjacentElements.push_back(lowerLeft);
  
  lowerRight.Y = center.Y - 1;
  lowerRight.X = center.X + 1;
  adjacentElements.push_back(lowerRight);
  
  for(int x = 0; x < adjacentElements.size(); x++)
  {
    if(currentGen.ContainsKey(adjacentElements[x]))
    {
      adj++;
    }
  }
  return adj;
}




void Update(AssociativeArray<orderedPair, char>& currentGen)
{
  orderedPair pair;
  int numAdj = 0;
  //const AssociativeArray<orderedPair, char> currentGenChecker(currentGen);
  AssociativeArray<orderedPair, char> nextGeneration;
  
  const int xMax = 10, xMin = -10, yMax = 10, yMin = -10;
  
  for(int y = yMax; y >= yMin; y--)
  {
    for(int x = xMin; x <= xMax; x++)
    {
      
      pair.X = x;
      pair.Y = y;
      
      numAdj = countAdj(currentGen, pair);
      
      if((numAdj == 2 && currentGen.ContainsKey(pair)) || numAdj == 3)
      {
        nextGeneration[pair] = '*';
      }
      
      
      
    }
  }
  currentGen = nextGeneration;
}


int main()
{
  //Universal Program Requirements
  cout << "VandeBrookeBenLab9bGameOfLife.cpp " << endl;
  cout << "by Ben Van de Brooke" << endl;
  cout << "On 10/16/16" << endl;
  cout << "Editor: X-Code" << endl;
  cout << "Compiler: GCC" << endl;
  cout << "Description:" << endl<< endl;
  
  
  /* Rules for Game of Life
   
   if adj = 2 && this == '*' then newGen[here] = '*'
   
   if adj = 3 newGen[here] = '*'
   
   else
    newGen[here] = ''
   
   */
  
  /*
      1. Initialize with user input
      2. While user doesnt enter q
          a. Update
              - for each * and empty element stored check to see if it will survive
          b. Print
      3. "Clean Up"
   
   */
  
  //initial capacity 400 = 20 x 20 grid
  AssociativeArray<orderedPair, char> currentGen(400);
  
  string input;
  int generationNumber = 1;
  
  cout << "Welcome to the game of life!" << endl;
  cout << "Please enter pairs of numbers when you are done enter a pair of -1. I will use these as coordinates to initialize our little game." << endl;
  
  getline(cin,input);
  
  InitializeGrid(currentGen,input);
 
  cout << "Here is what your cooridnates have given:" << endl;
  Print(currentGen);
  
  
  cout << "The game is ready. Press enter to see the next generation and Q to quit" << endl;
  getline(cin,input);
  
  
  while(input != "Q")
  {
    
    Update(currentGen);
    cout << "Generation " << generationNumber++ << endl;
    Print(currentGen);
    
    getline(cin,input);
  }
  
  
  
  return 0;
}