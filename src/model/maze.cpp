#include "maze.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>

namespace s21 {
void Maze::SetVerticalWalls(const Matrix &vert) { vertical_ = vert; }

void Maze::SetHorizontalWalls(const Matrix &horiz) { horizontal_ = horiz; }

void Maze::SetRows(size_t rows) { rows_ = rows; }

void Maze::SetColumns(size_t columns) { columns_ = columns; }

Matrix &Maze::GetVerticalWalls() { return vertical_; }

Matrix &Maze::GetHorizontalWalls() { return horizontal_; }

size_t Maze::GetRows() { return rows_; }

size_t Maze::GetColumns() { return columns_; }

void Maze::Generate() {
  InitGroups();
  FillGroup();
  for (size_t i = 0; i < rows_; i++) {
    AddVerticalWall();
    if (i != rows_ - 1) {
      AddHorizontalWall();
    } else {
      std::vector<bool> last(columns_, 1);
      horizontal_.push_back(last);
      LastVerticalWall(vertical_.at(i));
    }
    ReGroup(horizontal_.at(i));
    FillGroup();
  }
}

void Maze::Save(const std::string &filepath) {
  std::ofstream myfile(filepath);
  if (myfile.is_open()) {
    myfile << rows_ << " ";
    myfile << columns_ << "\n";
    for (auto &val : vertical_) {
      for (auto val2 : val) {
        myfile << val2 << " ";
      }
      myfile << "\n";
    }
    myfile << "\n";
    for (auto &val : horizontal_) {
      for (auto val2 : val) {
        myfile << val2 << " ";
      }
      myfile << "\n";
    }
    myfile.close();
  }
}

void Maze::Clear() {
  rows_ = 0;
  columns_ = 0;
  vertical_.clear();
  horizontal_.clear();
  groups_.clear();
}

void Maze::InitGroups() {
  std::pair<int, bool> init{-1, 1};
  group_counter_ = 1;
  for (size_t i = 0; i < columns_; i++) {
    groups_.push_back(init);
  }
}

void Maze::FillGroup() {
  for (size_t i = 0; i < columns_; i++) {
    if (groups_.at(i).first == -1) {
      groups_.at(i).first = group_counter_;
      group_counter_++;
    }
  }
}

void Maze::AddVerticalWall() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, 1);
  std::vector<bool> vert(columns_, 0);
  for (size_t i = 0; i < columns_ - 1; i++) {
    if (groups_.at(i).first == groups_.at(i + 1).first) {
      vert.at(i) = true;
    } else if (distr(gen)) {
      vert.at(i) = true;
    } else {
      UnionGroup(groups_.at(i).first, groups_.at(i + 1).first);
    }
  }
  vert.at(columns_ - 1) = true;
  vertical_.push_back(vert);
}

void Maze::AddHorizontalWall() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, 1);
  std::vector<bool> horiz(columns_, 0);
  for (size_t i = 0; i < columns_; i++) {
    if (GroupSize(groups_.at(i).first) != 1) {
      if (distr(gen)) {
        horiz.at(i) = true;
        groups_.at(i).second = false;
        if (!HaveExit(groups_.at(i).first)) {
          horiz.at(i) = false;
          groups_.at(i).second = true;
        }
      }
    }
  }
  horizontal_.push_back(horiz);
}

void Maze::LastVerticalWall(std::vector<bool> vert) {
  for (size_t i = 0; i < columns_ - 1; i++) {
    if (groups_.at(i).first != groups_.at(i + 1).first) {
      vert.at(i) = false;
      UnionGroup(groups_.at(i).first, groups_.at(i + 1).first);
    }
  }
  vertical_.pop_back();
  vertical_.push_back(vert);
}

void Maze::ReGroup(std::vector<bool> horiz) {
  for (size_t i = 0; i < columns_; i++) {
    if (horiz.at(i)) {
      groups_.at(i).first = -1;
      groups_.at(i).second = true;
    }
  }
}

void Maze::UnionGroup(int new_group, int old_group) {
  for (size_t i = 0; i < columns_; i++) {
    if (groups_.at(i).first == old_group) {
      groups_.at(i).first = new_group;
    }
  }
}

size_t Maze::GroupSize(int group) {
  size_t size = 0;
  for (size_t i = 0; i < columns_; i++) {
    if (groups_.at(i).first == group) {
      size++;
    }
  }
  return size;
}

bool Maze::HaveExit(int group) {
  bool res = false;
  for (size_t i = 0; i < columns_; i++) {
    if (groups_.at(i).first == group) {
      if (groups_.at(i).second) {
        res = true;
      }
    }
  }
  return res;
}
}  // namespace s21
