#ifndef SRC_MODEL_PATHFINDER_H_
#define SRC_MODEL_PATHFINDER_H_

#include <vector>

#include "maze.h"

namespace s21 {
using Matrix = std::vector<std::vector<bool>>;
using WayMatrix = std::vector<std::vector<int>>;
using Path = std::vector<std::pair<size_t, size_t>>;
class PathFinder {
 public:
  void SetMaze(const Maze &maze);
  Path FindPath(const Point &start, const Point &finish);

 private:
  Maze maze_;
  WayMatrix way_{};
  int way_counter_ = 1;
  bool find_finish_ = 0;

  void InitWayMatrix();
  void NewPathStep();
  void ResultingWayMatrix(Path *res, size_t row_pos, size_t column_pos);

  void MoveUp(size_t row_pos, size_t column_pos);
  void MoveDown(size_t row_pos, size_t column_pos);
  void MoveRight(size_t row_pos, size_t column_pos);
  void MoveLeft(size_t row_pos, size_t column_pos);

  void CheckUp(Path *res, size_t *row_pos, size_t *column_pos);
  void CheckDown(Path *res, size_t *row_pos, size_t *column_pos);
  void CheckLeft(Path *res, size_t *row_pos, size_t *column_pos);
  void CheckRight(Path *res, size_t *row_pos, size_t *column_pos);
};
}  // namespace s21

#endif  // SRC_MODEL_PATHFINDER_H_
