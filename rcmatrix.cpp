#include "matrix.h"

using namespace std;

int main()
{
	try
	{
	  	CMatrix A(2,3,3);
		CMatrix B(3,2,9,1);			
			
		cout << "Macierz A" << endl;				
		cout << A << endl;	
		
		cout << "Macierz B" << endl;	
		cout << B << endl;			
							
		cout << endl;

		CMatrix C = A * B;							
		cout << "Macierz C = A*B" << endl;	
		cout << C << endl;
		

		cout << "Macierz D (odczytana z pliku)" << endl;
		fstream f1;
		f1.open("plik.txt", ios::in);
		CMatrix D(f1);				
		f1.close();
		D[4][3] = 11;				
		cout << D << endl;

		CMatrix E;

		cout << "Macierz E" << endl;	
		
		E=D;		
		E[0][0] = 1.4;	
		cout << E << endl;				
		cout << "E[0][0]=" << E[0][0] << endl;		
		cout << "D[0][0]=" << D[0][0] << endl;	
		
	}
	catch(CMatrix::IndexOutOfRange)
	{
		cout << "Index Out of Range" << endl;
	}
	catch(CMatrix::WrongDim)
	{
		cout << "Wrong Matrix Dimensions" << endl;
	}
	catch(CMatrix::FileReadError)
	{
		cout << "File Read Error" << endl;
	}
	catch(bad_alloc)
	{
		cout << "Out of Memory" << endl;
	}
}
