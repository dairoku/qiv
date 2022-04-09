// =============================================================================
//  main.cpp
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
  \file     main.cpp
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/23
*/

// Includes --------------------------------------------------------------------
#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setApplicationName("qiv");
  QApplication::setApplicationVersion("v1.0.0-pre_alpha.0");

  MainWindow mainWindow;
  mainWindow.show();

  return QApplication::exec();
}
