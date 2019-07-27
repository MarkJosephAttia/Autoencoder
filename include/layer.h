#ifndef LAYER_H
#define LAYER_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <ctime>
#include "matrix.h"
#include "trainSet.h"
#include "trainer.h"
using namespace std;
class trainSet;
class trainer;
class layer
{
    public:
    int nIn;
    int nOut;
    float* pAlfa;
    float** w ;
    float** dw;
    float*  b;
    float*  db;
    float* mOutF;  //output a
    float* mOutB;  // dl/da1 from second layer and dl/da from training set.
    float* pInF;   // input a
    float* pInB;   // dl/da from output or dl/da1 from second to first (delta roul)
    trainer * tr;    // trainer pointer
    int*   pnPat;
    int*   pbatIC;   // pointer batch index count

   layer(int myin, int myout, float* myalfa,int*  mynPat);
    void makFirst();
    void makLast();
    void makeBefore(layer* L); //connect phantom before L
    void print();
    void printOut();
    void Reset();  // reset dw and db
    void FF();    // to  FF
    void BP();    // to BP
    void Updat(); // layer update
    int* DropOut1000;
    int* Drop;
    private:
};

#endif // LAYER_H
