#ifndef SRC_VIEW_CAVE_H_
#define SRC_VIEW_CAVE_H_

#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QWidget>

#include "controller/controller.h"
#include "view/widget_painter.h"

namespace Ui {
class Cave;
}

namespace s21 {
class CaveView : public QWidget {
  Q_OBJECT

 public:
  explicit CaveView(QWidget *parent = nullptr);
  explicit CaveView(s21::Controller *controller);
  ~CaveView();

  void ShowCaveView();

 private:
  Ui::Cave *ui;
  s21::Controller *controller_;
  QString filepath_;
  QTimer *timer_;

  void ShowErrorMessage();
  void ClearWidget();
  void Rendering();

 signals:
  void ShowMaze();

 private slots:
  void on_pushButton_load_cave_clicked();
  void on_pushButton_generate_cave_clicked();
  void on_pushButton_startRendering_clicked();
  void on_pushButton_clear_clicked();
  void on_radioButton_change_mode_maze_clicked();
};
}  //  namespace s21

#endif  // SRC_VIEW_CAVE_H_
