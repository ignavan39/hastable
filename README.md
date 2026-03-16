# C++ Hash Table with Custom Hash Functions

[![CI/CD Pipeline](https://github.com/ignavan39/cpp-hashtable/actions/workflows/ci.yml/badge.svg)](https://github.com/ignavan39/cpp-hashtable/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)


## Статус сборки

| ОС | Release | Debug |
|---|---|---|
| Ubuntu | ![Ubuntu Release](https://github.com/ignavan39/cpp-hashtable/actions/workflows/ci.yml/badge.svg) | ![Ubuntu Debug](https://github.com/ignavan39/cpp-hashtable/actions/workflows/ci.yml/badge.svg) |
| macOS | ![macOS Release](https://github.com/ignavan39/cpp-hashtable/actions/workflows/ci.yml/badge.svg) | ![macOS Debug](https://github.com/ignavan39/cpp-hashtable/actions/workflows/ci.yml/badge.svg) |
| Windows | ![Windows Release](https://github.com/ignavan39/cpp-hashtable/actions/workflows/ci.yml/badge.svg) | ![Windows Debug](https://github.com/ignavan39/cpp-hashtable/actions/workflows/ci.yml/badge.svg) |


Реализация хеш-таблицы на C++ с собственными алгоритмами хеширования.

## Мотивация

Мне долгое время не давало покоя старая лабораторная работа из универских готов с хэш таблицей
и мне кажется, что в прошлой ее реализции 6 лет назад
https://github.com/ignavan39/hashtable

проект был написан
без особого энтузиазма и полного понимания стандартных алгоритмов хеширования.

Я постарался сделать это проект более удобным и понятным, чтобы не забыть
о стандартных алгоритмах хеширования и понять, как они работают.
еще хочется больше практики в c++

## Алгоритмы хеширования

В проекте реализованы 3 алгоритма:

1. **DJB2** (Daniel J. Bernstein)
   - Формула: `hash = hash * 33 + char`
   - Быстрый, хорошее распределение для строк

2. **FNV-1a** (Fowler-Noll-Vo)
   - Формула: `hash = (hash ^ byte) * prime`
   - Отличное распределение, используется во многих системах

3. **Simple Multiplicative**
   - Формула: `hash = key * constant`
   - Учебный алгоритм, демонстрирует основы

## Сборка

```bash
# Release сборка (оптимизированная)
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel

# Debug сборка (с отладочной информацией)
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## Запуск

запуск src чтобы поиграться и проверить работоспособность

```bash
./build/hash_table_demo 
```

## Пример использования

```c++
// С хеш-функцией по умолчанию (DJB2)
HashTable<std::string, int> table1;

// С конкретной хеш-функцией
HashTable<std::string, int, FNV1aHash> table2;
```

