#ifndef LAGRANGE_H
#define LAGRANGE_H
#include <vector>
using namespace std;

class Lagrange{
private:
    vector<long> X;
    vector<float> Y;

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
        for(auto  i : this->X){
            Ys.push_back(timeSeries[i].getPrice());
        }
        return Ys;
    }

public:
    Lagrange() {}

    float lagrangeRate(float x, long a_i, long a_k){
        return (x-a_i)/(float)(a_k-a_i);
    }

    float l(long k, float x){
        float product = 1;
        for(auto i : this->X){
                if(i!=this->X[k]){
                    product *= lagrangeRate(x, i, this->X[k]);
                }
        }
        return product;
    }

    float g(float x){
        float summ = 0;
        for(unsigned long i = 0; i < this->X.size(); i++){
            summ += this->Y[i]*l(i, x);
        }
        return summ;
    }

    void load(map<long,Point> timeSeries){
        this->X = setXs(timeSeries);
        this->Y = setYs(timeSeries);
    }

   void load(vector<long> x, vector<float> y){
        this->X = x;
        this->Y = y;
    }

   float interpol(float x){
       return g(x);
   }
};

#endif // LAGRANGE_H
