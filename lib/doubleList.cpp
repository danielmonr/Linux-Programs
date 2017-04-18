#include "doubleList.h"

template <class T>
Node<T>::Node(){
    std::cout << "Value: ";
    std::cin>> value;
    prev = nullptr;
    next = nullptr;
}

template <class T>
Node<T>::Node(T v, Node<T>* p, Node<T>* n){
    value = v;
    prev = p;
    next = n;
}

template <class T>        
Node<T>::~Node(){
    prev = nullptr;
    if (next)
        delete next;
    next = nullptr;
}

template <class T>
T Node<T>::getValue(){
    return value;
}

template <class T>
Node<T>* Node<T>::getNext(){
    return next;
}

template <class T>
Node<T>* Node<T>::getPrev(){
    return prev;
}

template <class T>
void Node<T>::setValue(T v){
    value = v;
}

template <class T>
void Node<T>::setNext(Node<T>* n){
    next = n;
}

template <class T>
void Node<T>::setPrev(Node<T>* p){
    prev = p;
}


/*####### DLIST DEFINITION #######*/

template <class T>
DList<T>::DList(){
    length = 0;
    first = nullptr;
}

template <class T>
DList<T>::~DList(){
    if (first)
        delete first;
    first = nullptr;
}

template <class T>
Node<T>* DList<T>::Last(){
    Node<T>* temp = first;
    while(temp->getNext())
        temp = temp->getNext();
    return temp;
}

template <class T>
void DList<T>::Add(T v){
    Node<T>* n;
    if(length != 0){
        n = new Node<T>(v, Last(), nullptr);
        Last()->setNext(n);
    }
    else{
        n = new Node<T>(v, nullptr, nullptr);
        first = n;
    }
    length++;
}

template <class T>
bool DList<T>::Delete(int pos){
    Node<T>* temp = At(pos);
    if(!temp)
        return false;

    temp->getNext()->setPrev(temp->getPrev());

    if (pos == 0)
        first = temp->getNext();
    else
        temp->getPrev()->setNext(temp->getNext());

    temp->setPrev(nullptr);
    temp->setNext(nullptr);
    delete temp;
    length--;
    return true;

}

template <class T>
Node<T>* DList<T>::At(int pos){
    if (length <= pos)
        return nullptr;

    Node<T>* n = first;
    int i = 1;
    for (i; i <= pos; ++i){
        n = n->getNext();
    }

    return n;
}

template <class T>
int DList<T>::Length(){
    return length;
}

template <class T>
int DList<T>::Search(T v){
    int cont = 0;
    Node<T>* temp = first;
    while(temp){
        if(temp->getValue() == v)
            return cont;
        temp = temp->getNext();
        cont++;
    }
    return -1;
}