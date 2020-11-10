#ifndef LISTAENCADEADA_H_INCLUDED
#define LISTAENCADEADA_H_INCLUDED
#include "NoLista.h"

class ListaEncadeada {
    private:
        NoLista *noInicio; // ponteiro para No do comeco
        NoLista *noFim; // ponteiro para No do fim
        int tamanho;

    public:
        ListaEncadeada();
        ~ListaEncadeada();
        //NoLista *getInicio(); // retorna No do inicio
        //NoLista *getFim(); // retorna No do fim
        void adiciona(int val); // insere No no fim
        void adicionaEspecial(int val); // verifica se val existe antes de inserir
        void adiciona(int val, int vizinho); // insere No no fim
        void alteraValor(int pos, int val);//altera o valor para val na posição pos
        void removeValor(int val); //remove todos os Nós com o valor val
        //void removeValor(int val, int val2); //remove o primeiro No com o valor val
        bool isVazio(); // verifica se esta vazia
        int getTamanho();// retorna o tamanho da lista
        bool verificaElemento(int val); //verifica se o valor está na lista
        void imprimeLista();//imprime a lista
        NoLista* getPosicao(int pos); //retorna o valor na posicao pos
        //void removePosicao(int pos);//remove o valor na posicao pos
        int * getVetorInfo();//retorna um vetor com as informacoes dos nos
};

#endif // LISTAENCADEADA_H_INCLUDED
