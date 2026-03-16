#include <iostream>
#include <string>
#include <chrono>
#include "HashTable.h"
#include "HashFunctions.h"

template <typename HashFunc>
void testAlgorithm(const std::string& name) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "Testing: " << name << std::endl;
    std::cout << "========================================" << std::endl;

    HashTable<std::string, int, HashFunc> table(8, 0.75f);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        table.insert("key_" + std::to_string(i), i);
    }

    int sum = 0;
    for (int i = 0; i < 1000; ++i) {
        sum += table.get("key_" + std::to_string(i));
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Sum check: " << sum << std::endl;
    std::cout << "Time: " << duration.count() << " microseconds" << std::endl;
    table.printDistribution();
}

void testNumericHashing() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "Numeric Hashing Test" << std::endl;
    std::cout << "========================================" << std::endl;

    DJB2Hash djb2;
    FNV1aHash fnv1a;
    SimpleHash simple;

    std::cout << "Number | DJB2 | FNV-1a | Simple" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " | " 
                  << djb2(i) << " | " 
                  << fnv1a(i) << " | " 
                  << simple(i) << std::endl;
    }
}

int main() {
    std::cout << "=== Custom Hash Function Implementation ===" << std::endl;

    // 1. Тест числовых хешей
    testNumericHashing();

    // 2. Сравнение алгоритмов на строках
    testAlgorithm<DJB2Hash>("DJB2 Hash");
    testAlgorithm<FNV1aHash>("FNV-1a Hash");
    testAlgorithm<SimpleHash>("Simple Multiplicative Hash");

    // 3. Демонстрация коллизий на маленьком размере
    std::cout << "\n========================================" << std::endl;
    std::cout << "Collision Demo (Small Table)" << std::endl;
    std::cout << "========================================" << std::endl;
    
    HashTable<std::string, int, DJB2Hash> smallTable(4, 10.0f); // Размер 4, без ресайза
    smallTable.insert("A", 1);
    smallTable.insert("B", 2);
    smallTable.insert("C", 3);
    smallTable.insert("D", 4);
    smallTable.insert("E", 5); // Должна возникнуть коллизия
    smallTable.printDistribution();

    std::cout << "\nAll tests completed!" << std::endl;
    return 0;
}