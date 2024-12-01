#include <vector>
#include <algorithm>   // make_heap, push_heap, pop_heap
#include <iostream>

template <typename T>
class MyPriorityQueue {
    std::vector<T> lst; // działa domyślny konstruktor dla std::vector
public:
    MyPriorityQueue(std::size_t s=10) { lst.reserve(s); } // default constructor
    ~MyPriorityQueue() { lst.clear(); }
    MyPriorityQueue(const MyPriorityQueue& other); // copy constructor
    MyPriorityQueue(MyPriorityQueue&& other); // move constructor
    MyPriorityQueue& operator=(const MyPriorityQueue& other); // copy assignment operator, return *this
    MyPriorityQueue& operator=(MyPriorityQueue&& other); // move assignment operator, return *this
    bool empty() const { return lst.empty(); }
    std::size_t size() const { return lst.size(); } // liczba elementów w kolejce
    void push(const T& item) { // dodanie do kolejki
        lst.push_back(item);
        std::push_heap(lst.begin(), lst.end());
    }
    void push(T&& item) { // dodanie do kolejki
        lst.push_back(std::move(item));
        std::push_heap(lst.begin(), lst.end());
    }
    T& top() { return lst.front(); } // zwraca element największy, nie usuwa
    void pop() { // usuwa element największy
        std::pop_heap(lst.begin(), lst.end());
        lst.pop_back();
    }
    void clear() { lst.clear(); } // czyszczenie listy z elementów
    void display();
};

template<typename T>
MyPriorityQueue<T>& MyPriorityQueue<T>::operator=(const MyPriorityQueue& other){
    if (this != &other) {
        lst = other.lst;
    }
    return *this;
}

template<typename T>
MyPriorityQueue<T>& MyPriorityQueue<T>::operator=(MyPriorityQueue&& other){
    if (this != &other) {
        lst = std::move(other.lst);
    }
    return *this;
}

template <typename T>
MyPriorityQueue<T>::MyPriorityQueue(const MyPriorityQueue& other){
    lst = other.lst;
}

template <typename T>
MyPriorityQueue<T>::MyPriorityQueue(MyPriorityQueue&& other){
    lst = std::move(other.lst);
}

template <typename T>
void MyPriorityQueue<T>::display(){
    std::sort_heap(lst.begin(), lst.end());
    for (auto it = lst.rbegin(); it != lst.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::make_heap(lst.begin(), lst.end());
}

