#include "pathfinder.h"

namespace s21 {
void PathFinder::SetMaze(const Maze &maze) { maze_ = maze; }

Path PathFinder::FindPath(const Point &start, const Point &finish) {
  Path res;
  InitWayMatrix();
  way_.at(start.first).at(start.second) = 1;
  way_.at(finish.first).at(finish.second) = -1;
  while (!find_finish_ &&
         (size_t)way_counter_ < maze_.GetRows() * maze_.GetColumns()) {
    way_counter_++;
    NewPathStep();
  }
  if (find_finish_) {
    ResultingWayMatrix(&res, finish.first, finish.second);
  }
  return res;
}

void PathFinder::InitWayMatrix() {
  way_.clear();
  way_counter_ = 1;
  find_finish_ = 0;
  std::vector<int> tmp(maze_.GetColumns(), 0);
  way_.assign(maze_.GetRows(), tmp);
}

void PathFinder::NewPathStep() {
  size_t rows = maze_.GetRows();
  size_t columns = maze_.GetColumns();
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      if (way_.at(i).at(j) == way_counter_ - 1) {
        MoveUp(i, j);
        MoveDown(i, j);
        MoveLeft(i, j);
        MoveRight(i, j);
      }
    }
  }
}

void PathFinder::ResultingWayMatrix(Path *res, size_t row_pos,
                                    size_t column_pos) {
  std::pair first{row_pos, column_pos};
  res->push_back(first);
  while (way_counter_) {
    way_counter_--;
    CheckUp(res, &row_pos, &column_pos);
    CheckDown(res, &row_pos, &column_pos);
    CheckLeft(res, &row_pos, &column_pos);
    CheckRight(res, &row_pos, &column_pos);
  }
}

void PathFinder::MoveUp(size_t row_pos, size_t column_pos) {
  if (row_pos) {
    Matrix horizontal = maze_.GetHorizontalWalls();
    if (!horizontal.at(row_pos - 1).at(column_pos)) {
      if (way_.at(row_pos - 1).at(column_pos) == -1) {
        find_finish_ = true;
      } else if (way_.at(row_pos - 1).at(column_pos) == 0) {
        way_.at(row_pos - 1).at(column_pos) = way_counter_;
      }
    }
  }
}

void PathFinder::MoveDown(size_t row_pos, size_t column_pos) {
  if (row_pos < maze_.GetRows() - 1) {
    Matrix horizontal = maze_.GetHorizontalWalls();
    if (!horizontal.at(row_pos).at(column_pos)) {
      if (way_.at(row_pos + 1).at(column_pos) == -1) {
        find_finish_ = true;
      } else if (way_.at(row_pos + 1).at(column_pos) == 0) {
        way_.at(row_pos + 1).at(column_pos) = way_counter_;
      }
    }
  }
}

void PathFinder::MoveRight(size_t row_pos, size_t column_pos) {
  if (column_pos < maze_.GetColumns() - 1) {
    Matrix vertical = maze_.GetVerticalWalls();
    if (!vertical.at(row_pos).at(column_pos)) {
      if (way_.at(row_pos).at(column_pos + 1) == -1) {
        find_finish_ = true;
      } else if (way_.at(row_pos).at(column_pos + 1) == 0) {
        way_.at(row_pos).at(column_pos + 1) = way_counter_;
      }
    }
  }
}

void PathFinder::MoveLeft(size_t row_pos, size_t column_pos) {
  if (column_pos) {
    Matrix vertical = maze_.GetVerticalWalls();
    if (!vertical.at(row_pos).at(column_pos - 1)) {
      if (way_.at(row_pos).at(column_pos - 1) == -1) {
        find_finish_ = true;
      } else if (way_.at(row_pos).at(column_pos - 1) == 0) {
        way_.at(row_pos).at(column_pos - 1) = way_counter_;
      }
    }
  }
}

void PathFinder::CheckUp(Path *res, size_t *row_pos, size_t *column_pos) {
  if (*row_pos) {
    Matrix horizontal = maze_.GetHorizontalWalls();
    if (!horizontal.at(*row_pos - 1).at(*column_pos)) {
      if (way_.at(*row_pos - 1).at(*column_pos) == way_counter_) {
        *row_pos -= 1;
        std::pair<size_t, size_t> coord{*row_pos, *column_pos};
        res->push_back(coord);
      }
    }
  }
}

void PathFinder::CheckDown(Path *res, size_t *row_pos, size_t *column_pos) {
  if (*row_pos < maze_.GetRows() - 1) {
    Matrix horizontal = maze_.GetHorizontalWalls();
    if (!horizontal.at(*row_pos).at(*column_pos)) {
      if (way_.at(*row_pos + 1).at(*column_pos) == way_counter_) {
        *row_pos += 1;
        std::pair<size_t, size_t> coord{*row_pos, *column_pos};
        res->push_back(coord);
      }
    }
  }
}

void PathFinder::CheckRight(Path *res, size_t *row_pos, size_t *column_pos) {
  if (*column_pos < maze_.GetColumns() - 1) {
    Matrix vertical = maze_.GetVerticalWalls();
    if (!vertical.at(*row_pos).at(*column_pos)) {
      if (way_.at(*row_pos).at(*column_pos + 1) == way_counter_) {
        *column_pos += 1;
        std::pair<size_t, size_t> coord{*row_pos, *column_pos};
        res->push_back(coord);
      }
    }
  }
}

void PathFinder::CheckLeft(Path *res, size_t *row_pos, size_t *column_pos) {
  if (*column_pos) {
    Matrix vertical = maze_.GetVerticalWalls();
    if (!vertical.at(*row_pos).at(*column_pos - 1)) {
      if (way_.at(*row_pos).at(*column_pos - 1) == way_counter_) {
        *column_pos -= 1;
        std::pair<size_t, size_t> coord{*row_pos, *column_pos};
        res->push_back(coord);
      }
    }
  }
}
}  // namespace s21
