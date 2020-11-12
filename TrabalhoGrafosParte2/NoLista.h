#ifndef NOLISTA_H_INCLUDED
#define NOLISTA_H_INCLUDED

class NoLista {

public:
    NoLista();
    ~NoLista();
    int getInfo();
    NoLista* getAnt();
    NoLista* getProx();
    void setInfo(int val);
    void setProx(NoLista* p);
    void setAnt(NoLista* p);
    int getInfo2();
    void setInfo2(int val);

private:
    int info; // informacao
    int info2; //vizinho
    NoLista* proximo; // ponteiro para o proximo
    NoLista* anterior; // ponteiro para o proximo
};

#endif // NOLISTA_H_INCLUDED