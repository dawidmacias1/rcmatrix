#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class CMatrix{
  struct object;
  object* data;
public:
class WrongDim{};
class FileReadError{};
class IndexOutOfRange{};
class Cref2;
class Cref;
CMatrix(unsigned int ,unsigned int ,float, float);
CMatrix(fstream&);
CMatrix(const CMatrix&);
~CMatrix();
CMatrix operator*(const CMatrix&) const;
CMatrix& operator=(const CMatrix&);
friend ostream& operator<<(ostream&, const CMatrix&);
void check (unsigned int, unsigned int) const;
float read (unsigned int, unsigned int) const;
void write(unsigned int, unsigned int, float);
Cref2 operator[](unsigned int);
};

struct CMatrix::object 
{
  float **m;
  unsigned int n;
  unsigned int col;
  unsigned int row;


  object(unsigned int ncol, unsigned int nrow) 
  {
    unsigned int i=0;
    unsigned int j=0;
    n=1;
    col=ncol;
    row=nrow;
    m=new float *[col];

    try
    {
      for(i=0;i<col;i++)
        m[i]=new float[row];
    }
    catch(bad_alloc)
    {
     for(j=0;j<i;j++)
      delete [] m[j];
     delete [] m;
	throw;
    }
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

class CMatrix::Cref2
{
  friend class CMatrix; 
  CMatrix& s;
  unsigned int col;
  unsigned int row;
  Cref2 (CMatrix& ss, unsigned int i): s(ss), col(i){};
  public:
  class Cref;
  Cref operator[](unsigned int);
};

class CMatrix::Cref2::Cref
  {
  friend class Cref2;
  Cref2 &so;
  Cref (Cref2& sso): so(sso) {};
  public:

  operator float() const
  {
    return so.s.read(so.col,so.row);
  }

  CMatrix::Cref2::Cref& operator = (float f)
  {
    so.s.write(so.col,so.row,f);
    return *this;
  }

};

CMatrix::Cref2::Cref CMatrix::Cref2::operator[](unsigned int nrow)
{
  row=nrow;
  s.check(col,row);
  return Cref(*this);
}

CMatrix::CMatrix(unsigned int col=0, unsigned int row=0, float var=0, float ovar=0) 
{
  data=new object(col,row);
  data->fill(var, ovar);
}

CMatrix::CMatrix(fstream& f) 
{
  unsigned i=0,j =0;
  unsigned int col=0, row=0;
  if(!f.good())
    throw FileReadError();
  f >> col >> row;
  data=new object(col,row);
  for(i=0;i<col;i++)
    for(j=0;j<row;j++)
      f >> data->m[i][j];
}

CMatrix::CMatrix(const CMatrix & x)
{
    x.data->n++;
    data=x.data;
}

CMatrix::~CMatrix()
{
  if(--data->n==0)
    delete data;
}

CMatrix CMatrix::operator*(const CMatrix& x) const 
{
  CMatrix no(data->col,x.data->row,0,0);
  float s=0;
  unsigned int i=0,j=0,k=0;
  if(data->col!=x.data->row || data->row!=x.data->col)
    throw WrongDim();
  for(i=0;i<data->col;i++)
  {
    for(j=0;j<data->col;j++)
    {
      for(k=0;k<data->row;k++) 
        s+=data->m[i][k]*x.data->m[k][j];
    no.data->m[i][j]=s;
    s=0;
    }
  }
  return no;
}

CMatrix& CMatrix::operator=(const CMatrix & x) 
{
  x.data->n++;
  if(--data->n == 0)
    delete data;
  data=x.data;
  return *this;
}

ostream& operator << (ostream& o, const CMatrix& s)
{
  unsigned int i=0,j=0;
  o << "[  " << fixed;
  for(i=0;i<s.data->col;i++)
  {
    if(i!=0) o << "   ";
    for(j=0;j<s.data->row;j++)
      o << setprecision(1) << s.data->m[i][j] << "  ";
    if(i==s.data->col-1) cout << "]";
    o << endl;
  }
  return o;
}

void CMatrix::check (unsigned int i, unsigned int j) const
{
  if(data->col<=i || data->row<=j)
    throw IndexOutOfRange();
}
float CMatrix::read(unsigned int i, unsigned int j) const
{
  return data->m[i][j];
}

void CMatrix::write(unsigned int i, unsigned int j, float n)
{
  data = data->detach();
  data->m[i][j] = n;
}

CMatrix::Cref2 CMatrix::operator[](unsigned int i)
{
  return Cref2(*this,i);
}
