#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "errors.h"

namespace s21 {
using Matrix = std::vector<std::vector<bool>>;
class Parser {
 public:
  Matrix& GetMazeVerticalWalls();
  Matrix& GetMazeHorizontalWalls();
  Matrix& GetCaveMatrix();
  size_t GetRows();
  size_t GetColumns();
  ErrorType GetError();

  bool ParseMaze(const std::string& filename);
  bool ParseCave(const std::string& filename);

 private:
  Matrix maze_vertical_walls_{};
  Matrix maze_horizontal_walls_{};
  Matrix cave_matrix_{};
  size_t rows_ = 0;
  size_t columns_ = 0;
  ErrorType error_ = ErrorType::WITHOUT_ERRORS;

  void ParseFile(std::ifstream* read_file, std::vector<size_t>& temp_vector);
  void ParseMazeWallsMatrixes(std::vector<size_t>& temp_vector);
  void ParseCaveMatrix(std::vector<size_t>& temp_vector);
  std::vector<bool> TempRow(std::vector<size_t>& temp_vector);

  bool CheckMazeTempVector(const std::vector<size_t>& temp_vector);
  bool CheckCaveTempVector(const std::vector<size_t>& temp_vector);
  void CheckEmptyFile(const std::vector<size_t>& temp_vector);

  bool CheckMaze();
  bool CheckCave();

  void ClearMaze();
  void ClearCave();
};
}  // namespace s21
#endif  // SRC_MODEL_PARSER_H_
