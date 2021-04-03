#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include "panel_board.h"
#include <QLineEdit>
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void names_settled_done();

private:
    Ui::MainWindow *ui;
    Panel_board *board;
    QLineEdit input_lines[8];
    QPushButton* yesbutton;
    QDialog* dial;
    QStringList* competitor_names;
};
#endif // MAINWINDOW_H
