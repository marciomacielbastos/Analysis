#ifndef KERNEL_H
#define KERNEL_H
#include <vector>
#include <queue>
#include <thread>
#include <realestate.h>
#include <csvmanager.h>
using namespace std;

queue<string> tup;

class Kernel{
private:
    map<long, float> bbl_area;
    vector<long> bbls;
    string output;
    vector<RealEstate> re;
    int num_threads;
    CSVManager cs;

public:
    Kernel(string bblslist, string input, string output, int n){
        this->cs = CSVManager(input);
        this->output = output;
        this->num_threads =n;
        this->bbl_area = loadBBLS(bblslist);
        shareBBLs();
    }

    map<long, float> loadBBLS(string bblslist){
        map<long, float> bbl_area;
        long bbl;
        float area;
        CSVManager cs(bblslist);
        queue<string> fl = cs.read(true);
        while(!fl.empty()){
            bbl = atol(fl.front().c_str());
            fl.pop();
            area = atof(fl.front().c_str());
            bbl_area[bbl] = area;
            fl.pop();
            this->bbls.push_back(bbl);
            fl = cs.read(true);
        }
        return bbl_area;
    }

    void shareBBLs(){
        long offset = this->bbls.size() % this->num_threads;
        long len = this->bbls.size() / this->num_threads;
        unsigned long begin = 0, end = 0;
        long b, e;
        while(end < this->bbls.size()-1){
            begin = end;
            end += len;
            if(offset){
                end++;
                offset--;
            }
            if(end >= this->bbls.size()){
                end = this->bbls.size()-1;
            }
            b = this->bbls[begin];
            e = this->bbls[end];
            this->re.push_back(RealEstate(b, e));
        }
        //Empty this->bbls, since it will be not used anymore
        vector<long>().swap(this->bbls);
    }

    bool getTup(){
        queue<string> fl = this->cs.read(true);
        if (!fl.empty()){
            tup = fl;
            return true;
        } else {
            return false;
        }
    }

    static void feed(RealEstate *re){
        re->add(tup);
    }

    static void feedPt(RealEstate *re){
        re->addPt(tup);
    }

    void feedBunch(){
        thread t[this->num_threads];
        while(getTup()){
            for(int i = 0; i < this->num_threads ; i++){
                t[i] = thread(feed, &(this->re[i]));
            }
            for(int i = 0; i < this->num_threads ; i++){
                t[i].join();
            }
       }
    }

    void feedBunch(bool k){
        thread t[this->num_threads];
        while(getTup()){
            for(int i = 0; i < this->num_threads ; i++){
                t[i] = thread(feedPt, &(this->re[i]));
            }
            for(int i = 0; i < this->num_threads ; i++){
                t[i].join();
            }
       }
    }

    void start(){
        for(auto i : this->re){
            i.interpol();
        }
    }
};

#endif // KERNEL_H
