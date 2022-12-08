// Copyright 2022 XinWang xinw0219@bu.edu
#include <iostream>
#include <string>
#include <vector>
#include <map>
// allowed includes
// tuple, utility, vector, map, set, unordered_map,
// unordered_set, algorithm

using std::cin;
using std::cout;
using std::string;

using namespace std;
/* Blokus command glossary

Notes:
 - the first tile is numbered 100, and each new
   one is assigned the next available integer

 - the upper left corner is 0,0

 - first index is row, second index is column


COMMANDS

QUIT: exit the game
>quit
Goodbye

RESET: start the game from beginning
>reset
game reset

CREATE: create a new tile

>create 4
>..*.
>.**.
>.*..
>....
created tile 100


SHOW ALL TILES: show a tile inventory (unordered.)

>show tiles
tile inventory
102
*
101
**
**
100
***
**.
...


SHOW A TILE: show a tile by ID number
>show 100
***
**.
**.

PLAY A TILE: place a tile on the board at row and column numbers

>play 101 4 5
played 101

>play 99 0 0
99 not played

ROTATE A TILE: rotate a tile 90 degrees counterclockwise
>rotate 100
rotate 100 complete
**.
*..
*..

FLIP A TILE sideways (left becomes right)
>fliplr 100
fliplr 100 complete
**.
.*.
.*.

FLIP A TILE vertically (up becomes down)
>flipud 100
flipud 100 complete
.*.
.*.
**.

RESIZE: make the board bigger or smaller. When smaller,
        played pieces fall off the board. Show the new board.

>resize 5

- end of command glossary -
*/


typedef int TileID;

class Tile {
  public:
    vector<vector<char>> tile;
    TileID id;
  // common interface. required.
  public:
    void show() const;  // print out tile in tilebox format
    void rotate();
    void flipud();
    void fliplr();
};

void Tile::show() const {
  //todo
}

void Tile::rotate() {
  //todo
}

void Tile::flipud() {
  //todo
}

void Tile::fliplr() {
  //todo
}

class Blokus {
  // common interface. required.
  // collection of Tiles
  vector<vector<char>> board;
  map<int, Tile> tile_map;

 public:
  Tile* find_tile(TileID);
  void create_piece() {
    // read in the size
    // read in strings
    // make a Tile
    // store it in a collection of Tiles
    int error_type = 0;
    bool tile_is_empty = true;
    int a;
    string s;
    cin >> a;
    Tile t;
    t.tile.resize(a, vector<char>(a));
    for(int i = 0; i < a; i++)
    {
      cin >> s;
      if(s.length() != a)
      {
        // tile is not sqaure
        error_type = 3;
      }

      for(int j = 0; j < s.length(); j++)
      {
        char c = s.at(j);
        if(c == '*')
        {
          tile_is_empty = false;
        }

        if(c != '.' & c != '*')
        {
          // tile element is invalid;
          error_type = 2;
        }

        t.tile.at(i).push_back(c);
      }
    }

    if(tile_is_empty)
    {
      error_type = 1;
    }

    if(error_type > 0)
    {
      cout << "invalid tile" << endl;
      return;
    }

    for(int i = 0; i < t.tile.size(); i++)
    {
      for(int j=0; j < t.tile.at(i).size(); j++)
      {
        bool is_connected = false;
        if(i > 0 & t.tile.at(i-1).at(j) == '*')
        {
          // top connected
          is_connected = true;
        }
        if(i < (t.tile.size() - 1) & t.tile.at(i+1).at(j) == '*')
        {
          // bottom connected
          is_connected = true;
        }
        if(j > 0 & t.tile.at(i).at(j-1) == '*')
        {
          // left connected
          is_connected = true;
        }
        if(j < (t.tile.size() - 1) & t.tile.at(i).at(j+1) == '*')
        {
          //right connected
          is_connected = true;
        }

        if(!is_connected)
        {
          cout << "disconnected tile discarded" << endl;
          return;
        }
      }
    }

    

  }

  void reset();
  void show_tiles() const;
  void show_board() const;
  void play_tile(TileID, int, int);
  void set_size(int);
};

Tile* Blokus::find_tile(TileID id) {
  //todo
  Tile* t = new Tile();
  return t;
}

void Blokus::reset() {
  //todo
}

void Blokus::show_tiles() const {
  //todo;
}

void Blokus::show_board() const {
  for(int i = 0; i < this->board.size(); i++)
  {
    for(int j = 0; j < this->board.at(0).size(); j++)
    {
      cout<<this->board.at(i).at(j);
    }
    cout<<"\n";
  }
}

void Blokus::play_tile(TileID id, int col, int row)
{
  //todo
}

void Blokus::set_size(int a) {
  this->board.resize(a, vector<char>(a, '.'));
}



// MAIN. Do not change the below.


int main() {
  string command;
  Blokus b;

  while (true) {
    cin >> command;
    if (command == "quit")  {
      break;
    } else if (command == "//") {
      getline(cin, command);
    } else if (command == "board") {
      b.show_board();
    } else if (command == "create") {
      b.create_piece();
    } else if (command == "reset") {
      b.reset();
    } else if (command == "show") {
      string arg;
      cin >> arg;
      if (arg == "tiles") {
        b.show_tiles();
      } else {
        auto g = b.find_tile(std::stoi(arg));
        g->show();
      }
    } else if (command == "resize") {
      int newsize;
      cin >> newsize;
      b.set_size(newsize);
      b.show_board();
    } else if (command == "play") {
      TileID id;
      int row, col;
      cin >> id >> row >> col;
      b.play_tile(id, row, col);
    } else if (command == "rotate") {
      TileID id;
      cin >> id;
      auto g = b.find_tile(id);
      g->rotate();
      cout << "rotated " << id << "\n";
      g->show();
    } else if (command == "fliplr") {
      TileID id;
      cin >> id;
      auto g = b.find_tile(id);
      g->fliplr();
      cout << "fliplr " << id << "\n";
      g->show();
    } else if (command == "flipud") {
      TileID id;
      cin >> id;
      auto g = b.find_tile(id);
      g->flipud();
      cout << "flipud " << id << "\n";
      g->show();
    } else {
      cout << "command not understood.\n";
    }
  }
  cout << "Goodbye\n";
  return 0;
}
