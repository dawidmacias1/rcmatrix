#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class CMatrix{
  struct object;
  object* data;

};
public:
CMatrix(unsigned int ,unsigned int ,float, float);

struct CMatrix::object 
{
  float **m;
  unsigned int n;
  unsigned int col;
  unsigned int row;


  object(unsigned int ncol, unsigned int nrow) 
  {
  unsigned int i=0;
  n=1;
  col=ncol;
  row=nrow;
  m=new float *[col];
  for(i=0;i<col;i++)
    m[i]=new float[row];
  };


  ~object()
  {
  unsigned int i;
  for(i=0;i<col;i++)
    delete [] m[i];
  delete [] m;
  };

  object* detach()
  {
    if(n==1)
      return this;
    object* t=new object(col, row);
    copy(t->m);
    n--;
    return t;
  };

  void fill(float var, float ovar) 
  {
    unsigned int i;
    unsigned int j;
    for(i=0;i<col;i++)
      for(j=0;j<row;j++)
        if(i==j)
          m[i][j]=var;
        else
          m[i][j]=ovar;
  }

  void copy(float **p)
  {
    unsigned int i;
    unsigned int j;
    for(i=0;i<col;i++)
      for(j=0;j<row;j++)
        p[i][j]=m[i][j];
  }
};

CMatrix::CMatrix(unsigned int col=0, unsigned int row=0, float var=0, float ovar=0) 
{
  data=new object(col,row);
  data->fill(var, ovar);
}
