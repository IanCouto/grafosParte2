#include"NoFila.h"

/**
 * Contrutor
 */
NoFila::NoFila() {
}
/**
 * Destrutor
 */
NoFila::~NoFila() {
}
/**
 * Retorna a informação
 * @return info
 */
int NoFila::getInfo() {
    return info;
}
/**
 * Retorna o proximo No da fila
 * @return proximo
 */
NoFila* NoFila::getProx() {
    return proximo;
}
/**
 * Altera o valor da informação
 * @param val
 */
void NoFila::setInfo(int val) {
    info = val;
}
/**
 * Altera o valor do proximo nó
 * @param p
 */
void NoFila::setProx(NoFila* p) {
    proximo = p;
}
