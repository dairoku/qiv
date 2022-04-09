// =============================================================================
//  MainWindow.cpp
//
//  Written in 2022 by Dairoku Sekiguchi (sekiguchi at acm dot org)
//
//  To the extent possible under law, the author(s) have dedicated all copyright
//  and related and neighboring rights to this software to the public domain worldwide.
//  This software is distributed without any warranty.
//
//  You should have received a copy of the CC0 Public Domain Dedication along with
//  this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
// =============================================================================
/*!
  \file     MainWindow.cpp
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/23
*/

// Includes --------------------------------------------------------------------
#include "MainWindow.h"
#include "ImageWindow.h"

// -----------------------------------------------------------------------------
// MainWindow
// -----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  mUI.setupUi(this);
}

// -----------------------------------------------------------------------------
// on_action_Open_triggered
// -----------------------------------------------------------------------------
void MainWindow::on_action_Open_triggered(void)
{
  ImageWindow *child = new ImageWindow(this);
  mUI.mdiArea->addSubWindow(child);
  child->show();
}

// -----------------------------------------------------------------------------
// on_action_Histogram_triggered
// -----------------------------------------------------------------------------
void MainWindow::on_action_Histogram_triggered(void)
{
  QDockWidget *dock = new QDockWidget("Histogram", this);
  dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  ImageScrollArea *area = new ImageScrollArea(dock);
  dock->setWidget(area);
  addDockWidget(Qt::RightDockWidgetArea, dock);
}

// -----------------------------------------------------------------------------
// on_action_Quit_triggered
// -----------------------------------------------------------------------------
void MainWindow::on_action_Quit_triggered(void)
{
  close();
}
