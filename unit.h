#ifndef UNIT_H
#define UNIT_H
#include <subunit.h>
#include <map>
#include <queue>
#include <point.h>
#include <spline.h>

class Unit
{
private:
    map<string,SubUnit> subunits;
    map<long,Point> timeSeries;
public:
    Unit(){}

    void add(queue<string> su){
        string su_id = su.front();
        su.pop();
        map<string,SubUnit>::iterator it;
        it = this->subunits.find(su_id);
        if (it!= this->subunits.end()){
            it->second.add(su);
        } else {
            subunits[su_id] = SubUnit();
            subunits[su_id].add(su);
        }
    }

    void addPt(queue<string> p){
        Point pt(p);
        map<long,Point>::iterator it;
        it = this->timeSeries.find(pt.getSlot());
        if (it!= this->timeSeries.end()){
            timeSeries[it->first] = it->second + pt;
        } else {
            this->timeSeries[pt.getSlot()] = pt;
        }
    }

    void interpol(){
//        for(map<string, SubUnit>::iterator it = subunits.begin(); it != subunits.end(); it++){
//            (it->second).interpol();
//        }
        Spline s;
        s.load((this->timeSeries));
    }
};

#endif // UNIT_H
