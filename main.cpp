#include "matrix.h"

using namespace std;

int main()
{
  try
  {

  CMatrix a(2,3,32,44);
  CMatrix b(3,2,100,36);


  CMatrix c(a);
  cout << c;


  fstream f1;
  f1.open("plik.txt", ios::in);

  CMatrix d(f1);

  c=a*b;
  cout << c;

  b=d;

  cout << b[0][0];

  d[0][0]=5;

  cout << d;
  cout << endl;
  cout << b;


  }
  catch(CMatrix::WrongDim)
  {
    cout << "Wrong Matrix Dimensions" << endl;
  }
  catch(CMatrix::FileReadError)
  {
    cout << "Blad odczytu pliku" << endl;
  }
  catch(CMatrix::IndexOutOfRange)
  {
    cout << "Index Out of Range" << endl;
  }
  catch(bad_alloc)
  {
    cout << "Blad alokacji pamieci" << endl;
  }
  
    
    return 0;
}
