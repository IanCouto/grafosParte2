#ifndef NOFILA_H_INCLUDED
#define NOFILA_H_INCLUDED

class NoFila {

public:
    NoFila();
    ~NoFila();
    int getInfo();
    NoFila* getProx();
    void setInfo(int val);
    void setProx(NoFila* p);

private:
    int info; // informacao
    NoFila* proximo; // ponteiro para o proximo
};

#endif // NOFILA_H_INCLUDED
