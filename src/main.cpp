#include "tic-tac-toe.h"
#include <memory>
#include <iostream>
#include <random>
#include <fmt/format.h>
#include <boost/timer/timer.hpp>
using boost::timer::auto_cpu_timer;

// return new board state
// return nullptr if the game is over.
std::shared_ptr<Board> human_turn(const Board* board, Player player) {
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
  std::cout << std::endl;
  auto result          = std::make_shared<Board>(*board);
  result->at(row, col) = player;
  return result;
}

struct minimax_helper {
  Player player;
  Player op_player;
  minimax_helper(Player player)
      : player(player)
      , op_player(opponent(player)) { }

  int evaluate(const Board* board) {
    if (is_win(board, player)) {
      return 1;
    } else if (is_win(board, op_player)) {
      return -1;
    } else {
      return 0;
    }
  }

  std::tuple<int, int, int> operator()(const Board* board, Player p, int depth) {
    std::tuple<int, int, int> best;
    if (p == player)
      best = { -1, -1, INT_MIN };
    else {
      best = { -1, -1, INT_MAX };
    }

    if (depth == 0 || is_game_over(board)) {
      int score = evaluate(board);
      return { -1, -1, score };
    }

    for (auto cell : empty_cells(board)) {
      auto new_state      = std::make_shared<Board>(*board);
      new_state->at(cell) = p;
      auto score          = (*this)(new_state.get(), opponent(p), depth - 1);
      std::get<0>(score)  = cell / 3;
      std::get<1>(score)  = cell % 3;
      if (p == player) {
        if (std::get<2>(score) > std::get<2>(best)) {
          best = score;
        }
      } else {
        if (std::get<2>(score) < std::get<2>(best)) {
          best = score;
        }
      }
    }

    return best;
  };
};

/**
 * @return std::tuple<int, int, int> [the best row, best col, best score]
 */
std::tuple<int, int, int> minimax(const Board* board, Player player, int depth) {

  return minimax_helper { player }(board, player, depth);
}

std::shared_ptr<Board> ai_turn_minimax(const Board* board, Player player) {
  auto_cpu_timer timer;
  int depth = num_empty_cells(board);
  if (depth == 0 || is_game_over(board)) {
    return nullptr;
  }

  auto result = std::make_shared<Board>(*board);
  if (depth == 9) {
    std::mt19937                       gen(std::random_device {}());
    std::uniform_int_distribution<int> dis(0, 8);
    result->at(dis(gen)) = player;
  } else {
    auto [row, col, _] = minimax(board, player, depth);
    fmt::print("AI's choice is ({},{})\n", row, col);
    result->at(row, col) = player;
  }
  return result;
}

int start_game(std::shared_ptr<Board> (*turn_func_X)(const Board*, Player),
               std::shared_ptr<Board> (*turn_func_O)(const Board*, Player)) {
  auto board = std::make_shared<Board>();
  // return true if game over
  auto check_winner = [&](Player player) {
    if (is_win(board.get(), Player::X)) {
      std::cout << "Game over. Winner is " << Player::X << std::endl;
      return true;
    }
    if (board->is_full()) {
      std::cout << "Game over. Tie." << std::endl;
      return true;
    }
    return false;
  };

  int round = 0;
  while (!is_game_over(board.get())) {
    fmt::print("Round {}:\n", ++round);

    board = turn_func_X(board.get(), Player::X);
    print(board.get());
    std::cout << std::endl;
    if (check_winner(Player::X)) {
      break;
    }

    board = turn_func_O(board.get(), Player::O);
    print(board.get());
    std::cout << std::endl;
    check_winner(Player::O);
  }

  std::cout << "final board state:\n"
            << board << std::endl;

  return EXIT_SUCCESS;
}

int main() {
  std::cout << "choose mode:\n"
            << "1. human vs human\n"
            << "2. human vs computer (Minimax)\n"
            << "3. computer (Minimax) vs human\n"
            << "4. computer (Minimax) vs computer (Minimax)\n"
            << "input: ";
  int mode = -1;
  std::cin >> mode;
  while (mode < 1 || mode > 4) {
    if (std::cin.eof()) {
      exit(EXIT_FAILURE);
    }
    std::cout << "input error, retry: ";
    std::cin >> mode;
  }

  if (mode == 1)
    return start_game(&human_turn, &human_turn);
  else if (mode == 2)
    return start_game(&human_turn, &ai_turn_minimax);
  else if (mode == 3)
    return start_game(&ai_turn_minimax, &human_turn);
  else if (mode == 4)
    return start_game(&ai_turn_minimax, &ai_turn_minimax);
  else {
    std::cerr << "invalid mode" << std::endl;
    return EXIT_FAILURE;
  }
}
