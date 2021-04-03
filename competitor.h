#ifndef COMPETITOR_H
#define COMPETITOR_H
#include <QString>

class Competitor
{
public:
    Competitor();
    int id;
    QString name;
    int score=0;
    int panalty;
};

#endif // COMPETITOR_H
