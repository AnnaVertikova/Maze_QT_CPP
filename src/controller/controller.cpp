#include "controller.h"

namespace s21 {
Controller::Controller(const Controller& other) {
  if (this != &other) *this = other;
}

Controller::Controller(Controller&& other) {
  if (this != &other) *this = std::move(other);
}

Controller& Controller::operator=(const Controller& other) {
  if (this != &other) model_ = other.model_;
  return *this;
}

Controller& Controller::operator=(Controller&& other) {
  if (this != &other) {
    std::swap(this->model_, other.model_);
  }
  return *this;
}

Matrix& Controller::GetMazeVerticalWallsMatrix() {
  return model_.GetMazeVerticalWallsMatrix();
}

Matrix& Controller::GetMazeHorizontalWallsMatrix() {
  return model_.GetMazeHorizontalWallsMatrix();
}

size_t Controller::GetMazeRows() { return model_.GetMazeRows(); }

size_t Controller::GetMazeColumns() { return model_.GetMazeColumns(); }

Matrix& Controller::GetCaveMatrix() { return model_.GetCaveMatrix(); }

size_t Controller::GetCaveRows() { return model_.GetCaveRows(); }

size_t Controller::GetCaveColumns() { return model_.GetCaveColumns(); }

ErrorType Controller::GetError() { return model_.GetParser().GetError(); }

bool Controller::LoadMazeFromFile(const std::string& path) {
  bool result = model_.GetParser().ParseMaze(path);
  if (result) {
    model_.LoadMaze();
  }
  return result;
}

void Controller::GenerateMaze(size_t rows, size_t columns) {
  model_.GenerateMaze(rows, columns);
}

void Controller::SaveMaze(const std::string& path) { model_.SaveMaze(path); }

Path Controller::FindPath(Point start, Point finish) {
  return model_.FindMazePath(start, finish);
}

void Controller::ClearMaze() { model_.ClearMaze(); }

bool Controller::LoadCaveFromFile(const std::string& path) {
  bool result = model_.GetParser().ParseCave(path);
  if (result) {
    model_.LoadCave();
  }
  return result;
}

void Controller::GenerateCave(size_t rows, size_t columns, double chance) {
  model_.GenerateCave(rows, columns, chance);
}

void Controller::RebuildCave(size_t death_limit, size_t birth_limit) {
  model_.RebuildCave(death_limit, birth_limit);
}

void Controller::ClearCave() { model_.ClearCave(); }
}  // namespace s21
