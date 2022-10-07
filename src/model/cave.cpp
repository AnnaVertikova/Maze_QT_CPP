#include "cave.h"

#include <iostream>

namespace s21 {
void Cave::SetMatrix(const Matrix& matrix) { matrix_ = matrix; }

void Cave::SetRows(size_t rows) { rows_ = rows; }

void Cave::SetColumns(size_t columns) { columns_ = columns; }

Matrix& Cave::GetMatrix() { return matrix_; }

size_t Cave::GetRows() { return rows_; }

size_t Cave::GetColumns() { return columns_; }

void Cave::GenerateCave(double chance) {
  int rows = rows_;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> distr(0, 1);
  while (rows) {
    int columns = columns_;
    std::vector<bool> temp_matrix;
    while (columns) {
      if (distr(gen) > (1 - chance)) {
        temp_matrix.push_back(true);
      } else {
        temp_matrix.push_back(false);
      }
      columns--;
    }
    matrix_.push_back(temp_matrix);
    rows--;
  }
}

void Cave::RebuildCave(size_t birth_limit, size_t death_limit) {
  Cave tmp_cave(*this);
  for (size_t i = 0; i < matrix_.size(); i++) {
    for (size_t j = 0; j < matrix_.front().size(); j++) {
      size_t neighbours = tmp_cave.CountNeighbours(i, j);
      if (matrix_.at(i).at(j) == 1 && neighbours < death_limit) {
        matrix_.at(i).at(j) = 0;
      }
      if (matrix_.at(i).at(j) == 0 && neighbours > birth_limit) {
        matrix_.at(i).at(j) = 1;
      }
    }
  }
}

void Cave::Clear() {
  matrix_.clear();
  rows_ = 0;
  columns_ = 0;
}

int Cave::CountNeighbours(size_t row, size_t column) {
  int count = 0;
  for (int i = (row - 1); i <= (int)(row + 1); i++) {
    for (int j = (column - 1); j <= (int)(column + 1); j++) {
      if (i == (int)row && j == (int)column) {
        continue;
      }
      if (i < 0 || j < 0 || i >= (int)(rows_) || j >= (int)(columns_)) {
        count++;
      } else {
        count += matrix_.at(i).at(j);
      }
    }
  }
  return count;
}
}  // namespace s21
