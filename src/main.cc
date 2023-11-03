// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QApplication>

#include "main_window.hh"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow* main_window = new MainWindow();

  main_window->show();
  return app.exec();
}
