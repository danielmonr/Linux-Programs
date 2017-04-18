/*
 * ========================================================================
 *
 *
 *       Filename: main.cpp
 *
 *       Description: Program that creates a server that can handle 
 *                    multiple connections.
 *
 *       Version: 1.0
 *       Created: 19/01/17
 *       Revision: none
 *       Compiler: g++
 *
 *       Author: Daniel Monzalvo, danielmonr@gmail.com
 *
 * ========================================================================
*/

#include <stdlib.h>
#include <iostream>
#include "doubleList.h"

void TestPrint(DList<int>* lista){
    std::cout<< "Res::lista={";
    int i = 0;
    for (i; i < lista->Length(); ++i){
        std::cout<<"{" << i <<"," << lista->At(i)->getValue()<<"};";
    }
    std::cout<<"}\n";
}

int main(int argc, char* argv[]){

    DList<int>* lista = new DList<int>();
    lista->Add(1);
    lista->Add(3);
    lista->Add(2);

    TestPrint(lista);

    int pos = lista->Search(1);
    std::cout << "Res::pos=" << pos << std::endl;

    bool del = lista->Delete(pos);
    std::cout << "Res::del=" << del << std::endl;

    TestPrint(lista);

    lista->Add(5);

    TestPrint(lista);

    delete lista;
    return 1;
}
