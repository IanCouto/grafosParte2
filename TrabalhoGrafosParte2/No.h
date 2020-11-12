#ifndef TEORIADOSGRAFOS_NO_H
#define TEORIADOSGRAFOS_NO_H

class No {
private:
    int peso;
    int noDestino;
    No* proximoNo;

public:
    //Contrutor e Destrutor
    No(int noDestino);
    No();
    ~No();

    //Getters
    int getNoDestino();
    No* getProximoNo();

    //Setters
    void setNoDestino(int noDestino);
    void setProximoNo(No* proximoNo);
};
#endif //TEORIADOSGRAFOS_NO_H
