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
 * Retorna a informa��o
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
 * Altera o valor da informa��o
 * @param val
 */
void NoFila::setInfo(int val) {
    info = val;
}
/**
 * Altera o valor do proximo n�
 * @param p
 */
void NoFila::setProx(NoFila* p) {
    proximo = p;
}
