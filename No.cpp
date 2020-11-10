#include "header/No.h"

using namespace std;

//Construtor
No::No(int noDestino) {
    this->noDestino = noDestino;
    this->proximoNo = nullptr;
};

No::No() {
    this->noDestino = -1;
    this->proximoNo = nullptr;
}

// Destrutor
No::~No() {
}

//Getters

/**
 * Função que retorna o no destino da aresta
 * @return noDestino
 */
int No::getNoDestino(){
    return this->noDestino;
}

/**
 * Função que retorna o proximo No
 * @return proximoNo
 */
No* No::getProximoNo(){
    return this->proximoNo;
}

//Setters

/**
 * Função que altera o no destino da aresta
 * @param noDestino
 */
void No::setNoDestino(int noDestino ){
    this->noDestino = noDestino;
}

/**
 * Função que altera o proximo no
 * @param proximoNo
 */
void No::setProximoNo(No* proximoNo){
    this->proximoNo = proximoNo;
}