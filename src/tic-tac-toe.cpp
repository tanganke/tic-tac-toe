#include "tic-tac-toe.h"
#include <algorithm>

Board::Board() {
  std::fill(&board[0][0], &board[0][0] + 9, Player::None);
}

const Player& Board::at(int row, int col) const {
  assert(row >= 0 && row < 3);
  assert(col >= 0 && col < 3);
  return board[row][col];
}

Player& Board::at(int row, int col) {
  assert(row >= 0 && row < 3);
  assert(col >= 0 && col < 3);
  return board[row][col];
}

const Player& Board::at(int index) const {
  assert(index < 9);
  int row = index / 3;
  int col = index % 3;
  return board[row][col];
}

Player& Board::at(int index) {
  assert(index < 9);
  int row = index / 3;
  int col = index % 3;
  return board[row][col];
}

bool Board::operator==(const Board& other) const {
  for (int i = 0; i < 9; i++) {
    if ((*this)[i] != other[i]) {
      return false;
    }
  }
  return true;
}

bool Board::is_full() const {
  for (auto p : board) {
    if (*p == Player::None) {
      return false;
    }
  }
  return true;
}

Move::Move(Player player, int row, int col)
    : player(player)
    , row(row)
    , col(col) {
  assert(row >= 0 && row < 3);
  assert(col >= 0 && col < 3);
}

bool is_win(const Board* board, Player player) {
  // rows
  for (int i = 0; i < 3; i++) {
    if (board->at(i, 0) == player && board->at(i, 1) == player && board->at(i, 2) == player) {
      return true;
    }
  }
  // columns
  for (int i = 0; i < 3; i++) {
    if (board->at(0, i) == player && board->at(1, i) == player && board->at(2, i) == player) {
      return true;
    }
  }
  // diagonals
  if (board->at(0, 0) == player && board->at(1, 1) == player && board->at(2, 2) == player) {
    return true;
  }
  if (board->at(0, 2) == player && board->at(1, 1) == player && board->at(2, 0) == player) {
    return true;
  }
  return false;
}

bool is_game_over(const Board* board) {
  return is_win(board, Player::X) || is_win(board, Player::O) || board->is_full();
}

std::vector<int> empty_cells(const Board* board) {
  std::vector<int> result;
  for (int i = 0; i < 9; ++i) {
    if ((*board)[i] == Player::None) {
      result.push_back(i);
    }
  }
  return result;
}

int num_empty_cells(const Board* board) {
  int result = 0;
  for (int i = 0; i < 9; ++i) {
    if ((*board)[i] == Player::None) {
      result++;
    }
  }
  return result;
}

bool is_valid_move(const Board* board, int index) {
  if (index < 0 || index > 8) {
    return false;
  }
  return board->at(index) == Player::None;
}

bool is_valid_move(const Board* board, int row, int col) {
  if (row < 0 || row >= 3)
    return false;
  if (col < 0 || col >= 3)
    return false;
  return board->at(row, col) == Player::None;
}

std::ostream& operator<<(std::ostream& os, Player player) {
  switch (player) {
    case Player::None:
      os << "_";
      break;
    case Player::X:
      os << "X";
      break;
    case Player::O:
      os << "O";
      break;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Board* board) {
  os << "  0 1 2\n";
  for (int i = 0; i < 3; i++) {
    os << i << " ";
    for (int j = 0; j < 3; j++) {
      os << board->at(i, j) << " ";
    }
    os << "\n";
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
  return os << &board;
}