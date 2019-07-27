#ifndef TRAINER_H
#define TRAINER_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <ctime>
#include "matrix.h"
#include "layer.h"
#include "trainSet.h"
#include "net.h"
using namespace std;
class trainSet;
class layer;
class net;

const int Cont=0;     // normal
const int Done=1;     // we are done
const int minBat=2;   // full batch
const int fullBat=3;  // full batch
class trainer
{
    public:
        trainSet* ts;       // pointer to training set.
        net* Net;           // the net
        float MaxError;    // maximum error
        float Loss;        // sum of all error
        int patternInEror;  // number of pattern in error
        float * pa;       // pointer to the output of the last layer
        float * mda;      // dl/da
        int mode;           // cont, Done or Full

        // pointer for other variables to improve computation
        int* pnIn;            // pointer input,
        int* pnOut;           // pointer output,
        int* pnPat;           // pointer patterns

        float ** px;         // pointer to input
        float ** py;         // pointer to output
        int*   batI;          // batch indexes
        int    batIC;         // batch index count (number of pattern in error)
        int    ptrnI;         // pattern index
        int    mBatchCount;   // counter for mini batch

        float batchError;
        float TotalError;
        float div;


        trainer(net* theNet,trainSet* ts);
        void  NReset();      // to reset dw and db for the whole network
        void  NFF();         // network feed forward (one pattern)
        void  NBP();         // network back propagation (one pattern)
        void  NUpdat();      // to update the w and b (after any number of patterns)
        int   delta();       // to get dl/da and others
        void  printTs_out(); //
        void  initBatI();    // to fill completely
        void  initBatI(int fellPrecent) ;  // to fill for mini batch
        int   train (int cycles); //to train
        void  displayIm();
        void  test();
        void  initType(int type);
        void  initBatNotRand(int Patterns);
        void  testComplete();
        void  PrintBN();
        void  gen(int layerNumber);
        void  testLine();
        void  testSP();
        void  testSame(int layerNumber);
        void  testWater();
        void  mating(int layerNumber, int first, int second);
        void  testAnomaly();
        void  DTest();
};

#endif // TRAINER_H
