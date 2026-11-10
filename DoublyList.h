#pragma once

#include "Node.h"

// Двозв'язний список транзисторів
class DoublyList {
private:
    Node* head;    // перший вузол
    Node* tail;    // останній вузол
    int count;     // кількість вузлів

    Node* find(const Transistor& value) const;   // пошук першого вузла із заданим значенням

public:
    DoublyList();
    ~DoublyList();                                        // видаляє всі вузли
    DoublyList(const DoublyList&) = delete;               // копіювання заборонене (клас володіє вузлами)
    DoublyList& operator=(const DoublyList&) = delete;

    // ---- Додавання ----
    bool pushFront(const Transistor& value);                              // на початок
    bool pushBack(const Transistor& value);                               // у кінець
    bool insertAfter(const Transistor& target, const Transistor& value);  // після вказаного елемента

    // ---- Видалення ----
    bool popFront();                                      // з початку
    bool popBack();                                       // з кінця
    bool removeByValue(const Transistor& value);          // за значенням

    // ---- Виведення ----
    void printForward() const;                            // від head до tail
    void printBackward() const;                           // від tail до head

    // ---- Службові ----
    bool isEmpty() const;
    int size() const;
    void clear();                                         // видалення всіх вузлів
};
