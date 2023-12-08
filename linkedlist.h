#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <mutex>
#include <string>

template <typename T>
class Nodo {
private:
    T dato;
    Nodo* next;

public:
    Nodo(T valor) : dato(valor), next(nullptr) {}

    T getDato() const {
        return dato;
    }
    void setDato(T nuevoDato) {
        dato = nuevoDato;
    }

    Nodo* getNext() const {
        return next;
    }

    void setNext(Nodo* newNext) {
        next = newNext;
    }
};

template <typename T>
class LinkedList {
private:
    Nodo<T>* head;
    Nodo<T>* aux;
    std::mutex mutex;

public:
    LinkedList();
    ~LinkedList();

    void add(T valor);
    Nodo<T>* search(T valor);
    void remove(T valor);
    void modify(T valor, T valSuma);
    void show();

    void insertar(T valor);
    bool buscar(T valor);
    bool eliminar(T valor);
    void modificar(T valor, T valSuma);
    std::string operacion();
};

#endif // LINKEDLIST_H
