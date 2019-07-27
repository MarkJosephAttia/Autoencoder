#include "matrix.h"
#include <iostream>
#include <fstream>
using namespace std;



    //------------------------------------------------------
   matrix::matrix (int colum):r(1),c(colum)
    {
        m=new float*[r];
        for(int i=0; i<r; i++)
            m[i]=new float[c];
    }
    //-------------------------------------------------------
     matrix::matrix (int row,int colum):r(row),c(colum)
    {
        m=new float *[r];
        for(int i=0; i<r; i++)
            m[i]=new float[c];
    }
    //-------------------------------------------------------
     matrix::~matrix ()
    {
        for(int i=0; i<r; i++)
            delete [] m[i];
        delete [] m ;
    }
    //----------------------------------------------------------
    void  matrix::Emult (matrix* x,matrix* z) //check
    {
        if (z->r!=x->r || z->c!=x->c)
        {
            cout<<"Not the same"<<endl;
        }
        else
        {
            for(int n=0; n<r; n++)
                for(int j=0; j<c; j++)
                   m[n][j]=z->m[n][j]*x->m[n][j];
        }
    }
    //--------------------------------------------------------------
    void  matrix::mult(matrix* x,matrix* z)//check
    {
        if(x->c!=z->r)
        {
            cout<<"Multipli Error"<< x->c << ", " << z->r<<endl;
        }
        if (x== this|| z== this)
        {
            cout<<"Multipli Error"<< "resusing matrixes is prohebted" <<endl;
        }

        for(int n=0; n<r; n++)
        {
            for(int j=0; j<c; j++)
            {
                m[n][j]=0;
                for(int y=0; y<x->c; y++)
                    m[n][j]+=x->m[n][y]*z->m[y][j];
            }
        }
    }
    //------------------------------------------------
    void  matrix::add (matrix* x,matrix* z)//check
    {
        if(x->r!=z->r&&x->c!=z->c)
        {
            cout<<"Error input"<<endl;
        }
        else
        {
            for(int n=0; n<r; n++)
                for(int j=0; j<c; j++)
                    m[n][j]=x->m[n][j]+z->m[n][j];
        }
    }
    //-----------------------------------------------------
    void  matrix::sub(matrix* x,matrix* z)//check
    {
        if(x->r!=z->r&&x->c!=z->c)
        {
            cout<<"Error input"<<endl;
        }

        else
        {
            for(int n=0; n<r; n++)
                for(int j=0; j<c; j++)
                    m[n][j]=x->m[n][j]-z->m[n][j];
        }
    }
    //-------------------------------------------------------
    void  matrix::sub(matrix* x)//check
    {
        if(r!=x->r||c!=x->c)
        {
            cout<<"Error"<<endl;
        }
        else
            for(int n=0; n<r; n++)
                for(int j=0; j<c; j++)
                    m[n][j]=m[n][j]-x->m[n][j];
    }
    //-------------------------------------------------------
    matrix*  matrix::operator =(matrix* x)//check
    {
        matrix * rus = new matrix(x->r,x->c);
        for(int j=0;j<r;j++)
            for(int n=0;n<c;n++)
                m[j][n]=x->m[j][n];
        return rus;
    }
    //---------------------------
    void  matrix::eqaul(matrix* x)//check
    {
        if(r!=x->r||c!=x->c)
        {
            cout<<"Error"<<endl;
        }
        else
        for(int j=0;j<r;j++)
            for(int n=0;n<c;n++)
                m[j][n]=x->m[j][n];
    }
    //---------------------------------------------
    void  matrix::fil()//check
    {
        for(int j=0;j<r;j++)
        {
            for(int n=0;n<c;n++)
            {
                cout<<"value of ["<<j<<"]["<<n<<"]=?";
                cin>>m[j][n];
            }
        }
    }
    //------------------------------------------
    void  matrix::print(char * str)//check
    {
        cout<<"the value off "<<str<<endl;
        for(int j=0;j<r;j++)
        {
            for(int n=0;n<c;n++)
                cout<<m[j][n]<<" , ";//cout<<"["<<j<<"]["<<n<<"]="<<m[j][n]<<" , ";
            cout<<endl;
        }
    }
    //----------------------------------------
    void  matrix::print2mat(matrix* x)//check
    {
        cout<<"The of value of matrix"<<endl;
        for(int i=0;i<c;i++)
        {
            for(int j=0;j<r;j++)
                cout<<setw(3)<<m[j][i]<<" ";//<<setw(6)
            cout<<"="<<setw(9)<<x->m[0][i];
            cout<<endl;
        }
    }
    //---------------------------------------
    void  matrix::square(matrix* x)//check
    {
        this->mult(x,x);
    }
      //---------------------------------------
    void  matrix::Esquare(matrix* x)//check
    {
       Emult(x,x);
    }
    //--------------------------------------------
    void  matrix::transpose(matrix* x)//check
    {
        if(x->r!=c || x->c!= r)
        {
            cout<<"transpos: Error input dimention"<<endl;
        }
        for(int j=0;j<r;j++)
        {
            for(int n=0;n<c;n++)
                m[j][n]=x->m[n][j];
        }
    }
    //------------------------------------------------------
    void  matrix::filrandnum(int p) //p for percent //check
    {
       for(int j=0;j<r;j++)
        {
            for(int n=0;n<c;n++)
            {
            float r = rand() % 100;
            if(r>p)
                r=1;
            else
                r=-1;
            m[j][n]=r;
            }
        }
    }
    //----------------------------------------------------------
    void  matrix::filrandfrac() //p for percent//check
    {
        for(int j=0;j<r;j++)
        {
            for(int n=0;n<c;n++)
                m[j][n]=((rand()%100)-50)/200.00;
        }
    }
    //-----------------------------------------------------------------------
    void  matrix::filone()
    {
        for(int j=0;j<r;j++)
            for(int n=0;n<c;n++)
              m[j][n]=1;
    }
    //----------------------------
    void  matrix::sub(int p ,matrix* x)
    {
        int i,j;
        if(c!=x->c||r!=x->r)
        {
            cout<<"Sub: error coming"<<endl;
        }
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
                m[i][j]=p-(x->m[i][j]);
        }

    }
    //-----------------------------
    float  matrix::sumofmat()//check
    {
        int i,j;
        float sum=0;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
               sum+=m[i][j];
        }
        return sum;
    }
    //--------------------------------
    float  matrix::sumofrow (int num)// num number of colum
    {
        int i;
        float sum =0;
        for(i=0;i<c;i++)
            sum+=m[num][i];
        //cout<<"sum of row ="<<sum<<endl; //getch();
        return sum;
    }
    //---------------------------------------------------
    float  matrix::sumofcolum (int num)
    {
        int i;
        float sum =0;
        for(i=0;i<r;i++)
            sum+=m[i][num];
        return sum;
    }
    //--------------------------------
    void  matrix::Ediv(float d, matrix * x)//check
    {
        int i,j;
        if(c!=x->c||r!=x->r)
        {
            cout<<"Sub: error coming"<<endl;
        }
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
               m[i][j]=x->m[i][j]/d;
        }
    }
    //----------------------------------------
    void  matrix::Emult(float d ,matrix * x)
    {
        if (r!=x->r || c!=x->c)
        {
            cout<<"Not the same"<<endl;
        }
        else
        {
            for(int n=0; n<r; n++)
                for(int j=0; j<c; j++)
                   m[n][j]=d*x->m[n][j];
        }
    }
    //-----------------------------------------------------------
    void  matrix::geta(matrix * x, matrix * w,matrix * b)
    {
        float z=0;
        int i,j,k;
        if(x->r!=w->c||w->r!=b->r||b->c!=1)
            cout<<"Geta : Error input dimention "<<endl;

        if(r!=w->r||r!=b->r||c!=x->c)
            cout<<"Geta : Error output dimention"<<endl;
        else
        {
            for(k=0;k<x->c;k++)
            {
              for(j=0;j<w->r;j++)
                {
                  z=0;
                  for(i=0;i<w->c;i++) z+=w->m[j][i]*x->m[i][k];

                  z+=b->m[j][0];
                  m[j][k]=tanh(z);
                }
            }
        }
    }

    //-----------------------------------
    void  matrix::getdldz2(matrix * y,matrix * a)
    {
        if(c!=y->c||r!=y->r||y->r!=a->r||y->c!=a->c)
            cout<<"Error getdldz"<<endl;
        int i,j;
        for(i=0;i<y->r;i++)
            for(j=0;j<y->c;j++)
                m[i][j]=(y->m[i][j]-a->m[i][j])*(1-(a->m[i][j]*a->m[i][j]));
    }
    //-----------------------------------
float ** matD(int r, int c)
 {
   float ** m=new float* [r];
        for(int i=0; i<r; i++)
            m[i]=new float[c];
    return m;
 }
 //--------------------------------------------
 float * matD(int r)
 {
   float * m=new float [r];
    return m;
 }


     //-----------------------------------
int ** matI(int r, int c)
 {
   int ** m=new int* [r];
        for(int i=0; i<r; i++)
            m[i]=new int[c];
    return m;
 }

 //--------------------------------------------
 int * matI(int r)
 {
   int * m=new int [r];
    return m;
 }

//--------------------------------------------
 float** matDP(int r)
 {
   float** m=new float* [r];
    return m;
 }
 //-------------------------------------------
 void OutIm(float* pic, float* pic2)
 {
        int temp;
        static int num = 0;

        typedef struct                       /**** BMP file header structure ****/
            {
            unsigned int   bfSize;           /* Size of file */
            unsigned short bfReserved1;      /* Reserved */
            unsigned short bfReserved2;      /* ... */
            unsigned int   bfOffBits;        /* Offset to bitmap data */
            } BITMAPFILEHEADER;

        typedef struct                       /**** BMP file info structure ****/
            {
            unsigned int   biSize;           /* Size of info header */
            int            biWidth;          /* Width of image */
            int            biHeight;         /* Height of image */
            unsigned short biPlanes;         /* Number of color planes */
            unsigned short biBitCount;       /* Number of bits per pixel */
            unsigned int   biCompression;    /* Type of compression to use */
            unsigned int   biSizeImage;      /* Size of image data */
            int            biXPelsPerMeter;  /* X pixels per meter */
            int            biYPelsPerMeter;  /* Y pixels per meter */
            unsigned int   biClrUsed;        /* Number of colors used */
            unsigned int   biClrImportant;   /* Number of important colors */
            } BITMAPINFOHEADER;

        BITMAPFILEHEADER bfh;
        BITMAPINFOHEADER bih;

        /* Magic number for file. It does not fit in the header structure due to alignment requirements, so put it outside */
        unsigned short bfType=0x4d42;
        bfh.bfReserved1 = 0;
        bfh.bfReserved2 = 0;
        bfh.bfSize = 2+sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+10000*3;
        bfh.bfOffBits = 0x36;

        bih.biSize = sizeof(BITMAPINFOHEADER);
        bih.biWidth = 100;
        bih.biHeight = 100;
        bih.biPlanes = 1;
        bih.biBitCount = 24;
        bih.biCompression = 0;
        bih.biSizeImage = 0;
        bih.biXPelsPerMeter = 5000;
        bih.biYPelsPerMeter = 5000;
        bih.biClrUsed = 0;
        bih.biClrImportant = 0;

        char arr[50];
        char arr2[50];
        sprintf(arr,"image%d.bmp",num);
        sprintf(arr2,"image%d Original.bmp",num);

        FILE *file = fopen(arr, "wb");
        if (!file)
            {
            printf("Could not write file\n");
            return;
            }

        /*Write headers*/
        fwrite(&bfType,1,sizeof(bfType),file);
        fwrite(&bfh, 1, sizeof(bfh), file);
        fwrite(&bih, 1, sizeof(bih), file);

        /*Write bitmap*/
        for (int y = bih.biHeight-1; y>=0; y--) /*Scanline loop backwards*/
            {
            for (int x = 0; x < bih.biWidth; x++) /*Column loop forwards*/
                {
                /*compute some pixel values*/
                temp = (pic[(y*100) + x]*127.5) + 127.5;
                unsigned char r = temp;
                unsigned char g = temp;
                unsigned char b = temp;
                fwrite(&b, 1, 1, file);
                fwrite(&g, 1, 1, file);
                fwrite(&r, 1, 1, file);
                }
            }
        fclose(file);

        FILE *file2 = fopen(arr2, "wb");
        if (!file2)
            {
            printf("Could not write file\n");
            return;
            }

        /*Write headers*/
        fwrite(&bfType,1,sizeof(bfType),file2);
        fwrite(&bfh, 1, sizeof(bfh), file2);
        fwrite(&bih, 1, sizeof(bih), file2);

        /*Write bitmap*/
        for (int y = bih.biHeight-1; y>=0; y--) /*Scanline loop backwards*/
            {
            for (int x = 0; x < bih.biWidth; x++) /*Column loop forwards*/
                {
                /*compute some pixel values*/
                temp = (pic2[(y*100) + x]*127.5) + 127.5;
                unsigned char r = temp;
                unsigned char g = temp;
                unsigned char b = temp;
                fwrite(&b, 1, 1, file2);
                fwrite(&g, 1, 1, file2);
                fwrite(&r, 1, 1, file2);
                }
            }
        fclose(file2);
        num++;
 }

 void OutIm(float* pic)
 {
        int temp;
        static int num = 0;

        typedef struct                       /**** BMP file header structure ****/
            {
            unsigned int   bfSize;           /* Size of file */
            unsigned short bfReserved1;      /* Reserved */
            unsigned short bfReserved2;      /* ... */
            unsigned int   bfOffBits;        /* Offset to bitmap data */
            } BITMAPFILEHEADER;

        typedef struct                       /**** BMP file info structure ****/
            {
            unsigned int   biSize;           /* Size of info header */
            int            biWidth;          /* Width of image */
            int            biHeight;         /* Height of image */
            unsigned short biPlanes;         /* Number of color planes */
            unsigned short biBitCount;       /* Number of bits per pixel */
            unsigned int   biCompression;    /* Type of compression to use */
            unsigned int   biSizeImage;      /* Size of image data */
            int            biXPelsPerMeter;  /* X pixels per meter */
            int            biYPelsPerMeter;  /* Y pixels per meter */
            unsigned int   biClrUsed;        /* Number of colors used */
            unsigned int   biClrImportant;   /* Number of important colors */
            } BITMAPINFOHEADER;

        BITMAPFILEHEADER bfh;
        BITMAPINFOHEADER bih;

        /* Magic number for file. It does not fit in the header structure due to alignment requirements, so put it outside */
        unsigned short bfType=0x4d42;
        bfh.bfReserved1 = 0;
        bfh.bfReserved2 = 0;
        bfh.bfSize = 2+sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+10000*3;
        bfh.bfOffBits = 0x36;

        bih.biSize = sizeof(BITMAPINFOHEADER);
        bih.biWidth = 100;
        bih.biHeight = 100;
        bih.biPlanes = 1;
        bih.biBitCount = 24;
        bih.biCompression = 0;
        bih.biSizeImage = 0;
        bih.biXPelsPerMeter = 5000;
        bih.biYPelsPerMeter = 5000;
        bih.biClrUsed = 0;
        bih.biClrImportant = 0;

        char arr[50];
        sprintf(arr,"image%d.bmp",num);
        FILE *file = fopen(arr, "wb");
        if (!file)
            {
            printf("Could not write file\n");
            return;
            }

        /*Write headers*/
        fwrite(&bfType,1,sizeof(bfType),file);
        fwrite(&bfh, 1, sizeof(bfh), file);
        fwrite(&bih, 1, sizeof(bih), file);

        /*Write bitmap*/
        for (int y = bih.biHeight-1; y>=0; y--) /*Scanline loop backwards*/
            {
            for (int x = 0; x < bih.biWidth; x++) /*Column loop forwards*/
                {
                /*compute some pixel values*/
                temp = (pic[(y*100) + x]*127.5) + 127.5;
                unsigned char r = temp;
                unsigned char g = temp;
                unsigned char b = temp;
                fwrite(&b, 1, 1, file);
                fwrite(&g, 1, 1, file);
                fwrite(&r, 1, 1, file);
                }
            }
        fclose(file);
        num++;
 }

 float rms(float* mat1, float* mat2, int num)
 {
     float temp = 0.0;
     for(int i=0; i < num; i++)
     {
         temp+= ((mat1[i] - mat2[i])*(mat1[i] - mat2[i]));
     }
     temp = sqrt(temp);
     return temp;
 }

 void cop(float* empt, float* mat, int num)
 {
     for(int i=0; i < num; i++)
     {
         empt[i] = mat[i];
     }
 }

 void color(float* x, int siz)
 {
    for (int j = 0; j < siz; j++)
    {
        if(x[j]<-.6 ) cout<<char(32)<<char(32);
        else if(x[j]<-.2) cout<<char(176)<<char(176);
        else if(x[j]<.2) cout<<char(177)<<char(177);
        else if(x[j]<.56) cout<<char(178)<<char(178);
        else cout<<char(219)<<char(219);
    }
    cout<<endl;
 }

 void conv(float* Input, float* Filters, float* Out)
 {
    int OutLength = 98;
    int OutSize = OutLength * OutLength;
    int start = 0;
    for (int i = 0; i < OutSize; i++)
    {
        Out[i] = 0.0;
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                Out[i] += Input[start + col + (100*row)] * Filters[col + (row * 3)];
            }
        }
        if (start % 100 == 97) start += 3;
        else start++;
    }
 }

 void unmask(float* image)
 {
     float Im[98*98];
     float G[98*98];
     float Out[10000];
     float FilterGause[9] = {-1, -1, -1, -1, 9, -1, -1, -1, -1};
     float FilterUnit[9] =  { 0,   0, 0,  0, 1,  0,  0,  0,  0};
     conv(image, FilterGause, G);
     conv(image, FilterUnit, Im);
     add(Im,G,Out);



        int temp;
        static int num = 0;

        typedef struct                       /**** BMP file header structure ****/
            {
            unsigned int   bfSize;           /* Size of file */
            unsigned short bfReserved1;      /* Reserved */
            unsigned short bfReserved2;      /* ... */
            unsigned int   bfOffBits;        /* Offset to bitmap data */
            } BITMAPFILEHEADER;

        typedef struct                       /**** BMP file info structure ****/
            {
            unsigned int   biSize;           /* Size of info header */
            int            biWidth;          /* Width of image */
            int            biHeight;         /* Height of image */
            unsigned short biPlanes;         /* Number of color planes */
            unsigned short biBitCount;       /* Number of bits per pixel */
            unsigned int   biCompression;    /* Type of compression to use */
            unsigned int   biSizeImage;      /* Size of image data */
            int            biXPelsPerMeter;  /* X pixels per meter */
            int            biYPelsPerMeter;  /* Y pixels per meter */
            unsigned int   biClrUsed;        /* Number of colors used */
            unsigned int   biClrImportant;   /* Number of important colors */
            } BITMAPINFOHEADER;

        BITMAPFILEHEADER bfh;
        BITMAPINFOHEADER bih;

        /* Magic number for file. It does not fit in the header structure due to alignment requirements, so put it outside */
        unsigned short bfType=0x4d42;
        bfh.bfReserved1 = 0;
        bfh.bfReserved2 = 0;
        bfh.bfSize = 2+sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+100*100*3;
        bfh.bfOffBits = 0x36;

        bih.biSize = sizeof(BITMAPINFOHEADER);
        bih.biWidth = 100;
        bih.biHeight = 100;
        bih.biPlanes = 1;
        bih.biBitCount = 24;
        bih.biCompression = 0;
        bih.biSizeImage = 0;
        bih.biXPelsPerMeter = 5000;
        bih.biYPelsPerMeter = 5000;
        bih.biClrUsed = 0;
        bih.biClrImportant = 0;

        char arr[50];
        sprintf(arr,"image%d Sharpened.bmp",num);
        FILE *file = fopen(arr, "wb");
        if (!file)
            {
            printf("Could not write file\n");
            return;
            }

        /*Write headers*/
        fwrite(&bfType,1,sizeof(bfType),file);
        fwrite(&bfh, 1, sizeof(bfh), file);
        fwrite(&bih, 1, sizeof(bih), file);

        /*Write bitmap*/
        for (int y = bih.biHeight-1; y>=0; y--) /*Scanline loop backwards*/
            {
            for (int x = 0; x < bih.biWidth; x++) /*Column loop forwards*/
                {
                /*compute some pixel values*/
                temp = (Out[(y*100) + x]*127.5) + 127.5;
                unsigned char r = temp;
                unsigned char g = temp;
                unsigned char b = temp;
                fwrite(&b, 1, 1, file);
                fwrite(&g, 1, 1, file);
                fwrite(&r, 1, 1, file);
                }
            }
        fclose(file);
        num++;

 }

 void add(float* a, float* b, float* out)
 {
     int start = 0;
     for(int i = 0; i < 100; i++)
     {
         for(int j = 0; j < 100; j++)
         {
             if( i < 1 || i > 98 || j < 1 || j > 98) out[j+(i*100)] = -1.0;
             else
             {
                 out[j+(i*100)] = 0.45*(a[start] + b[start]);
                 start++;
             }

         }
     }
 }
