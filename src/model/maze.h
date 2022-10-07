#ifndef SRC_MAZE_H_
#define SRC_MAZE_H_

#include <string>
#include <utility>
#include <vector>

namespace s21 {
using Matrix = std::vector<std::vector<bool>>;
using Groups = std::vector<std::pair<int, bool>>;
using Point = std::pair<int, int>;
class Maze {
 public:
  void SetVerticalWalls(const Matrix &vert);
  void SetHorizontalWalls(const Matrix &horiz);
  void SetRows(size_t rows);
  void SetColumns(size_t columns);

  Matrix &GetVerticalWalls();
  Matrix &GetHorizontalWalls();
  size_t GetRows();
  size_t GetColumns();

  void Generate();
  void Save(const std::string &filepath);
  void Clear();

 private:
  Matrix vertical_{};
  Matrix horizontal_{};
  size_t rows_ = 0;
  size_t columns_ = 0;
  Groups groups_{};
  size_t group_counter_ = 0;

  void InitGroups();
  void FillGroup();
  void AddVerticalWall();
  void AddHorizontalWall();
  void LastVerticalWall(std::vector<bool> vert);
  void ReGroup(std::vector<bool> horiz);
  void UnionGroup(int new_group, int old_group);
  size_t GroupSize(int group);
  bool HaveExit(int group);
};
}  // namespace s21

#endif  // SRC_MAZE_H_
