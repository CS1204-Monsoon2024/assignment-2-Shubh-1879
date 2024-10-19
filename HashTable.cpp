#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;     
    std::vector<int> values; // To store corresponding values
    int size;                   
    int count;                  
    int EMPTY;            
    int DELETED;          
    double loadFactorThreshold; 

    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    int hashFunction(int key) {
        return key % size;
    }

    void resize() {
        int oldSize = size;
        std::vector<int> oldTable = table;
        std::vector<int> oldValues = values;
        size = nextPrime(2 * oldSize);
        table = std::vector<int>(size, EMPTY);
        values = std::vector<int>(size, 0); // Initialize values
        count = 0;

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != EMPTY && oldTable[i] != DELETED) {
                insert(oldTable[i], oldValues[i]); // Reinsert old keys and values
            }
        }
    }

public:
    HashTable(int initialSize)
        : EMPTY(-1), DELETED(-2), loadFactorThreshold(0.8) { 
        size = nextPrime(initialSize);  
        table = std::vector<int>(size, EMPTY);  
        values = std::vector<int>(size, 0); // Initialize values
        count = 0;  
    }

    void insert(int key, int value) {
        if ((double)count / size > loadFactorThreshold) {
            resize();
        }

        int idx = hashFunction(key);
        int i = 0;
        while (i < size) {  
            int probeIdx = (idx + i * i) % size;
            if (table[probeIdx] == EMPTY || table[probeIdx] == DELETED) {
                table[probeIdx] = key;
                values[probeIdx] = value; // Store the value
                count++;
                return;
            } else if (table[probeIdx] == key) {
                values[probeIdx] = value; // Update the value if key exists
                return;
            }
            i++;
        }
    }

    int search(int key) {
        int idx = hashFunction(key);
        int i = 0;
        while (i < size) {
            int probeIdx = (idx + i * i) % size;
            if (table[probeIdx] == EMPTY) {
                return -1;  
            } else if (table[probeIdx] == key) {
                return values[probeIdx]; // Return the corresponding value
            }
            i++;
        }
        return -1;  
    }

    void remove(int key) {
        int idx = hashFunction(key);
        int i = 0;
        while (i < size) {
            int probeIdx = (idx + i * i) % size;
            if (table[probeIdx] == EMPTY) {
                return; // Key not found
            } else if (table[probeIdx] == key) {
                table[probeIdx] = DELETED; // Mark as deleted
                count--;
                return;
            }
            i++;
        }
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] == EMPTY || table[i] == DELETED) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << ":" << values[i] << " "; // Print key:value pairs
            }
        }
        std::cout << std::endl;
    }
};
