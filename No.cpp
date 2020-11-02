#include "No.h"
#include <iostream>
#include <fstream>
using namespace std;

//Construtor
No::No(int id, int x, int y){

    this->id = id;
    this->potencia = 0;
    this->canal = 0;
    this->interferencia = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->proximo_no = nullptr;
    this->primeiro_cliente = this->ultimo_cliente = nullptr;
    this->x = x;
    this->y = y;

};

No::No(){}

// Destrutor
No::~No(){

    Aresta* proxima_aresta = this->primeira_aresta;

    while(proxima_aresta != nullptr){

        Aresta* aux_aresta = proxima_aresta->getProximaAresta();
        delete proxima_aresta;
        proxima_aresta = aux_aresta;

    }

    No *proximo_cliente = this->primeiro_cliente;

    while (proximo_cliente != nullptr)
    {
        proximo_cliente->removerTodasArestas();
        No *aux_no = proximo_cliente->getProximoNo();
        delete proximo_cliente;
        proximo_cliente = aux_no;
    }

}

//Getters
Aresta *No::getPrimeiraAresta() {
    return this->primeira_aresta;
}



int No::getId() {
    return this->id;
}

float No::getInterferencia() {
    return this->interferencia;
}

float No::getPotencia() {
    return this->potencia;
}

No *No::getProximoNo() {
    return this->proximo_no;
}

No *No::getPrimeiroCliente() {
    return this->primeiro_cliente;
}

int No::getX() {
    return this->x;
}

int No::getY() {
    return this->y;
}

int No::getCanal() {
    return this->canal;
}




//Setters
void No::setProximoNo(No *proximo_no) {
    this->proximo_no = proximo_no;
}


void No::setPotencia(float potencia) {
    this->potencia = potencia;
}

void No::setInterferencia(float interferencia) {
    this->interferencia = interferencia;
}


void No::setCanal(int canal) {
    this->canal = canal;
}

void No::inserirCliente(int id, int x, int y, float dist){
    //Verifica se existe pelo menos um Cliente, caso negativo, o primeiro Cliente sera setado
    if(this->primeiro_cliente != nullptr){
        No* no = new No(id,x,y);
        no->setPotencia(dist);
        this->ultimo_cliente -> setProximoNo(no);
        this->ultimo_cliente = no;
    }
    else{
        this->primeiro_cliente = new No(id,x,y);
        this->primeiro_cliente->setPotencia(dist);
        this->ultimo_cliente = this->primeiro_cliente;
    }
}

void No::mostrarClientes(ofstream& arquivo_saida) {
    arquivo_saida<<"-----------CLIENTES------------"<<endl;
    arquivo_saida<<"ID. X - Y / Dist ate o ap"<<endl;
    for(No* no = primeiro_cliente; no != nullptr; no = no->getProximoNo()){
        arquivo_saida << no->getId() << ". ";
        arquivo_saida << no->getX() << " - ";
        arquivo_saida << no->getY() << " / ";
        arquivo_saida << no->getPotencia();
        arquivo_saida << endl;
    }
    arquivo_saida<<endl<<endl;
}

void No::atribuirPotenciaTransmissao() {
    No* cliente = primeiro_cliente;
    if(cliente!= nullptr){
        float maiorDistancia = cliente->getPotencia();
        for(cliente = cliente->getProximoNo(); cliente != nullptr; cliente = cliente->getProximoNo()){
            if(maiorDistancia<cliente->getPotencia()){
                maiorDistancia = cliente->getPotencia();
            }
        }
        this->potencia = maiorDistancia;
    }
}

void No::inserirAresta(int id) {
    //Verifica se existe pelo menos uma aresta no No, caso negativo, a primeira aresta sera setada
    if(this->primeira_aresta != nullptr){
        Aresta* aresta = new Aresta(id);
        this->ultima_aresta -> setProximaAresta(aresta);
        this->ultima_aresta = aresta;
    }
    else{
        this->primeira_aresta = new Aresta(id);
        this->ultima_aresta = this->primeira_aresta;
    }

}

void No::removerTodasArestas() {
    //Verifica se existe pelo menos uma aresta no No
    if(this->primeira_aresta != nullptr){
        Aresta* prox = nullptr;
        Aresta* aux = this->primeira_aresta;

        while (aux != nullptr) {
            prox = aux->getProximaAresta();
            delete aux;
            aux=prox;
        }
    }

    this->primeira_aresta = this->ultima_aresta = nullptr;
}














