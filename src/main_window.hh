// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#ifndef MAIN_WINDOW_HH
#define MAIN_WINDOW_HH

#include <QMainWindow>

#include "cubic_bezier.hh"

class CentralWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  MainWindow();

protected:
  void closeEvent(QCloseEvent* event) override;

private slots:
  void about();

  void cut();
  void copy();
  void paste();
  void selectAll();

private:
  CubicBezier cb;
  CentralWidget* central_widget;

  void create_file_menu();
  void create_edit_menu();
};

#endif // MAIN_WINDOW_HH
