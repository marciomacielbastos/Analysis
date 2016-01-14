#ifndef UNIT_H
#define UNIT_H
#include <subunit.h>
#include <map>
#include <queue>
#include <point.h>

class Unit
{
private:
    map<string,SubUnit> subunits;
    map<unsigned long,Point> timeSeries;
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

    void addPoint(queue<string> p){
        Point pto(p, startDate);
        map<unsigned long,Point>::iterator it;
        it = this->timeSeries.find(pto.getSlot());
        if (it!= this->timeSeries.end()){
            timeSeries[it->first] = it->second + pto;
        } else {
            this->timeSeries[pto.getSlot()] = pto;
        }
    }

    void interpol(){
        for(map<string, SubUnit>::iterator it = subunits.begin(); it != subunits.end(); it++){
            (it->second).interpol();
        }
    }
};

#endif // UNIT_H
