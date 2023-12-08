#include "linkedlist.h"

template class Nodo<int>;
template class LinkedList<int>;

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), aux(nullptr) {}
template <typename T>
LinkedList<T>::~LinkedList() {
    aux = head;
    while (aux != nullptr) {
        Nodo<T>* temp = aux;
        aux = aux->getNext();
        delete temp;
    }
}

template <typename T>
void LinkedList<T>::add(T valor) {
    Nodo<T>* newNode = new Nodo<T>(valor);
    if (head == nullptr) {
        head = newNode;
        aux = head;
    } else {
        aux->setNext(newNode);
        aux = newNode;
    }
}

template <typename T>
Nodo<T>* LinkedList<T>::search(T valor) {
    Nodo<T>* sr = head;
    while (sr != nullptr) {
        if (sr->getDato() == valor) {
            return sr;
        }
        sr = sr->getNext();
    }
    return nullptr;
}

template <typename T>
void LinkedList<T>::remove(T valor) {
    Nodo<T>* rem = search(valor);
    if (rem == head && rem == aux) {
        head = nullptr;
        aux = nullptr;
        delete rem;
    } else if (rem == head) {
        head = head->getNext();
        delete rem;
    } else if (rem == aux) {
        Nodo<T>* temp = head;
        while (temp->getNext() != aux) {
            temp = temp->getNext();
        }
        aux = temp;
        aux->setNext(nullptr);
        delete rem;
    } else {
        Nodo<T>* temp = head;
        while (temp->getNext() != rem) {
            temp = temp->getNext();
        }
        temp->setNext(rem->getNext());
        delete rem;
    }
}

template <typename T>
void LinkedList<T>::modify(T valor, T valSuma) {
    Nodo<T>* mod = search(valor);
    if (mod != nullptr) {
        mod->setDato(mod->getDato() + valSuma);
    }
}

template <typename T>
void LinkedList<T>::show() {
    aux = head;
    while (aux->getNext() != nullptr) {
        std::cout << aux->getDato() << " ";
        aux = aux->getNext();
    }
    std::cout << aux->getDato() << " ";
    std::cout << std::endl;
}

template <typename T>
void LinkedList<T>::insertar(T valor) {
    std::lock_guard<std::mutex> lock(mutex);
    add(valor);
    std::cout << "Insertando: " << valor << std::endl;
}

template <typename T>
bool LinkedList<T>::buscar(T valor) {
    std::lock_guard<std::mutex> lock(mutex);
    Nodo<T>* resultado = search(valor);
    if (resultado != nullptr) {
        std::cout << "Buscado: " << valor << std::endl;
        return true;
    } else {
        std::cout << "No encontrado: " << valor << std::endl;
        return false;
    }
}

template <typename T>
bool LinkedList<T>::eliminar(T valor) {
    std::lock_guard<std::mutex> lock(mutex);
    bool eliminado = false;
    Nodo<T>* rem = search(valor);
    if (rem != nullptr) {
        remove(valor);
        std::cout << "Eliminando: " << valor << std::endl;
        eliminado = true;
    } else {
        std::cout << "No se eliminó: " << valor << std::endl;
    }
    return eliminado;
}

template <typename T>
void LinkedList<T>::modificar(T valor, T valSuma) {
    std::lock_guard<std::mutex> lock(mutex);
    Nodo<T>* mod = search(valor);
    if (mod != nullptr) {
        mod->setDato(mod->getDato() + valSuma);
        std::cout << "Modificando " << valor << " a " << mod->getDato() << std::endl;
    } else {
        std::cout << "No se encontró: " << valor << std::endl;
    }
}

template <typename T>
std::string LinkedList<T>::operacion() {
    if (head == nullptr) {
        return "La lista está vacía.";
    }
    srand(static_cast<unsigned>(time(nullptr)));
    std::string resultado = std::to_string(head->getDato());
    aux = head->getNext();
    while (aux != nullptr) {
        bool suma = rand() % 2 == 0;

        if (suma) {
            resultado += " + " + std::to_string(aux->getDato());
        } else {
            resultado += " - " + std::to_string(aux->getDato());
        }
        aux = aux->getNext();
    }
    return resultado;
}

