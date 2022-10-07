#ifndef SRC_MODEL_CAVE_H_
#define SRC_MODEL_CAVE_H_

#include <stdlib.h>

#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
using Matrix = std::vector<std::vector<bool>>;
class Cave {
 public:
  void SetMatrix(const Matrix& matrix);
  void SetRows(size_t rows);
  void SetColumns(size_t columns);

  Matrix& GetMatrix();
  size_t GetRows();
  size_t GetColumns();

  void GenerateCave(double chance);
  void RebuildCave(size_t birth_limit, size_t death_limit);
  void Clear();

 private:
  Matrix matrix_;
  size_t rows_ = 0;
  size_t columns_ = 0;

  int CountNeighbours(size_t row, size_t column);
};
}  // namespace s21

#endif  // SRC_MODEL_CAVE_H_
