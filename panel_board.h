#ifndef PANEL_BOARD_H
#define PANEL_BOARD_H

#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include "competitor.h"
#include "competition.h"
#include <QDialog>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include "role.h"
class Panel_board : public QWidget
{
    Q_OBJECT

public:
    explicit Panel_board(QWidget *parent = nullptr);
    void set_names(QStringList *names);
public slots:
    void add_comp_result();
    void finish_adding_result();
    void add_panalty();
    void finish_adding_panalty();
private:
    int score_by_comp[8][8];
    void set_cells();
    QLabel* score_Labels[8][8];
    QWidget* cell_widgets[8][8];
    QTableWidget* table;
    QTableWidget* result_table;
    Competitor competitors[8];
    void set_roles();
    void update_result_table();
    void init_result_table();
    void init_panalty_board();
    Role roles[4];
    int comp_num=8;
    QDialog* add_comp_result_dial;
    QComboBox* player_names_box;
    QComboBox* winning_role_box;
    QLineEdit* current_comp_id;
    QLineEdit* role1_killed;
    QLineEdit* role2_killed;
    QLineEdit* role1_killed_before_role3;
    QCheckBox* role0_vs_role3;
    QCheckBox* role0_vs_role2_vs_role3;
    QCheckBox* finsh_in_one_round;
    QComboBox *role_boxes[8][8];
    Competition competitions[8];
    QPushButton* panalty_ok_button;
    QComboBox* temp_namelist;
    QLineEdit* panalty_edit;
    QDialog* panalty_dial;
signals:

};

#endif // PANEL_BOARD_H
