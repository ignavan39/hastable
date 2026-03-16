#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <string>
#include <cstdint>
#include <type_traits>


struct DJB2Hash {
    size_t operator()(const std::string& str) const {
        uint64_t hash = 5381;
        for (char c : str) {
            hash = ((hash << 5) + hash) + static_cast<unsigned char>(c);
        }
        return static_cast<size_t>(hash);
    }

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, size_t>::type
    operator()(const T& value) const {
        uint64_t hash = 5381;
        uint64_t num = static_cast<uint64_t>(value);
        for (size_t i = 0; i < sizeof(T); ++i) {
            hash = ((hash << 5) + hash) + ((num >> (i * 8)) & 0xFF);
        }
        return static_cast<size_t>(hash);
    }
};

struct FNV1aHash {
    static constexpr uint64_t FNV_PRIME = 1099511628211ULL;
    static constexpr uint64_t FNV_OFFSET = 14695981039346656037ULL;

    size_t operator()(const std::string& str) const {
        uint64_t hash = FNV_OFFSET;
        for (char c : str) {
            hash ^= static_cast<unsigned char>(c);
            hash *= FNV_PRIME;
        }
        return static_cast<size_t>(hash);
    }

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, size_t>::type
    operator()(const T& value) const {
        uint64_t hash = FNV_OFFSET;
        uint64_t num = static_cast<uint64_t>(value);
        for (size_t i = 0; i < sizeof(T); ++i) {
            hash ^= ((num >> (i * 8)) & 0xFF);
            hash *= FNV_PRIME;
        }
        return static_cast<size_t>(hash);
    }
};

struct SimpleHash {
    static constexpr size_t MULTIPLIER = 2654435761ULL; // Константа Кнута

    template <typename T>
    size_t operator()(const T& value) const {
        if constexpr (std::is_same<T, std::string>::value) {
            size_t sum = 0;
            for (char c : value) {
                sum += static_cast<unsigned char>(c);
            }
            return (sum * MULTIPLIER);
        } else {
            return static_cast<size_t>(value) * MULTIPLIER;
        }
    }
};

inline size_t compressHash(size_t hash, size_t bucketCount) {
    return hash % bucketCount;
}

#endif // HASH_FUNCTIONS_H