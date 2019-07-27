#include "net.h"


////////////////////////////////////////////////////////////////////
net::net(int mynL,trainSet* myts): nL(mynL), ts(myts)
{
    // we assume the input is not a layer but output is
    Ls= new layer*[nL];
    nForLayers= new int[nL];
    pnIn= &(ts->nIn);              // number of inputs per pattern
    nForLayers[nL-1]=ts->nOut;     // number of outputs per pattern
    pnPat=&(ts->nPat);            // number of patterns in the training set
}

////////////////////////////////////////////////////////////////////
void net::Creat()
{
    Ls[0]= new layer(*pnIn,nForLayers[0],&alfa,pnPat); // input to first layer
    for (int i=1; i<nL; i++)
    {
        if(i != nL-1)Ls[i]= new layer(nForLayers[i-1],nForLayers[i],&alfa,pnPat);
        else Ls[i]= new layer(nForLayers[i-1],nForLayers[i],&alfa,pnPat);
        Ls[i-1]->makeBefore(Ls[i]);
    }
}


//////////////////////////////////////////////////////////////
layer* net::operator [] (int i) // to return a pointer to layer.
{
    return Ls[i];
}
//////////////////////////////////////////////////////////////
void net::print()
{
    int i;
    cout<<endl<< "network information"<<endl;
    cout<<"number of layers= "<<nL<< endl;
    cout<<"number of inputs"<< *pnIn<<endl;
     for (i=0; i<nL; i++){
        cout<<"number of neurons in layer "<<i<<"= " <<nForLayers[i]<<" location= "<< Ls[i]<<endl;
     }

    for (i=0; i<nL; i++)
    {
        cout<<endl<<i;
        Ls[i]->print();
    }

}
//////////////////////////////////////////////////////////////////////////
void net::save()
{
    int i,s,L;
    ofstream Report;
    Report.open("200N 38E.bin", ios::binary);
    for (L=0; L<nL; L++)
    {
        for (s=0; s<Ls[L]->nOut; s++)
        {
            Report.write(reinterpret_cast<char*>(Ls[L]->w[s]),Ls[L]->nIn*sizeof(float));
        }
        Report.write(reinterpret_cast<char*>(Ls[L]->b),Ls[L]->nOut*sizeof(float));
    }
    Report.close();
}

void net::saveLayers()
{
    int i,s,L;
    char arr[50];
    for (L=0; L<nL; L++)
    {
        ofstream Report;
        sprintf(arr,"Layer %d Weights.bin",L);
        Report.open(arr, ios::binary);
        for (s=0; s<Ls[L]->nOut; s++)
        {
            Report.write(reinterpret_cast<char*>(Ls[L]->w[s]),Ls[L]->nIn*sizeof(float));
        }
        Report.write(reinterpret_cast<char*>(Ls[L]->b),Ls[L]->nOut*sizeof(float));
        Report.close();
    }
}


/////////////////////////////////////////////////////////////////////////
void net::load()
{
    int i,s,L;
    ifstream Report;
    Report.open("200N 38E.bin", ios::binary);
    for (L=0; L<nL; L++)
    {
        for (s=0; s<Ls[L]->nOut; s++)
        {
            Report.read(reinterpret_cast<char*>(Ls[L]->w[s]),Ls[L]->nIn*sizeof(float));
        }
        Report.read(reinterpret_cast<char*>(Ls[L]->b),Ls[L]->nOut*sizeof(float));
    }
    Report.close();
}

void net::loadLayers()
{
    int i,s,L;
    char arr[50];
    for (L=0; L<nL; L++)
    {
        ifstream Report;
        sprintf(arr,"Layer %d Weights.bin",L);
        Report.open(arr, ios::binary);
        for (s=0; s<Ls[L]->nOut; s++)
        {
            Report.read(reinterpret_cast<char*>(Ls[L]->w[s]),Ls[L]->nIn*sizeof(float));
        }
        Report.read(reinterpret_cast<char*>(Ls[L]->b),Ls[L]->nOut*sizeof(float));
        Report.close();
    }
}

void net::transferWeight(net* sNET)//pointer to small net
{
    for (int L=0; L<nL; L++)
    {
        for (int s=0; s<Ls[L]->nOut; s++)
        {
            for (int i=0; i<Ls[L]->nIn; i++){
               if((s>=(*sNET)[L]->nOut) || (i>=(*sNET)[L]->nIn) ) Ls[L]->w[s][i]=((rand()%100) -50)/5000.0;//for new neorons in current layer or the layer before
               else Ls[L]->w[s][i]=(*sNET)[L]->w[s][i];
            }
            if((s>=(*sNET)[L]->nOut))Ls[L]->b[s]=((rand()%100) -50)/5000.0;
            else Ls[L]->b[s]=(*sNET)[L]->b[s];
        }
    }
}

void net::WeightAdd()//pointer to small net
{
    for (int L=0; L<nL; L++)
    {
        for (int s=0; s<Ls[L]->nOut; s++)
        {
            for (int i=0; i<Ls[L]->nIn; i++)
            {
               if( Ls[L]->w[s][i] == 0 ) Ls[L]->w[s][i]=((rand()%100) -50)/5000.0;//for new neorons in current layer or the layer before
            }
            if(Ls[L]->b[s])Ls[L]->b[s]=((rand()%100) -50)/5000.0;
        }
    }
}


void net::WeightDecay()
{
    for (int L=0; L<nL; L++)
    {
        for (int s=0; s<Ls[L]->nOut; s++)
        {
            for(int h=0; h<Ls[L]->nIn; h++)
            {
                Ls[L]->w[s][h] = Ls[L]->w[s][h] * 0.9;
            }
            Ls[L]->b[s] = Ls[L]->b[s] * 0.9;
        }
    }
}

