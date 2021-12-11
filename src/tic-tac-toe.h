#pragma once
#include <vector>
#include <cassert>
#include <iostream>

enum class Player {
  None = 0,
  X    = 1, // first player
  O    = 2, // second player
};

struct Board {
  Player board[3][3];
  Board();

  // get the player at the given position
  const Player&        at(int row, int col) const;
  Player&              at(int row, int col);
  const Player&        at(int index) const;
  Player&              at(int index);
  inline const Player& operator[](int index) const { return board[index / 3][index % 3]; }
  inline Player&       operator[](int index) { return board[index / 3][index % 3]; }
  // 比较两个棋盘的状态是否相同
  bool operator==(const Board& other) const;
  // 棋盘是否已经满了
  bool is_full() const;
};

struct Move {
  Player player;
  int    row, col;
  Move() = default;
  Move(Player player, int row, int col);
  Move(Player player, int index)
      : Move(player, index / 3, index % 3) { }
};

// check if the given player has won the game
bool is_win(const Board* board, Player player);
// check if the game is over
bool is_game_over(const Board* board);
// return the empty cells
std::vector<int> empty_cells(const Board* board);
// number of empty cells
int num_empty_cells(const Board* board);
// check if a move is valid
bool is_valid_move(const Board* board, int index);
bool is_valid_move(const Board* board, int row, int col);

std::ostream& operator<<(std::ostream& os, Player player);
std::ostream& operator<<(std::ostream& os, const Board* board);
std::ostream& operator<<(std::ostream& os, const Board& board);
