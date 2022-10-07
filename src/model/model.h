#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "cave.h"
#include "maze.h"
#include "parser.h"
#include "pathfinder.h"

namespace s21 {
using Matrix = std::vector<std::vector<bool>>;
using Point = std::pair<int, int>;
using Path = std::vector<std::pair<size_t, size_t>>;
class Model {
 public:
  Matrix& GetMazeVerticalWallsMatrix();
  Matrix& GetMazeHorizontalWallsMatrix();
  size_t GetMazeRows();
  size_t GetMazeColumns();

  Matrix& GetCaveMatrix();
  size_t GetCaveRows();
  size_t GetCaveColumns();

  Parser& GetParser();

  void LoadMaze();
  void LoadMazeVerticalWallsMatrix();
  void LoadMazeHorizontalWallsMatrix();
  void LoadMazeRows();
  void LoadMazeColumns();
  void GenerateMaze(size_t rows, size_t columns);
  void SaveMaze(const std::string& filepath);
  Path FindMazePath(Point start, Point finish);
  void ClearMaze();

  void LoadCave();
  void LoadCaveMatrix();
  void LoadCaveRows();
  void LoadCaveColumns();
  void GenerateCave(size_t rows, size_t columns, double chance);
  void RebuildCave(size_t death_limit, size_t birth_limit);
  void ClearCave();

 private:
  Cave cave_;
  Maze maze_;
  Parser parser_;
  PathFinder path_finder_;
};
}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_
