#ifndef SRC_VIEW_MAZE_H_
#define SRC_VIEW_MAZE_H_

#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>

#include "controller/controller.h"
#include "view/view_cave.h"
#include "view/widget_painter.h"

namespace Ui {
class Maze;
}

namespace s21 {
class MazeView : public QWidget {
  Q_OBJECT

 public:
  explicit MazeView(QWidget *parent = nullptr);
  explicit MazeView(s21::Controller *controller);
  ~MazeView();

 private:
  Ui::Maze *ui;
  s21::Controller *controller_;
  QString filepath_;
  s21::CaveView *cave_view_;

  void ShowMazeView();
  void ShowErrorMessage();
  void ClearWidget();

 private slots:
  void on_pushButton_load_maze_clicked();
  void on_pushButton_generate_maze_clicked();
  void on_pushButton_save_maze_clicked();
  void on_pushButton_clear_clicked();
  void on_radioButton_change_mode_cave_clicked();
  void on_pushButton_clear_2_clicked();
};
}  //  namespace s21

#endif  // SRC_VIEW_MAZE_H_
