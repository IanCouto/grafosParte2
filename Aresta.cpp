#include "Aresta.h"

Aresta::Aresta(){}

Aresta::Aresta(int id) {
    this->id= id;
    this->proxima_aresta = nullptr;
}

Aresta::~Aresta() {
    if(this->proxima_aresta != nullptr){
        delete this->proxima_aresta;
        this->proxima_aresta = nullptr;
    }
}

int Aresta::getId() {
    return this->id;
}

//Getters
Aresta *Aresta::getProximaAresta() {
    return this->proxima_aresta;
}

//Setters
void Aresta::setProximaAresta(Aresta *aresta) {
    this->proxima_aresta = aresta;
}








