#ifndef KERNEL_H
#define KERNEL_H
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <realestate.h>
#include <csvmanager.h>
using namespace std;

queue<string> tup;

class Kernel{
private:
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
        this->bbls = loadBBLS(bblslist);
        shareBBLs();
    }

    vector<long> loadBBLS(string bblslist){
        vector<long> bbls;
        CSVManager cs(bblslist);
        queue<string> fl = cs.read(true);
        while(!fl.empty()){
            bbls.push_back(atol(fl.front().c_str()));
            fl.pop();
            fl = cs.read(true);
        }
        return bbls;
    }

    void shareBBLs(){
        int offset = bbls.size() % this->num_threads;
        int len = bbls.size() / this->num_threads;
        unsigned int begin = 0, end = 0;
        for(auto i : this->bbls){
            begin = end;
            end += len;
            if(offset){
                end++;
                offset--;
            }
            if(end > bbls.size()){

                end = bbls.size();
            }
            this->re.push_back(RealEstate(begin, end));
        }
    }

    bool getTup(){
        queue<string> fl = cs.read(true);
        if (!fl.empty()){
            tup = fl;
            return true;
        } else {
            return false;
        }
    }

    static void feed(RealEstate re){
        re.addTuple(tup);
    }

    void feedBunch(){
        thread t[this->num_threads];
        while(getTup()){
            for(int i = 0; i < num_threads ; i++){
                t[i] = thread(feed, re[i]);
            }
            for(int i = 0; i < num_threads ; i++){
                t[i].join();
            }
       }
    }

    void start(){
        for(auto i : bbls){
            cout<<i<<endl;
        }
    }
};

#endif // KERNEL_H
