#include "mypriorityqueue.h"
#include "test.h"
#include <iostream>
#include <cassert>

void test(){
    MyPriorityQueue<int> priorityQueue;

    assert(priorityQueue.size() == 0);   //kolejka priorytetowa jest pusta
    assert(priorityQueue.empty());

    priorityQueue.push(3);  // {3}

    assert(priorityQueue.top() == 3);

    priorityQueue.display();

    assert(priorityQueue.size() == 1);

    priorityQueue.push(4);   //{4, 3}

    assert(priorityQueue.top() == 4);

    priorityQueue.display();

    assert(priorityQueue.size() == 2);

    priorityQueue.push(5); // {5, 4, 3}

    assert(priorityQueue.top() == 5);

    priorityQueue.display();

    assert(priorityQueue.size() == 3);

    priorityQueue.pop();  // {4,3}

    priorityQueue.display();

    priorityQueue.push(2);  // {4,3,2}

    assert(priorityQueue.size() == 3);

    priorityQueue.display();

    assert(priorityQueue.top() == 4);

    priorityQueue.clear();

    assert(priorityQueue.empty());

    //TESTY KONSTRUKTOROW I OPERATOROW =

    MyPriorityQueue<int> priorityQueue1;

    priorityQueue1.push(9);
    priorityQueue1.push(1);
    priorityQueue1.push(5);

    std::cout << "priorityQueue1:" << std::endl;
    priorityQueue1.display();

    MyPriorityQueue<int> priorityQueue2(priorityQueue1);

    std::cout << "priorityQueue2:" << std::endl;
    priorityQueue2.display();

    assert(priorityQueue1.size() == priorityQueue2.size());

    priorityQueue1.pop();

    assert(priorityQueue1.size() != priorityQueue2.size());


    MyPriorityQueue<int> priorityQueue3;

    for (size_t i = 0; i < 10; i++)
    {
        priorityQueue3.push(i);
    }

    

    std::cout << "priorityQueue3 przed uzyciem operatora =:" << std::endl;
    priorityQueue3.display();

    priorityQueue3 = priorityQueue2;

    std::cout << "priorityQueue3:" << std::endl;
    priorityQueue3.display();

    std::cout << "priorityQueue2:" << std::endl;
    priorityQueue2.display();

    assert(priorityQueue2.size() == priorityQueue3.size());

    priorityQueue2.pop();

    assert(priorityQueue2.size() != priorityQueue3.size());


    std::cout << "Testy zostaly zakonczone pomyslnie" << std::endl;

}