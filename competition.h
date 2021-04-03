#ifndef COMPETITION_H
#define COMPETITION_H


class Competition
{
public:
    Competition();
    void get_score_by_role();
    int id;
    int result_type=0; //0-undefine 1-主忠 2-反贼 3-内奸
    int role1_killed=0;
    int role2_killed=0;
    bool role0vsrole3=false;
    bool role0vsrole2vsrole3=false;
    int role1_killed_before_role3=0;
    bool finsh_in_one_round=false;
    int mvp_id=-1;
    int score_by_role[4];
};

#endif // COMPETITION_H
