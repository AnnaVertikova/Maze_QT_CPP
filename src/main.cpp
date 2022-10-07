#include <QApplication>

#include "view/view_maze.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  s21::MazeView maze(&controller);
  s21::CaveView cave(&controller);
  maze.setWindowTitle("Maze");
  maze.show();
  return app.exec();
}
