// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef MAIN_WINDOW_HH
#define MAIN_WINDOW_HH

#include <QMainWindow>

#include "bezier.hh"
#include "bezier_object.hh"

class BezierWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  MainWindow();

signals:
  void view_graph_changed(bool visible);
  void view_cp_convex_hull_changed(bool visible);
  void view_cp_bounding_box_changed(bool visible);
  void view_bezier_bounding_box_changed(bool visible);

  void view_params_changed(bool visible);

private slots:
  void on_about();

  void on_cut();
  void on_copy();
  void on_paste();
  void on_select_all();

  void on_view_graph_changed();
  void on_view_cp_convex_hull_changed();
  void on_view_cp_bounding_box_changed();
  void on_view_bezier_bounding_box_changed();

  void on_view_params_changed();

protected:
  void closeEvent(QCloseEvent* event) override;

private:
  Bezier b;
  BezierObject bezier;
  BezierWidget* bezier_widget;

  QMenu* fileMenu;
  QMenu* editMenu;
  QMenu* viewMenu;

  QAction* view_graph_action;
  QAction* view_cp_convex_hull_action;
  QAction* view_cp_bounding_box_action;
  QAction* view_bezier_bounding_box_action;

  QAction* view_params_action;

  void create_file_menu();
  void create_edit_menu();
  void create_view_menu();
};

#endif // MAIN_WINDOW_HH
