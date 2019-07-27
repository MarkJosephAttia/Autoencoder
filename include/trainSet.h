#ifndef TRAINSET_H
#define TRAINSET_H
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <ctime>
#include "matrix.h"
#include<fstream>

#define NTST    36
#define NSAME   100
#define NTRN    25046
#define NGIRLS  5394
#define NANO    1345
#define NTSTD    26

using namespace std;
class trainSet
{
    public:
        int nIn;            // input,
        int nOut;           // output,
        int nPat;           // patterns
        float ** x;        // input
        float ** y;        // output
        unsigned char* pics;
		int Pic ; 			// number of pics
		unsigned int s;
        trainSet();
        void Creat(); // to actually construct the TS.

        void displayIm(int pI);
        void loadPic(); // load pictures ( )
        void loadTest();
        void loadSmall();
        void lineNoise();
        void SP();
        void loadSame();
        void loadTestWater();
        void loadPicGirls();
        void loadAnomaly();
        void loadTestDoctor();
    private:
};

#endif // TRAINSET_H
