#ifndef UNIT_H
#define UNIT_H
#include <subunit.h>
#include <map>
#include <queue>

class Unit
{
private:
    map<string,SubUnit> subunits;
    string startDate;
public:
    Unit(){
        this->startDate = "1980-01-01";
    }

    void setStartDate(string startDate){
        this->startDate = startDate;
    }

    void add(queue<string> su){
        string su_id = su.front();
        su.pop();
        map<string,SubUnit>::iterator it;
        it = this->subunits.find(su_id);
        if (it!= this->subunits.end()){
            it->second.add(su);
        } else {
            subunits[su_id] = SubUnit(startDate);
            subunits[su_id].add(su);
        }
    }
};

#endif // UNIT_H
