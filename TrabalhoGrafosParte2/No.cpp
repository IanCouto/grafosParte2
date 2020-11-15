#include "No.h"

using namespace std;

//Construtor
/*
* Construtor
* @param noDestino
*/
No::No(int noDestino) {
    this->noDestino = noDestino;
    this->proximoNo = nullptr;
    this->peso = 0;
};

/*
* Construtor
*/
No::No() {
    this->noDestino = -1;
    this->proximoNo = nullptr;
    this->peso = 0;
}

// Destrutor
No::~No() {
    this->proximoNo = nullptr;
}

//Getters

/**
 * Fun��o que retorna o no destino da aresta
 * @return noDestino
 */
int No::getNoDestino() {
    return this->noDestino;
}

/**
 * Fun��o que retorna o proximo No
 * @return proximoNo
 */
No* No::getProximoNo() {
    return this->proximoNo;
}

//Setters

/**
 * Fun��o que altera o no destino da aresta
 * @param noDestino
 */
void No::setNoDestino(int noDestino) {
    this->noDestino = noDestino;
}

/**
 * Fun��o que altera o proximo no
 * @param proximoNo
 */
void No::setProximoNo(No* proximoNo) {
    this->proximoNo = proximoNo;
}