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
#define DEFAULT_ID 100

class Tile {
  public:
    TileID id;
    int size;
    vector<vector<char>> tile;
    
  // common interface. required.
  public:
    void show() const;  // print out tile in tilebox format
    void rotate();
    void flipud();
    void fliplr();
};

void Tile::show() const {
    for(auto row : Tile::tile)
    {
      for(auto c : row)
      {
        cout << c;
      }
      cout << "\n";
    }
}

void Tile::rotate() {
  //todo
    int size=tile.size();
    for (int i = 0; i < size / 2; i++) {
        for (int j = i; j < size - i - 1; j++) {
        // save the top left element in a temporary variable
        int temp = tile[i][j];

        // move the top right element to the top left
        tile[i][j] = tile[j][size - i - 1];

        // move the bottom right element to the top right
        tile[j][size - i - 1] = tile[size - i - 1][size - j - 1];

        // move the bottom left element to the bottom right
        tile[size - i - 1][size - j - 1] = tile[size - j - 1][i];

        // move the top left element (saved in temp) to the bottom left
        tile[size - j - 1][i] = temp;
        }
    }
}

void Tile::flipud() {
  //todo
  int rowstart=0;
  int rowend=tile.size()-1;
  bool isStart=false;
  bool isEnd=false;
  for(int i=0;i<tile.size();i++) {
    if(!isStart) {
        for(int j=0;j<tile[0].size();j++) {
            if(tile[i][j]=='*') {
                isStart=true;
                rowstart=i;
                break;
            }
        }
    }
    if(isStart && !isEnd) {
        rowend=i-1;
        for(int j=0;j<tile[0].size();j++) {
            if(tile[i][j]=='*') {
                isEnd=false;
                rowend=tile.size()-1;
                break;
            }
            isEnd=true;
        }        
    }
  }
  for(int r=rowstart;r<=(rowend-rowstart)/2;r++) {
    for(int c=0;c<tile[0].size();c++) {
        char temp=tile[r][c];
        tile[r][c]=tile[rowend-rowstart-r][c];
        tile[rowend-rowstart-r][c]=temp;
    }
  }
}

void Tile::fliplr() {
  //todo
  int colstart=0;
  int colend=tile[0].size()-1;
  bool isStart=false;
  bool isEnd=false;
  for(int i=0;i<tile[0].size();i++) {
    if(!isStart) {
        for(int j=0;j<tile.size();j++) {
            if(tile[j][i]=='*') {
                isStart=true;
                colstart=i;
                break;
            }
        }
    }
    if(isStart && !isEnd) {
        colend=i-1;
        for(int j=0;j<tile.size();j++) {
            if(tile[j][i]=='*') {
                isEnd=false;
                colend=tile[0].size()-1;
                break;
            }
            isEnd=true;
        }        
    }
  }
    for(int c=colstart;c<=(colend-colstart)/2;c++) {
        for(int r=0;r<tile.size();r++) {
            char temp=tile[r][c];
            tile[r][c]=tile[r][colend-colstart-c];
            tile[r][colend-colstart-c]=temp;
        }
    }
}



class Blokus {
  // common interface. required.
  // collection of Tiles
  public:
    vector<vector<char>> board;
    map<TileID, Tile> tile_map;

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
      cout << "input size:" << endl;
      cin >> a;
      Tile t;

      for(int i = 0; i < a; i++)
      {
        vector<char> line;
        cout << "input " << i << " line:" << endl;
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

          line.push_back(c);
        }
        t.tile.push_back(line);
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
        for(int j = 0; j < t.tile.at(i).size(); j++)
        {
          bool is_connected = false;
          // cout << "check top" <<endl;
          if(i > 0)
          {
            if(t.tile.at(i-1).at(j) == '*')
            {
              // top connected
              is_connected = true;
            }
          }
          // cout << "check bottom" <<endl;
          if(i < (t.tile.size() - 1))
          {
            if(t.tile.at(i+1).at(j) == '*')
            {
              // bottom connected
              is_connected = true;
            }
          }
          // cout << "check left" << endl;
          if(j > 0)
          {
            if(t.tile.at(i).at(j-1) == '*')
            {
              // left connected
              is_connected = true;
            }
          }
          // cout << "check right" <<endl;
          if(j < (t.tile.size() - 1))
          {
            if(t.tile.at(i).at(j+1) == '*')
            {
              //right connected
              is_connected = true;
            }
          }

          if(!is_connected)
          {
            cout << "disconnected tile discarded" << endl;
            return;
          }
        }
      }

      // todo: check whether t is already existed.


      TileID id = this->tile_map.size() + DEFAULT_ID;
      this->tile_map.insert({id, t});

      cout << "created tile " << id << endl;
    }

    void reset();
    void show_tiles() const;
    void show_board() const;
    void play_tile(TileID, int, int);
    void set_size(int);
};

Tile* Blokus::find_tile(TileID id) {
  //todo
  return &tile_map[id];
}

void Blokus::reset() {
  //todo
}

void Blokus::show_tiles() const {

  for(auto it : Blokus::tile_map)
  {
    cout << "Tile ID: " << it.first << endl;
    it.second.show();
  }

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
