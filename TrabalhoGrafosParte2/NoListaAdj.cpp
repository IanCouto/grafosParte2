#include "NoListaAdj.h"
#include <iostream>

using namespace std;

/*
* Construtor
* @param id Id do n�
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
* @param id ID do n�
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
* @return ID do n�
*/
int NoListaAdj::getId() {
    return this->id;
}

/*
* Retorna o grau do n�
* @return grau
*/
int NoListaAdj::getGrau() {
    return this->grau;
}

/*
* Retorna o proximo n�
* @return proximoNo
*/
NoListaAdj* NoListaAdj::getProx() {
    return this->proximoNo;
}

/*
* Retorna o n� anterior
* @return noAnterior
*/
NoListaAdj* NoListaAdj::getAnt() {
    return this->noAnterior;
}

//Setters
/*
* Altera o ID do n�
* @param val
*/
void NoListaAdj::setId(int val) {
    this->id = id;
}

/*
* Altera o pr�ximo n�
* @param val
*/
void NoListaAdj::setProx(NoListaAdj* val) {
    this->proximoNo = val;
}

/*
* Altera o n� anterior
* @param val
*/
void NoListaAdj::setAnt(NoListaAdj* val) {
    this->noAnterior = val;
}

//Outras fun��es
/*
* Deleta o n� vizinho
* @param val
*/
void NoListaAdj::deletaVizinho(int val) {
    if (grau > 0) {
        if (vizinhos->getNoDestino() == val) {
            No* p = vizinhos;
            vizinhos = vizinhos->getProximoNo();
            //p->setProximoNo(nullptr);
            delete p;
            grau--;
        }
        else {
            for (No* aux = vizinhos; aux != nullptr; aux = aux->getProximoNo()) {
                if (aux->getProximoNo() != nullptr) {
                    if (aux->getProximoNo()->getNoDestino() == val) {
                        No* p = aux->getProximoNo();
                        aux->setProximoNo(p->getProximoNo());
                        //p->setProximoNo(nullptr);
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
* Adiciona um n� vizinho
* @param val
*/
void NoListaAdj::adicionaVizinho(int val) {
    No* p = new No(val);
    if (vizinhos == nullptr) {
        vizinhos = p;
        grau++;
    }
    else {
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
* @param vizinhos
*/
No* NoListaAdj::getVizinhos() {
    return this->vizinhos;
}
