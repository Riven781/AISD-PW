#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>
using namespace std;

class Container 
{protected:
    Container (){};
 public:
    virtual unsigned int Count () const = 0;
    virtual bool IsEmpty () const {return Count()==0;};
    virtual bool IsFull () const = 0;
    virtual void MakeNull() = 0;
 };
 

template <typename T>
class PriorityQueue : public Container
{
public:
    virtual void Enqueue (T element) = 0;
    virtual T  FindMin () const = 0;
    virtual T DequeueMin () = 0;
};

template <typename T>
class BinaryHeap : public PriorityQueue<T>
{
protected:
    int count;
	std::vector<T> data;
    
public:
	BinaryHeap (unsigned int n);
	BinaryHeap ();
	~BinaryHeap (){;};
	void MakeNull();
	void Enqueue (T element);
	T FindMin () const;
	T DequeueMin ();
	//bool IsEmpty () const {return Count()==0;};
    bool IsFull () const ;
    void Wypisz() const;
    unsigned int Count() const {return count;}
};

template <typename T>
BinaryHeap<T>::BinaryHeap (unsigned int n):count(0),data(n){};

template <typename T>
BinaryHeap<T>::BinaryHeap (): count(0), data() {};


template <typename T>
void BinaryHeap<T>::Wypisz() const{
    if (this->IsEmpty())
    {
        return;
    }
    
    int levels = static_cast<int>(std::log2(count)) + 1;
    int index = 0;
    for (size_t i = 0; i < levels; i++)
    {
        for (size_t j = 0; j < (int)pow(2, i); j++)
        {
            if (index < count)
            {
                std::cout << data[index] << " ";
                ++index;
            }
        }
        
        std::cout  << std::endl;
    }
    
}

template <typename T>
void BinaryHeap<T>::Enqueue (T element){
    if (IsFull()) {
        data.resize(data.size() * 2 + 3);
    }

    data[count] = element;
    int i = count;
    ++count;
    while (data[(i-1)/2] > data[i] && i > 0){
        swap(data[(i-1)/2], data[i]);
        i = (i-1)/2;
    }
}

template <typename T>
bool BinaryHeap<T>::IsFull () const{
    return count >= data.size();
}


template <typename T>
void BinaryHeap<T>::MakeNull(){
    count = 0;
}

template <typename T>
T BinaryHeap<T>::FindMin() const{
    if (this->IsEmpty()) {
        throw std::out_of_range("Heap is empty");
    }
    return data[0];
}


template <typename T>
T BinaryHeap<T>::DequeueMin() {
    if (this->IsEmpty()) {
        throw std::out_of_range("Heap is empty");
    }

    T data_return = data[0];
    data[0] = data[--count];

    int i = 0;
    while (true) {
        int left_child_index = 2 * i + 1;
        int right_child_index = 2 * i + 2;
        int smallest = i;

        if (left_child_index < count && data[left_child_index] < data[smallest]) {
            smallest = left_child_index;
        }
        if (right_child_index < count && data[right_child_index] < data[smallest]) {
            smallest = right_child_index;
        }

        if (smallest == i) {
            break;
        }
        std::swap(data[i], data[smallest]);
        i = smallest;
    }

    data[count] = T();

    return data_return;
}

void test(int length){
    BinaryHeap <int> kolejka(length);
    assert(kolejka.IsEmpty());
    std::cout << "Czy kolejka jest pusta? " << kolejka.IsEmpty() << std::endl;
    kolejka.Enqueue(5);
    assert(!kolejka.IsEmpty());
    std::cout << "Czy kolejka jest pusta? " << kolejka.IsEmpty() << std::endl;
    kolejka.Wypisz();
    assert(kolejka.FindMin() == 5); 
    std::cout <<"Minimum: " << kolejka.FindMin() << std::endl;
    kolejka.Enqueue(6);
    kolejka.Wypisz();
    assert(kolejka.FindMin() == 5); 
    std::cout <<"Minimum: " << kolejka.FindMin() << std::endl;
    kolejka.Enqueue(8);
    kolejka.Wypisz();
    assert(kolejka.FindMin() == 5);
    std::cout <<"Minimum: " << kolejka.FindMin() << std::endl;
    kolejka.Enqueue(3);
    kolejka.Wypisz();
    assert(kolejka.FindMin() == 3); 
    std::cout <<"Minimum: " << kolejka.FindMin() << std::endl;
    kolejka.Enqueue(9);
    kolejka.Wypisz();
    assert(kolejka.FindMin() == 3); 
    std::cout <<"Minimum: " << kolejka.FindMin() << std::endl;
    kolejka.Enqueue(2);
    kolejka.Wypisz();
    assert(kolejka.FindMin() == 2); 
    std::cout <<"Minimum: " << kolejka.FindMin() << std::endl;
    kolejka.Enqueue(1);
    kolejka.Wypisz();
    assert(kolejka.FindMin() == 1); 
    std::cout <<"Minimum: " << kolejka.FindMin() << std::endl;
    kolejka.DequeueMin();
    std::cout << "DequeueMin" << std::endl;
    kolejka.Wypisz();
    std::cout <<"Minimum: " << kolejka.FindMin() << std::endl;
    kolejka.DequeueMin();
    std::cout << "DequeueMin" << std::endl;
    kolejka.Wypisz();
    std::cout <<"Minimum: " << kolejka.FindMin() << std::endl;
    assert(kolejka.FindMin() == 3); 
    kolejka.MakeNull();
    assert(kolejka.IsEmpty());
    std::cout << "Czy kolejka jest pusta? " << kolejka.IsEmpty() << std::endl;


    std::cout << "TEST DLA dlugosci = " << length << " przeszedl pomyslnie" << std::endl;


}



int main(int argc, char const *argv[])
{
    std::cout << "Test dla dlugosci 10" << std::endl;
    test(10); 
    std::cout << "Test dla dlugosci 2" << std::endl;
    test(2); 

    return 0;
}
