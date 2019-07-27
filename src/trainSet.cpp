#include "trainSet.h"

trainSet::trainSet()
{
}
////////////////////////////////////////////////////////////////////////
void trainSet::Creat()
{
    nOut=nIn;
    //x = matD(nPat,nIn);       // full input data
    pics = new unsigned char[nIn];
    x = new float*[nPat];
    for(int i = 0; i < nPat; i++)
    {
        x[i] = new float[nIn];
    }
    y = x ;      // output pic is the same input pic (value dont change)
	Pic = 0;   // first pic
}
////////////////////////////////////////////////////////////////////////
void trainSet::loadPic()
{		// nPat = number of pics to be loaded in trainset at a time
		// Pic  = Picture number in the full dataset (at computer)
		ifstream imagetxt("Train.bin",ios::binary);
		for(int i =0; i<nPat; i++,Pic++) // Pic++ = to avoid dublication
		{
			if(Pic==25299)
				Pic=0;
            if(Pic%100==0)
                Pic++;
            imagetxt.seekg(Pic*10000*sizeof(unsigned char));
            imagetxt.read(reinterpret_cast<char*>(pics),10000*sizeof(unsigned char));
            float Min = 255.0; float Max = 0.0;
            for(int j=0; j< nIn &&!imagetxt.eof(); j++)
			{
			    if(pics[j] < Min) Min = pics[j];
			    if(pics[j] > Max) Max = pics[j];
			}
			for(int j=0; j< nIn &&!imagetxt.eof(); j++)
			{
                x[i][j] = pics[j];
				x[i][j] = (x[i][j] - 127.5 )/ 127.5;
				//x[i][j] = (2.0*(x[i][j] - Min) / (Max - Min))-1.0;
			}
		}
		imagetxt.close();


}

void trainSet::loadAnomaly()
{
		ifstream imagetxt("Anomaly.bin",ios::binary);
		for(int i =0; i<NANO; i++) // Pic++ = to avoid dublication
		{
            imagetxt.seekg(i*10000*sizeof(unsigned char));
            imagetxt.read(reinterpret_cast<char*>(pics),10000*sizeof(unsigned char));
			for(int j=0; j< nIn &&!imagetxt.eof(); j++)
			{
                x[i][j] = pics[j];
				x[i][j] = (x[i][j] - 127.5 )/ 127.5;
			}
		}
		imagetxt.close();
}

void trainSet::loadPicGirls()
{		// nPat = number of pics to be loaded in trainset at a time
		// Pic  = Picture number in the full dataset (at computer)
		ifstream imagetxt("Girls.bin",ios::binary);
		for(int i =0; i<nPat; i++,Pic++) // Pic++ = to avoid dublication
		{
			if(Pic==NGIRLS)
				Pic=0;
            imagetxt.seekg(Pic*10000*sizeof(unsigned char));
            imagetxt.read(reinterpret_cast<char*>(pics),10000*sizeof(unsigned char));
			for(int j=0; j< nIn &&!imagetxt.eof(); j++)
			{
			    x[i][j] = pics[j];
				x[i][j] = (x[i][j] - 127.5 )/ 127.5;
			}
		}
		imagetxt.close();


}


void trainSet::loadTest()
{		// nPat = number of pics to be loaded in trainset at a time
		// Pic  = Picture number in the full dataset (at computer)
		ifstream imagetxt("Test.bin",ios::binary);
		for(int i =0; i<NTST; i++) // Pic++ = to avoid dublication
		{
            imagetxt.seekg(i*10000*sizeof(unsigned char));
            imagetxt.read(reinterpret_cast<char*>(pics),10000*sizeof(unsigned char));
			for(int j=0; j< nIn &&!imagetxt.eof(); j++)
			{
			    x[i][j] = pics[j];
				x[i][j] = (x[i][j] - 127.5 )/ 127.5;
			}
		}
		imagetxt.close();
}

void trainSet::loadTestDoctor()
{		// nPat = number of pics to be loaded in trainset at a time
		// Pic  = Picture number in the full dataset (at computer)
		ifstream imagetxt("Doctor.bin",ios::binary);
		for(int i =0; i<NTSTD; i++) // Pic++ = to avoid dublication
		{
            imagetxt.seekg(i*10000*sizeof(unsigned char));
            imagetxt.read(reinterpret_cast<char*>(pics),10000*sizeof(unsigned char));
			for(int j=0; j< nIn &&!imagetxt.eof(); j++)
			{
			    x[i][j] = pics[j];
				x[i][j] = (x[i][j] - 127.5 )/ 127.5;
			}
		}
		imagetxt.close();
}

void trainSet::loadTestWater()
{		// nPat = number of pics to be loaded in trainset at a time
		// Pic  = Picture number in the full dataset (at computer)
		ifstream imagetxt("TestWater.bin",ios::binary);
		for(int i =0; i<NTST; i++) // Pic++ = to avoid dublication
		{
            imagetxt.seekg(i*10000*sizeof(unsigned char));
            imagetxt.read(reinterpret_cast<char*>(pics),10000*sizeof(unsigned char));
			for(int j=0; j< nIn &&!imagetxt.eof(); j++)
			{
			    x[i][j] = pics[j];
				x[i][j] = (x[i][j] - 127.5 )/ 127.5;
			}
		}
		imagetxt.close();
}

void trainSet::loadSmall()
{		// nPat = number of pics to be loaded in trainset at a time
		// Pic  = Picture number in the full dataset (at computer)
		ifstream imagetxt("Output 100.bin",ios::binary);
		for(int i =0; i<NTRN; i++,Pic++) // Pic++ = to avoid dublication
		{
			if(Pic==NTRN) // if we reach final pic load from 1
				Pic=0;
            imagetxt.seekg(Pic*100*sizeof(unsigned char));
            imagetxt.read(reinterpret_cast<char*>(x[i]),100*sizeof(float));
		}
		imagetxt.close();
}

////////////////////////////////////////////////////////////////////////
 void trainSet::displayIm(int pI ) //pI image number at loaded train set (x(pI))
{
	int rows = sqrt(nIn); // size of image
	int cols = rows ;
	if (pI >= nPat)   // for safety
		return;
	for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if(x[pI][j+cols*i]<-.6 ) cout<<char(32)<<char(32);
            else if(x[pI][cols*i+j]<-.2) cout<<char(176)<<char(176);
            else if(x[pI][cols*i+j]<.2) cout<<char(177)<<char(177);
            else if(x[pI][cols*i+j]<.56) cout<<char(178)<<char(178);
            else cout<<char(219)<<char(219);
        }
        cout << endl;
    }
}


void trainSet::lineNoise()
{
    ifstream imagetxt("Test.bin",ios::binary);
    for(int i =0; i<NTST; i++) // Pic++ = to avoid dublication
    {
        imagetxt.seekg(i*10000*sizeof(unsigned char));
        imagetxt.read(reinterpret_cast<char*>(pics),10000*sizeof(unsigned char));
        for(int j=0; j< nIn &&!imagetxt.eof(); j++)
        {
            x[i][j] = pics[j];
            x[i][j] = (x[i][j] - 127.5 )/ 127.5;
        }
    }
    imagetxt.close();


    int rows = sqrt(nIn); // size of image
	int cols = rows ;

    for( int k = 0 ; k < nPat ; k++)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if( i==0 && j==0 )
                {
                    x [k][cols*i + j] = 0 ;
                    x [k][cols*(i+1) + j] = 0 ;
                }
                else if( i==(rows-1) && j==(cols-1))
                {
                    x [k][cols*i + j] = 0 ;
                    x [k][cols*(i-1)+j] = 0 ;
                }
                else if(i == j)
                {
                    x [k][cols*(i-1) + j] = 0;
                    x [k][cols*i +j] = 0 ;
                    x [k][cols*(i+1) + j] = 0;
                }
                else     x [i][j] = x [i][j];
            }
        }
    }
}

void trainSet::SP()
{
    ifstream imagetxt("Test.bin",ios::binary);
    for(int i =0; i<NTST; i++) // Pic++ = to avoid dublication
    {
        imagetxt.seekg(i*10000*sizeof(unsigned char));
        imagetxt.read(reinterpret_cast<char*>(pics),10000*sizeof(unsigned char));
        for(int j=0; j< nIn &&!imagetxt.eof(); j++)
        {
            x[i][j] = pics[j];
            x[i][j] = (x[i][j] - 127.5 )/ 127.5;
            if(rand()%5 == 0)  x[i][j] = 0;
        }
    }
    imagetxt.close();
}

void trainSet::loadSame()
{
    ifstream imagetxt("Angelina.bin",ios::binary);
    for(int i =0; i<NSAME; i++) // Pic++ = to avoid dublication
    {
        imagetxt.seekg(i*10000*sizeof(unsigned char));
        imagetxt.read(reinterpret_cast<char*>(pics),10000*sizeof(unsigned char));
        for(int j=0; j< nIn &&!imagetxt.eof(); j++)
        {
            x[i][j] = pics[j];
            x[i][j] = (x[i][j] - 127.5 )/ 127.5;
        }
    }
    imagetxt.close();
}

