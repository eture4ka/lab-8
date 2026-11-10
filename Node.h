#pragma once

#include "Transistor.h"

// Базовий клас елемента (вузла) двозв'язного списку
class Node {
public:
    Transistor data;   // корисні дані вузла
    Node* prev;        // вказівник на попередній вузол (nullptr для head)
    Node* next;        // вказівник на наступний вузол (nullptr для tail)

    explicit Node(const Transistor& value);
};
