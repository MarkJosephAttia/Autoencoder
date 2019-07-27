#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <ctime>
#include "matrix.h"
#include "trainSet.h"
#include "layer.h"
#include "net.h"
#include "trainer.h"
using namespace std;
////////////////////////////////////////////////////////////////
//dynamic pattern selection
////////////////////////////////////////////////////////////////
int main()
{
    int i;
    //srand(27);
    srand(time(NULL));
    trainSet* TS = new trainSet();
    TS->nIn =  10000;
    TS->nPat = NTRN;
    TS->Creat();
    net* N= new net(2,TS);
    N->alfa      =0.00003;
    N->nForLayers[0]= 200;
    /*N->nForLayers[1]= 9;
    N->nForLayers[2]= 150;
    N->nForLayers[3]= 100;
    N->nForLayers[4]= 400;*/
    N->Creat();
    TS->loadPic();
    //TS->loadPicGirls();
    N->load();
    //N->WeightAdd();
    //TS->loadSmall();
    //N->loadLayers();

    /*net* N1= new net(2,TS);
    N1->alfa      =.5;
    N1->nForLayers[0]= 500;
    //N1->nForLayers[1]= 100;
    //N1->nForLayers[2]= 500;
    N1->Creat();
    N1->transferWeight(N);*/

    trainer*  tr = new trainer(N, TS);
    //TS->loadPic();
    //N->saveLayers();
    //N1->save();
    /*for(int rep = 0; rep < 5000000; rep++)
    {
        //N1->WeightDecay();
        i=tr->train(500);
        //N->saveLayers();
        //N->alfa *=0.1;
        //N->WeightDecay();
        N->save();
    }*/
    tr->DTest();
    //N->WeightDecay();
    //N->save();
    //tr->testLine();
    //tr->testSP();
    //tr->test();
    //tr->testComplete();
    //tr->testAnomaly();
    //tr->testWater();
    //tr->testSame(0);
    //tr->gen(0);
    //tr->mating(0,18,8);
    //tr->PrintBN();
    return 0;
}

