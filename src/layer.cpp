#include "layer.h"

layer:: layer(int myin, int myout, float* myalfa,int*  mynPat)
    :nIn(myin), nOut(myout),pAlfa(myalfa),pnPat(mynPat)
    {
    int i, j;
    w     = matD(nOut,nIn);
    dw    = matD(nOut,nIn);
    b     = matD(nOut);
    db    = matD(nOut);
    mOutF = matD(nOut);
    mOutB = matD(nIn);

    for(i=0;i<nOut;i++)
     {
      for(j=0;j<nIn;j++)  w[i][j]=((rand()%100)-50)/1000.00;
      b[i]=((rand()%100)-50)/1000.00;
     }
    }
////////////////////////////////////////////////////////////////////
void layer:: Reset()
{
   int i,j;
   for(j=0;j<nOut;j++)
   {
       for(i=0;i<nIn; i++)
       {
           dw[j][i]=0;
       }
       db[j]=0;
   }
}
////////////////////////////////////////////////////////////////////
void layer::BP () // to update dl/dw   (can improve)
  {
   int i,j;
   float dz;
   for(i=0;i<nIn; i++) mOutB[i]=0;
   for(j=0;j<nOut;j++)
    {
     dz=pInB[j]*(1.0-mOutF[j]*mOutF[j]);
     db[j]+= dz;
     for(i=0;i<nIn;i++) {
         dw[j][i]+= dz*pInF[i];
         mOutB[i]+=w[j][i]*dz;
         }
    }
  }
////////////////////////////////////////////////////////////////////
  void layer::FF() // to get layer output no mask just batch
  {
  int i,j;
  float z,a;
  for(j=0;j<nOut;j++){
       z=b[j];
       for(i=0;i<nIn;i++) z+=w[j][i]*pInF[i];
       //if (z>1)a=1; else if(z<-1)a=-1; else a=z;
       mOutF[j]=tanh(z);
       }
   }

 //////////////////////////////////////////////////////////////////////
 void layer::Updat()  // to update w and b
 {
    int i,j,num;
    num=*pbatIC+1;
    for(j=0;j<nOut;j++)
     {
       b[j]+=db[j]*(*pAlfa/num);
       for(i=0;i<nIn;i++) w[j][i]+=dw[j][i]*(*pAlfa/num);
      }
  }
//////////////////////////////////////////////////////////////////////
void layer::makeBefore(layer* L) //connect phantom before L
{
     pInB=L->mOutB;
     L->pInF= mOutF;
}
//////////////////////////////////////////////////////////////////////
void layer::print()
{
    int i,j;
    //int nPat=*tr->pnPat;
    cout << "No of Input    ="<< nIn  <<  endl;
    cout << "No of Output   ="<< nOut <<  endl;
    cout << "No of Patterns ="<< (*pnPat) <<  endl;
    cout << "Alfa Value     ="<< (*pAlfa) <<  endl;

    for(i=0;i<nOut  ;i++)
    {
        cout<<"w["<<i+1<<"] = ";
        for(j=0;j<nIn;j++) cout<<w[i][j]<<" , ";
        cout<< "b["<<i+1<<"] = "<<b[i]<<endl;
    }
}
