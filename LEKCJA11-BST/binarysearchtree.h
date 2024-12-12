#ifndef __BINARYSEARCHTREE__H__
#define __BINARYSEARCHTREE__H__

#include <iostream>
#include <cassert>

template <typename T>
struct BSTNode {
// the default access mode and default inheritance mode are public
    T value;
    BSTNode *left, *right;
    //BSTNode *parent;   // używane w pewnych zastosowaniach
    // kostruktor domyślny
    BSTNode() : value(T()), left(nullptr), right(nullptr) {}
    // konstruktor zwykły
    BSTNode(const T& item) : value(item), left(nullptr), right(nullptr) {}
    ~BSTNode() { delete left; delete right; } // destruktor rekurencyjny
};


template <typename T>
class BinarySearchTree {
    BSTNode<T> *root;
public:
    BinarySearchTree() : root(nullptr) {} // konstruktor domyślny
    ~BinarySearchTree() { delete root; } // trzeba wyczyścić
    void clear() { delete root; root = nullptr; }
    bool empty() const { return root == nullptr; }
    T& top() { assert(root != nullptr); return root->value; } // podgląd korzenia
    void insert(const T& item) { root = insert(root, item); }
    void remove(const T& item); // usuwanie przez złączanie
    // Szukając element dostajemy wskaźnik do elementu lub nullptr.
    T* search(const T& item) const {
        auto ptr = search(root, item);
        return ((ptr == nullptr) ? nullptr : &(ptr->value));
    }
    T* iter_search(const T& item) const { // wg libavl
        for (auto node=root; node != nullptr; ) {
            if (item == node->value) {
                return &(node->value);
            } else if (item < node->value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return nullptr;
    }
    T* find_min();
    T* find_max();
    void preorder() { preorder(root); }
    void inorder() { inorder(root); }
    void postorder() { postorder(root); }
    void iter_preorder();
    void iter_inorder(); // trudne
    void iter_postorder(); // trudne
    void bfs(); // przejście poziomami (wszerz)
    void display() { display(root, 0); }

    // Metody bezpośrednio odwołujące się do node.
    // Mogą działać na poddrzewie.
    BSTNode<T> * insert(BSTNode<T> *node, const T& item); // zwraca nowy korzeń
    BSTNode<T> * search(BSTNode<T> *node, const T& item) const; // zwraca węzeł
    BSTNode<T> * remove(BSTNode<T> *node); // zwraca nowy korzeń poddrzewa
    void preorder(BSTNode<T> *node);
    void inorder(BSTNode<T> *node);
    void postorder(BSTNode<T> *node);
    void display(BSTNode<T> *node, int level);
    virtual void visit(BSTNode<T> *node) {
        assert(node != nullptr);
        std::cout << "visiting " << node->value << std::endl;
    }
};

//---------------------------------------------------------------------------------------------------------

template <typename T>
T* BinarySearchTree<T>::find_min(){
    if (root == nullptr) return nullptr;
    BSTNode<T>* p = root;
    while (p->left != nullptr)
    {
        p = p->left;
    }
    return &p->value;
    
}

template <typename T>
T* BinarySearchTree<T>::find_max(){
    if (root == nullptr) return nullptr;
    BSTNode<T>* p = root;
    while (p->right != nullptr)
    {
        p = p->right;
    }
    return &p->value;
    
}


//--------------------------------------------------------------------------------------------------------------


template <typename T>
BSTNode<T> * BinarySearchTree<T>::insert(BSTNode<T> *node, const T& item) {
    if (node == nullptr) {
        return new BSTNode<T>(item);
    }
    if (item < node->value) {
        node->left = insert(node->left, item);
    } else {
        node->right = insert(node->right, item);
    }
    return node; // zwraca nowy korzeń
}

template <typename T>
void BinarySearchTree<T>::display(BSTNode<T> *node, int level) {
    if (node == nullptr) return;
    display(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "   |";
    }
    std::cout << "---" << node->value << std::endl;
    display(node->left, level + 1);
}

#endif  //!__BINARYSEARCHTREE__H__

