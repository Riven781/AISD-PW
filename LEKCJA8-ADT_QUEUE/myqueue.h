#include <iostream>
#include <cassert>
#include <stack>


template <typename T>
class MyQueue {
    std::stack<T> stos1;
    std::stack<T> stos2;
public:
    MyQueue(){} // default constructor
    ~MyQueue(){};
    MyQueue(const MyQueue& other); // copy constructor
    MyQueue(MyQueue&& other); // move constructor
    MyQueue& operator=(const MyQueue& other); // copy assignment operator, return *this
    MyQueue& operator=(MyQueue&& other); // move assignment operator, return *this
    bool empty() const{return stos1.empty() && stos2.empty();} // checks if the container has no elements
    std::size_t size() const{return stos1.size() + stos2.size();} // liczba elementów w kolejce
    void push(const T& item); // dodanie na koniec, push_back(item)
    void push(T&& item); // dodanie na koniec, push_back(std::move(item))
    T& front(); // zwraca koniec, nie usuwa
    T& back(); // zwraca koniec, nie usuwa
    void pop(); // usuwa początek kolejki, pop_front()
    void clear(); // czyszczenie listy z elementów
    void display();
};



template <typename T>
MyQueue<T>::MyQueue(MyQueue&& other){
    stos1 = std::move(other.stos1);
    stos2 = std::move(other.stos2);

}


template <typename T>
MyQueue<T>::MyQueue(const MyQueue& other){
    stos1 = other.stos1;
    stos2 = other.stos2;
}

template <typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue& other){
    if (this != &other) {
        stos1 = other.stos1;
        stos2 = other.stos2;
    }
    return *this; 
}

template <typename T>
MyQueue<T>& MyQueue<T>::operator=(MyQueue&& other){
    if (this != &other) {
        stos1 = std::move(other.stos1);
        stos2 = std::move(other.stos2);
    }
    return *this; 
}



template <typename T>
void MyQueue<T>::push(const T& item) {
    stos1.push(item);
    
}

template <typename T>
void MyQueue<T>::push(T&& item) {
    stos1.push(std::move(item));
    
}

template <typename T>
void MyQueue<T>::pop(){
    if (!empty()){
        if (!stos2.empty()){
            stos2.pop();
        }
        else{
            while (!stos1.empty()) {
                stos2.push(stos1.top());
                stos1.pop();
            }
            stos2.pop();
        }
    }
}


template <typename T>
T& MyQueue<T>::front(){
    assert(!empty());
    
    if (!stos2.empty()){
        return stos2.top();
    }
    else{
        while (!stos1.empty())
        {
            stos2.push(stos1.top());
            stos1.pop();
        }
            
    
        return stos2.top();
    }
    
}

template <typename T>
T& MyQueue<T>::back(){
    assert(!empty());

    if(!stos1.empty()){

        return stos1.top();
    }
    else{

        while (!stos2.empty())
        {
            stos1.push(stos2.top());
            stos2.pop();
        }
        return stos1.top(); 
    }
}
  


template <typename T>
void MyQueue<T>::clear(){
    while(!stos1.empty()){
        stos1.pop();
    }
    while(!stos2.empty()){
        stos2.pop();
    }
}


template <typename T>
void MyQueue<T>::display(){
    if (!empty()){
        if (stos1.empty()){
            std::cout << "[" << " ";
            while (!stos2.empty())
            {
                std::cout << stos2.top() << " ";
                stos1.push(stos2.top());
                stos2.pop();
            }
            std::cout << "]" << std::endl;
        
        }
        else if (stos2.empty())
        {
            std::cout << "[" << " ";
            while (!stos1.empty())
            {
                stos2.push(stos1.top());
                stos1.pop();
            }
            while (!stos2.empty())
            {
                std::cout << stos2.top() << " ";
                stos1.push(stos2.top());
                stos2.pop();
            }
            std::cout << "]" << std::endl;
        }
        else{
            int rozmiarStosu1 = stos1.size();
            std::cout << "[" << " ";
            while (!stos2.empty())
            {
                std::cout << stos2.top() << " ";
                stos1.push(stos2.top());
                stos2.pop();
            }
            while (!stos1.empty())
            {
                stos2.push(stos1.top());
                stos1.pop();
            }
            for (int i = 0; i < rozmiarStosu1; i++)
            {
                std::cout << stos2.top() << " ";
                stos1.push(stos2.top());
                stos2.pop();
            }
            std::cout << "]" << std::endl;
        }
    }
    else{
       std::cout << "Kolejka jest pusta" << std::endl; 
    }
    

}