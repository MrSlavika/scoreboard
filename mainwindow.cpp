#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "competitor.h"
#include <QListWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <iostream>
#include <QLabel>
#include <QDialog>
#include <string>
void MainWindow::names_settled_done(){
    for(int i=0;i<8;i++){
        (*competitor_names)<<input_lines[i].text();
        //std::cout<<(this->input_lines[i].text()).toLocal8Bit().constData()<<std::endl;
    }
    this->dial->accept();
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    competitor_names= new QStringList();
    dial=new QDialog(this);
    dial->setWindowTitle(QString::fromLocal8Bit("选手设置"));
    QVBoxLayout* m =new QVBoxLayout();
    yesbutton= new QPushButton(QString::fromLocal8Bit("确定"));

    for(int i=0;i<8;i++){
        QLabel* label =new QLabel(QString::fromLocal8Bit("选手")+QString::number(i+1));
        input_lines[i].setText(QString::fromLocal8Bit("昵称")+QString::number(i+1));
        m->addWidget(label);
        m->addWidget(&input_lines[i]);
    }

    m->addWidget(yesbutton);

    connect(yesbutton, SIGNAL(clicked()), this, SLOT(names_settled_done()));
    dial->setLayout(m);
    dial->exec();

    board =new Panel_board();

    board->set_names(competitor_names);
    this->setCentralWidget(board);

    this->setWindowTitle(QString::fromLocal8Bit("赛事成绩记录"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

