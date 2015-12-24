#include <iostream>
#include <csvmanager.h>
#include <iomanip>      // std::put_time
#include <ctime>        // std::time_t, struct std::tm, std::localtime
#include <chrono>
#include <point.h>
#include <queue>
#include <realestate.h>
#include <kernel.h>
using namespace std;
//int argc, char *argv[]
int main(){
    string bbls, input, output;
//    if(argc <3){
//        cout<<"You have to put 3 args"<<endl;
//        return 0;
//    }
//    bbls = argv[0];
//    input = argv[1];
//    output = argv[2];

    Kernel k("/home/marcio/Marcio/bbls.csv", "/home/marcio/Marcio/aip.csv", "/home/marcio/Marcio/t.csv", 3);
    k.feedBunch();
}
