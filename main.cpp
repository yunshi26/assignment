// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT8L
// Names: CHAN KAR KIN | NG YUN SHI
// IDs: 1211102630 | 1211103311
// Emails: 1211102630@student.mmu.edu.my | 1211103311@student.mmu.edu.my
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
  vector<vector<char>> map_; // convention to put trailing underscore
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
  int alienAttack = 0;
  int x_, y_;
  char alien; // A
  vector<int> alienLife = {100, 200};

public:
  Alien();
  void land(GameBoard &game_board);
  bool turnLeft(GameBoard &game_board);
  bool turnRight(GameBoard &game_board);
  bool moveup(GameBoard &game_board);
  bool movedown(GameBoard &game_board);
  int getX() const;
  int getY() const;
  int getAlienLife();
  int getAlienAttack();

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

char GameBoard::getObject(int x, int y) const { return map_[y - 1][x - 1]; }

void GameBoard::setObject(int x, int y, char ch) { map_[y - 1][x - 1] = ch; }

bool GameBoard::isEmpty(int x, int y) { return map_[y - 1][x - 1] == ' '; }

bool GameBoard::isInsideMap(int x, int y) {
  return x >= 1 && x <= dimX_ && y >= 1 && y <= dimY_;
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
  int newy = y_ - 1;

  game_board.setObject(x_, newy, 'A');
  game_board.setObject(x_, y_, '.');

  y_ = newy;

  return true;
}

bool Alien::movedown(GameBoard &game_board) {
  int newy = y_ + 1;

  game_board.setObject(x_, newy, 'A');
  game_board.setObject(x_, y_, '.');

  y_ = newy;

  return true;
}

int Alien::getX() const { return x_; }

int Alien::getY() const { return y_; }

int Alien::getAlienLife() { return alienLife[0]; } // get alien life

int Alien::getAlienAttack() { return alienAttack; }

// bool changeArrow(int row, int)
// {
//     Alien alien;
//     GameBoard game_board(columns, rows);
//     string arrowDirection;
//     int aX, aY;

//     cout << "Enter row, column and direction: ";
//     cin >> aX >> aY >> arrowDirection;
//     if (game_board.getObject(aX, aY) == '^' || game_board.getObject(aX, aY)
//     == 'v' ||
//      game_board.getObject(aX, aY) == '<' || game_board.getObject(aX, aY) ==
//      '>')
//     {
//         if (arrowDirection == "up")
//         {
//             game_board.setObject(aX, aY, '^');
//             cout << "Arrow is changed to upwards.";
//         }
//         if (arrowDirection == "down")
//         {
//             game_board.setObject(aX, aY, '^');
//             cout << "Arrow is changed to downwards.";
//         }
//         if (arrowDirection == "left")
//         {
//             game_board.setObject(aX, aY, '^');
//             cout << "Arrow is changed to left.";
//         }
//         if (arrowDirection == "right")
//         {
//             game_board.setObject(aX, aY, '^');
//             cout << "Arrow is changed to right.";
//         }
//     }
//     return true;
// }

bool changeArrow() {
  int row, column;
  string direction;
  cout << "Enter row, column and direction: ";
  cin >> row >> column >> direction;
  system("pause");
  cout << endl;
  cout << "Arrow changed." << endl;
  system("pause");

  return true;
}

bool save() {
  string filename;
  cout << "Enter a filename to save: ";
  cin >> filename;
  system("pause");
  cout << endl;
  cout << "Game saved to " << filename << ".txt" << endl;
  system("pause");

  return true;
}

bool help() {
  cout.width(15);
  cout << "Commands" << endl;
  cout << "1.  up      - Move up" << endl;
  cout << "2.  down    - Move down" << endl;
  cout << "3.  left    - Move left" << endl;
  cout << "4.  right   - Move right" << endl;
  cout << "5.  arrow   - Switch direction of an arrow" << endl;
  cout << "6.  help    - View list of player commands" << endl;
  cout << "7.  save    - Save the current game" << endl;
  cout << "8.  load    - Load a game" << endl;
  cout << "9.  quit    - Exit current game" << endl;
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
  cout << "Command invalid. Please enter valid command." << endl;
  cout << "Enter 'help' to view valid game commands." << endl;
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
  case 'A':
    success = changeArrow();
    break;
  case 'S':
    success = save();
    break;
  case 'H':
    success = help();
    system("pause");
    break;
  case 'Q':
    success = quit();
    system("pause");
    break;
  case 'I':
    success = invalid();
    system("pause");
    break;
  }
  return success;
}
class Zombie {
private:
  int zombieAttack = 10;
  int zombieRange = 1;
  int x_, y_;
  char zombie_;
  vector<int> zombieLife = {100, 50};

public:
  Zombie();
  int getZombieLife();
  int getZombieAttack();
  int getZombieRange();
  void spawn(GameBoard &game_board);
  bool move(GameBoard &game_board, int alienX, int alienY);
  int getX() const;
  int getY() const;
};

Zombie::Zombie() {}

void Zombie::spawn(GameBoard &game_board) {
  char zombie = '1';

  int dimX = game_board.getDimX();
  int dimY = game_board.getDimY();

  do {
    x_ = rand() % dimX + 1;
    y_ = rand() % dimY + 1;

  } while (!game_board.isEmpty(x_, y_));

  game_board.setObject(x_, y_, zombie);
}

bool Zombie::move(GameBoard &game_board, int alienX, int alienY) {
  int dx = alienX - x_;
  int dy = alienY - y_;

  if (dx > 0) {
    if (game_board.isEmpty(x_ + 1, y_)) {
      game_board.setObject(x_, y_, ' ');
      game_board.setObject(x_ + 1, y_, zombie_);
      x_++;
      return true;
    }
  } else if (dx < 0) {
    if (game_board.isEmpty(x_ - 1, y_)) {
      game_board.setObject(x_, y_, ' ');
      game_board.setObject(x_ - 1, y_, zombie_);
      x_--;
      return true;
    }
  }

  if (dy > 0) {
    if (game_board.isEmpty(x_, y_ + 1)) {
      game_board.setObject(x_, y_, ' ');
      game_board.setObject(x_, y_ + 1, zombie_);
      y_++;
      return true;
    }
  } else if (dy < 0) {
    if (game_board.isEmpty(x_, y_ - 1)) {
      game_board.setObject(x_, y_, ' ');
      game_board.setObject(x_, y_ - 1, zombie_);
      y_--;
      return true;
    }
  }

  return false;
}

int Zombie::getX() const { return x_; }

int Zombie::getY() const { return y_; }

int Zombie::getZombieLife() { return zombieLife[0]; }

int Zombie::getZombieAttack() { return zombieAttack; }

int Zombie::getZombieRange() { return zombieRange; }

void menu(int &rows, int &columns, int &zombies) {
  char input;
  cout << "Default Game Settings" << endl;
  cout << "---------------------" << endl;

  cout << "1. Board Rows: " << rows << endl;
  cout << "2. Board Columns: " << columns << endl;
  cout << "---------------- " << endl;
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
      cout << "Invalid input. Row number is too big! Maximum row number is 30. "
           << endl;
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
      cout << "Ivalid input. Column number is too big! Maximum column number "
              "is 30. "
           << endl;
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

  Alien alien;
  GameBoard game_board(columns, rows);
  Zombie zombie;

  zombie.spawn(game_board);
  alien.land(game_board);
  game_board.display(columns, rows);
  // cout << "Alien has landed at position (" << alien.getX() << ", " <<
  // alien.getY() << ")" << endl; cout << "Alien      : Life " <<
  // alien.getAlienLife() << endl; cout << "Zombie: " << endl;

  string commseq;
  char command;
  string message;

  for (int i = 0; i < INT_MAX; ++i) {
    cout << "Alien      : Life " << alien.getAlienLife()
         << ", Attack: " << alien.getAlienAttack() << endl;
    cout << "Zombie     : Life " << zombie.getZombieLife()
         << ", Attack: " << zombie.getZombieAttack()
         << ", Range: " << zombie.getZombieRange() << endl;
    cout << "Command => ";
    cin >> commseq;

    if (commseq == "up") {
      command = 'U';
      message = "Alien is moving upwards.";
    } else if (commseq == "down") {
      command = 'D';
      message = "Alien is moving downwards.";
    } else if (commseq == "left") {
      command = 'L';
      message = "Alien is moving to the left.";
    } else if (commseq == "right") {
      command = 'R';
      message = "Alien is moving to the right";
    } else if (commseq == "arrow") {
      command = 'A';
      message = " ";
    } else if (commseq == "quit") {
      command = 'Q';
      message = ' ';
    } else if (commseq == "help") {
      command = 'H';
      message = ' ';
    } else if (commseq == "save") {
      command = 'S';
      message = ' ';
    } else if (commseq != "up" || commseq != "down" || commseq != "left" ||
               commseq != "right" || commseq != "help" || commseq != "save" ||
               commseq != "load" || commseq != "quit") {
      command = 'I';
    } // invalid command
    // else if (commseq == "save") {command = 'S';}
    // else if (commseq == "load") {command = 'L';}

    system("CLS");
    game_board.display(columns, rows);
    cout << message;
    Sleep(1200);

    bool success = alien.executeComm(game_board, command);

    system("CLS");
    game_board.display(columns, rows);
    if (!success) {
      cout << endl;
      system("cls");
      // cout << " [failed to execute]" << endl;
      break;
    }
    Sleep(1200);
  }
}

void randomZombieMove(string **gameboard, int zcount, int row, int column,
                      int **Zombiearr) {
  for (int i = 0; i < zcount; i++) {
    int move = rand() % 4; // generate a random number between 0 and 3
    int prev_row = Zombiearr[i][0];
    int prev_col = Zombiearr[i][1];

    if (move == 0) // move up
    {
      if (prev_row > 0) // check if the zombie is not already at the top row
      {
        Zombiearr[i][0] = prev_row - 1;
        gameboard[prev_row][prev_col] = ".";
        gameboard[prev_row - 1][prev_col] = to_string(i + 1);
        cout << "Zombie " << i + 1 << " moved up." << endl;
      } else {
        cout << "Zombie" << i + 1 << "hits the top border." << endl;
      }
      system("pause");
    } else if (move == 1) // move down
    {
      if (prev_row <
          row - 1) // check if the zombie is not already at the bottom row
      {
        Zombiearr[i][0] = prev_row + 1;
        gameboard[prev_row][prev_col] = ".";
        gameboard[prev_row + 1][prev_col] = to_string(i + 1);
        cout << "Zombie " << i + 1 << " moved down." << endl;
      } else {
        cout << "Zombie " << i + 1 << " hits the bottom border." << endl;
      }
      system("pause");
    }

    else if (move == 2) // move left
    {
      if (prev_col >
          0) // check if the zombie is not already at the leftmost column
      {
        Zombiearr[i][1] = prev_col - 1;
        gameboard[prev_row][prev_col] = " ";
        gameboard[prev_row][prev_col - 1] = to_string(i + 1);
        cout << "Zombie " << i + 1 << " moved left." << endl;
      } else {
        cout << "Zombie " << i + 1 << " hits the left border." << endl;
      }
      system("pause");
    } else // move right
    {
      if (prev_col <
          column -
              1) // check if the zombie is not already at the rightmost column
      {
        Zombiearr[i][1] = prev_col + 1;
        gameboard[prev_row][prev_col] = ".";
        gameboard[prev_row][prev_col + 1] = to_string(i + 1);
        cout << "Zombie " << i + 1 << " moved right." << endl;
      } else {
        cout << "Zombie " << i + 1 << " hits the right border." << endl;
      }
      system("pause");
    }
  }
}

int main() {
  srand(time(NULL)); // set random seed

  int dimX = 20, dimY = 10;
  char command;
  int rows = 21;
  int columns = 21;
  int zombies = 1;
  bool quit = false;
  char input;
  char choice;

  // Alien Alien;
  // GameBoard game_board(columns, rows);
  do {
    system("cls");
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
