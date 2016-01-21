#ifndef SPLINE_H
#define SPLINE_H
#include <interpolchain.h>
#include <map>
#include <point.h>
#include <cmath>
#include <vector>
#include <queue>

class Spline{
private:

public:
   Spline(){}

   double calcVar(double samech, double y, long h){
       double var = y/(double)h - (h/(double)6)*samech;
       return var;
   }

   vector<long> setXs(map<long,Point> timeSeries){
       map<long,Point>::iterator it = timeSeries.begin();
       vector<long> Xs;
       for(; it!=timeSeries.end();it++){
           Xs.push_back(it->first);
       }


       return Xs;
   }





   vector<long> interpol(map<long,Point> timeSeries){
       vector<long> Xs = setXs(timeSeries);
       queue<double> samech;
       queue<double> C;
       C.push(1/(double)timeSeries[0].getPrice());

       for(int i = 1; i < Xs.size(); i++){
              C.push(1);
       }
       return Xs;


   }

};

#endif // SPLINE_H
