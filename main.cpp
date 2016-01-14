#include <iostream>
#include <csvmanager.h>
#include <iomanip>      // std::put_time
#include <ctime>        // std::time_t, struct std::tm, std::localtime
#include <chrono>
#include <point.h>
#include <queue>
#include <realestate.h>
#include <kernel.h>
#include <spline.h>
#include <matrix.h>

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
//    Spline(2);

//    Kernel k("/tmp/bl(sample).csv", "/tmp/bdv(sample).csv", "/home/marcio/Marcio/RealEstateFiles/teste.csv", 2);
//    k.feedBunch(true);
//    k.start();
    float **matrix;
    matrix =new (nothrow) float*[3];
    for(int i=0;i<3;i++){
        matrix[i]=new (nothrow) float[3];
    }
    float k=1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            matrix[i][j]=i+j+k;
        }
        k+=2;
    }
    //Matrix A=Matrix(3,3,matrix);
    Matrix B=Matrix(4,4);
    Matrix E(3,3,matrix);
    B.setMatrix();
    Matrix D;
    cout<<"det="<<B.det()<<endl;
    Matrix C = Matrix(4,4,B.inv().getMatrix());
//    Matrix D = Matrix(3,3,(C*B).getMatrix());
//    C=D;
    C=C.cat(B);

    D=B.inv();
    cout<<"Matriz D:"<<endl;
    D=D*B;
    for(int i=0;i<D.getRows();i++){
        for(int j=0;j<D.getCols();j++){
            cout<<D.getMatrix()[i][j]<<" ";
        }
        cout<<endl;
    }
    D=D+B;
    C=B*D;
    cout<<"Matriz C:"<<endl;
    for(int i=0;i<C.getRows();i++){
        for(int j=0;j<C.getCols();j++){
            cout<<C.getMatrix()[i][j]<<" ";
        }
        cout<<endl;
    }
    B.setMatrix();
    D=B*C;
    cout<<"Matriz D:"<<endl;
    for(int i=0;i<D.getRows();i++){
        for(int j=0;j<D.getCols();j++){
            cout<<D.getMatrix()[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
