#include "Transistor.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

bool operator==(const Transistor& a, const Transistor& b) {
    return a.type == b.type &&
           fabs(a.gain - b.gain) < 1e-9 &&               // числа з плаваючою крапкою порівнюємо з допуском
           fabs(a.maxCurrent - b.maxCurrent) < 1e-9;
}

ostream& operator<<(ostream& os, const Transistor& t) {
    ostringstream ss;                                    // форматуємо у локальному потоці, щоб не міняти налаштування cout
    ss << t.type << " | підсилення: " << fixed << setprecision(1) << t.gain
       << " | макс. струм: " << setprecision(2) << t.maxCurrent << " А";
    return os << ss.str();
}

bool isValid(const Transistor& t) {
    if (t.type.empty() || t.type.find_first_not_of(' ') == string::npos) {
        cout << "  ! Помилка: тип транзистора не може бути порожнім.\n";
        return false;
    }
    if (!(t.gain > 0 && t.gain <= 10000)) {              // такий запис відхиляє і NaN
        cout << "  ! Помилка: коефіцієнт підсилення " << t.gain
             << " некоректний (потрібно 0 < gain <= 10000).\n";
        return false;
    }
    if (!(t.maxCurrent > 0 && t.maxCurrent <= 100)) {
        cout << "  ! Помилка: струм " << t.maxCurrent
             << " А некоректний (потрібно 0 < I <= 100).\n";
        return false;
    }
    return true;
}
