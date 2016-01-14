#ifndef REALESTATE_H
#define REALESTATE_H
#include <unit.h>
#include <queue>
#include <map>
using namespace std;

class RealEstate{

protected:
    long inf;
    long sup;
    map<long,Unit> units;

public:
    RealEstate(long inf, long sup){
        this->inf = inf;
        this->sup = sup;
    }

    bool canBeAdd(long bbl){
        //remind to put a extra row 00000000 in the bbl
        if(this->inf < bbl && bbl <= this->sup){
            return true;
        } else {
            return false;
        }
    }

    void add(queue<string> tup){
        long bbl = atol(tup.front().c_str());
        tup.pop();
        if (canBeAdd(bbl)){
            map<long,Unit>::iterator it;
            it = this->units.find(bbl);
            if (it!= this->units.end()){
                it->second.add(tup);
            } else {
                this->units[bbl] = Unit();
                this->units[bbl].add(tup);
            }
        } else {
            return;
        }
    }

    void addPt(queue<string> tup){
        long bbl = atol(tup.front().c_str());
        tup.pop();
        if (canBeAdd(bbl)){
            map<long,Unit>::iterator it;
            it = this->units.find(bbl);
            if (it!= this->units.end()){
                it->second.addPoint(tup);
            } else {
                this->units[bbl] = Unit();
                this->units[bbl].addPoint(tup);
            }
        } else {
            return;
        }
    }

    void interpol(){
        for(auto i: this->units){
            (i.second).interpol();
        }
    }
};

#endif // REALESTATE_H
