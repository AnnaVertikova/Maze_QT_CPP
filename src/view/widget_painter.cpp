#include "widget_painter.h"

namespace s21 {
WidgetPainter::WidgetPainter(QWidget *parent)
    : QWidget(parent),
      map_image_(QSize(500, 500), QImage::Format_ARGB32),
      path_image_(QSize(500, 500), QImage::Format_ARGB32),
      start_image_(QSize(500, 500), QImage::Format_ARGB32) {
  ClearImage(map_image_);
  ClearImage(path_image_);
}

void WidgetPainter::DrawMaze() {
  Clear();
  QPainter painter(&map_image_);
  painter.setPen(
      QPen(Qt::darkGray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  CalculateHorizontalStep();
  CalculateVerticalStep();
  DrawVerticalWalls(&painter);
  DrawHorizontalWalls(&painter);
  update();
}

void WidgetPainter::DrawCave() {
  ClearImage(map_image_);
  QPainter painter(&map_image_);
  painter.setPen(
      QPen(Qt::darkGray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  CalculateCellLength();
  CalculateCellHight();
  DrawCells(&painter);
  update();
}

void WidgetPainter::ClearPath() {
  ClearImage(start_image_);
  ClearImage(path_image_);
  start_.setX(0);
  start_.setY(0);
  finish_.setX(0);
  finish_.setY(0);
}

void WidgetPainter::Clear() {
  ClearImage(map_image_);
  ClearPath();
}

void WidgetPainter::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setPen(
      QPen(Qt::darkGray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter.drawRect(1, 1, 498, 498);
  painter.drawImage(0, 0, map_image_);
  painter.drawImage(0, 0, path_image_);
  painter.drawImage(0, 0, start_image_);
  this->update();
}

void WidgetPainter::mousePressEvent(QMouseEvent *event) {
  ResetPoints();
  if (controller_->GetMazeHorizontalWallsMatrix().size() != 0) {
    QPainter painter(&path_image_);
    QPainter start_painter(&start_image_);
    LeftButtonEvent(event, &start_painter);
    RightButtonEvent(event, &painter);
  }
}

void WidgetPainter::ClearImage(QImage &image) {
  image.fill(QColor(0, 0, 0, 0));
}

void WidgetPainter::CalculateHorizontalStep() {
  horizontal_step_ = 499.0 / controller_->GetMazeColumns();
}

void WidgetPainter::CalculateVerticalStep() {
  vertical_step_ = 499.0 / controller_->GetMazeRows();
}

void WidgetPainter::DrawVerticalWalls(QPainter *painter) {
  std::vector<std::vector<bool>> vertical =
      controller_->GetMazeVerticalWallsMatrix();
  double y = 499.0;
  while (vertical.size()) {
    double x = 499.0;
    while (vertical.back().size()) {
      if (vertical.back().back() == 1) {
        painter->drawLine(x, y, x, (y - vertical_step_));
      }
      x -= horizontal_step_;
      vertical.back().pop_back();
    }
    y -= vertical_step_;
    vertical.pop_back();
  }
}

void WidgetPainter::DrawHorizontalWalls(QPainter *painter) {
  std::vector<std::vector<bool>> horizontal =
      controller_->GetMazeHorizontalWallsMatrix();
  double y = 499.0;
  while (horizontal.size()) {
    double x = 499.0;
    while (horizontal.back().size()) {
      if (horizontal.back().back() == 1) {
        painter->drawLine(x, y, x - horizontal_step_, y);
      }
      x -= horizontal_step_;
      horizontal.back().pop_back();
    }
    y -= vertical_step_;
    horizontal.pop_back();
  }
}

void WidgetPainter::CalculateCellLength() {
  cell_length_ = 499.0 / controller_->GetCaveColumns();
}

void WidgetPainter::CalculateCellHight() {
  cell_hight_ = 499.0 / controller_->GetCaveRows();
}

void WidgetPainter::DrawCells(QPainter *painter) {
  std::vector<std::vector<bool>> cells = controller_->GetCaveMatrix();
  painter->setBrush(Qt::darkGray);
  double y = 499.0 - cell_hight_;
  while (cells.size()) {
    double x = 499.0 - cell_length_;
    while (cells.back().size()) {
      if (cells.back().back() == 1) {
        painter->drawRect(x, y, cell_length_, cell_hight_);
      }
      x -= cell_length_;
      cells.back().pop_back();
    }
    y -= cell_hight_;
    cells.pop_back();
  }
}

void WidgetPainter::ResetPoints() {
  if (!start_.isNull() && !finish_.isNull()) {
    ClearImage(path_image_);
    finish_.setX(0);
    finish_.setY(0);
  }
}

void WidgetPainter::LeftButtonEvent(QMouseEvent *event, QPainter *painter) {
  int x = GetXPoint(event);
  int y = GetYPoint(event);
  int w = horizontal_step_ - 2;
  int h = vertical_step_ - 2;
  if (event->buttons() == Qt::LeftButton) {
    ClearImage(start_image_);
    ClearImage(path_image_);
    painter->setBrush(QColor(170, 255, 0));
    painter->drawRect(x, y, w, h);
    start_ = event->pos();
    x_finish_ = x;
    y_finish_ = y;
  }
}

void WidgetPainter::RightButtonEvent(QMouseEvent *event, QPainter *painter) {
  int x = GetXPoint(event);
  int y = GetYPoint(event);
  int w = horizontal_step_ - 2;
  int h = vertical_step_ - 2;
  if (event->buttons() == Qt::RightButton && !start_.isNull() &&
      !(x_finish_ == x && y_finish_ == y)) {
    painter->setBrush(QColor(255, 49, 49));
    painter->drawRect(x, y, w, h);
    finish_ = event->pos();
    std::pair<int, int> start;
    start.first = start_.y() / vertical_step_;
    start.second = start_.x() / horizontal_step_;
    std::pair<int, int> finish;
    finish.first = finish_.y() / vertical_step_;
    finish.second = finish_.x() / horizontal_step_;
    DrawPath(painter, controller_->FindPath(start, finish));
  }
}

int WidgetPainter::GetXPoint(QMouseEvent *event) {
  int x = event->pos().x() / horizontal_step_;
  x *= horizontal_step_;
  x += 1;
  return x;
}

int WidgetPainter::GetYPoint(QMouseEvent *event) {
  int y = event->pos().y() / vertical_step_;
  y *= vertical_step_;
  y += 1;
  return y;
}

void WidgetPainter::DrawPath(QPainter *painter, Path path) {
  painter->setPen(QPen(QColor(253, 218, 13), 2, Qt::SolidLine, Qt::RoundCap,
                       Qt::RoundJoin));
  if (!path.empty()) {
    for (size_t i = 0; i < path.size() - 1; i++) {
      int y1 = path.at(i).first * vertical_step_ + vertical_step_ / 2;
      int y2 = path.at(i + 1).first * vertical_step_ + vertical_step_ / 2;
      int x1 = path.at(i).second * horizontal_step_ + horizontal_step_ / 2;
      int x2 = path.at(i + 1).second * horizontal_step_ + horizontal_step_ / 2;
      painter->drawLine(x1, y1, x2, y2);
    }
  }
}
}  //  namespace s21
