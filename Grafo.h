#ifndef TEORIADOSGRAFOS_GRAFO_H
#define TEORIADOSGRAFOS_GRAFO_H

#include <iostream>
#include <fstream>
#include "No.h"


using namespace std;

class Grafo{
private:
    int ordem;
    int quantClientes;
    int quant_aresta;
    No* primeiro_no;
    No* ultimo_no;
    float interferenciaTotal;
    float tabelaInterferencia[11][11];

public:

    //Contrutor e Destrutor
    Grafo();
    Grafo(int ordem, int quantClientes);
    ~Grafo();

    //Getters
    int getOrdem();
    int getQuantAresta();
    No* getPrimeiroNo();
    No* getPrimeiroCliente();
    No* getUltimoNo();
    No* getUltimoCliente();
    No *getNo(int id);
    float interferencia(int canal1,int canal2);

    //Outros Metodos
    void inserirNo(int id,int x, int y);
    void criarGrafoConflito();
    void mostrarGrafo(ofstream& arquivo_saida);
    void mostrarNos(ofstream& arquivo_saida);
    float distanciaEuclidiana(int x1, int y1, int x2, int y2);
    void inserirCliente(int id,int x, int y);

    void definePotencia(); //Verifica qual cliente possui a maior distancia para cada ap essa distancia ira definir a potencia do ap
    int* baseCanais1611();//Define todos os aps possiveis com os canais 1,6 e 11 ao final retorna um vetor de ids dos aps sem um canal definido
    void defineInterferencias(int idsNosInteferencia[]); //Define o valor de interferencia para cada ap  do grafo
    bool possuiClientesNaInterseccao(No *ap, No*ap2); //Retorna verdadeiro caso possua clientes na interseccao do raio de dois aps
    bool estaNaInterseccao(No *cliente, No *ap, No*ap2); //Retorna verdadeiro caso o cliente esteja na interseccao do raio de dois aps

    float guloso();
    float gulosoRandomizado(float alfa, int quantInteracoes);
    float gulosoRandomizadoReativo(int quantInteracoes, float* vetorAlfas);

    int* randomizaVetor(float alfa);
    float randomizaAlfa(float *vetorAlfas, double *probabilidades, double *medias, double melhorSolucao);

};
#endif //TEORIADOSGRAFOS_GRAFO_H
