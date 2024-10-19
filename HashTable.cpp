#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;         // Hash table storage
    std::vector<bool> occupied;     // Track occupied spots in the table
    int size;                       // Current size of the hash table
    int count;                      // Number of elements in the hash table
    const double loadFactorThreshold = 0.8; // Load factor threshold for resizing

    // Helper function to find the next prime number greater than a given number
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

    // Hash function: key mod size of the table
    int hashFunction(int key) {
        return key % size;
    }

    // Quadratic probing: h(k) + i^2 mod m
    int quadraticProbe(int key, int i) {
        return (hashFunction(key) + i * i) % size;
    }

    // Resize the hash table when load factor exceeds threshold
    void resize() {
        int newSize = nextPrime(size * 2);  // Get the next prime size
        std::vector<int> oldTable = table;
        std::vector<bool> oldOccupied = occupied;

        // Resize the table
        table = std::vector<int>(newSize, -1);
        occupied = std::vector<bool>(newSize, false);
        size = newSize;
        count = 0;

        // Rehash all elements into the new table
        for (int i = 0; i < oldTable.size(); i++) {
            if (oldOccupied[i]) {
                insert(oldTable[i]);
            }
        }
    }

public:
    // Constructor
    HashTable(int initialSize) {
        size = nextPrime(initialSize);
        table.resize(size, -1);
        occupied.resize(size, false);
        count = 0;
    }

    // Insert a key into the hash table
    void insert(int key) {
        if (static_cast<double>(count) / size > loadFactorThreshold) {
            resize();
        }

        // Check for duplicate keys
        if (search(key) != -1) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        int i = 0;
        while (i < size) {
            int idx = quadraticProbe(key, i);
            if (!occupied[idx]) {
                table[idx] = key;
                occupied[idx] = true;
                count++;
                return;
            }
            i++;
        }

        std::cout << "Max probing limit reached!" << std::endl;
    }

    // Search for a key in the hash table. Returns the index or -1 if not found.
    int search(int key) {
        int i = 0;
        while (i < size) {
            int idx = quadraticProbe(key, i);
            if (!occupied[idx]) return -1;  // Key not in the table
            if (table[idx] == key) return idx;
            i++;
        }
        return -1;
    }

    // Remove a key from the hash table
    void remove(int key) {
        int idx = search(key);
        if (idx == -1) {
            std::cout << "Element not found" << std::endl;
            return;
        }
        occupied[idx] = false;
        count--;
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < size; i++) {
            if (occupied[i])
                std::cout << table[i] << " ";
            else
                std::cout << "- ";
        }
        std::cout << std::endl;
    }
};
