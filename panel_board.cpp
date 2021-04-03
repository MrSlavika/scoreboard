#include "panel_board.h"
#include <QGridLayout>
#include <QPushButton>
#include "competitor.h"
#include <QSplitter>
#include <QHBoxLayout>
#include <QLabel>
#include <iostream>
#include <QDialog>
#include <QHeaderView>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>

int COMP_NUM=8;
Competitor competitors[8];
void Panel_board::set_roles(){
    roles[0].id=0;
    roles[0].showname=QString::fromLocal8Bit("主公");
    roles[0].color=QColor(255,100,100);
    roles[1].id=1;
    roles[1].showname=QString::fromLocal8Bit("忠臣");
    roles[1].color=QColor(255,255,100);
    roles[2].id=2;
    roles[2].showname=QString::fromLocal8Bit("反贼");
    roles[2].color=QColor(100,255,100);
    roles[3].id=3;
    roles[3].showname=QString::fromLocal8Bit("内奸");
    roles[3].color=QColor(100,100,255);
}

void Panel_board::update_result_table(){
    for(int i=0;i<8;i++){
        competitors[i].score=0;
        for(int j=0;j<8;j++){
            competitors[i].score+=score_by_comp[i][j];
        }
        QTableWidgetItem* it2 =new QTableWidgetItem();
        it2->setText(QString::number(competitors[i].score));
        result_table->setItem(1,i,it2);
        //result_table->item(1,i)->setText(QString::number(competitors[i].score));
    }

}
void Panel_board::add_comp_result(){
    add_comp_result_dial->exec();

}
void Panel_board::finish_adding_result(){
    int id=current_comp_id->text().toInt();
    if(id>=1 && id<=8){
        id-=1;
        competitions[id].mvp_id=player_names_box->currentIndex()-1;
        competitions[id].result_type=winning_role_box->currentIndex();
        competitions[id].role1_killed=role1_killed->text().toInt();
        competitions[id].role1_killed_before_role3=role1_killed_before_role3->text().toInt();
        competitions[id].role2_killed=role2_killed->text().toInt();
        competitions[id].role0vsrole2vsrole3=role0_vs_role2_vs_role3->isChecked();
        competitions[id].role0vsrole3=role0_vs_role3->isChecked();
        competitions[id].finsh_in_one_round=finsh_in_one_round->isChecked();
        competitions[id].get_score_by_role();
        for(int j=0;j<8;j++){
            int role_id=role_boxes[j][id]->currentIndex()-1;
            if(role_id>=0){
                score_by_comp[j][id]=competitions[id].score_by_role[role_id];
                if(j==competitions[id].mvp_id){
                    score_by_comp[j][id]++;
                }
                score_Labels[j][id]->setText(QString::number(score_by_comp[j][id]));
                //table->item(j,id+1)->setBackground(Qt::red);
                //score_Labels[j][id]->setStyleSheet("QLabel { background-color : red; color : blue; }");
            }
        }
        update_result_table();
        add_comp_result_dial->accept();
    }else{
        QMessageBox* alert=new QMessageBox();
        alert->setText(QString::fromLocal8Bit("比赛场次不合法"));
        alert->exec();
    }
}
Panel_board::Panel_board(QWidget *parent) : QWidget(parent)
{

    this->setMinimumWidth(1140);
    set_roles();

    memset(score_by_comp,0,sizeof(score_by_comp));
    add_comp_result_dial= new QDialog(this);
    add_comp_result_dial->setWindowTitle(QString::fromLocal8Bit("更新比赛结果"));
    player_names_box=new QComboBox();
    player_names_box->addItem(QString::fromLocal8Bit("不适用"));
    winning_role_box=new QComboBox();
    finsh_in_one_round=new QCheckBox(QString::fromLocal8Bit("1轮胜"));
    winning_role_box->addItem(QString::fromLocal8Bit("主忠胜利"));
    winning_role_box->addItem(QString::fromLocal8Bit("反贼胜利"));
    winning_role_box->addItem(QString::fromLocal8Bit("内奸胜利"));
    current_comp_id= new QLineEdit();

    role1_killed=new QLineEdit(QString("0"));

    role2_killed= new QLineEdit(QString("0"));
    role1_killed_before_role3= new QLineEdit(QString("0"));
    role0_vs_role3=new QCheckBox(QString::fromLocal8Bit("主内单挑"));
    role0_vs_role2_vs_role3=new QCheckBox(QString::fromLocal8Bit("主内反"));
    current_comp_id->setFixedWidth(90);
    role2_killed->setFixedWidth(90);
    role1_killed->setFixedWidth(150);
    role1_killed_before_role3->setFixedWidth(150);
    QGridLayout *add_result_layout =new QGridLayout();

    QPushButton *add_result_yes_button=new QPushButton(QString::fromLocal8Bit("确定"));
    add_result_layout->addWidget(new QLabel(QString::fromLocal8Bit("比赛场次：")),0,0);
    add_result_layout->addWidget(new QLabel(QString::fromLocal8Bit("MVP")),1,1);
    add_result_layout->addWidget(new QLabel(QString::fromLocal8Bit("胜利方")),1,0);
    add_result_layout->addWidget(new QLabel(QString::fromLocal8Bit("反贼阵亡数")),1,2);
    add_result_layout->addWidget(new QLabel(QString::fromLocal8Bit("忠臣阵亡数(反贼全灭前)")),1,3);
    add_result_layout->addWidget(new QLabel(QString::fromLocal8Bit("忠臣阵亡数(内奸死亡前)")),1,4);
    add_result_layout->addWidget(player_names_box,2,1);
    add_result_layout->addWidget(current_comp_id,0,1);
    add_result_layout->addWidget(winning_role_box,2,0);
    add_result_layout->addWidget(role2_killed,2,2);
    add_result_layout->addWidget(role1_killed,2,3);
    add_result_layout->addWidget(role1_killed_before_role3,2,4);
    add_result_layout->addWidget(role0_vs_role3,3,0);
    add_result_layout->addWidget(role0_vs_role2_vs_role3,3,1);
    add_result_layout->addWidget(finsh_in_one_round,3,4);
    add_result_layout->addWidget(add_result_yes_button,4,3);
    connect(add_result_yes_button,SIGNAL(clicked()), this, SLOT(finish_adding_result()));

    add_comp_result_dial->setLayout(add_result_layout);
    QVBoxLayout* m=new QVBoxLayout();
    QWidget *tab =new QWidget();
    QWidget *buttons =new QWidget();
    QGridLayout *layout = new QGridLayout();
    QHBoxLayout *buttonlayout=new QHBoxLayout();
    QPushButton* add_result_button =new QPushButton(QString::fromLocal8Bit("添加比赛结果"));
    QPushButton* add_comp_button =new QPushButton(QString::fromLocal8Bit("添加罚分"));
    QPushButton* clear_button =new QPushButton(QString::fromLocal8Bit("全部重置"));
    connect(add_result_button,SIGNAL(clicked()), this, SLOT(add_comp_result()));
    buttonlayout->addWidget(add_result_button);
    buttonlayout->addWidget(add_comp_button);
    buttonlayout->addWidget(clear_button);
    buttons->setLayout(buttonlayout);
    table =new QTableWidget(8,COMP_NUM+1);
    result_table=new QTableWidget(2,8);
    const QStringList header={"","1","2","3","4","5","6","7","8"};
    table->setHorizontalHeaderLabels(header);
    table->setColumnWidth(0,60);
    table->verticalHeader()->setVisible(false);
    result_table->verticalHeader()->setVisible(false);
    for(int i=0;i<8;i++){
        table->setRowHeight(i,51);
    }
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            role_boxes[i][j]=new QComboBox();
            role_boxes[i][j]->addItem(QString::fromLocal8Bit("待定"));
            for(int k=0;k<=3;k++){
                role_boxes[i][j]->addItem(roles[k].showname);
            }
            role_boxes[i][j]->setFixedWidth(63);
            cell_widgets[i][j]=new QWidget();
            score_Labels[i][j]=new QLabel(QString::number(score_by_comp[i][j]));
            score_Labels[i][j]->setFixedWidth(18);
            QHBoxLayout* tmp_layout =new QHBoxLayout();
            tmp_layout->addWidget(role_boxes[i][j]);
            tmp_layout->addWidget(score_Labels[i][j]);
            cell_widgets[i][j]->setLayout(tmp_layout);
            table->setCellWidget(i,j+1,cell_widgets[i][j]);
        }
    }
    QLabel* label=new QLabel(QString::fromLocal8Bit("选手总积分"));
    result_table->setFixedHeight(120);
    layout->addWidget(table,0,0);
    layout->addWidget(label,1,0);
    layout->addWidget(result_table,2,0);

    tab->setLayout(layout);
    m->addWidget(tab);
    m->addWidget(buttons);
    this->setLayout(m);

}

void Panel_board::set_names(QStringList *names){
    for(int i=0;i<8;i++){
        competitors[i].name=names->at(i);
        player_names_box->addItem(names->at(i));
        QTableWidgetItem* it =new QTableWidgetItem();
        it->setText(competitors[i].name);
        table->setItem(i,0,it);
        QTableWidgetItem* it2 =new QTableWidgetItem();
        it2->setText(competitors[i].name);
        result_table->setItem(0,i,it2);
    }
}




