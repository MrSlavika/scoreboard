#ifndef RULES_H
#define RULES_H
#include "role.h"
#include "competitor.h"
#include "competition.h"
const int COMP_NUM=8;
class Rules
{
public:
    Rules();

    Role roles[4];
    Competitor competitors[8];
    Competition competitions[COMP_NUM];
};

#endif // RULES_H
