// =============================================================================
//  MainWindow.h
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
  \file     MainWindow.h
  \author   Dairoku Sekiguchi
  \version  1.0.0-pre_alpha.0
  \date     2022/02/23
*/

#ifndef QIV_MAIN_WINDOW_H
#define QIV_MAIN_WINDOW_H

// Includes --------------------------------------------------------------------
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

// -----------------------------------------------------------------------------
// MainWindow class
// -----------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
Q_OBJECT

public:
  // Constructors and Destructor -----------------------------------------------
  MainWindow(QWidget *parent = Q_NULLPTR);

protected:
  // Member variables ----------------------------------------------------------

private:
  // Member variables ----------------------------------------------------------
  Ui::MainWindow  mUI;

private slots:
  void on_action_Open_triggered(void);
  void on_action_Histogram_triggered(void);
  void on_action_Quit_triggered(void);
};


#endif //QIV_MAIN_WINDOW_H
