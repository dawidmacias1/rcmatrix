CMatrix: CMatrix.o
	g++ -g -Wall -pedantic -fno-elide-constructors $^ -o $@

CMatrix.o: rcmatrix.cpp matrix.h
	g++ -g -c -Wall -pedantic -fno-elide-constructors $< -o $@

.PHONY: clean

clean:
	-rm CMatrix.o CMatrix

