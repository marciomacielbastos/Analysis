#ifndef INTERPOL_H
#define INTERPOL_H
#include <map>
#include <point.h>
using namespace std;


class Interpol
{   map<unsigned long,Point> * timeSeries;

public:
    Interpol(map<unsigned long,Point> * timeSeries){
        this->timeSeries = timeSeries;
    }

    void calcHlist(){
        cout<<timeSeries->size();

    }
};

#endif // INTERPOL_H