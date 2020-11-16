#include "NoListaAdj.h"
#include <iostream>

using namespace std;

/*
* Construtor
* @param id Id do nó
*/
NoListaAdj::NoListaAdj(int id) {
    this->id = id;
    this->noAnterior = nullptr;
    this->proximoNo = nullptr;
    this->vizinhos = nullptr;
    this->grau = 0;
}

/*
* Construtor
* @param id ID do nó
* @param vizinho ID do vizinho
*/
NoListaAdj::NoListaAdj(int id, int vizinho) {
    this->id = id;
    this->noAnterior = nullptr;
    this->proximoNo = nullptr;
    this->vizinhos = new No(vizinho);
    this->grau = 1;
}

/*
* Construtor
*/
NoListaAdj::NoListaAdj() {
    this->id = -1;
    this->noAnterior = nullptr;
    this->proximoNo = nullptr;
    this->vizinhos = nullptr;
    this->grau = 0;
}

/*
* Destrutor
*/
NoListaAdj::~NoListaAdj() {
    No* p = vizinhos;
    while (p != nullptr)
    {
        No* t = p->getProximoNo();
        delete p;
        p = t;
    }
}

//Getters
/*
* @return ID do nó
*/
int NoListaAdj::getId() {
    return this->id;
}

/*
* Retorna o grau do nó
* @return grau
*/
int NoListaAdj::getGrau() {
    return this->grau;
}

/*
* Retorna o proximo nó
* @return proximoNo
*/
NoListaAdj* NoListaAdj::getProx() {
    return this->proximoNo;
}

/*
* Retorna o nó anterior
* @return noAnterior
*/
NoListaAdj* NoListaAdj::getAnt() {
    return this->noAnterior;
}

//Setters
/*
* Altera o ID do nó
* @param val
*/
void NoListaAdj::setId(int val) {
    this->id = id;
}

/*
* Altera o próximo nó
* @param val
*/
void NoListaAdj::setProx(NoListaAdj* val) {
    this->proximoNo = val;
}

/*
* Altera o nó anterior
* @param val
*/
void NoListaAdj::setAnt(NoListaAdj* val) {
    this->noAnterior = val;
}

//Outras funções
/*
* Deleta o nó vizinho
* @param val
*/
void NoListaAdj::deletaVizinho(int val) {
    if (grau > 0) {
        //Se o primeiro vizinho é igual a val, ele é excluido e o proximo valor se torna o primeiro
        if (vizinhos->getNoDestino() == val) {
            No* p = vizinhos;
            vizinhos = vizinhos->getProximoNo();
            delete p;
            grau--;
        }
        else {
            //Percorre a lista de vizinhos para encontrar val, se encontrar, val é removido
            for (No* aux = vizinhos; aux != nullptr; aux = aux->getProximoNo()) {
                if (aux->getProximoNo() != nullptr) {
                    if (aux->getProximoNo()->getNoDestino() == val) {
                        No* p = aux->getProximoNo();
                        aux->setProximoNo(p->getProximoNo());
                        delete p;
                        grau--;
                        break;
                    }
                }
            }
        }
    }
}

/*
* Adiciona um nó vizinho
* @param val ID do vértice vizinho
*/
void NoListaAdj::adicionaVizinho(int val) {
    No* p = new No(val);
    //Se a lista de vizinhos for vazia, val é o primeiro vizinho
    if (vizinhos == nullptr) {
        vizinhos = p;
        grau++;
    }
    else {
        //Percorre a lista de vizinhos para adicionar val na última posição
        for (No* aux = vizinhos; aux != nullptr; aux = aux->getProximoNo()) {
            if (aux->getProximoNo() == nullptr) {
                aux->setProximoNo(p);
                grau++;
                break;
            }
        }
    }
}

/*
* Retorna os vizinhos
* @return vizinhos Lista de vizinhos
*/
No* NoListaAdj::getVizinhos() {
    return this->vizinhos;
}
