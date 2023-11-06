// Copyright 2023 Eric Smith
// SPDX-License-Identifier: GPL-3.0-only

#include <QAction>
#include <QApplication>
#include <QLineEdit>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QTextEdit>

#include "cubic_bezier_widget.hh"
#include "main_window.hh"

MainWindow::MainWindow():
  bezier { Point(-60.0, -40.0),
	   Point(-60.0, -80.0),
	   Point( 60.0,  80.0),
	   Point( 60.0,  40.0) },
  cubic_bezier_widget(new CubicBezierWidget(bezier,
					    this)) // QWidget* parent
{
  setCentralWidget(cubic_bezier_widget);

  create_file_menu();
  create_edit_menu();
  create_view_menu();
}

    

void MainWindow::create_file_menu()
{
  fileMenu = menuBar()->addMenu(tr("&File"));

  QAction* aboutAction = fileMenu->addAction(tr("About cubic-bezier-bounding-box"));
  connect(aboutAction, &QAction::triggered,
	  this,        &MainWindow::on_about);

  (void) fileMenu->addSeparator();

  QAction* quitAction = fileMenu->addAction(tr("&Quit"));
  quitAction->setShortcuts(QKeySequence::Quit);
  connect(quitAction, &QAction::triggered, this, &MainWindow::close);
}


void MainWindow::create_edit_menu()
{
  editMenu = menuBar()->addMenu(tr("&Edit"));

  QAction* cutAction = editMenu->addAction(tr("Cu&t"));
  cutAction->setShortcuts(QKeySequence::Cut);
  cutAction->setStatusTip(tr("Cut the selection to the clipboard"));
  connect(cutAction, &QAction::triggered, this, &MainWindow::on_cut);

  QAction* copyAction = editMenu->addAction(tr("&Copy"));
  copyAction->setShortcuts(QKeySequence::Copy);
  copyAction->setStatusTip(tr("Copy the selection to the clipboard"));
  connect(copyAction, &QAction::triggered, this, &MainWindow::on_copy);

  QAction* pasteAction = editMenu->addAction(tr("&Paste"));
  pasteAction->setShortcuts(QKeySequence::Paste);
  pasteAction->setStatusTip(tr("Paste the clipboard into the selection"));
  connect(pasteAction, &QAction::triggered, this, &MainWindow::on_paste);

  (void) editMenu->addSeparator();

  QAction* selectAllAction = editMenu->addAction(tr("Select &All"));
  selectAllAction->setShortcuts(QKeySequence::SelectAll);
  selectAllAction->setStatusTip(tr("Select all"));
  connect(selectAllAction, &QAction::triggered, this, &MainWindow::on_select_all);
}


void MainWindow::create_view_menu()
{
  viewMenu = menuBar()->addMenu(tr("&View"));

  view_graph_action = viewMenu->addAction(tr("Graph"));
  view_graph_action->setCheckable(true);
  view_graph_action->setChecked(true);
  view_graph_action->setStatusTip(tr("Toggle viewing of the Bezier curve graphs"));
  connect(view_graph_action,   &QAction::triggered,
	  this,                &MainWindow::on_view_graph_changed);
  connect(this,                &MainWindow::view_graph_changed,
	  cubic_bezier_widget, &CubicBezierWidget::on_view_graph_changed);

  (void) viewMenu->addSeparator();

  view_params_action = viewMenu->addAction(tr("Coordinats"));
  view_params_action->setCheckable(true);
  view_params_action->setChecked(true);
  view_params_action->setStatusTip(tr("Toggle viewing of the Bezier curve control point coordinates"));
  connect(view_params_action,  &QAction::triggered,
	  this,                &MainWindow::on_view_params_changed);
  connect(this,                &MainWindow::view_params_changed,
	  cubic_bezier_widget, &CubicBezierWidget::on_view_params_changed);
}


void MainWindow::on_view_graph_changed()
{
  std::cout << "MainWindow::on_view_graph_changed()\n";
  emit view_graph_changed(view_graph_action->isChecked());
}

void MainWindow::on_view_params_changed()
{
  std::cout << "MainWindow::on_view_params_changed()\n";
  emit view_params_changed(view_params_action->isChecked());
}


void MainWindow::closeEvent(QCloseEvent* event)
{
}

void MainWindow::on_about()
{
  QMessageBox::about(this,
		     tr("About cubic-bezier-bounding-box"),
		     tr("A program to demonstrate computation of a bounding box for a cubic bezier curve."));
}


void MainWindow::on_cut()
{
  // This is utterly insane, but Qt apparently doesn't provide any better
  // means to delegate standard edit menu items to the focused widget.
  QWidget* widget = QApplication::focusWidget();
  if (! widget)
    return;

  QLineEdit* line_edit = dynamic_cast<QLineEdit*>(widget);
  if (line_edit)
  {
    // The following should normally be emitted as a signal, not a direct
    // method call. However, we have to emit the signal to only the focused
    // object, so we can't keep connections open permanently. Rather than
    // constantly connecting and disconnecting, we could use
    // QMetaObject::invokeMethod() with Qt::QueuedConnection or
    // Qt::QAutoConnection.
    // However, since this is for activation of a menu item or keyboard
    // shortcut, we should already be in the GUI thread, so callint the
    // widget directly should be OK.
    // See:
    //   https://stackoverflow.com/questions/3297456/invoke-slot-method-without-connection
    // and the QMetaObject docuemntation.
    line_edit->cut();
    return;
  }

  QTextEdit* text_edit = dynamic_cast<QTextEdit*>(widget);
  if (text_edit)
  {
    text_edit->cut();
    return;
  }
}

void MainWindow::on_copy()
{
  // This is utterly insane, but Qt apparently doesn't provide any better
  // means to delegate standard edit menu items to the focused widget.
  QWidget* widget = QApplication::focusWidget();
  if (! widget)
    return;

  QLineEdit* line_edit = dynamic_cast<QLineEdit*>(widget);
  if (line_edit)
  {
    // See comments in the cut method above.
    line_edit->copy();
    return;
  }

  QTextEdit* text_edit = dynamic_cast<QTextEdit*>(widget);
  if (text_edit)
  {
    text_edit->copy();
    return;
  }
}

void MainWindow::on_paste()
{
  // This is utterly insane, but Qt apparently doesn't provide any better
  // means to delegate standard edit menu items to the focused widget.
  QWidget* widget = QApplication::focusWidget();
  if (! widget)
    return;

  QLineEdit* line_edit = dynamic_cast<QLineEdit*>(widget);
  if (line_edit)
  {
    // See comments in the cut method above.
    line_edit->paste();
    return;
  }

  QTextEdit* text_edit = dynamic_cast<QTextEdit*>(widget);
  if (text_edit)
  {
    text_edit->paste();
    return;
  }
}

void MainWindow::on_select_all()
{
  // This is utterly insane, but Qt apparently doesn't provide any better
  // means to delegate standard edit menu items to the focused widget.
  QWidget* widget = QApplication::focusWidget();
  if (! widget)
    return;

  QLineEdit* line_edit = dynamic_cast<QLineEdit*>(widget);
  if (line_edit)
  {
    // See comments in the cut method above.
    line_edit->selectAll();
    return;
  }

  QTextEdit* text_edit = dynamic_cast<QTextEdit*>(widget);
  if (text_edit)
  {
    text_edit->selectAll();
    return;
  }
}
