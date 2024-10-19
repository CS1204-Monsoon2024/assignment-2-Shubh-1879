#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
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

        size = nextPrime(2 * oldSize);
        table = std::vector<int>(size, EMPTY);
        count = 0;

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != EMPTY && oldTable[i] != DELETED) {
                insert(oldTable[i]);
            }
        }
    }

public:
    HashTable(int initialSize)
        : EMPTY(-1), DELETED(-2), loadFactorThreshold(0.8) {
        size = nextPrime(initialSize);
        table = std::vector<int>(size, EMPTY);
        count = 0;
    }

    void insert(int key) {
        if ((double)count / size > loadFactorThreshold) {
            resize();
        }

        int idx = hashFunction(key);
        int i = 0;
        int firstDeletedIdx = -1;

        while (i < size) {
            int probeIdx = (idx + i * i) % size;

            if (table[probeIdx] == EMPTY) {
                if (firstDeletedIdx != -1) {
                    table[firstDeletedIdx] = key;
                } else {
                    table[probeIdx] = key;
                }
                count++;
                return;
            } else if (table[probeIdx] == DELETED) {
                if (firstDeletedIdx == -1) {
                    firstDeletedIdx = probeIdx;
                }
            } else if (table[probeIdx] == key) {
                std::cout << "Duplicate key insertion is not allowed" << std::endl;
                return;
            }
            i++;
        }

        std::cout << "Max probing limit reached!" << std::endl;
    }

    int search(int key) {
        int idx = hashFunction(key);
        int i = 0;

        while (i < size) {
            int probeIdx = (idx + i * i) % size;

            if (table[probeIdx] == EMPTY) {
                return -1;
            } else if (table[probeIdx] == key) {
                return probeIdx;
            }
            i++;
        }
        return -1;
    }

    void remove(int key) {
        int idx = search(key);
        if (idx == -1) {
            std::cout << "Element not found" << std::endl;
            return;
        }
        table[idx] = DELETED;
        count--;
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] == EMPTY || table[i] == DELETED) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};
