#include "test.h"
#include "singlelist.h"
#include <iostream>




void testSingleList(){
    SingleList<int> listInt;

    assert(listInt.empty());

    const int liczbaElementow = 10;

    for (int i = 0; i < liczbaElementow; i++)
    {
        listInt.push_front(i * 2);
    }

    listInt.display();

    assert(!listInt.empty());
    assert(listInt.size() == liczbaElementow);

    for (int i = 0; i < liczbaElementow; i++)
    {
        listInt.push_back(i * 3);
    }

    listInt.display();
    assert(listInt.size() == liczbaElementow * 2);

    assert(listInt.front() == 18);
    assert(listInt.back() == 27);

    listInt.reverse();
    listInt.display();

    assert(listInt.front() == 27);
    assert(listInt.back() == 18);

    listInt.pop_front();

    assert(listInt.front() == 24);

    listInt.pop_back();

    assert(listInt.back() == 16);

    listInt.clear();

    assert(listInt.empty());
    assert(listInt.size() == 0);
 
    SingleList<double> listDouble;

    for (int i = 0; i < liczbaElementow; i++)
    {
        listDouble.push_back(i);
    }
    SingleList<double> listDouble2(listDouble);

    assert(!listDouble.empty());

    assert(listDouble.size() == listDouble2.size());

    for (int i = 0; i < liczbaElementow; i++)
    {
        assert(listDouble.front() == listDouble2.front());
        listDouble.pop_front();
        listDouble2.pop_front();
    }
    
    assert(listDouble.empty() && listDouble2.empty());

    SingleList<double> listDouble3;

    for (int i = 0; i < liczbaElementow; i++)
    {
        listDouble3.push_front(i);
    }

    assert(listDouble3.size() == liczbaElementow);

    listDouble2 = listDouble3;

    assert(listDouble2.size() == listDouble3.size());

    for (int i = 0; i < liczbaElementow; i++)
    {
        assert(listDouble2.front() == listDouble3.front());
        listDouble2.pop_front();
        listDouble3.pop_front();
    }


    std::cout << "Testy zostaly zakonczone pomyslnie" << std::endl;
}