#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include <string>

#include "../model/model.h"

namespace s21 {
using Matrix = std::vector<std::vector<bool>>;
using Point = std::pair<int, int>;
using Path = std::vector<std::pair<size_t, size_t>>;
class Controller {
 public:
  Controller() {}
  explicit Controller(const s21::Model* m) : model_(*m) {}
  Controller(const Controller& other);
  Controller(Controller&& other);
  ~Controller() {}

  Controller& operator=(const Controller& other);
  Controller& operator=(Controller&& other);

  Matrix& GetMazeVerticalWallsMatrix();
  Matrix& GetMazeHorizontalWallsMatrix();
  size_t GetMazeRows();
  size_t GetMazeColumns();

  Matrix& GetCaveMatrix();
  size_t GetCaveRows();
  size_t GetCaveColumns();

  ErrorType GetError();

  bool LoadMazeFromFile(const std::string& path);
  void GenerateMaze(size_t rows, size_t columns);
  void SaveMaze(const std::string& path);
  Path FindPath(Point start, Point finish);
  void ClearMaze();

  bool LoadCaveFromFile(const std::string& path);
  void GenerateCave(size_t rows, size_t columns, double chance);
  void RebuildCave(size_t death_limit, size_t birth_limit);
  void ClearCave();

 private:
  Model model_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
