#ifndef SUBUNIT_H
#define SUBUNIT_H
#include <map>
#include <point.h>
#include <queue>
#include <interpol.h>
using namespace std;


class SubUnit{
private:
    map<unsigned long,Point> timeSeries;
public:
    SubUnit(){}

    void add(queue<string> p){
        Point pto(p);
        map<unsigned long,Point>::iterator it;
        it = this->timeSeries.find(pto.getSlot());
        if (it!= this->timeSeries.end()){
            timeSeries[it->first] = it->second + pto;
        } else {
            this->timeSeries[pto.getSlot()] = pto;
        }
    }

    void interpol(){
//        for(map<unsigned long, Point>::iterator it = timeSeries.begin(); it != timeSeries.end(); it++){

//        }
        Interpol i(&timeSeries);
        i.calcHlist();
    }
};

#endif // SUBUNIT_H
