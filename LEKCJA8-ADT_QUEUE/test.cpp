#include <iostream>
#include "test.h"
#include "myqueue.h"


void test(){
    MyQueue<int> kolejka;
    assert(kolejka.empty());
    for (size_t i = 0; i < 10; i++)
    {
        kolejka.push(i);   //kolejka = {0,1,2,3,4,5,6,7,8,9}
    }

    kolejka.display();

    assert(!kolejka.empty());
    assert(kolejka.size() == 10);

    assert(kolejka.back() == 9);
    assert(kolejka.front() == 0);
  
    kolejka.pop(); //kolejka = {1,2,3,4,5,6,7,8,9}

    kolejka.display();

    assert(kolejka.front() == 1);

    kolejka.push(10); //kolejka = {1,2,3,4,5,6,7,8,9,10}

    kolejka.display();

    assert(kolejka.back() == 10);

    kolejka.pop(); //kolejka = {2,3,4,5,6,7,8,9, 10}

    kolejka.display();

    assert(kolejka.front() == 2);
    assert(kolejka.back() == 10);

    kolejka.clear();

    kolejka.display();  //kolejka jest pusta

    assert(kolejka.empty());
    assert(kolejka.size() == 0);

    MyQueue<int> kolejka2;

    kolejka2.push(3);
    kolejka2.display();
    kolejka2.push(6);
    kolejka2.display();

    MyQueue<int> kolejka3(kolejka2);  //kolejka2 = kolejka3 = {3,6}

    kolejka2.display();
    kolejka3.display();

    assert(kolejka2.size() == kolejka3.size());
    assert(kolejka2.size() == 2);

    kolejka2.push(9); // kolejka2 = {3,6,9}

    assert(kolejka2.size() != kolejka3.size());
    assert(kolejka2.size() == 3);
    assert(kolejka2.back() == 9);
    assert(kolejka2.front() == 3);

    kolejka3.pop(); //kolejka3 = {6}

    assert(kolejka3.size() == 1);

    MyQueue<int> kolejka4;

    kolejka4 = kolejka3; //kolejka4 = kolejka3 = {6}

    assert(kolejka4.size() == kolejka3.size());

    kolejka4.pop(); //kolejka4 = {}

    assert(kolejka4.size() != kolejka3.size());

    kolejka4.empty();

    kolejka4.display(); //kolejka jest pusta
    


    std::cout << "Testy zostaly zakonczone pomyslnie" << std::endl;
    
}