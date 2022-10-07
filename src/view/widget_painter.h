#ifndef WIDGET_PAINTER_H
#define WIDGET_PAINTER_H

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <vector>

#include "controller/controller.h"
#include "model/model.h"

namespace s21 {
using Path = std::vector<std::pair<size_t, size_t>>;
class WidgetPainter : public QWidget {
  Q_OBJECT

 public:
  explicit WidgetPainter(QWidget *parent = nullptr);
  void SetController(s21::Controller *ctr) { controller_ = ctr; }

  void DrawMaze();
  void DrawCave();
  void ClearPath();
  void Clear();

 protected:
  void paintEvent(QPaintEvent *) override;
  void mousePressEvent(QMouseEvent *event) override;

 private:
  s21::Controller *controller_;
  QImage map_image_;
  QImage path_image_;
  QImage start_image_;
  QPoint start_;
  QPoint finish_;
  double horizontal_step_;
  double vertical_step_;
  double cell_hight_;
  double cell_length_;
  int x_finish_;
  int y_finish_;

  void ClearImage(QImage &image);

  void CalculateHorizontalStep();
  void CalculateVerticalStep();
  void DrawVerticalWalls(QPainter *painter);
  void DrawHorizontalWalls(QPainter *painter);

  void CalculateCellLength();
  void CalculateCellHight();
  void DrawCells(QPainter *painter);

  void ResetPoints();
  void LeftButtonEvent(QMouseEvent *event, QPainter *painter);
  void RightButtonEvent(QMouseEvent *event, QPainter *painter);
  int GetXPoint(QMouseEvent *event);
  int GetYPoint(QMouseEvent *event);
  void DrawPath(QPainter *painter, Path path);
};
}  //  namespace s21

#endif  // WIDGET_PAINTER_H
