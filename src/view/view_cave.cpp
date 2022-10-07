#include "view_cave.h"

#include "ui_view_cave.h"

namespace s21 {
CaveView::CaveView(QWidget *parent) : QWidget(parent), ui(new Ui::Cave) {
  ui->setupUi(this);
  filepath_ = nullptr;
  timer_ = new QTimer(this);

  connect(timer_, &QTimer::timeout, this, &CaveView::Rendering);
  ui->radioButton_change_mode_cave->setChecked(true);
}

CaveView::CaveView(s21::Controller *controller) : CaveView() {
  controller_ = controller;
  ui->widget->SetController(controller_);
}

CaveView::~CaveView() {
  delete ui;
  delete timer_;
}

void CaveView::ShowCaveView() {
  show();
  ui->radioButton_change_mode_cave->setChecked(true);
}

void CaveView::on_pushButton_load_cave_clicked() {
  if ((filepath_ = QFileDialog::getOpenFileName(0, "", QDir::homePath(),
                                                "*.txt")) != nullptr) {
    timer_->stop();
    controller_->LoadCaveFromFile(filepath_.toStdString());
    if (controller_->GetError() == ErrorType::WITHOUT_ERRORS) {
      ClearWidget();
      ui->widget->DrawCave();
    } else {
      ShowErrorMessage();
    }
  }
}

void CaveView::on_pushButton_generate_cave_clicked() {
  emit ui->pushButton_clear->clicked();
  timer_->stop();
  controller_->GenerateCave(ui->spinBox_cave_rows->value(),
                            ui->spinBox_cave_columns->value(),
                            (ui->spinBox_chance->value() / 100.0));
  ui->spinBox_speed->setValue(0);
  ui->widget->DrawCave();
}

void CaveView::on_pushButton_startRendering_clicked() {
  if (ui->spinBox_speed->value()) {
    timer_->start(ui->spinBox_speed->value());
  } else {
    Rendering();
  }
}

void CaveView::on_pushButton_clear_clicked() {
  ClearWidget();
  controller_->ClearCave();
}

void CaveView::on_radioButton_change_mode_maze_clicked() {
  hide();
  emit ShowMaze();
}

void CaveView::ShowErrorMessage() {
  if (controller_->GetError() == ErrorType::WRONG_FILENAME) {
    QMessageBox::warning(this, "Error", "Wrong filename.");
  } else if (controller_->GetError() == ErrorType::WRONG_DATA_FORMAT) {
    QMessageBox::warning(this, "Error", "Wrong file data.");
  } else if (controller_->GetError() == ErrorType::EMPTY_FILE) {
    QMessageBox::warning(this, "Error", "File is empty.");
  }
}

void CaveView::ClearWidget() { ui->widget->Clear(); }

void CaveView::Rendering() {
  controller_->RebuildCave(ui->spinBox_birth->value(),
                           ui->spinBox_death->value());
  ui->widget->DrawCave();
}
}  //  namespace s21
