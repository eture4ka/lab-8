#include "DoublyList.h"
#include <iostream>

using namespace std;

DoublyList::DoublyList() : head(nullptr), tail(nullptr), count(0) {
    cout << "[Конструктор DoublyList] створено порожній список\n";
}

DoublyList::~DoublyList() {
    int n = count;                                       // запам'ятовуємо, скільки вузлів буде видалено
    clear();                                             // коректно звільняємо всю пам'ять
    cout << "[Деструктор DoublyList] видалено вузлів: " << n << "\n";
}

Node* DoublyList::find(const Transistor& value) const {
    for (Node* p = head; p; p = p->next)                 // йдемо від head до tail
        if (p->data == value) return p;                  // перше збігання за значенням
    return nullptr;                                      // не знайдено
}

// ---------- Додавання ----------

bool DoublyList::pushFront(const Transistor& value) {
    if (!isValid(value)) return false;                   // некоректні дані не додаємо
    Node* n = new Node(value);
    n->next = head;                                      // новий вузол вказує на старий head
    if (head) head->prev = n;                            // старий head вказує назад на новий
    else tail = n;                                       // список був порожній: новий вузол є і tail
    head = n;
    ++count;
    cout << "  > додано на початок: " << value << "\n";
    return true;
}

bool DoublyList::pushBack(const Transistor& value) {
    if (!isValid(value)) return false;
    Node* n = new Node(value);
    n->prev = tail;                                      // новий вузол вказує назад на старий tail
    if (tail) tail->next = n;                            // старий tail вказує вперед на новий
    else head = n;                                       // список був порожній: новий вузол є і head
    tail = n;
    ++count;
    cout << "  > додано в кінець: " << value << "\n";
    return true;
}

bool DoublyList::insertAfter(const Transistor& target, const Transistor& value) {
    if (!isValid(value)) return false;
    Node* p = find(target);                              // шукаємо елемент, після якого вставляємо
    if (!p) {
        cout << "  ! Помилка: елемент \"" << target.type << "\" не знайдено, вставка неможлива.\n";
        return false;
    }
    Node* n = new Node(value);
    n->prev = p;                                         // новий вузол між p і p->next
    n->next = p->next;
    if (p->next) p->next->prev = n;                      // наступний вузол вказує назад на новий
    else tail = n;                                       // p був останнім: новий стає tail
    p->next = n;
    ++count;
    cout << "  > вставлено після \"" << target.type << "\": " << value << "\n";
    return true;
}

// ---------- Видалення ----------

bool DoublyList::popFront() {
    if (!head) {
        cout << "  ! Помилка: список порожній, видаляти нічого.\n";
        return false;
    }
    Node* t = head;
    head = head->next;                                   // head зсувається на наступний вузол
    if (head) head->prev = nullptr;                      // новий head не має попереднього
    else tail = nullptr;                                 // список став порожнім
    cout << "  > видалено з початку: " << t->data << "\n";
    delete t;
    --count;
    return true;
}

bool DoublyList::popBack() {
    if (!tail) {
        cout << "  ! Помилка: список порожній, видаляти нічого.\n";
        return false;
    }
    Node* t = tail;
    tail = tail->prev;                                   // tail зсувається на попередній вузол
    if (tail) tail->next = nullptr;                      // новий tail не має наступного
    else head = nullptr;                                 // список став порожнім
    cout << "  > видалено з кінця: " << t->data << "\n";
    delete t;
    --count;
    return true;
}

bool DoublyList::removeByValue(const Transistor& value) {
    Node* p = find(value);
    if (!p) {
        cout << "  ! Помилка: елемент \"" << value.type << "\" не знайдено.\n";
        return false;
    }
    if (p->prev) p->prev->next = p->next;                // попередній пропускає p
    else head = p->next;                                 // p був head
    if (p->next) p->next->prev = p->prev;                // наступний пропускає p
    else tail = p->prev;                                 // p був tail
    cout << "  > видалено за значенням: " << p->data << "\n";
    delete p;
    --count;
    return true;
}

// ---------- Виведення ----------

void DoublyList::printForward() const {
    if (!head) {
        cout << "  (список порожній)\n";
        return;
    }
    int i = 1;
    for (Node* p = head; p; p = p->next, ++i)            // від head до tail
        cout << "  " << i << ". " << p->data << "\n";
}

void DoublyList::printBackward() const {
    if (!tail) {
        cout << "  (список порожній)\n";
        return;
    }
    int i = count;
    for (Node* p = tail; p; p = p->prev, --i)            // від tail до head
        cout << "  " << i << ". " << p->data << "\n";
}

// ---------- Службові ----------

bool DoublyList::isEmpty() const { return head == nullptr; }
int DoublyList::size() const { return count; }

void DoublyList::clear() {
    while (head) {
        Node* next = head->next;                         // спершу запам'ятовуємо наступний
        delete head;                                     // потім видаляємо поточний
        head = next;
    }
    tail = nullptr;
    count = 0;
}
