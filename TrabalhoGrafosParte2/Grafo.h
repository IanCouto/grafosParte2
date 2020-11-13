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
    int mapeamento(int* mapa, int id);
    void auxDijkstra(float* distancia, int* aPercorrer, int* Nonterior, int* mapa, int atual);
    void auxBuscaEmProfundidade(int id_no, int* mapa, int cont, ofstream& arquivo_saida);
    bool ehVizinho(No* noU, No* noV);
    void imprimeCaminhoFloyd(int** caminho, int vertice1, int vertice2, ofstream& arquivo_saida);
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

    //Setters
    void setQuantAresta(int val);

    //Outros m�todos
    void inserirAresta(int id, int id_destino);
    void mostrarGrafo(ofstream& arquivo_saida);
    void mostrarArestas(ofstream& arquivo_saida);
    void mostrarNos(ofstream& arquivo_saida);
    void gerarResultadosGrafo(ofstream& arquivo_saida);
    int guloso(ofstream& arquivo_saida);
    int gulosoRandomizado(float alfa);
};
#endif //TEORIADOSGRAFOS_GRAFO_H
