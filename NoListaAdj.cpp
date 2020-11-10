#include "header/NoListaAdj.h"
#include <iostream>

using namespace std;

    //Contrutor e Destrutor
    NoListaAdj::NoListaAdj(int id){
        this->id = id;
        this->noAnterior = nullptr;
        this->proximoNo = nullptr;
        this->vizinhos = nullptr;
        this->grau = 0;
    }

    NoListaAdj::NoListaAdj(int id, int vizinho){
        this->id = id;
        this->noAnterior = nullptr;
        this->proximoNo = nullptr;
        this->vizinhos = new No(vizinho);
        this->grau = 1;
    }

    NoListaAdj::NoListaAdj(){
        this->id = -1;
        this->noAnterior = nullptr;
        this->proximoNo = nullptr;
        this->vizinhos = nullptr;
        this->grau=0;
    }
    NoListaAdj::~NoListaAdj(){

    }

    //Getters
    int NoListaAdj::getId(){
        return this->id;
    }

    int NoListaAdj::getGrau(){
        return this->grau;
    }

    NoListaAdj* NoListaAdj::getProx(){
        return this->proximoNo;
    }
    NoListaAdj* NoListaAdj::getAnt(){
        return this->noAnterior;
    }

    //Setters
    void NoListaAdj::setId(int val){
        this->id = id;
    }
    void NoListaAdj::setProx(NoListaAdj* val){
        this->proximoNo = val;
    }
    
    void NoListaAdj::setAnt(NoListaAdj* val){
        this->noAnterior = val;
    }

    //Outras funções
    void NoListaAdj::deletaVizinho(int val){
        if(grau>0){
            if(vizinhos->getNoDestino()==val){
                No *p = vizinhos;
                vizinhos = vizinhos->getProximoNo();
                p->setProximoNo(nullptr);
                delete p;
                grau--;
            } else {
                for(No * aux = vizinhos; aux != nullptr; aux = aux->getProximoNo()){
                    if(aux->getProximoNo()!=nullptr){
                        if(aux->getProximoNo()->getNoDestino()==val){
                            No *p = aux->getProximoNo();
                            aux->setProximoNo(p->getProximoNo());
                            p->setProximoNo(nullptr);
                            delete p;
                            grau--;
                            break;
                        }
                    }
                }
            }
        }
    }

    void NoListaAdj::adicionaVizinho(int val){
        No *p = new No (val);
        if(vizinhos==nullptr){
            vizinhos = p;
            grau++;
        } else {
            for(No *aux = vizinhos; aux != nullptr; aux = aux->getProximoNo()){
                if(aux->getProximoNo()==nullptr){
                    aux->setProximoNo(p);
                    grau++;
                    break;
                }
            }
        }
    }

    No* NoListaAdj::getVizinhos(){
        return this->vizinhos;
    }
