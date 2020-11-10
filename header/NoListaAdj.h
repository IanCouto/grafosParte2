#ifndef NOLISTAADJ_H
#define NOLISTAADJ_H
#include "No.h"

class NoListaAdj{
private:
    int id;
    int grau;
    No* vizinhos;
    NoListaAdj* proximoNo;
    NoListaAdj* noAnterior;

public:
    //Contrutor e Destrutor
    NoListaAdj(int id);
    NoListaAdj(int id, int vizinho);
    NoListaAdj();
    ~NoListaAdj();

    //Getters
    int getId();
    int getGrau();
    NoListaAdj* getProx();
    NoListaAdj* getAnt();
    No* getVizinhos();

    //Setters
    void setId(int val);
    void setProx(NoListaAdj* val);
    void setAnt(NoListaAdj* val);

    //Outras funções
    void deletaVizinho(int val);
    void adicionaVizinho(int val);
};

#endif // NOLISTAADJ_H
