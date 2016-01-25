/*************************************************************************
 *
 * Author: Marcio Maciel Bastos
 * __________________
 *
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Marcio Maciel Bastos.
 * The intellectual and technical concepts contained
 * herein are proprietary to Marcio Maciel Bastos
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Marcio Maciel Bastos.
 */

#ifndef SPLINE_H
#define SPLINE_H
#include <map>
#include </home/marcio/Marcio/Analysis/Analysis/point.h>
#include <cmath>
#include <vector>
#include <queue>

class Spline{
private:
    vector<long> Xs;
    vector<float> Y;
    vector<float> Yp;

    vector<long> setXs(map<long,Point> timeSeries){
        map<long,Point>::iterator it = timeSeries.begin();
        vector<long> Xs;
        for(; it!=timeSeries.end();it++){
            Xs.push_back(it->first);
        }


        return Xs;
    }

    vector<float> setYs(map<long,Point> timeSeries){
        vector<float> Ys;
        for(auto  i : this->Xs){
            Ys.push_back(timeSeries[i].getPrice());
        }
        return Ys;
    }

    vector<float> setYp(){
        vector<float> Yp;
        for(auto  i : this->Xs){
            Yp.push_back(0);
        }
        return Yp;
    }

public:
   Spline(){}



   long h(long i){
       long h_ = this->Xs[i+1]-this->Xs[i];
       if(h_==0){
           "teste";
           cout<<i<<endl;
       } else {
           "mozo";
       }
       return h_;
   }

   long dy(long i){
       return this->Y[i+1]-this->Y[i];
   }

   long a(long i){
       return h(i);
   }

   long c(long i){
       return h(i+1);
   }

   long b(long i){
       return 2*(h(i)+h(i+1));
   }

   float c_(long i){
       if(i == 0){
           return c(i)/(float)b(i);
       } else {
           return h(i)/(float)(b(i)-a(i)*c_(i-1));
       }
   }

   float r(long i){
       float r_ = dy(i)/(float)h(i);
       return r_;
   }

   float d(long i){
       float d_ = 6*(r(i)-r(i-1));
       return d_;
   }

   float d_(long i){
       if(i == 1){
           return d(i)/(float)b(i);
       } else {
          float _d = (d(i)-a(i)*d_(i-1))/(float)(b(i)-a(i)*c_(i-1));
          return _d;
       }
   }

   void solveTridiagonal(){
       this->Yp[this->Xs.size()-2] = d_(this->Xs.size()-2);
       for(unsigned long i = this->Xs.size()-3; i > 0; i--){
            this->Yp[i] = d_(i) - c_(i)*this->Yp[i+1];
       }
   }

   void load(map<long,Point> timeSeries){
       this->Xs = setXs(timeSeries);
       this->Y = setYs(timeSeries);
       this->Yp = setYp();
       solveTridiagonal();
   }

  bool load(vector<long> x, vector<float> y){
       this->Xs = x;
       this->Y = y;
       this->Yp = setYp();
       solveTridiagonal();
       return true;
   }

   long getInterval(float x){
       for(unsigned long i = 0; i < this->Xs.size(); i++){
            if(this->Xs[i] < x && x < this->Xs[i+1]){
                return i;
            }
       }
       return -1;
   }

   float* f(long k){
       float* A = new float[4];
       A[0] = this->Y[k];
       A[1] = r(k)-(h(k)/float(6))*(this->Yp[k+1]+2*this->Yp[k]);
       A[2] = this->Yp[k]/(float)2;
       A[3] = (1/(float)(6*h(k)))*(this->Yp[k+1]-this->Yp[k]);
       return A;
   }

   float interpol(float x){
       for(unsigned long i = 0; i < this->Xs.size() ; i++){
           if(x == (float)Xs[i]){
               return this->Y[i];
           }
       }
       long i = getInterval(x);
       float * A = f(i);
       float P3 = A[3]*(float)(x-this->Xs[i])*(float)(x-this->Xs[i])*(float)(x-this->Xs[i]);
       float P2 = A[2]*(float)(x-this->Xs[i])*(float)(x-this->Xs[i]);
       float P1 = A[1]*(float)(x-this->Xs[i]);
       float P0 = A[0];
       return P3 + P2 + P1 + P0;
   }

   vector<long> * getXs(){
       return &(this->Xs);
   }
};

#endif // SPLINE_H
