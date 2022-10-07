#include "parser.h"

namespace s21 {
Matrix& Parser::GetMazeVerticalWalls() { return maze_vertical_walls_; }

Matrix& Parser::GetMazeHorizontalWalls() { return maze_horizontal_walls_; }

Matrix& Parser::GetCaveMatrix() { return cave_matrix_; }

size_t Parser::GetRows() { return rows_; }

size_t Parser::GetColumns() { return columns_; }

ErrorType Parser::GetError() { return error_; }

bool Parser::ParseMaze(const std::string& filename) {
  ClearMaze();
  std::ifstream read_file;
  read_file.open(filename);
  if (read_file.is_open()) {
    std::vector<size_t> temp_vector;
    ParseFile(&read_file, temp_vector);
    if (CheckMazeTempVector(temp_vector)) {
      ParseMazeWallsMatrixes(temp_vector);
      return CheckMaze();
    } else {
      error_ = ErrorType::WRONG_DATA_FORMAT;
      return false;
    }
  } else {
    error_ = ErrorType::WRONG_FILENAME;
    return false;
  }
}

bool Parser::ParseCave(const std::string& filename) {
  ClearCave();
  std::ifstream read_file;
  read_file.open(filename);
  if (read_file.is_open()) {
    std::vector<size_t> temp_vector;
    ParseFile(&read_file, temp_vector);
    if (CheckCaveTempVector(temp_vector)) {
      ParseCaveMatrix(temp_vector);
      return CheckCave();
    } else {
      error_ = ErrorType::WRONG_DATA_FORMAT;
      return false;
    }
  } else {
    error_ = ErrorType::WRONG_FILENAME;
    return false;
  }
}

void Parser::ParseFile(std::ifstream* read_file,
                       std::vector<size_t>& temp_vector) {
  std::string temp_string;
  while (getline(*read_file, temp_string)) {
    if (!temp_string.empty()) {
      std::istringstream stream(temp_string);
      std::string token;
      while (getline(stream, token, ' ')) {
        if (token != "") {
          temp_vector.push_back(std::stoi(token));
        }
      }
    }
  }
}

void Parser::ParseMazeWallsMatrixes(std::vector<size_t>& temp_vector) {
  rows_ = temp_vector.at(0);
  temp_vector.erase(temp_vector.begin());
  columns_ = temp_vector.at(0);
  temp_vector.erase(temp_vector.begin());
  if (temp_vector.size() == rows_ * columns_ * 2) {
    for (size_t rows = 0; rows < rows_; rows++) {
      maze_vertical_walls_.push_back(TempRow(temp_vector));
    }
    if (temp_vector.size() == rows_ * columns_) {
      for (size_t rows = 0; rows < rows_; rows++) {
        maze_horizontal_walls_.push_back(TempRow(temp_vector));
      }
    }
  }
}

void Parser::ParseCaveMatrix(std::vector<size_t>& temp_vector) {
  rows_ = temp_vector.at(0);
  temp_vector.erase(temp_vector.begin());
  columns_ = temp_vector.at(0);
  temp_vector.erase(temp_vector.begin());
  if (temp_vector.size() == rows_ * columns_) {
    for (size_t rows = 0; rows < rows_; rows++) {
      cave_matrix_.push_back(TempRow(temp_vector));
    }
  }
}

std::vector<bool> Parser::TempRow(std::vector<size_t>& temp_vector) {
  std::vector<bool> temp;
  for (size_t columns = 0; columns < columns_; columns++) {
    temp.push_back(temp_vector.at(0));
    temp_vector.erase(temp_vector.begin());
  }
  return temp;
}

bool Parser::CheckMazeTempVector(const std::vector<size_t>& temp_vector) {
  CheckEmptyFile(temp_vector);
  return (!temp_vector.empty() &&
          temp_vector.size() == temp_vector.at(0) * temp_vector.at(1) * 2 + 2);
}

bool Parser::CheckCaveTempVector(const std::vector<size_t>& temp_vector) {
  CheckEmptyFile(temp_vector);
  return (!temp_vector.empty() &&
          temp_vector.size() == temp_vector.at(0) * temp_vector.at(1) + 2);
}

void Parser::CheckEmptyFile(const std::vector<size_t>& temp_vector) {
  if (temp_vector.empty()) {
    error_ = ErrorType::EMPTY_FILE;
  }
}

bool Parser::CheckMaze() {
  return (rows_ != 0 && columns_ != 0 && !maze_horizontal_walls_.empty() &&
          maze_horizontal_walls_.size() == rows_ &&
          !maze_vertical_walls_.empty() &&
          maze_vertical_walls_.size() == rows_);
}

bool Parser::CheckCave() {
  return (rows_ != 0 && columns_ != 0 && !cave_matrix_.empty() &&
          cave_matrix_.size() == rows_);
}

void Parser::ClearMaze() {
  error_ = ErrorType::WITHOUT_ERRORS;
  maze_vertical_walls_.clear();
  maze_horizontal_walls_.clear();
  rows_ = 0;
  columns_ = 0;
}

void Parser::ClearCave() {
  error_ = ErrorType::WITHOUT_ERRORS;
  cave_matrix_.clear();
  rows_ = 0;
  columns_ = 0;
}
}  // namespace s21
