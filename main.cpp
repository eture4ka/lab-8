#include <iostream>
#include <limits>
#include <string>
#include "DoublyList.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Виняток: введення закінчилось (Ctrl+Z / Ctrl+D або кінець файлу)
struct InputEnded {};

// ---------- Допоміжне введення ----------

static string readString(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        if (!getline(cin, s)) throw InputEnded();          // кінець введення
        if (!s.empty() && s.find_first_not_of(' ') != string::npos) return s;
        cout << "  ! Помилка: рядок не може бути порожнім.\n";
    }
}

// Читає будь-яке число; чи воно в допустимих межах, перевіряє сам список
static double readNumber(const string& prompt) {
    double v;
    while (true) {
        cout << prompt;
        if (cin >> v) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        if (cin.eof()) throw InputEnded();                 // без цього цикл не мав би виходу
        cout << "  ! Помилка: введіть число.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

static int readMenu(const string& prompt, int minV, int maxV) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v && v >= minV && v <= maxV) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        if (cin.eof()) throw InputEnded();
        cout << "  ! Помилка: введіть число від " << minV << " до " << maxV << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

static Transistor readTransistor(const string& title) {
    cout << title << "\n";
    Transistor t;
    t.type = readString("  Тип: ");
    t.gain = readNumber("  Коефіцієнт підсилення: ");
    t.maxCurrent = readNumber("  Максимальний струм, А: ");
    return t;
}

// ---------- Демонстрація ----------

static void runDemo(DoublyList& list) {
    cout << "\n--- Перевірка: чи порожній список ---\n";
    cout << "  Порожній? " << (list.isEmpty() ? "так" : "ні") << "\n";

    cout << "\n--- Додавання в кінець та на початок ---\n";
    list.pushBack({"KT315B", 200.0, 0.1});
    list.pushBack({"IRF540N", 1500.0, 33.0});
    list.pushFront({"BC547", 110.0, 0.1});
    list.pushBack({"2N3055", 20.0, 15.0});

    cout << "\n--- Вивід вперед (head -> tail) ---\n";
    list.printForward();
    cout << "\n--- Вивід назад (tail -> head) ---\n";
    list.printBackward();

    cout << "\n--- Вставка після вказаного елемента ---\n";
    list.insertAfter({"IRF540N", 1500.0, 33.0}, {"2N2222", 100.0, 0.8});
    list.insertAfter({"NoSuch", 1.0, 1.0}, {"X", 10.0, 1.0});   // елемента немає
    list.printForward();

    cout << "\n--- Некоректні дані ---\n";
    list.pushBack({"", 100.0, 1.0});          // порожній тип
    list.pushBack({"Test", -5.0, 1.0});       // від'ємне підсилення
    list.pushBack({"Test", 100.0, 250.0});    // завеликий струм

    cout << "\n--- Видалення з початку, з кінця, за значенням ---\n";
    list.popFront();
    list.popBack();
    list.removeByValue({"2N2222", 100.0, 0.8});
    list.removeByValue({"2N2222", 100.0, 0.8});   // повторно: вже немає
    list.printForward();
    cout << "  Розмір списку: " << list.size() << "\n";

    cout << "\n--- Видалення всіх елементів по одному ---\n";
    while (!list.isEmpty()) list.popFront();
    list.popFront();                          // з порожнього списку
    list.printForward();
    cout << "  Порожній? " << (list.isEmpty() ? "так" : "ні") << "\n";

    cout << "\n--- Додаємо кілька елементів, щоб деструктор їх прибрав ---\n";
    list.pushBack({"KT315B", 200.0, 0.1});
    list.pushBack({"BC547", 110.0, 0.1});
}

// ---------- Меню ----------

static void runMenu(DoublyList& list) {
    while (true) {
        cout << "\n===== МЕНЮ =====\n"
             << " 1 - Додати на початок\n"
             << " 2 - Додати в кінець\n"
             << " 3 - Додати після елемента\n"
             << " 4 - Видалити з початку\n"
             << " 5 - Видалити з кінця\n"
             << " 6 - Видалити за значенням\n"
             << " 7 - Вивести від head до tail\n"
             << " 8 - Вивести від tail до head\n"
             << " 9 - Чи порожній список\n"
             << " 0 - Вихід\n";
        int c = readMenu("Ваш вибір: ", 0, 9);
        switch (c) {
            case 1: list.pushFront(readTransistor("Новий елемент:")); break;
            case 2: list.pushBack(readTransistor("Новий елемент:")); break;
            case 3: {
                Transistor target = readTransistor("Після якого елемента вставити (значення існуючого):");
                Transistor value = readTransistor("Новий елемент:");
                list.insertAfter(target, value);
                break;
            }
            case 4: list.popFront(); break;
            case 5: list.popBack(); break;
            case 6: list.removeByValue(readTransistor("Який елемент видалити (значення):")); break;
            case 7: list.printForward(); break;
            case 8: list.printBackward(); break;
            case 9: cout << "  Список " << (list.isEmpty() ? "порожній" : "не порожній")
                         << " (елементів: " << list.size() << ")\n"; break;
            case 0: return;
        }
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    cout << "===== Двозв'язний список. Варіант 18: Транзистор =====\n"
         << "Поля: тип, коефіцієнт підсилення, максимальний струм\n\n";

    DoublyList list;

    try {
        int mode = readMenu("1 - меню (ручне керування), 2 - автоматична демонстрація: ", 1, 2);
        if (mode == 1) runMenu(list);
        else runDemo(list);
    } catch (const InputEnded&) {
        cout << "\n  Введення завершено, виходимо з програми.\n";
    }

    cout << "\nЗавершення програми.\n";
    return 0;                                // деструктор list видалить усі вузли, що лишились
}
