#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include "HashFunctions.h"

template <typename K, typename V, typename HashFunc = DJB2Hash>
class HashTable {
private:
    struct Node {
        K key;
        V value;
        Node* next;

        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    std::vector<Node*> buckets;
    size_t numElements;
    size_t numBuckets;
    float maxLoadFactor;
    HashFunc hasher;

    size_t getBucketIndex(const K& key) const {
        size_t hashValue = hasher(key);
        return compressHash(hashValue, numBuckets);
    }

    void rehash() {
        size_t oldNumBuckets = numBuckets;
        std::vector<Node*> oldBuckets = buckets;

        numBuckets *= 2;
        numElements = 0;
        buckets = std::vector<Node*>(numBuckets, nullptr);

        for (size_t i = 0; i < oldNumBuckets; ++i) {
            Node* current = oldBuckets[i];
            while (current != nullptr) {
                Node* next = current->next;
                size_t newIndex = getBucketIndex(current->key);
                current->next = buckets[newIndex];
                buckets[newIndex] = current;
                numElements++;
                current = next;
            }
        }
    }

    void clearMemory() {
        for (size_t i = 0; i < numBuckets; ++i) {
            Node* current = buckets[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            buckets[i] = nullptr;
        }
        numElements = 0;
    }

public:
    HashTable(size_t initialSize = 16, float loadFactor = 0.75f) 
        : numElements(0), numBuckets(initialSize), maxLoadFactor(loadFactor) {
        buckets.resize(numBuckets, nullptr);
    }

    ~HashTable() {
        clearMemory();
    }

    void insert(const K& key, const V& value) {
        if ((float)(numElements + 1) / numBuckets > maxLoadFactor) {
            rehash();
        }

        size_t index = getBucketIndex(key);
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        Node* newNode = new Node(key, value);
        newNode->next = buckets[index];
        buckets[index] = newNode;
        numElements++;
    }

    V& get(const K& key) {
        size_t index = getBucketIndex(key);
        Node* current = buckets[index];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        throw std::out_of_range("Key not found");
    }

    const V& get(const K& key) const {
        size_t index = getBucketIndex(key);
        Node* current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) return current->value;
            current = current->next;
        }
        throw std::out_of_range("Key not found");
    }

    bool remove(const K& key) {
        size_t index = getBucketIndex(key);
        Node* current = buckets[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) buckets[index] = current->next;
                else prev->next = current->next;
                delete current;
                numElements--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    bool contains(const K& key) const {
        try { get(key); return true; } 
        catch (...) { return false; }
    }

    size_t size() const { return numElements; }
    bool empty() const { return numElements == 0; }

    void printDistribution() const {
        std::cout << "\n=== Bucket Distribution ===" << std::endl;
        size_t emptyBuckets = 0;
        size_t maxChain = 0;
        
        for (size_t i = 0; i < numBuckets; ++i) {
            size_t chainLen = 0;
            Node* current = buckets[i];
            while (current != nullptr) {
                chainLen++;
                current = current->next;
            }
            if (chainLen == 0) emptyBuckets++;
            if (chainLen > maxChain) maxChain = chainLen;
        }
        
        std::cout << "Total Buckets: " << numBuckets << std::endl;
        std::cout << "Empty Buckets: " << emptyBuckets << std::endl;
        std::cout << "Max Chain Length: " << maxChain << std::endl;
        std::cout << "Load Factor: " << (float)numElements / numBuckets << std::endl;
    }
};

#endif // HASHTABLE_H