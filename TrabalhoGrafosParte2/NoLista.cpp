#include"NoLista.h"
/**
 * Contrutor
 */
NoLista::NoLista() {
    proximo = nullptr;
    anterior = nullptr;
    info = -1;
    info2 = -1;
}

/**
 * Destrutor
 */
NoLista::~NoLista() {

}
/**
 * Retorna a informação
 * @return info
 */
int NoLista::getInfo() {
    return info;
}

/**
 * Retorna a informação
 * @return vizinho
 */
int NoLista::getInfo2() {
    return this->info2;
}

/**
 * Retorna o proximo No da fila
 * @return proximo
 */
NoLista* NoLista::getProx() {
    return proximo;
}

NoLista* NoLista::getAnt() {
    return anterior;
}
/**
 * Altera o valor da informação
 * @param val
 */
void NoLista::setInfo(int val) {
    info = val;
}

/**
 * Altera o valor do vizinho
 * @param val
 */
void NoLista::setInfo2(int val) {
    this->info2 = val;
}

/**
 * Altera o valor do proximo nó
 * @param p
 */
void NoLista::setProx(NoLista* p) {
    proximo = p;
}

void NoLista::setAnt(NoLista* p) {
    anterior = p;
}
