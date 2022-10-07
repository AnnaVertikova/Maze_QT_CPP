#include <gtest/gtest.h>

#include <cmath>
#include <filesystem>

#include "./controller/controller.h"
#include "./model/model.h"

TEST(controller, copy_constructor_maze) {
  std::string filename = "./datasets/maze_1.txt";
  s21::Model model;
  s21::Controller controller(&model);
  controller.LoadMazeFromFile(filename);
  s21::Controller controller_2 = controller;

  ASSERT_TRUE(controller_2.GetMazeRows() == controller.GetMazeRows());
}

TEST(controller, copy_constructor_cave) {
  std::string filename = "./datasets/cave_1.txt";
  s21::Model model;
  s21::Controller controller(&model);
  controller.LoadCaveFromFile(filename);
  s21::Controller controller_2 = controller;

  ASSERT_TRUE(controller_2.GetCaveRows() == controller.GetCaveRows());
}

TEST(controller, move_constructor_maze) {
  std::string filename = "./datasets/maze_1.txt";
  s21::Model model;
  s21::Controller controller(&model);
  controller.LoadMazeFromFile(filename);
  ASSERT_TRUE(controller.GetMazeRows() == 10);

  s21::Controller controller_2 = std::move(controller);
  ASSERT_TRUE(controller_2.GetMazeRows() == 10);
  ASSERT_TRUE(controller.GetMazeRows() == 0);
  ASSERT_FALSE(controller_2.GetMazeRows() == controller.GetMazeRows());
}

TEST(controller, move_constructor_cave) {
  std::string filename = "./datasets/cave_1.txt";
  s21::Model model;
  s21::Controller controller(&model);
  controller.LoadCaveFromFile(filename);
  ASSERT_TRUE(controller.GetCaveRows() == 10);

  s21::Controller controller_2 = std::move(controller);
  ASSERT_TRUE(controller_2.GetCaveRows() == 10);
  ASSERT_TRUE(controller.GetCaveRows() == 0);
  ASSERT_FALSE(controller_2.GetCaveRows() == controller.GetCaveRows());
}

TEST(controller, maze_bad_file_name) {
  std::string bad_filename = "./datasets/not_exist";
  s21::Model model;
  s21::Controller controller(&model);
  ASSERT_FALSE(controller.LoadMazeFromFile(bad_filename));
  ASSERT_EQ(controller.GetError(), ErrorType::WRONG_FILENAME);
}

TEST(controller, maze_empty_file) {
  std::string empty_file = "./datasets/empty.txt";
  s21::Model model;
  s21::Controller controller(&model);
  ASSERT_FALSE(controller.LoadMazeFromFile(empty_file));
  ASSERT_EQ(controller.GetError(), ErrorType::WRONG_DATA_FORMAT);
}

TEST(maze, load_maze_wrong_file_1) {
  std::string filename = "./datasets/cave_1.txt";
  s21::Model model;
  s21::Controller controller(&model);
  ASSERT_FALSE(controller.LoadMazeFromFile(filename));
  ASSERT_EQ(controller.GetError(), ErrorType::WRONG_DATA_FORMAT);
}

TEST(maze, load_maze_wrong_file_2) {
  std::string filename = "./datasets/maze_without_spaces.txt";
  s21::Model model;
  s21::Controller controller(&model);
  ASSERT_FALSE(controller.LoadMazeFromFile(filename));
  ASSERT_EQ(controller.GetError(), ErrorType::WRONG_DATA_FORMAT);
}

TEST(maze, load_maze_wrong_file_3) {
  std::string filename = "./datasets/maze_wrong matrixes.txt";
  s21::Model model;
  s21::Controller controller(&model);
  ASSERT_FALSE(controller.LoadMazeFromFile(filename));
  ASSERT_EQ(controller.GetError(), ErrorType::WRONG_DATA_FORMAT);
}

TEST(maze, load_maze) {
  std::string filename = "./datasets/maze_1.txt";
  s21::Model model;
  s21::Controller controller(&model);
  controller.LoadMazeFromFile(filename);

  ASSERT_EQ(controller.GetMazeVerticalWallsMatrix().at(0).at(0), 0);
  ASSERT_EQ(controller.GetMazeHorizontalWallsMatrix().at(0).at(0), 0);
  ASSERT_EQ(controller.GetMazeRows(), 10);
  ASSERT_EQ(controller.GetMazeColumns(), 10);
  ASSERT_EQ(controller.GetError(), ErrorType::WITHOUT_ERRORS);
}

TEST(maze, generate_maze) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.GenerateMaze(10, 10);

  ASSERT_EQ(controller.GetMazeRows(), 10);
  ASSERT_EQ(controller.GetMazeColumns(), 10);
}

TEST(maze, save_maze) {
  std::string filename = "./datasets/save_maze.txt";
  s21::Model model;
  s21::Controller controller(&model);
  controller.GenerateMaze(10, 10);
  controller.SaveMaze(filename);

  s21::Model model_2;
  s21::Controller controller_2(&model_2);
  controller_2.LoadMazeFromFile(filename);
  ASSERT_EQ(controller_2.GetMazeRows(), controller.GetMazeRows());
}

TEST(maze, find_path) {
  std::string filename = "./datasets/maze_1.txt";
  s21::Model model;
  s21::Controller controller(&model);
  controller.LoadMazeFromFile(filename);
  std::vector<std::pair<size_t, size_t>> path =
      controller.FindPath(std::pair(9, 9), std::pair(1, 1));
  ASSERT_EQ(path.at(0).first, 1);
  ASSERT_EQ(path.at(0).second, 1);
  ASSERT_EQ(path.size(), 51);
}

TEST(maze, clear_maze) {
  std::string filename = "./datasets/maze_1.txt";
  s21::Model model;
  s21::Controller controller(&model);
  controller.LoadMazeFromFile(filename);
  controller.ClearMaze();
  ASSERT_EQ(controller.GetMazeRows(), 0);
  ASSERT_EQ(controller.GetMazeColumns(), 0);
}

TEST(cave, load_cave) {
  std::string filename = "./datasets/cave_1.txt";
  s21::Model model;
  s21::Controller controller(&model);
  controller.LoadCaveFromFile(filename);

  ASSERT_EQ(controller.GetCaveMatrix().at(0).at(0), 1);
  ASSERT_EQ(controller.GetCaveRows(), 10);
  ASSERT_EQ(controller.GetCaveColumns(), 10);
  ASSERT_EQ(controller.GetError(), ErrorType::WITHOUT_ERRORS);
}

TEST(controller, cave_bad_file_name) {
  std::string bad_filename = "./datasets/not_exist";
  s21::Model model;
  s21::Controller controller(&model);
  ASSERT_FALSE(controller.LoadCaveFromFile(bad_filename));
  ASSERT_EQ(controller.GetError(), ErrorType::WRONG_FILENAME);
}

TEST(controller, cave_empty_file) {
  std::string empty_file = "./datasets/empty.txt";
  s21::Model model;
  s21::Controller controller(&model);
  ASSERT_FALSE(controller.LoadCaveFromFile(empty_file));
  ASSERT_EQ(controller.GetError(), ErrorType::WRONG_DATA_FORMAT);
}

TEST(cave, load_cave_wrong_file_1) {
  std::string filename = "./datasets/maze_1.txt";
  s21::Model model;
  s21::Controller controller(&model);
  ASSERT_FALSE(controller.LoadCaveFromFile(filename));
  ASSERT_EQ(controller.GetError(), ErrorType::WRONG_DATA_FORMAT);
}

TEST(cave, load_cave_wrong_file_2) {
  std::string filename = "./datasets/cave_without_spaces.txt";
  s21::Model model;
  s21::Controller controller(&model);
  ASSERT_FALSE(controller.LoadCaveFromFile(filename));
  ASSERT_EQ(controller.GetError(), ErrorType::WRONG_DATA_FORMAT);
}

TEST(cave, load_cave_wrong_file_3) {
  std::string filename = "./datasets/cave_wrong_matrix.txt";
  s21::Model model;
  s21::Controller controller(&model);
  ASSERT_FALSE(controller.LoadCaveFromFile(filename));
  ASSERT_EQ(controller.GetError(), ErrorType::WRONG_DATA_FORMAT);
}

TEST(cave, generate_cave) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.GenerateCave(10, 10, 1.2);

  ASSERT_EQ(controller.GetCaveRows(), 10);
  ASSERT_EQ(controller.GetCaveColumns(), 10);
}

TEST(cave, rebuild_cave) {
  std::string filename = "./datasets/cave_1.txt";
  s21::Model model;
  s21::Controller controller(&model);
  controller.LoadCaveFromFile(filename);
  controller.RebuildCave(2, 3);

  ASSERT_EQ(controller.GetCaveMatrix().at(0).at(0), 1);
  ASSERT_EQ(controller.GetCaveRows(), 10);
  ASSERT_EQ(controller.GetCaveColumns(), 10);
}

TEST(cave, rebuild_cave_2) {
  s21::Model model;
  s21::Controller controller(&model);
  controller.GenerateCave(10, 10, 0.2);
  controller.RebuildCave(2, 3);

  ASSERT_EQ(controller.GetCaveRows(), 10);
  ASSERT_EQ(controller.GetCaveColumns(), 10);
}

TEST(cave, clear_cave) {
  std::string filename = "./datasets/cave_1.txt";
  s21::Model model;
  s21::Controller controller(&model);
  controller.LoadCaveFromFile(filename);
  controller.ClearCave();
  ASSERT_EQ(controller.GetCaveRows(), 0);
  ASSERT_EQ(controller.GetCaveColumns(), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
