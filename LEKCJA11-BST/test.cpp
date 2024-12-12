#include "test.h"
#include <iostream>
#include <cassert>
#include <set>
#include <random>
#include <algorithm>

void test(){
    emptyTreeTest();
    stardardBSTTest();
    std::cout << "---------------------------------------------------" << std::endl;
    randomElementsTest();
}

void emptyTreeTest(){
    BinarySearchTree<int> tree;
    assert(tree.find_min() == nullptr);
    assert(tree.find_max() == nullptr);
}

void stardardBSTTest(){
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(3);
    tree.insert(10);
    tree.insert(5);
    tree.insert(1);
    assert(*tree.find_min() == 1);
    assert(*tree.find_max() == 10);
    display_test(tree);
    tree.insert(20);
    tree.insert(0);
    assert(*tree.find_min() == 0);
    assert(*tree.find_max() == 20);
    display_test(tree);
}

void randomElementsTest(){
    BinarySearchTree<int> tree;

    std::set<int> uniqueNumbers;
    std::size_t n = 20;
    int min = 1, max = 100;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);

    while (uniqueNumbers.size() < n) {
        uniqueNumbers.insert(dist(gen));
    }

    int minValue = *uniqueNumbers.begin();
    int maxValue = *uniqueNumbers.rbegin();

    std::vector<int> shuffledNumbers(uniqueNumbers.begin(), uniqueNumbers.end());
    std::shuffle(shuffledNumbers.begin(), shuffledNumbers.end(), gen);

    for(auto value : shuffledNumbers)
    {
        tree.insert(value);
        //std::cout << value << std::endl;
    }

    assert(*tree.find_min() == minValue);
    assert(*tree.find_max() == maxValue);

    display_test(tree);
    
}

void display_test(BinarySearchTree<int>& tree){
    tree.display();
    std::cout <<"Najmniejsza wartosc: " << *tree.find_min() << std::endl;
    std::cout <<"Najwieksza wartosc: " << *tree.find_max() << std::endl;
}
