a.out: main.o  Manhattan.o Euclidean.o Minkowski.o Canberra.o Chebyshev.o
	gcc -o a.out main.o Manhattan.o Euclidean.o Minkowski.o Canberra.o Chebyshev.o

main.o: main.cpp calculate/Distance.h calculate/Euclidean.h calculate/Minkowski.h calculate/Canberra.h calculate/Chebyshev.h calculate/Manhattan.h
	gcc -c -o main.o main.cpp

Manhattan.o: calculate/Manhattan.cpp
	gcc -c -o Manhattan.o calculate/Manhattan.cpp	

Euclidean.o: calculate/Euclidean.cpp
	gcc -c -o Euclidean.o calculate/Euclidean.cpp
Minkowski.o: calculate/Minkowski.cpp
	gcc -c -o Minkowski.o calculate/Minkowski.cpp

Canberra.o: calculate/Canberra.cpp
	gcc -c -o Canberra.o calculate/Canberra.cpp

Chebyshev.o: calculate/Chebyshev.cpp
	gcc -c -o Chebyshev.o calculate/Chebyshev.cpp

clean:
	rm -f *.o a.out
