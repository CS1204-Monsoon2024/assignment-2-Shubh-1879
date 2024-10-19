#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;
    std::vector<bool> occupied;
    std::vector<bool> deleted;
    int size;
    int count;
    const double loadFactorThreshold = 0.8;

    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    int nextPrime(int n) {
        while (!isPrime(n)) n++;
        return n;
    }

    int hashFunction(int key) {
        return key % size;
    }

    int quadraticProbe(int key, int i) {
        return (hashFunction(key) + i * i) % size;
    }

    void resize() {
        int newSize = nextPrime(size * 2);
        std::vector<int> oldTable = table;
        std::vector<bool> oldOccupied = occupied;
        std::vector<bool> oldDeleted = deleted;

        table = std::vector<int>(newSize, -1);
        occupied = std::vector<bool>(newSize, false);
        deleted = std::vector<bool>(newSize, false);
        size = newSize;
        count = 0;

        for (int i = 0; i < oldTable.size(); i++) {
            if (oldOccupied[i] && !oldDeleted[i]) {
                insert(oldTable[i]);
            }
        }
    }

public:
    HashTable(int initialSize) {
        size = nextPrime(initialSize);
        table.resize(size, -1);
        occupied.resize(size, false);
        deleted.resize(size, false);
        count = 0;
    }

    void insert(int key) {
        if (static_cast<double>(count) / size > loadFactorThreshold) {
            resize();
        }

        if (search(key) != -1) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        int i = 0;
        while (i < size) {
            int idx = quadraticProbe(key, i);
            if (!occupied[idx] || deleted[idx]) {
                table[idx] = key;
                occupied[idx] = true;
                deleted[idx] = false;
                count++;
                return;
            }
            i++;
        }

        std::cout << "Max probing limit reached!" << std::endl;
    }

    int search(int key) {
        int i = 0;
        while (i < size) {
            int idx = quadraticProbe(key, i);
            if (!occupied[idx] && !deleted[idx]) return -1;
            if (table[idx] == key && !deleted[idx]) return idx;
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
        deleted[idx] = true;
        count--;
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            if (occupied[i] && !deleted[i])
                std::cout << table[i] << " ";
            else
                std::cout << "- ";
        }
        std::cout << std::endl;
    }
};
