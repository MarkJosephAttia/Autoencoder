#ifndef MATRIX_H
#define MATRIX_H
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include<ctime>
class matrix
   {
    private:
    public:
    float **m;
    const int r; // row
    const int c;  //colum
    matrix (int colum);
    matrix (int row,int colum);
   ~matrix () ;
    void Emult (matrix* x,matrix* z);
    void mult(matrix* x,matrix* z);
    void add (matrix* x,matrix* z);
    void sub(matrix* x,matrix* z);
    void sub(matrix* x);
    void eqaul(matrix* x);
    void fil();
    void print(char * str);
    void print2mat(matrix* x);
    void square(matrix* x);
    void Esquare(matrix* x);
    void transpose(matrix* x);
    void filrandnum(int p) ;
    void filrandfrac() ;
    void filone();
    void sub(int p ,matrix* x);
    float sumofmat();
    float sumofrow (int num);
    float sumofcolum (int num);
    void Ediv(float d, matrix * x);
    void Emult(float d ,matrix * x);
    void geta(matrix * x, matrix * w,matrix * b);
    void getdldz2(matrix * y,matrix * a);
    matrix* operator =(matrix* x);

////////////
};
 float ** matD(int r, int c);
 float * matD(int r);
 float** matDP(int r);
 int    ** matI(int r, int c);
 int     * matI(int r);
 void      OutIm(float* pic, float* pic2);
 void      bitmap(float* pic, float* pic2);
  void  OutIm(float* pic);
  float rms(float* mat1, float* mat2, int num);
  void cop(float* empt, float* mat, int num);
  void color(float* x, int siz);
  void unmask(float* image);
  void conv(float* Input, float* Filters, float* Out);
  void add(float* a, float* b, float* out);

#endif // MATRIX_H
