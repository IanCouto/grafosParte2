#ifndef LISTAADJACENTEENCADEADA_H
#define LISTAADJACENTEENCADEADA_H

#include "NoListaAdj.h"

class ListaAdjacenteEncadeada {
private:
    NoListaAdj* noInicio; // ponteiro para No do comeco
    NoListaAdj* noFim; // ponteiro para No do fim
    int tamanho;

public:
    ListaAdjacenteEncadeada();
    ~ListaAdjacenteEncadeada();
    int getTamanho();
    void adiciona(int no, int noDestino);
    void deletaNo(int no);
    //void deletaVizinhos(int no);
    NoListaAdj* getNo(int no);
    NoListaAdj* getPos(int index);
    void imprimeLista();
};

#endif // LISTAADJACENTEENCADEADA_H
