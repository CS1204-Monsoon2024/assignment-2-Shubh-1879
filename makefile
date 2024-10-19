default:
	g++ -std=c++11 -Wall -o main.out main.cpp HashTable.cpp
	@echo "Running main.out..."
	@./main.out

clean:
	rm -f *.out
