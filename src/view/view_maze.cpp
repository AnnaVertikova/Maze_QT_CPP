#include "view_maze.h"

#include "ui_view_maze.h"

namespace s21 {
MazeView::MazeView(QWidget *parent) : QWidget(parent), ui(new Ui::Maze) {
  ui->setupUi(this);
  filepath_ = nullptr;
}

MazeView::MazeView(s21::Controller *controller) : MazeView() {
  controller_ = controller;
  ui->widget->SetController(controller_);
  cave_view_ = new CaveView(controller_);
  connect(cave_view_, &CaveView::ShowMaze, this, &MazeView::ShowMazeView);
  ui->radioButton_change_mode_maze->setChecked(true);
}

MazeView::~MazeView() { delete ui; }

void MazeView::on_pushButton_load_maze_clicked() {
  if ((filepath_ = QFileDialog::getOpenFileName(0, "", QDir::homePath(),
                                                "*.txt")) != nullptr) {
    controller_->LoadMazeFromFile(filepath_.toStdString());
    if (controller_->GetError() == ErrorType::WITHOUT_ERRORS) {
      ClearWidget();
      ui->widget->DrawMaze();
    } else {
      ShowErrorMessage();
    }
  }
}

void MazeView::on_pushButton_generate_maze_clicked() {
  emit ui->pushButton_clear->clicked();
  controller_->GenerateMaze(ui->spinBox_maze_rows->value(),
                            ui->spinBox_maze_columns->value());
  ui->widget->DrawMaze();
}

void MazeView::on_pushButton_save_maze_clicked() {
  QString filename = QFileDialog::getSaveFileName(
      this, tr("Save File"), QDir::homePath() + "/maze.txt", tr("TXT (*.txt)"));
  controller_->SaveMaze(filename.toStdString());
}

void MazeView::on_pushButton_clear_clicked() {
  ClearWidget();
  controller_->ClearMaze();
}

void MazeView::on_radioButton_change_mode_cave_clicked() {
  hide();
  cave_view_->move(this->pos());
  cave_view_->ShowCaveView();
}

void MazeView::ShowMazeView() {
  show();
  this->move(cave_view_->pos());
  ui->radioButton_change_mode_maze->setChecked(true);
}

void MazeView::ShowErrorMessage() {
  if (controller_->GetError() == ErrorType::WRONG_FILENAME) {
    QMessageBox::warning(this, "Error", "Wrong filename.");
  } else if (controller_->GetError() == ErrorType::WRONG_DATA_FORMAT) {
    QMessageBox::warning(this, "Error", "Wrong file data.");
  } else if (controller_->GetError() == ErrorType::EMPTY_FILE) {
    QMessageBox::warning(this, "Error", "File is empty.");
  }
}

void MazeView::ClearWidget() { ui->widget->Clear(); }

void MazeView::on_pushButton_clear_2_clicked() { ui->widget->ClearPath(); }

}  //  namespace s21
