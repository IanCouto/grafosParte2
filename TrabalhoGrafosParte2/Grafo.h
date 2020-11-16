#ifndef TEORIADOSGRAFOS_GRAFO_H
#define TEORIADOSGRAFOS_GRAFO_H

#include <iostream>
#include <fstream>
#include "No.h"
#include "ListaEncadeada.h"
#include "ListaAdjacenteEncadeada.h"

using namespace std;
class ListaEncadeada;
class Grafo
{
private:
    int ordem;
    int quant_aresta;
    bool comecaZero;
    No* listaAdj;
    bool auxInserirAresta(int id, int id_destino);
    int encontraMaiorGrau(ListaAdjacenteEncadeada* lista);
    int encontraMaiorGrauRandomizado(ListaAdjacenteEncadeada* lista, float alfa);

public:
    //Contrutor e Destrutor
    Grafo();
    Grafo(int ordem);
    ~Grafo();

    //Getters
    int getOrdem();
    int getQuantAresta();
    bool isComecaZero();

    //Setter
    void setQuantAresta(int val);

    //Outros métodos
    void inserirAresta(int id, int id_destino);
    void mostrarGrafo(ofstream& arquivo_saida);
    void mostrarArestas(ofstream& arquivo_saida);
    void mostrarNos(ofstream& arquivo_saida);
    int guloso(ofstream& arquivo_saida);
    int* gulosoRandomizado(float alfa);
};
#endif //TEORIADOSGRAFOS_GRAFO_H
