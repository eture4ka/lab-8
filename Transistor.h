#pragma once

#include <ostream>
#include <string>

// Дані одного елемента списку: транзистор (варіант 18)
struct Transistor {
    std::string type;     // тип, наприклад "KT315B"
    double gain;          // коефіцієнт підсилення
    double maxCurrent;    // максимальний струм, А
};

// Порівняння за значенням (потрібне для пошуку та видалення за значенням)
bool operator==(const Transistor& a, const Transistor& b);

// Форматований вивід одного транзистора
std::ostream& operator<<(std::ostream& os, const Transistor& t);

// Перевірка коректності даних; при помилці виводить попередження і повертає false
bool isValid(const Transistor& t);
