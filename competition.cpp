#include "competition.h"
#include <cstring>
#include <algorithm>

void Competition::get_score_by_role(){
    if(result_type==0){
        score_by_role[0]=12;
        score_by_role[1]=12;
        score_by_role[2]=role1_killed;
        score_by_role[3]=1+role1_killed_before_role3*3+3*role0vsrole3;
    }else if(result_type==1){
        score_by_role[0]=role2_killed;
        score_by_role[1]=role2_killed;
        score_by_role[2]=8;
        score_by_role[3]=2+4*role0vsrole2vsrole3;
    }else if(result_type==2){
        score_by_role[3]=20;
        score_by_role[2]=role1_killed;
        score_by_role[0]=6;
        score_by_role[1]=6;
    }
    if(finsh_in_one_round){
        for(int i=0;i<4;i++){
            score_by_role[i]--;
            score_by_role[i]=std::max(score_by_role[i],0);
        }
    }
}
Competition::Competition()
{
    std::memset(score_by_role,0,sizeof(score_by_role));
}
