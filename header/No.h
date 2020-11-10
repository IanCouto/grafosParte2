#ifndef TEORIADOSGRAFOS_NO_H
#define TEORIADOSGRAFOS_NO_H

class No{
private:
    int peso;
    int noDestino;
    No* proximoNo;

public:
    //Contrutor e Destrutor
    No(int peso, int noDestino);
    No();
    ~No();

    //Getters
    int getPeso();
    int getNoDestino();
    No* getProximoNo();

    //Setters
    void setPeso(int peso);
    void setNoDestino(int noDestino);
    void setProximoNo(No* proximoNo);
};
#endif //TEORIADOSGRAFOS_NO_H
