#ifndef SUBUNIT_H
#define SUBUNIT_H
#include <map>
#include <point.h>
#include <queue>
using namespace std;


class SubUnit{
private:
    map<int,Point> timeSeries;
    string startDate;
public:
    SubUnit(){
        this->startDate = "1980-01-01";
    }

    SubUnit(string startDate){
        this->startDate = startDate;
    }
    void add(queue<string> p){
        Point pto(p, startDate);
        map<int,Point>::iterator it;
        it = this->timeSeries.find(pto.getSlot());
        if (it!= this->timeSeries.end()){
            timeSeries[it->first] = it->second + pto;
        } else {
            this->timeSeries[pto.getSlot()] = pto;
        }
    }
};

#endif // SUBUNIT_H
