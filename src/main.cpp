#include "tic-tac-toe.h"
#include <memory>
#include <iostream>
#include <fmt/format.h>

// return new board state
// return nullptr if the game is over.
std::shared_ptr<Board> human_move(const Board* board, Player player) {
  int depth = num_empty_cells(board);
  if (depth == 0 || is_game_over(board)) {
    return nullptr;
  }

  std::cout << "Player " << player << "'s turn:\n"
            << board
            << "Input your choice (row,col):\n"
            << std::flush;

  int row = -1, col = -1;
  std::cin >> row >> col;
  while (!is_valid_move(board, row, col)) {
    if (std::cin.eof()) {
      exit(EXIT_FAILURE);
    }
    std::cout << "input error, retry:" << std::endl;
    std::cin >> row >> col;
  }
  fmt::print("Your choice is ({}, {}).\n", row, col);
  auto result          = std::make_shared<Board>(*board);
  result->at(row, col) = player;
  return result;
}

int main_hvh() {
  auto board = std::make_shared<Board>();

  while (!is_game_over(board.get())) {
    board = human_move(board.get(), Player::X);
    if (is_game_over(board.get())) {
      std::cout << "Game over. Winner is " << Player::X << std::endl;
      break;
    }

    board = human_move(board.get(), Player::O);
    if (is_game_over(board.get())) {
      std::cout << "Game over. Winner is " << Player::O << std::endl;
      break;
    }
  }

  std::cout << "final board state:\n"
            << board << std::endl;

  return EXIT_SUCCESS;
}

int main() {
  return main_hvh();
}
