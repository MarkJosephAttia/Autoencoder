#include "trainer.h"

trainer::trainer(net* theNet,trainSet* myts): ts(myts), Net(theNet)
{
    pnIn   = &(ts->nIn);
    pnOut  = &(ts->nOut);
    pnPat  = &(ts->nPat);
    py = ts->y;
    px = ts->x;
    mda  = matD(*pnOut);     // dl/da
    batI = matI(*pnPat);     // batch index for dynamic pattern selection
    mBatchCount=0;           // to count number of mini-batch done.
    initBatI(2);
    mode= minBat;
    ptrnI=0;                 // pattern pointer

    // to connect trainer to the network and training set.
    Net->Ls[Net->nL-1]->pInB  = mda;      // connect input for last layer for BP
    pa = Net->Ls[Net->nL-1]->mOutF;       // connect the output of the last layer to trainer

    // to adjust the layer data
    for ( int i=0; i<Net->nL; i++){
        Net->Ls[i]->pbatIC = &batIC;          // pointer batch index count
    }
    div = 2 * (ts->nIn);
}
////////////////////////////////////////////////////////////////////////
  int trainer::delta()
 {
   int j;
   int nError=0;
   TotalError = 0.0;     // number of outputs with error
   float error=0;

   for(j=0; j<*pnOut; j++) // for all outputs
   {
      mda[j] = (py[ptrnI][j]-pa[j]);
      error = abs(mda[j]);
      TotalError += error;
      Loss += error;
      if (error>MaxError) MaxError=error;
      //nError += error>0.4;
   }
   batchError += (TotalError/div);
   if ((TotalError/div)>0.1)    //  pattern still has error
   {
       patternInEror++;
   }

   return nError;
 }

  ////////////////////////////////////////////////////////////////
  int   trainer:: train (int cycles)
  {
   int i,j,k;
   int nError;  // number of outputs with error
   float sav = 1;

   for ( j=0; j<cycles; j++)
   {
      MaxError=0; Loss=0; patternInEror=0;   // to collect statistics.
      i=0; batchError = 0.0;
      NReset();
      while(i<batIC)    //for each location in the batch index table
      {
         k=batI[i];    // actual pattern number in the training set
         ptrnI=k;      // the current pattern to be trained
         NFF ();
         nError=delta();
         NBP ();
         i++;
      }
      NUpdat();
      batchError /= batIC;
      //if(batchError < 0.28) return 0;
      cout<<batchError*100<<", ";
      //cout<<nError<<", ";
      if(j%2==0)
      {
         mBatchCount++;
         cout<<"    -"<<j<<"  "<<patternInEror<<"/"<<batIC<<" Patterns have Errors"<<endl;
         initBatI(2);     // to fill table
         //initBatNotRand(25);
      }
      //if(j > cycles - 4) initBatI(100);
    }
   return j;
  }

  void trainer::test()
  {
      float total = 0.0;
      cout<<endl<<endl<<"           --Testing--"<<endl;
      ts->loadTest();
      initBatI(1000);
      int i = 0;
      MaxError=0; Loss=0; patternInEror=0;
      while(i<NTST)
      {
          batchError = 0.0;
          //OutIm(ts->x[i]);
          ptrnI = batI[i];
          NFF ();
          int nError=delta();
          displayIm();
          i++;
          total += batchError;
          cout<<"Photo # "<< i <<" Error : "<<batchError*100<<"%"<<endl;
      }
      cout<<endl<<"            Total Test Error =  "<< total*100/NTST <<"%"<<endl;
      cout<<"            Total Error Patterns =  "<<patternInEror<<endl;
  }

  void trainer::DTest()
  {
      float total = 0.0;
      cout<<endl<<endl<<"           --Doctors Test--"<<endl;
      ts->loadTestDoctor();
      initBatI(1000);
      int i = 0;
      MaxError=0; Loss=0; patternInEror=0;
      while(i<NTSTD)
      {
          batchError = 0.0;
          //OutIm(ts->x[i]);
          ptrnI = batI[i];
          NFF ();
          int nError=delta();
          displayIm();
          i++;
          total += batchError;
          cout<<"Photo # "<< i <<" Error : "<<batchError*100<<"%"<<endl;
      }
      cout<<endl<<"            Total Test Error =  "<< total*100/NTSTD <<"%"<<endl;
      cout<<"            Total Error Patterns =  "<<patternInEror<<endl;
  }

  void trainer::testComplete()
  {
      float total = 0.0;
      cout<<endl<<endl<<"           --Testing--"<<endl;
      initBatI(1000);
      int i = 0;
      MaxError=0; Loss=0; patternInEror=0;
      while(i<NTRN)
      {
          batchError = 0.0;
          //OutIm(ts->x[i]);
          ptrnI = batI[i];
          NFF ();
          int nError=delta();
          if(batchError > 0.1) OutIm(px[ptrnI]);
          i++;
          total += batchError;
          cout<<"Photo # "<< i <<" Error : "<<batchError*100<<"%"<<endl;
      }
      cout<<endl<<"            Total Test Error =  "<< total*100/NTRN <<"%"<<endl;
      cout<<"            Total Error Patterns =  "<<patternInEror<<endl;
  }

  ////////////////////////////////////////////////////////////////
  void trainer::NReset () // to reset dw and db for the whole network
  {
     int i;
     int nlayer;        // number of layers in the net
     nlayer= Net->nL;
     for (i=0; i<nlayer; i++ ) (*Net)[i]->Reset();
  }

  ////////////////////////////////////////////////////////////////
  void  trainer:: NFF ()   // work with one pattern
  {
    int i;
    int nlayer;        // number of layers in the net
    nlayer= Net->nL;
    (*Net)[0]->pInF = px[ptrnI];   // to point t the pattern selected
    for (i=0; i<nlayer; i++ ) (*Net)[i]->FF();
  }
  ////////////////////////////////////////////////////////////////
  void  trainer:: NBP ()
  {
    int i;
    int nlayer;        // number of layers in the net
    nlayer= Net->nL;
    for (i=nlayer-1; i>=0; i-- )  (*Net)[i]->BP();

  }
////////////////////////////////////////////////////////////////
  void  trainer:: NUpdat ()
  {
    int i;
    int nlayer;        // number of layers in the net
    nlayer= Net->nL;
    for (i=nlayer-1; i>=0; i-- )(*Net)[i]->Updat();

  }

////////////////////////////////////////////////////////////////
  void   trainer::initBatI()
  {
      int i;
      for (i=0; i<*pnPat; i++)   batI[i]=i;
      batIC=*pnPat;
  }
////////////////////////////////////////////////////////////////
// to partially fell the index table
  void   trainer::initBatI(int fellPrecent)
  {
      int i,j;
      for (i=0,j=0; i<*pnPat; i++)
      {
         if ((rand()%1000)<fellPrecent) // include in the training set
         {
            batI[j]=i;
            j++;
         }
      }
      batIC=j;
  }

  void   trainer::initBatNotRand(int Patterns)
  {
      int i,j;
      static int current = 0;//0;
      for (j=0; j<Patterns; j++)
      {
            if(current == NTRN) current = 0;
            batI[j]=current;
            current++;
      }
      batIC=Patterns;
  }

////////////////////////////////////////////////////////////////
void  trainer::printTs_out()
 {
    int i,j;
    cout<<"Ts="<<endl;
    for(i=0;i<*pnPat;i++)
    {
     ptrnI=i;   // the current pattern to be trained
     NFF ();
     for(j=0;j<*pnIn;j++)
         cout<<setw(3)<<px[i][j]<<" ";
     cout<<"=";
     for(j=0;j<*pnOut;j++) cout<<setw(3)<<py[i][j];
     for(j=0;j<*pnOut;j++) cout<<setw(3)<<pa[j]<<" E=";
     for(j=0;j<*pnOut;j++) cout<<setw(3)<<abs(pa[j]-py[i][j]);
     cout<<endl;
    }
 }

void trainer::displayIm() //pI image number at loaded train set (x(pI))
{
    OutIm(pa,px[ptrnI]);
}

void trainer::PrintBN()
{
      initBatI(1000);
      int i = 0;
      MaxError=0; Loss=0; patternInEror=0;
      ofstream Report;
      Report.open("Output 100.bin", ios::binary);
      while(i<NTRN)
      {
          ptrnI = batI[i];
          NFF ();
          int nError=delta();
          i++;
          Report.write(reinterpret_cast<char*>(Net->Ls[1]->mOutF),Net->Ls[1]->nOut*sizeof(float));
      }
      Report.close();
}
void trainer::gen(int layerNumber)
{
      float total = 0.0;
      ts->loadTest();
      cout<<endl<<endl<<"           --Generating--"<<endl;
      initBatNotRand(10);
      int i = 0;
      MaxError=0; Loss=0; patternInEror=0;
      while(i<batIC)
      {
          ptrnI = batI[i];
          (*Net)[0]->pInF = px[ptrnI];
          for(int m=0; m<40; m++)
          {
                  for (int z=0; z<Net->nL; z++ )
                  {
                      (*Net)[z]->FF();
                  }
                  if(m==0)OutIm(pa);
                  for (int z=0; z<Net->nL; z++ )
                  {
                      (*Net)[z]->FF();
                      if(z==layerNumber)
                      {
                          for(int h=0; h <100;h++ )
                          {
                              Net->Ls[layerNumber]->mOutF[rand()%(Net->Ls[layerNumber]->nOut)] *= (rand()%200)/100;
                          }
                      }
                  }
                  int nError=delta();
                  OutIm(pa);
          }
          i++;
      }
}

void trainer::testLine()
  {
      float total = 0.0;
      cout<<endl<<endl<<"           --Testing--"<<endl;
      ts->lineNoise();
      initBatI(1000);
      int i = 0;
      MaxError=0; Loss=0; patternInEror=0;
      while(i<NTST)
      {
          batchError = 0.0;
          //OutIm(ts->x[i]);
          ptrnI = batI[i];
          NFF ();
          int nError=delta();
          displayIm();
          unmask(pa);
          i++;
          total += batchError;
      }
  }

  void trainer::testAnomaly()
  {
      cout<<endl<<endl<<"           --Testing Anomaly--"<<endl;
      ts->loadAnomaly();
      initBatI(1000);
      int i = 0;
      MaxError=0; Loss=0; patternInEror=0;
      while(i<NANO)
      {
          batchError = 0.0;
          //OutIm(ts->x[i]);
          ptrnI = batI[i];
          NFF ();
          int nError=delta();
          if(TotalError/div < 0.05)
          {
              //displayIm();
              OutIm(px[ptrnI]);//0.45  0.035
              color(Net->Ls[0]->mOutF, 200);
          }
          i++;
      }
  }

  void trainer::testSP()
  {
      float total = 0.0;
      cout<<endl<<endl<<"           --Salt & Pepper--"<<endl;
      ts->SP();
      initBatI(1000);
      int i = 0;
      MaxError=0; Loss=0; patternInEror=0;
      while(i<NTST)
      {
          batchError = 0.0;
          //OutIm(ts->x[i]);
          ptrnI = batI[i];
          NFF ();
          int nError=delta();
          displayIm();
          i++;
          total += batchError;
      }
  }
  void trainer::testSame(int layerNumber)
  {
      float distance;
      int nNeu =Net->Ls[layerNumber]->nOut;
      float* arr = new float[nNeu];
      float total = 0.0;
      cout<<endl<<endl<<"           --Same People--"<<endl;
      ts->loadSame();
      initBatI(1000);
      int i = 0;
      MaxError=0; Loss=0; patternInEror=0;
          ptrnI = batI[1];
          (*Net)[0]->pInF = px[ptrnI];
          for (int z=0; z<layerNumber+1; z++ )
          {
               (*Net)[z]->FF();
          }
          cop(arr,Net->Ls[layerNumber]->mOutF,nNeu);
          while(i<NSAME)
          {
              batchError = 0.0;
              ptrnI = batI[i];
              (*Net)[0]->pInF = px[ptrnI];
              for (int z=0; z<layerNumber+1; z++ )
              {
                   (*Net)[z]->FF();
              }
              if(rms(arr,Net->Ls[layerNumber]->mOutF,nNeu) < 10.4) cout<<i+1<<endl;//color(Net->Ls[layerNumber]->mOutF, nNeu);//
              //if(i == 55)color(Net->Ls[layerNumber]->mOutF, nNeu);
              //cout<< setw(7) <<rms(arr,Net->Ls[layerNumber]->mOutF,nNeu)<<"   ";
              i++;
          }
          //cout<<endl;
          i = 0;
  }

  void trainer::testWater()
  {
      cout<<endl<<endl<<"           --Testing Watermark--"<<endl;
      ts->loadTestWater();
      initBatI(1000);
      int i = 0;
      MaxError=0; Loss=0; patternInEror=0;
      while(i<NTST)
      {
          batchError = 0.0;
          //OutIm(ts->x[i]);
          ptrnI = batI[i];
          NFF ();
          int nError=delta();
          displayIm();
          unmask(pa);
          i++;
      }
  }

  void trainer::mating(int layerNumber, int first, int second)
{
      float* temp = matD(Net->Ls[layerNumber]->nOut);
      ts->loadTest();
      cout<<endl<<endl<<"           --Mating--"<<endl;
      initBatNotRand(36);
      int i = 0;
      MaxError=0; Loss=0; patternInEror=0;

      ptrnI = batI[first-1];
      (*Net)[0]->pInF = px[ptrnI];
      OutIm(px[ptrnI]);
      for (int z=0; z<Net->nL; z++ )
      {
          (*Net)[z]->FF();
          if(z==layerNumber)
          {
                cop(temp, Net->Ls[layerNumber]->mOutF, Net->Ls[layerNumber]->nOut);
          }
      }


      ptrnI = batI[second-1];
      (*Net)[0]->pInF = px[ptrnI];
      OutIm(px[ptrnI]);
      for (int z=0; z<Net->nL; z++ )
      {
          (*Net)[z]->FF();
          if(z==layerNumber)
          {
              for(int m = 0; m < Net->Ls[layerNumber]->nOut; m++)
                        Net->Ls[layerNumber]->mOutF[m] = (Net->Ls[layerNumber]->mOutF[m] + temp[m])/1.5;//2.0;
                        //if(rand()%2 == 0) Net->Ls[layerNumber]->mOutF[m] = temp[m];
          }
      }


      OutIm(pa);

}
