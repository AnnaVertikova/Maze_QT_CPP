#include "model.h"

namespace s21 {
Matrix& Model::GetMazeVerticalWallsMatrix() { return maze_.GetVerticalWalls(); }

Matrix& Model::GetMazeHorizontalWallsMatrix() {
  return maze_.GetHorizontalWalls();
}

size_t Model::GetMazeRows() { return maze_.GetRows(); }

size_t Model::GetMazeColumns() { return maze_.GetColumns(); }

Matrix& Model::GetCaveMatrix() { return cave_.GetMatrix(); }

size_t Model::GetCaveRows() { return cave_.GetRows(); }

size_t Model::GetCaveColumns() { return cave_.GetColumns(); }

Parser& Model::GetParser() { return parser_; }

void Model::LoadMaze() {
  maze_.Clear();
  LoadMazeHorizontalWallsMatrix();
  LoadMazeVerticalWallsMatrix();
  LoadMazeRows();
  LoadMazeColumns();
}

void Model::LoadMazeVerticalWallsMatrix() {
  maze_.SetVerticalWalls(parser_.GetMazeVerticalWalls());
}

void Model::LoadMazeHorizontalWallsMatrix() {
  maze_.SetHorizontalWalls(parser_.GetMazeHorizontalWalls());
}

void Model::LoadMazeRows() { maze_.SetRows(parser_.GetRows()); }

void Model::LoadMazeColumns() { maze_.SetColumns(parser_.GetColumns()); }

void Model::GenerateMaze(size_t rows, size_t columns) {
  maze_.Clear();
  maze_.SetRows(rows);
  maze_.SetColumns(columns);
  maze_.Generate();
}

void Model::SaveMaze(const std::string& filepath) { maze_.Save(filepath); }

Path Model::FindMazePath(Point start, Point finish) {
  path_finder_.SetMaze(maze_);
  return path_finder_.FindPath(start, finish);
}

void Model::ClearMaze() { maze_.Clear(); }

void Model::LoadCave() {
  cave_.Clear();
  LoadCaveMatrix();
  LoadCaveRows();
  LoadCaveColumns();
}

void Model::LoadCaveMatrix() { cave_.SetMatrix(parser_.GetCaveMatrix()); }

void Model::LoadCaveRows() { cave_.SetRows(parser_.GetRows()); }

void Model::LoadCaveColumns() { cave_.SetColumns(parser_.GetColumns()); }

void Model::GenerateCave(size_t rows, size_t columns, double chance) {
  cave_.Clear();
  cave_.SetRows(rows);
  cave_.SetColumns(columns);
  cave_.GenerateCave(chance);
}

void Model::RebuildCave(size_t death_limit, size_t birth_limit) {
  cave_.RebuildCave(death_limit, birth_limit);
}
void Model::ClearCave() { cave_.Clear(); }
}  // namespace s21
