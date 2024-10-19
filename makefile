default:
	g++ -std=c++11 -Wall -o main.out main.cpp HashTable.cpp
	@if [ -f ./main.out ]; then ./main.out; else echo "Compilation failed or main.out not found."; fi

clean:
	rm *.out
