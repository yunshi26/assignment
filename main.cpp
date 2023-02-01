// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT8L
// Names: CHAN KAR KIN | NG YUN SHI
// IDs: 1211102630 | 1211103311
// Emails: 1211102630.student.mmu.edu.my | 1211103311@student.mmu.edu.my
// Phones: 0169209773 | 0102799327
// *********************************************************

#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <windows.h> // for Sleep()
using namespace std;

class GameBoard {
private:
  vector<vector<char> > map_; // convention to put trailing underscore
  int dimX_, dimY_;

public:
  GameBoard(int &dimX, int &dimY);
  void init(int &dimX, int &dimY);
  void display(int &dimX, int &dimY);
  int getDimX();
  int getDimY();
  char getObject(int x, int y) const;
  void setObject(int x, int y, char ch);
  bool isEmpty(int x, int y);
  bool isInsideMap(int x, int y);
};

class Alien {
private:
  int x_, y_;
  char alien; // A

public:
  Alien();
  void land(GameBoard &game_board);
  bool turnLeft(GameBoard &game_board);
  bool turnRight(GameBoard &game_board);
  bool moveup(GameBoard &game_board);
  bool movedown(GameBoard &game_board);
  int getX() const;
  int getY() const;

  bool executeComm(GameBoard &game_board, char command);
};

GameBoard::GameBoard(int &dimX, int &dimY) { init(dimX, dimY); }

void GameBoard::init(int &dimX, int &dimY) {
  dimX_ = dimX;
  dimY_ = dimY;

  char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', '^',
                    'v', '<', '>', 'p', 'h', 'r'};
  int noOfObjects = 13; // number of objects in the objects array
  // create dynamic 2D array using vector
  map_.resize(dimY_); // create empty rows
  for (int i = 0; i < dimY_; ++i) {
    map_[i].resize(dimX_); // resize each row
  }
  // put random characters into the vector array

  for (int i = 0; i < dimY_; ++i) {
    for (int j = 0; j < dimX_; ++j) {

      int objNo = rand() % noOfObjects;
      map_[i][j] = objects[objNo];
    }
  }
}

void GameBoard::display(int &dimX, int &dimY) {
  dimX_ = dimX;
  dimY_ = dimY;
  // comment this out during testing
  // system("cls"); // OR system("clear"); for Linux / MacOS
  cout << " - Alien vs Zombie -" << endl;
  // for each row
  for (int i = 0; i < dimY_; ++i) {
    // display upper border of the row
    cout << "  ";
    for (int j = 0; j < dimX_; ++j) {
      cout << "+-";
    }
    cout << "+" << endl;
    // display row number
    cout << setw(2) << (dimY_ - i);
    // display cell content and border of each column
    for (int j = 0; j < dimX_; ++j) {
      cout << "|" << map_[i][j];
    }
    cout << "|" << endl;
  }
  // display lower border of the last row
  cout << "  ";
  for (int j = 0; j < dimX_; ++j) {
    cout << "+-";
  }
  cout << "+" << endl;
  // display column number
  cout << "  ";
  for (int j = 0; j < dimX_; ++j) {
    int digit = (j + 1) / 10;
    cout << " ";
    if (digit == 0)
      cout << " ";
    else
      cout << digit;
  }
  cout << endl;
  cout << "  ";
  for (int j = 0; j < dimX_; ++j) {
    cout << " " << (j + 1) % 10;
  }
  cout << endl << endl;
}

int GameBoard::getDimX() { return dimX_; }

int GameBoard::getDimY() { return dimY_; }

char GameBoard::getObject(int x, int y) const { return map_[-(y - 5)][x - 1]; }

void GameBoard::setObject(int x, int y, char ch) {
  map_[dimY_ - y][x - 1] = ch;
}

bool GameBoard::isEmpty(int x, int y) {
  if (map_[-(y - 5)][x - 1] == ' ')
    return true;
  return false;
}

bool GameBoard::isInsideMap(int x, int y) {
  if ((x >= 1 && x <= dimX_) && (y >= 1 && y <= dimY_))
    return true;
  else
    return false;
}

Alien::Alien() {}

void Alien::land(GameBoard &game_board) // place alien at center of board
{
  char alien = 'A';

  x_ = (game_board.getDimX() + 1) / 2;
  y_ = (game_board.getDimY() + 1) / 2;
  game_board.setObject(x_, y_, alien);
}

bool Alien::turnLeft(GameBoard &game_board) {

  int newx = x_ - 1;

  game_board.setObject(newx, y_, 'A');
  game_board.setObject(x_, y_, '.');

  x_ = newx;

  return true;
}

bool Alien::turnRight(GameBoard &game_board) {

  int newx = x_ + 1;

  game_board.setObject(newx, y_, 'A');
  game_board.setObject(x_, y_, '.');

  x_ = newx;

  return true;
}

bool Alien::moveup(GameBoard &game_board) {

  int newy = y_ + 1;

  game_board.setObject(x_, newy, 'A');
  game_board.setObject(x_, y_, '.');

  y_ = newy;

  return true;
}

bool Alien::movedown(GameBoard &game_board) {

  int newy = y_ - 1;

  game_board.setObject(x_, newy, 'A');
  game_board.setObject(x_, y_, '.');

  y_ = newy;

  return true;
}

int Alien::getX() const { return x_; }

int Alien::getY() const { return y_; }

bool help() {
  cout.width(15);
  cout << "Commands" << endl;
  cout << "1.  U  - Move up" << endl;
  cout << "2.  D  - Move down" << endl;
  cout << "3.  L  - Move left" << endl;
  cout << "4.  R  - Move right" << endl;
  // cout << "5.  arrow   - Switch direction of an arrow" << endl;
  cout << "5.  H  - View list of player commands" << endl;
  // cout << "7.  save    - Save the current game" << endl;
  // cout << "8.  load    - Load a game" << endl;
  cout << "6.  Q  - Exit current game" << endl;
  return true;
}

bool quit() {
  char choice;
  cout << "Do you want to quit? (y/n): ";
  cin >> choice;
  switch (choice) {
  case 'y':
    return false;
  default:
    return true;
  }
}

bool invalid() {
  cout << "Command invalid. Please enter valid command.";
  cout << endl;
  cout << "Enter 'H' to view valid game commands.";
  cout << endl;
  return true;
}

bool Alien::executeComm(GameBoard &game_board, char command) {
  bool success;
  switch (command) {
  case 'L':
    success = turnLeft(game_board);
    break;
  case 'R':
    success = turnRight(game_board);
    break;
  case 'U':
    success = moveup(game_board);
    break;
  case 'D':
    success = movedown(game_board);
    break;
  case 'H':
    success = help();
    system("pause");
    break;
  case 'Q':
    success = quit();
    system("pause");
    break;
  default:
    success = invalid();
    system("pause");
    break;
  }
  return success;
}

void menu(int &rows, int &columns, int &zombies) {
  char input;
  cout << "Default Game Settings" << endl;
  cout << "---------------------" << endl;

  cout << "1. Board Rows: " << rows << endl;
  cout << "2. Board Columns: " << columns << endl;
  cout << "--------------------- " << endl;
  cout << "Zombie Settings " << endl;
  cout << "1. Zombie Count: " << zombies << endl;

  cout << "Do you wish to change the game settings(y/n)? ";
}

int changeSetting(int &rows, int &columns, int &zombies) {

  system("CLS");
  cout << "Change Game Settings" << endl;
  cout << "---------------------" << endl;

  do {
    cout << "Enter Board Rows: ";
    cin >> rows;
    if (rows % 2 == 0) {
      cout << "Invalid input. Please only enter odd numbers!" << endl;
    } else if (rows < 3) // make sure row numbers are not too small or too big
    {
      cout << "Invalid input. Row number is too small!" << endl;
    } else if (rows > 30) {
      cout << "Invalid input. Row number is too big!" << endl;
    }
  } while (rows % 2 == 0 || rows < 1 || rows >= 30);

  do {
    cout << "Enter Board Columns: ";
    cin >> columns;
    if (columns % 2 == 0) {
      cout << "Invalid input. Please only enter odd numbers!" << endl;
    } else if (columns < 3) {
      cout << "Invalid input. Column number is too small!" << endl;
    } else if (columns > 30) // make sure columns are not too small or too big
    {
      cout << "Ivalid input. Column number is too big!" << endl;
    }
  } while (columns % 2 == 0 || columns < 3 || columns > 30);

  do {
    cout << "Enter Zombie Count: ";
    cin >> zombies;
    if (zombies < 1 || zombies > 9) {
      cout << "Invalid input. Zombie number should be in range of 1 to 9!"
           << endl;
    }
  } while (zombies < 1 || zombies > 9);
  return rows, columns, zombies;
}

void playGame(int &rows, int &columns, int &zombies) {

  system("CLS");

  Alien Alien;
  GameBoard game_board(columns, rows);

  Alien.land(game_board);
  game_board.display(columns, rows);

  string commseq;
  char command;

  for (int i = 0; i < INT_MAX; ++i) {

    // cout << "Valid Command:" << endl;
    // cout << "L = Move Left" << endl;
    // cout << "R = Move Right" << endl;
    // cout << "U = Move Up" << endl;
    // cout << "D = Move Down" << endl;
    // cout << "H - View list of commands" << endl;
    // cout << "Q = Quit Game" << endl;
    // cout << endl;
    cout << "Command => ";
    cin >> commseq[i];

    command = commseq[i];
    command = toupper(command);

    game_board.display(columns, rows);
    cout << "Command = " << command << " ..." << endl;
    Sleep(1200);

    bool success = Alien.executeComm(game_board, command);

    game_board.display(columns, rows);
    cout << "Command = " << command;

    if (success)
      cout << " [executed] " << endl;
    else {
      cout << " [failed to execute]" << endl;
      break;
    }
    Sleep(1200);
  }
}

int main() {
  int rows = 21;
  int columns = 21;
  int zombies = 1;
  bool quit = false;
  char input;
  char choice;

  Alien Alien;
  GameBoard game_board(columns, rows);

  do {
    menu(rows, columns, zombies);
    cin >> input;
    switch (input) {
    case 'y':
      changeSetting(rows, columns, zombies);
      cout << "Settings updated successfully!" << endl;
      cout << endl;
      playGame(rows, columns, zombies);
      break;
    case 'n':
      cout << "Please wait for game to load!" << endl;
      cout << endl;
      playGame(rows, columns, zombies);
      break;
    }
  } while (!quit);
}
