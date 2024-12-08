#include "test.h"
#include <iostream>
#include <cassert>


void drzewo1WezelTest(){
    RandomBinaryTree<int> tree1;
    tree1.insert(1);
    int liczbaLisciRekurencyjna = tree1.calc_leaves_r();
    int liczbaLisciIteracyjna = tree1.calc_leaves_i();
    assert(liczbaLisciIteracyjna == 1);
    assert(liczbaLisciRekurencyjna == 1);
    wypiszWizualnie(tree1, liczbaLisciRekurencyjna, liczbaLisciIteracyjna);
}

void drzewo2WezlyTest(){
    RandomBinaryTree<int> tree1;
    tree1.insert(1);
    tree1.insert(2);
    int liczbaLisciRekurencyjna = tree1.calc_leaves_r();
    int liczbaLisciIteracyjna = tree1.calc_leaves_i();
    assert(liczbaLisciIteracyjna == 1);
    assert(liczbaLisciRekurencyjna == 1);
    wypiszWizualnie(tree1, liczbaLisciRekurencyjna, liczbaLisciIteracyjna);
}

void drzewo10WezlowTest(){
    RandomBinaryTree<int> tree1;
    for (int i = 0; i < 10; ++i){
        tree1.insert(i);
    }
    int liczbaLisciRekurencyjna = tree1.calc_leaves_r();
    int liczbaLisciIteracyjna = tree1.calc_leaves_i();
    assert(liczbaLisciIteracyjna == liczbaLisciRekurencyjna);
    wypiszWizualnie(tree1, liczbaLisciRekurencyjna, liczbaLisciIteracyjna);
}

void drzewo100WezlowTest(){
    RandomBinaryTree<int> tree1;
    for (int i = 0; i < 100; ++i){
        tree1.insert(i);
    }
    int liczbaLisciRekurencyjna = tree1.calc_leaves_r();
    int liczbaLisciIteracyjna = tree1.calc_leaves_i();
    assert(liczbaLisciIteracyjna == liczbaLisciRekurencyjna);
    wypiszWizualnie(tree1, liczbaLisciRekurencyjna, liczbaLisciIteracyjna);
}

void test(){
    drzewo1WezelTest();
    drzewo2WezlyTest();
    drzewo10WezlowTest();
    drzewo100WezlowTest();
    std::cout << "Testy zakonczone pomyslnie" << std::endl;

}


void wypiszWizualnie(RandomBinaryTree<int> &tree, int liczbaLisciRekurencyjna, int liczbaLisciIteracyjna){
    tree.display();
    std::cout <<"Liczba lisci: (funkcja rekurencyjna): " << liczbaLisciRekurencyjna << std::endl;
    std::cout << "Liczba lisci: (funkcja iteracyjna): " << liczbaLisciIteracyjna << std::endl;
}


