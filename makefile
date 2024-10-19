default:
	g++ -std=c++11 -Wall -o main.out main.cpp HashTable.cpp
	./main.out

clean:
	rm *.out
