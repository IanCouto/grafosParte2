#include "FilaEncadeada.h"
/**
 * construtor
 */
FilaEncadeada::FilaEncadeada() {
    NoInicio = nullptr;
    NoFim = nullptr;
    tamanho = 0;
}
/**
 * destrutor
 */
FilaEncadeada::~FilaEncadeada() {
    NoFila* p = NoInicio;
    while (p != nullptr)
    {
        NoFila* t = p->getProx();
        delete p;
        p = t;
    }
}
/**
 * fun��o que retorna o No inicial
 */
int FilaEncadeada::getInicio() {
    if (!vazia())
        return NoInicio->getInfo();
    else {
        cout << "Lista vazia\n";
        exit(1);
    }
}

/**
 * fun��o que insere um No no fim
 * @param val valor do No
 */
void FilaEncadeada::enfileira(int val) {
    NoFila* p = new NoFila();
    p->setInfo(val);
    p->setProx(nullptr);

    if (NoFim == nullptr)
        NoInicio = p; // insere o primeiro No
    else
        NoFim->setProx(p); // liga No p na fila
    NoFim = p; // No p passa a ser o ultimo
}

/**
 * fun��o que elimina o No inicial
 */
int FilaEncadeada::desenfileira() {
    NoFila* p;
    if (NoInicio != NULL)
    {
        p = NoInicio;
        NoInicio = p->getProx();
        if (NoInicio == nullptr)
            NoFim = nullptr; // a fila esvaziou
        int val = p->getInfo();
        delete p; // exclui o No do inicio
        return val;
    }
    cout << "ERRO: Fila vazia" << endl;
    exit(1);
}
/**
 * fun��o que verifica se a fila est� vazia
 */
bool FilaEncadeada::vazia() {

    if (NoInicio == nullptr)
        return true;
    else
        return false;
}

/**
 * fun��o que retorna o n�mero de Nos
 */
int FilaEncadeada::numeroNos() {
    return tamanho;
}
