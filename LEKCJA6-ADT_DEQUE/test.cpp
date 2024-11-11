#include <iostream>
#include <cassert>
#include "test.h"
#include "mydeque.h"

int testMyDeque(){
    MyDeque<int> deq = MyDeque<int>();

    deq.push_back(5);
    deq.push_back(6);

    assert(!deq.empty());

    deq.display_reversed();
    deq.display();

    assert(deq.back() == 6);

    deq.push_front(100);
    deq.push_front(200);

    assert(deq.front() == 200);

    deq.display_reversed();
    deq.display();

    deq.clear();

    assert(deq.empty());
    assert(!deq.full());

    for (int i = 0; i < 10; i++)
    {

        deq.push_front(i);
    }

    
    assert(deq.full());
    assert(!deq.empty());
    deq.pop_back();

    deq.display();

    assert(deq.front() == 9);
    assert(deq.back() == 1);

    deq.pop_front();

    assert(deq.front() == 8);

    //test konstruktora kopiującego

    MyDeque<int> deq2 = MyDeque<int>(deq);

    assert(deq.size() == deq2.size());

    for (size_t i = 0; i < deq.size(); i++)
    {
        assert(deq.front() == deq2.front());
        deq.pop_front();
        deq2.pop_front();
    }

    //test =

    MyDeque<int> deq3 = MyDeque<int>(5);
    
    assert(deq3.max_size() == 5);

    for (int i = 0; i < 5; i++)
    {
        deq3.push_front(i);
    }
    

    MyDeque<int> deq4 = MyDeque<int>(5);
    
    deq4 = deq3;

        assert(deq3.size() == deq4.size());

    for (size_t i = 0; i < deq3.size(); i++)
    {
        assert(deq3.front() == deq4.front());
        deq3.pop_front();
        deq4.pop_front();
    }
    
    std::cout << "Testy zostaly zakonczone pomyslnie" << std::endl;

    

    return 0;
}