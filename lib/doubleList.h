#include <stdlib.h>
#include <iostream>
#pragma once

template <class T>
class Node{
    public:
        Node();
        Node(T v, Node<T>* p, Node<T>* n);
        ~Node();

        T getValue();

        Node<T>* getNext();
        Node<T>* getPrev();
        void setValue(T v);
        void setNext(Node<T>* n);
        void setPrev(Node<T>* p);

    private:
        T value;
        Node<T>* prev;
        Node<T>* next;
};

template <class T>
class DList{
    public:
        DList();
        ~DList();

        Node<T>* Last();

        void Add(T v);

        bool Delete(int pos);

        Node<T>* At(int pos);

        int Length();

        int Search(T v);

    private:
        int length;
        Node<T>* first;
};
