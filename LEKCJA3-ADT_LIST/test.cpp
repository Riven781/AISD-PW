#include <iostream>
#include "arraylist.h"
#include "test.h"


void testArrayList() {
    ArrayList<int> list;

    //TESTY DLA METOD

    assert(list.empty());
    assert(list.size() == 0);

    list.push_back(10);
    list.push_back(20);
    list.push_back(-100);
    assert(!list.empty());
    assert(list.size() == 3);
    assert(list[0] == 10);
    assert(list[1] == 20);

    list.push_front(15);
    assert(list.size() == 4);
    assert(list[0] == 15);
    assert(list[1] == 10);
    assert(list[2] == 20);
    assert(list[3] == -100);

    list.pop_front();
    assert(list.size() == 3);
    assert(list[0] == 10);
    assert(list[1] == 20);

    list.pop_back();
    assert(list.size() == 2);
    assert(list[0] == 10);
    assert(list[1] == 20);


    list.clear();
    assert(list.empty());

    for (int i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    assert(list.size() == 10);
    assert(list.full());


    std::cout << "Test funkcji  display: " << std::endl;
    list.display(); 

    list.erase(5); 
    assert(list.size() == 9);
  
    assert(list.index(0) == 0);
    assert(list.index(5) == -1); 

    list.insert(5, 50); 
    assert(list[5] == 50);
    assert(list.size() == 10);

    assert(list.front() == 0);
    assert(list.back() == 9);
    
    list.reverse();
    assert(list.front() == 9);
    assert(list.back() == 0);
    
    list.sort();
    assert(list.front() == 0);
    assert(list.back() == 50);

    assert(list.index(50) == 9);

    //TESTY DLA KONSTRUKTORA KOPIUJACEGO I OPERATORA =:

    ArrayList<int>list2(list);

    assert(list2.size() == list.size());

    for (int i = 0; i < list2.size(); ++i){
        assert(list[i] == list2[i]);
    }

    ArrayList<double> listDouble;

    listDouble.push_back(6.35);
    listDouble.push_back(0.5);
    listDouble.push_back(2.5);
    listDouble.push_back(-4.5);

    ArrayList<double> listDouble2;

    listDouble2.push_back(90.35);
    listDouble2.push_back(44.5);
    listDouble2.push_back(21.5);
    listDouble2.push_back(-44.5);
    listDouble2.push_back(-100.5);
    listDouble2.push_back(-1040.5);

    listDouble = listDouble2;

    assert(listDouble.size() == listDouble2.size());

    for (int i = 0; i < listDouble.size(); ++i){
        assert(listDouble[i] == listDouble2[i]);
    }

    //std::cout << list << std::endl;

    std::cout << "Testy zostaly zakonczone pomyslnie" << std::endl;
}
