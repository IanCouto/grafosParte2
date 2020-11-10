#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <string.h>
#include <chrono>
#include <limits>
#include "header/Grafo.h"
#include "header/FilaEncadeada.h"
#include "header/ListaEncadeada.h"
#include "header/ListaAdjacenteEncadeada.h"

#define INFINITO std::numeric_limits<int>::max()

using namespace std;

/**
 * Construtor
 * @param ordem do grafo
 */
Grafo::Grafo(int ordem)
{
    this->ordem = ordem;
    this->quant_aresta = 0;
    this->listaAdj = new No[ordem];
    this->comecaZero = true;
}

/**
 * Construtor
 */
Grafo::Grafo()
{
    this->comecaZero = true;
}

/**
 * Destrutor
 */
Grafo::~Grafo()
{
    this->listaAdj = nullptr;
    delete[] this->listaAdj;
}

/**
 * @return ordem do grafo
 */
int Grafo::getOrdem()
{
    return this->ordem;
}

/**
 * @return quantidade de arestas do grafo
 */
int Grafo::getQuantAresta()
{
    return this->quant_aresta;
}
/**
 * @return se o grafo começa com zero
 */
bool Grafo::isComecaZero()
{
    return this->comecaZero;
}

/**
 * @param val incrementa a quantidade de arestas do grafo
 */
void Grafo::setQuantAresta(int val)
{
    this->quant_aresta++;
}

/**
 * função auxiliar para inserir arestas no grafo
 * @param id id do nó de origem
 * @param id_destino id do nó de destino
 * @return true se conseguiu enatualrar o id do nó de destino false caso não tenha conseguido
 */
bool Grafo::auxInserirAresta(int id, int id_destino)
{
    //não permite self-loops
    if (id == id_destino)
    {
        return true;
    }
    for (No *a = &listaAdj[id]; a != nullptr; a = a->getProximoNo())
    {
        //verifica se o id nó de destino existente no grafo é igual o id do nó de destino a ser inserido
        if (a->getNoDestino() == id_destino)
        {
            return true;
        }
    }
    return false;
}

/**
 * insere as arestas no grafo
 * @param id id do nó de origem
 * @param id_destino id do nó de destino
 * @param peso peso da aresta entre os nós
 */
void Grafo::inserirAresta(int id, int id_destino, float peso)
{
    //caso a aresta entre os nó não exista
    if (!auxInserirAresta(id, id_destino))
    {
        //tratamento para grafo que começa com vértice igual a 1
        if (id == this->getOrdem())
        {
            this->comecaZero = false;
            id = 0;
        }
        if (id_destino == this->getOrdem())
        {
            this->comecaZero = false;
            id_destino = 0;
        }
        //insere a aresta no nó de origem;
        //caso a primeira posição esteja vazia
        if (this->listaAdj[id].getPeso() == -1)
        {
            this->listaAdj[id].setPeso(peso);
            this->listaAdj[id].setNoDestino(id_destino);
        }
        else
        {
            No *aux = &this->listaAdj[id];
            while (aux->getProximoNo() != nullptr)
            {
                aux = aux->getProximoNo();
            }
            aux->setProximoNo(new No(peso, id_destino));
        }
        //insere a aresta no nó de destino
        //caso a primeira posição esteja vazia
        if (this->listaAdj[id_destino].getPeso() == -1)
        {
            this->listaAdj[id_destino].setPeso(peso);
            this->listaAdj[id_destino].setNoDestino(id);
        }
        else
        {
            No *aux = &this->listaAdj[id_destino];
            while (aux->getProximoNo() != nullptr)
            {
                aux = aux->getProximoNo();
            }
            aux->setProximoNo(new No(peso, id));
        }
        this->quant_aresta++;
    }
}

/**
 * mostra os nós e seus vizinhos de forma ordenada
 * @param arquivo_saida arquivo de saída de dados
 */
void Grafo::mostrarGrafo(ofstream &arquivo_saida)
{
    arquivo_saida << "------------GRAFO-------------" << endl;
    arquivo_saida << "  No  |  No(s) Vizinho(s) " << endl;
    arquivo_saida << "------------------------------" << endl;
    int atual = 0;
    //acertar a posição dos elementos a serem imprimidos
    for (int i = 0; i < getOrdem(); i++)
    {
        if (!comecaZero && i == 0)
        {
            arquivo_saida << this->getOrdem();
        }
        else
        {
            arquivo_saida << i;
        }
        if ((i / 100000) > 0)
        {
            arquivo_saida << "| ";
        }
        else if ((i / 10000) > 0)
        {
            arquivo_saida << " | ";
        }
        else if ((i / 1000) > 0)
        {
            arquivo_saida << "  | ";
        }
        else if ((i / 100) > 0)
        {
            arquivo_saida << "   | ";
        }
        else if ((i / 10) > 0)
        {
            arquivo_saida << "    | ";
        }
        else if ((i / 1) > 0)
        {
            arquivo_saida << "     | ";
        }
        else if (i == 0)
        {
            arquivo_saida << "     | ";
        }
        //percorre o nó imprimindo todas as arestas
        for (No *a = &listaAdj[i]; a != nullptr; a = a->getProximoNo())
        {
            if (!comecaZero && a->getNoDestino() == 0)
            {
                if (a->getProximoNo() != nullptr)
                    arquivo_saida << this->getOrdem() << ", ";
                else
                    arquivo_saida << this->getOrdem();
            }
            else
            {
                if (a->getProximoNo() != nullptr)
                    arquivo_saida << a->getNoDestino() << ", ";
                else
                    arquivo_saida << a->getNoDestino();
            }
        }
        arquivo_saida << endl;
    }
    arquivo_saida << "--------------------------------------------------------------------------------------------------------" << endl
                  << endl;
}

/**
 * Mostra os nós e seus pesos de forma ordenada
 * @param arquivo_saida arquivo de saida de dados
 */
void Grafo::mostrarNos(ofstream &arquivo_saida)
{
    arquivo_saida << "-------------NOS--------------" << endl;
    arquivo_saida << "  No  |   Grau " << endl;
    arquivo_saida << "------------------------------" << endl;
    int atual = 0;
    //acertar a posição dos elementos a serem imprimidos
    for (int i = 0; i < getOrdem(); i++)
    {
        if (!comecaZero && i == 0)
        {
            arquivo_saida << this->getOrdem();
        }
        else
        {
            arquivo_saida << i;
        }
        if ((i / 100000) > 0)
        {
            arquivo_saida << "| ";
        }
        else if ((i / 10000) > 0)
        {
            arquivo_saida << " | ";
        }
        else if ((i / 1000) > 0)
        {
            arquivo_saida << "  | ";
        }
        else if ((i / 100) > 0)
        {
            arquivo_saida << "   | ";
        }
        else if ((i / 10) > 0)
        {
            arquivo_saida << "    | ";
        }
        else if ((i / 1) > 0)
        {
            arquivo_saida << "     | ";
        }
        else if (i == 0)
        {
            arquivo_saida << "     | ";
        }
        //percorre o grafo, imprimindo as arestas
        for (No *a = &listaAdj[i]; a != nullptr; a = a->getProximoNo())
        {
            atual++;
        }
        arquivo_saida << atual << endl;
        atual = 0;
    }
    arquivo_saida << "--------------------------------------------------------------------------------------------------------" << endl
                  << endl;
}

/**
 * Mostra as arestas entre os nós e seus pesos
 * @param arquivo_saida arquivo de saida de dados
 */
void Grafo::mostrarArestas(ofstream &arquivo_saida)
{
    arquivo_saida << "-----------ARESTAS------------" << endl;
    arquivo_saida << "  No -- No |   Peso " << endl;
    arquivo_saida << "------------------------------" << endl;
    //percorre o grafo imprimindo as arestas de cada nó de forma ordenada
    for (int i = 0; i < getOrdem(); i++)
    {
        for (No *a = &listaAdj[i]; a != nullptr; a = a->getProximoNo())
        {
            if (!comecaZero && i == 0)
            {
                arquivo_saida << this->getOrdem() << " -- " << a->getNoDestino() << " | " << a->getPeso() << endl;
            }
            else
            {
                if (!comecaZero && a->getNoDestino() == 0)
                {
                    arquivo_saida << i << " -- " << this->getOrdem() << " | " << a->getPeso() << endl;
                }
                else
                {
                    arquivo_saida << i << " -- " << a->getNoDestino() << " | " << a->getPeso() << endl;
                }
            }
        }
    }
    arquivo_saida << "--------------------------------------------------------------------------------------------------------" << endl
                  << endl;
}

void Grafo::gerarResultadosGrafo(ofstream &arquivo_saida)
{
    arquivo_saida << this->getOrdem() << endl;
    arquivo_saida << this->getQuantAresta() << endl;
    double media = 0;
    int *grau = new int[this->getOrdem()];
    for (int i = 0; i < this->getOrdem(); i++)
    {
        grau[i] = 0;
        for (No *no = &listaAdj[i]; no != nullptr; no = no->getProximoNo())
        {
            grau[i] = grau[i] + 1;
        }
        media = media + grau[i];
    }
    media = media / this->getOrdem();
    arquivo_saida << media << endl;
    for (int i = 0; i < this->getOrdem(); i++)
    {
        int atual = 0;
        for (int j = 0; j < this->getOrdem(); j++)
        {
            if (grau[j] != 0 && grau[j] == i)
                atual++;
        }
        if (atual != 0)
            arquivo_saida << "Grau " << i << ": " << (double(atual) / this->getOrdem()) << endl;
    }
    delete[] grau;
}

/**
 * mapeia as arestas de retorno para os algoritmos de busca
 * @param mapa mapa das arestas
 * @param id id do nó
 * @return -1 caso não seja um retorno e i caso seja retorno
 */
int Grafo::mapeamento(int *mapa, int id)
{
    for (int i = 0; i < this->getOrdem(); i++)
    {
        if (mapa[i] == id)
            return i;
    }
    return -1;
}

/**
 * caminhamento em largura a partir de um nó digitado pelo usuário
 * @param id_no id do nó digitado pelo usuário
 * @param arquivo_saida arquivo de saida de dados
 */
void Grafo::caminhamentoLargura(int id_no, ofstream &arquivo_saida)
{
    int *mapa = new int[this->getOrdem()];
    int atual = 0;
    //preenche o mapa com -1
    for (int i = 0; i < this->ordem; i++)
    {
        mapa[i] = -1;
    }
    FilaEncadeada *fila = new FilaEncadeada();
    mapa[id_no] = atual++;
    fila->enfileira(id_no);
    arquivo_saida << "-----------CAMINHAMENTO EM LARGURA------------" << endl;
    arquivo_saida << "  [NoU - NoV]  | É retorno?" << endl;
    arquivo_saida << "----------------------------------------------" << endl;
    //enquanto a fila não estiver vazia
    while (!fila->vazia())
    {
        int vertice = fila->desenfileira();
        //percorre todas as arestas do primeiro vértice da fila
        for (No *a = &listaAdj[vertice]; a != nullptr; a = a->getProximoNo())
        {
            //caso o valor desta aresta seja igual a -1 no mapa a aresta não é um retorno
            if (mapa[a->getNoDestino()] == -1)
            {
                if (this->comecaZero)
                {
                    arquivo_saida << "[" << vertice << "," << a->getNoDestino() << "] | nao é uma aresta de retorno" << endl;
                }
                else
                {
                    if (vertice == 0)
                    {
                        arquivo_saida << "[" << this->getOrdem() << "," << a->getNoDestino() << "] | nao é uma aresta de retorno" << endl;
                    }
                    else if (a->getNoDestino() == 0)
                    {
                        arquivo_saida << "[" << vertice << "," << this->getOrdem() << "] | nao é uma aresta de retorno" << endl;
                    }
                    else
                    {
                        arquivo_saida << "[" << vertice << "," << a->getNoDestino() << "] | nao é uma aresta de retorno" << endl;
                    }
                }
                mapa[a->getNoDestino()] = atual++;
                fila->enfileira(a->getNoDestino());
            }
            else
            {
                if (this->comecaZero)
                {
                    arquivo_saida << "[" << vertice << "," << a->getNoDestino() << "]  | é  uma aresta de retorno" << endl;
                }
                else
                {
                    if (vertice == 0)
                    {
                        arquivo_saida << "[" << this->getOrdem() << "," << a->getNoDestino() << "]  | é  uma aresta de retorno" << endl;
                    }
                    else if (a->getNoDestino() == 0)
                    {
                        arquivo_saida << "[" << vertice << "," << this->getOrdem() << "]  | é  uma aresta de retorno" << endl;
                    }
                    else
                    {
                        arquivo_saida << "[" << vertice << "," << a->getNoDestino() << "]  | é  uma aresta de retorno" << endl;
                    }
                }
            }
        }
    }
    arquivo_saida << "--------------------------------------------------------------------------------------------------------" << endl
                  << endl;
}

/**
 * função auxiliar para a busca em profundidade
 * @param id_no id do nó de origem
 * @param mapa mapa
 * @param atual atualador
 * @param arquivo_saida arquivo de saida de dados
 */
void Grafo::auxBuscaEmProfundidade(int id_no, int *mapa, int atual, ofstream &arquivo_saida)
{
    mapa[id_no] = atual++;
    //percorre todos os nós do grafo
    for (No *a = &listaAdj[id_no]; a != nullptr; a = a->getProximoNo())
    {
        int vertice = a->getNoDestino();
        //caso o valor da posição no mapa seja -1, não é uma aresta de retorno
        if (this->comecaZero)
        {
            if (mapa[a->getNoDestino()] == -1)
            {
                arquivo_saida << "[" << id_no << "," << vertice << "] | nao é uma aresta de retorno" << endl;
                auxBuscaEmProfundidade(vertice, mapa, atual, arquivo_saida);
            }
            else
            {
                arquivo_saida << "[" << id_no << "," << vertice << "] | é uma aresta de retorno" << endl;
            }
        }
        else
        {
            if (mapa[a->getNoDestino()] == -1)
            {
                if (vertice == 0)
                {
                    arquivo_saida << "[" << id_no << "," << this->getOrdem() << "] | nao é uma aresta de retorno" << endl;
                }
                else if (id_no == 0)
                {
                    arquivo_saida << "[" << this->getOrdem() << "," << vertice << "] | nao é uma aresta de retorno" << endl;
                }
                else
                {
                    arquivo_saida << "[" << id_no << "," << vertice << "] | nao é uma aresta de retorno" << endl;
                }
                auxBuscaEmProfundidade(vertice, mapa, atual, arquivo_saida);
            }
            else
            {
                if (vertice == 0)
                {
                    arquivo_saida << "[" << id_no << "," << this->getOrdem() << "] | é uma aresta de retorno" << endl;
                }
                else if (id_no == 0)
                {
                    arquivo_saida << "[" << this->getOrdem() << "," << vertice << "] | é uma aresta de retorno" << endl;
                }
                else
                {
                    arquivo_saida << "[" << id_no << "," << vertice << "] | é uma aresta de retorno" << endl;
                }
            }
        }
    }
}

/**
 * função para efetuar o caminhamento em profundidade a partir de um nó digitado pelo usuário
 * @param id_no id do nó de origem
 * @param arquivo_saida arquivo de saida de dados
 */
void Grafo::caminhamentoProfundidade(int id_no, ofstream &arquivo_saida)
{
    arquivo_saida << "-----------CAMINHAMENTO EM PROFUNDIDADE------------" << endl;
    arquivo_saida << "  [NoU - NoV] | É uma aresta de retorno?" << endl;
    arquivo_saida << "---------------------------------------------------" << endl;
    int atual = 0;
    int *mapa = new int[this->getOrdem()];
    //preenche o mapa com o valor -1
    for (int i = 0; i < this->ordem; i++)
    {
        mapa[i] = -1;
    }

    //percorre o mapa verificando se a posição atual é igual a -1
    for (int i = 0; i < this->getOrdem(); i++)
    {
        if (mapa[i] == -1)
        {
            auxBuscaEmProfundidade(id_no, mapa, atual, arquivo_saida); // começa nova etapa
        }
    }
    arquivo_saida << "--------------------------------------------------------------------------------------------------------" << endl
                  << endl;
}

/**
 * Árvore geradora mínima gerada pelo algoritmo de Dijkstra
 * @param idOrigem id do nó de origem
 * @param idDestino id do nó de destino
 * @param arquivo_saida arquivo de saida de dados
 */
void Grafo::dijkstra(int idOrigem, int idDestino, ofstream &arquivo_saida)
{
    float *distancia = new float[this->getOrdem()];
    int *mapa = new int[this->getOrdem()];
    int *aPercorrer = new int[this->getOrdem()];
    int *noAnterior = new int[this->getOrdem()];

    //preenche os vetores mapa, a distancia e aPercorrer com os valores 0, 1 ou -1
    for (int i = 0; i < this->getOrdem(); i++)
    {
        mapa[i] = i;
        if (i == idOrigem)
        {
            distancia[i] = 0;
            aPercorrer[i] = 0;
        }
        else
        {
            distancia[i] = -1;
            aPercorrer[i] = 1;
        }
        noAnterior[i] = -1;
    }

    auxDijkstra(distancia, aPercorrer, noAnterior, mapa, idOrigem);

    arquivo_saida << "---------DIJKSTRA---------" << endl;
    if (this->comecaZero)
    {
        arquivo_saida << "[Caminho minimo entre os nos " << idOrigem << " e " << idDestino << " ]"
                      << " - custo do caminho minimo" << endl;
    }
    else
    {
        if (idOrigem == 0)
        {
            arquivo_saida << "[Caminho minimo entre os nos " << this->getOrdem() << " e " << idDestino << " ]"
                          << " - custo do caminho minimo" << endl;
        }
        else if (idDestino == 0)
        {
            arquivo_saida << "[Caminho minimo entre os nos " << idOrigem << " e " << this->getOrdem() << " ]"
                          << " - custo do caminho minimo" << endl;
        }
        else
        {
            arquivo_saida << "[Caminho minimo entre os nos " << idOrigem << " e " << idDestino << " ]"
                          << " - custo do caminho minimo" << endl;
        }
    }
    arquivo_saida << "--------------------------" << endl;
    if (distancia[mapeamento(mapa, idDestino)] != -1)
    {
        if (comecaZero)
        {
            arquivo_saida << "[" << idDestino;
        }
        else
        {
            if (idDestino == 0)
            {
                arquivo_saida << "[" << this->getOrdem();
            }
            else
            {
                arquivo_saida << "[" << idDestino;
            }
        }

        int caminho = noAnterior[mapeamento(mapa, idDestino)];
        //percorre o vetor de nós a percorrer até que enatualre uma posição igual a -1
        while (caminho != -1)
        {
            if (this->comecaZero)
            {
                arquivo_saida << ", " << caminho;
            }
            else
            {
                if (caminho == 0)
                {
                    arquivo_saida << ", " << this->getOrdem();
                }
                else
                {
                    arquivo_saida << ", " << caminho;
                }
            }
            caminho = noAnterior[mapeamento(mapa, caminho)];
        }
        arquivo_saida << "] - " << distancia[mapeamento(mapa, idDestino)] << endl;
    }
    else
    {
        if (this->comecaZero)
        {
            arquivo_saida << "[" << idOrigem << ", " << idDestino << "] - -1";
        }
        else
        {
            if (idOrigem == 0)
            {
                arquivo_saida << "[" << this->getOrdem() << ", " << idDestino << "] - -1";
            }
            else if (idDestino == 0)
            {
                arquivo_saida << "[" << idOrigem << ", " << this->getOrdem() << "] - -1";
            }
            else
            {
                arquivo_saida << "[" << idOrigem << ", " << idDestino << "] - -1";
            }
        }
    }
    arquivo_saida << "--------------------------------------------------------------------------------------------------------" << endl
                  << endl;
    delete[] aPercorrer;
    delete[] noAnterior;
    delete[] distancia;
    delete[] mapa;
}

/**
 * auxiliar para o algoritmo de Dijkstra
 * @param distancia somatório dos pesos do caminho entre dois nós
 * @param aPercorrer nós a percorres
 * @param noAnterior nó anterior
 * @param mapa mapa de arestas
 * @param atual nó atual
 */
void Grafo::auxDijkstra(float *distancia, int *aPercorrer, int *noAnterior, int *mapa, int atual)
{

    No *aresta = &listaAdj[atual];
    int indiceAtual = mapeamento(mapa, atual);
    int indiceAresta;
    //enquanto a aresta não é nula preenche os vetores de distância e noAnterior
    while (aresta != nullptr)
    {
        indiceAresta = mapeamento(mapa, aresta->getNoDestino());
        //caso o indicie atual da aresta não seja -1
        if (distancia[indiceAresta] != -1)
        {
            if (distancia[indiceAresta] > distancia[indiceAtual] + aresta->getPeso())
            {
                distancia[indiceAresta] = distancia[indiceAtual] + aresta->getPeso();
                noAnterior[indiceAresta] = atual;
            }
        }
        else
        {
            distancia[indiceAresta] = distancia[indiceAtual] + aresta->getPeso();
            noAnterior[indiceAresta] = atual;
        }
        aresta = aresta->getProximoNo();
    }
    int menor = -1;
    //percorre o vetor de nós aPercorrer
    for (int i = 0; i < this->getOrdem() && menor == -1; i++)
    {
        if (aPercorrer[i])
        {
            if (distancia[i] != -1)
            {
                menor = distancia[i];
                atual = mapa[i];
            }
        }
    }
    if (menor != -1)
    {
        for (int i = 0; i < this->getOrdem(); i++)
        {
            if (aPercorrer[i])
                if (distancia[i] != -1)
                    if (distancia[i] < menor)
                    {
                        menor = distancia[i];
                        atual = mapa[i];
                    }
        }
        aPercorrer[indiceAtual] = 0;
        auxDijkstra(distancia, aPercorrer, noAnterior, mapa, atual);
    }
    delete aresta;
}

/**
 * caminho mínimo entre dois vértices pelo algoritmo de Floyd
 * @param idOrigem id do nó de origem
 * @param idDestino id do nó de destino
 * @param arquivo_saida arquivo de saida de dados
 */
void Grafo::floyd(int idOrigem, int idDestino, ofstream &arquivo_saida)
{ //
    // custo[] e matrizAdjacencias[] armazenam o menor caminho
    int **custo, **caminho;
    int **matrizAdjacencias;
    caminho = new int *[this->getOrdem()];
    custo = new int *[this->getOrdem()];
    matrizAdjacencias = new int *[this->getOrdem()];

    //inicializa as matrizes
    for (int i = 0; i < this->getOrdem(); i++)
    {
        caminho[i] = new int[this->getOrdem()];
        custo[i] = new int[this->getOrdem()];
        matrizAdjacencias[i] = new int[this->getOrdem()];
        for (int j = 0; j < this->getOrdem(); j++)
        {
            matrizAdjacencias[i][j] = INFINITO;
            if (i == j)
            {
                matrizAdjacencias[i][j] = 0;
            }
        }
    }

    //preenche a matriz de adjacência com o peso das arestas
    for (int i = 0; i < this->getOrdem(); i++)
    {
        for (No *a = &listaAdj[i]; a != nullptr; a = a->getProximoNo())
        {
            matrizAdjacencias[i][a->getNoDestino()] = a->getPeso();
            matrizAdjacencias[a->getNoDestino()][i] = a->getPeso();
        }
    }

    // inicializa custo[] e matrizAdjacencias[]
    for (int v = 0; v < this->getOrdem(); v++)
    {
        for (int u = 0; u < this->getOrdem(); u++)
        {
            // inicialmente o custo será igual ao peso da aresta
            custo[v][u] = matrizAdjacencias[v][u];
            if (v == u)
                caminho[v][u] = 0;
            else if (custo[v][u] != INFINITO)
                caminho[v][u] = v;
            else
                caminho[v][u] = -1;
        }
    }

    //algoritmo de Floyd
    //como a complexidade deste algoritmo é O(n^3), para instâncias muito grandes ele demora a executar
    for (int k = 0; k < this->getOrdem(); k++)
    {
        for (int v = 0; v < this->getOrdem(); v++)
        {
            for (int u = 0; u < this->getOrdem(); u++)
            {
                // caso o vertice k esteja no menor caminho de v para u, então o valor da posição custo[v][u] é atualizado
                if (custo[v][k] != INFINITO && custo[k][u] != INFINITO && custo[v][k] + custo[k][u] < custo[v][u])
                {
                    custo[v][u] = custo[v][k] + custo[k][u];
                    caminho[v][u] = caminho[k][u];
                }
            }

            // se os elementos da diagonal se tornam negativos, o grafo atual um ciclo de peso negativo
            if (custo[v][v] < 0)
            {
                arquivo_saida << "ciclo de peso negativo enatualrado!!";
                return;
            }
        }
    }

    arquivo_saida << "---------FLOYD---------" << endl;
    arquivo_saida << "[Caminho minimo entre os nos " << idOrigem << " e " << idDestino << " ]"
                  << " - custo do caminho minimo" << endl;
    arquivo_saida << "-----------------------" << endl;
    arquivo_saida << "[" << idOrigem << ", ";
    imprimeCaminhoFloyd(caminho, idOrigem, idDestino, arquivo_saida);
    arquivo_saida << idDestino << "] - " << custo[idOrigem][idDestino] << endl;

    for (int i = 0; i < this->getOrdem(); i++)
    {
        delete[] caminho[i];
        delete[] custo[i];
        delete[] matrizAdjacencias[i];
    }
    delete[] caminho;
    delete[] custo;
    delete[] matrizAdjacencias;
    arquivo_saida << "--------------------------------------------------------------------------------------------------------" << endl
                  << endl;
}

/**
 * função para imprimir o caminho gerado pelo algoritmo de floyd
 * @param caminho matriz do caminho entre nós
 * @param idOrigem id do nó de origem
 * @param idDestino id do nó de destino
 * @param arquivo_saida arquivo de saida de dados
 */
void Grafo::imprimeCaminhoFloyd(int **caminho, int idOrigem, int idDestino, ofstream &arquivo_saida)
{
    if (caminho[idOrigem][idDestino] == idOrigem)
        return;

    imprimeCaminhoFloyd(caminho, idOrigem, caminho[idOrigem][idDestino], arquivo_saida);
    arquivo_saida << caminho[idOrigem][idDestino] << ", ";
}

/**
 * árvore geradora mínima gerada pelo algoritmo de Prim
 * @param arquivo_saida
 */
void Grafo::AGMPrim(ofstream &arquivo_saida)
{
    arquivo_saida << "---------AGM Prim---------" << endl;
    arquivo_saida << "No -- No  |  Peso" << endl;
    arquivo_saida << "--------------------------" << endl;
    int **matrizDeAdjacencias;
    int *menoresCustos = new int[this->getOrdem()];
    int *maisProximo = new int[this->getOrdem()];
    bool *visitados = new bool[this->getOrdem()];

    matrizDeAdjacencias = new int *[this->getOrdem()];

    //preenche a matriz de adjacências com o valor infinito
    for (int i = 0; i < this->getOrdem(); i++)
    {
        matrizDeAdjacencias[i] = new int[this->getOrdem()];
        for (int j = 0; j < this->getOrdem(); j++)
        {
            matrizDeAdjacencias[i][j] = INFINITO;
        }
    }

    //preenche a matriz de adjacências com o peso
    for (int i = 0; i < getOrdem(); i++)
    {
        for (No *a = &listaAdj[i]; a != nullptr; a = a->getProximoNo())
        {
            matrizDeAdjacencias[i][a->getNoDestino()] = a->getPeso();
            matrizDeAdjacencias[a->getNoDestino()][i] = a->getPeso();
        }
    }

    visitados[0] = true;
    //preenche o vetor de menores custos com os menores custos da matriz de adjacências
    for (int i = 1; i < this->getOrdem(); i++)
    {
        menoresCustos[i] = matrizDeAdjacencias[0][i];
        maisProximo[i] = 0;
        visitados[i] = false;
    }

    int peso = 0;
    int atualArestas = 0;
    int verticeAnterior = 0;

    //para o tamanho do grafo
    for (int i = 0; i < this->getOrdem(); i++)
    {
        int min = INFINITO;
        int indice = 1;

        // percorre o vetor de menores custos atualizando-o de acordo com os nós já visitados
        for (int j = 0; j < this->getOrdem(); j++)
        {
            if (menoresCustos[j] < min && !visitados[j])
            {
                min = menoresCustos[j];
                indice = j;
            }
        }

        //caso o indice seja 1 e o minimo sejá infinito, break
        if (indice == 1 && min == INFINITO)
        {
            break;
        }
        else
        {
            peso += min;
        }

        if (comecaZero)
        {
            arquivo_saida << verticeAnterior << " -- " << indice << " | " << min << endl;
        }
        else
        {
            if (verticeAnterior == 0)
            {
                arquivo_saida << this->getOrdem() << " -- " << indice << " | " << min << endl;
            }
            else if (indice == 0)
            {
                arquivo_saida << verticeAnterior << " -- " << this->getOrdem() << " | " << min << endl;
            }
            else
            {
                arquivo_saida << verticeAnterior << " -- " << indice << " | " << min << endl;
            }
        }

        verticeAnterior = indice;
        visitados[indice] = true;
        atualArestas++;
        for (int j = 1; j < this->getOrdem(); j++)
        {
            // Como o novo ponto j é adicionado, é possível enatualrar o peso do ponto j recém-adicionado para o ponto K não em S.
            if ((matrizDeAdjacencias[indice][j] < menoresCustos[j]) && (!visitados[j]))
            {
                //menoresCustos representa o peso minimo requerido para ir de um ponto a outro em uma árvore
                menoresCustos[j] = matrizDeAdjacencias[indice][j];
                maisProximo[j] = indice;
            }
        }
    }

    arquivo_saida << "Somatorio dos Pesos: " << peso << endl;
    arquivo_saida << "Quantidade de arestas: " << atualArestas << endl;
    arquivo_saida << "--------------------------------------------------------------------------------------------------------" << endl
                  << endl;
    for (int i = 0; i < this->getOrdem(); i++)
    {
        delete[] matrizDeAdjacencias[i];
    }
    delete[] matrizDeAdjacencias;
}

/**
 * Classe que define uma aresta simples auxiliar ao algoritmo de Kruskal
 */
class ArestaSimples
{
public:
    int origem;
    int destino;
    int peso;
};

/**
 * verifica se o No já está no vetor de visitados, portando não será necessário colocar a aresta
 * @param nosJaVisitados nós já visitados do grafo
 * @param id_no id do nó de origem
 * @param id_destino id do nó de destino
 * @param tam tamanho da lista de arestas até o momento
 * @return
 */
bool verificaId(ArestaSimples nosJaVisitados[], int id_no, int id_destino, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        if (nosJaVisitados[i].origem == id_destino && nosJaVisitados[i].destino == id_no)
        {
            return true;
        }
    }
    return false;
}

/**
 * árvore geradora mínima gerado pelo algoritmo de Kruskal
 * @param arquivo_saida de saida de dados
 */
void Grafo::AGMKruskal(ofstream &arquivo_saida)
{
    int i = 0, quantNos = 0;

    ArestaSimples *listaAresta = new ArestaSimples[quant_aresta];

    //percorre a lista de adjacências preenchendo as informações da aresta simples
    for (int j = 0; j < getOrdem(); j++)
    {
        for (No *a = &listaAdj[j]; a != nullptr; a = a->getProximoNo())
        {
            if (!verificaId(listaAresta, j, a->getNoDestino(), i))
            {
                listaAresta[i].origem = j;
                listaAresta[i].destino = a->getNoDestino();
                listaAresta[i].peso = a->getPeso();
                i++;
            }
        }
    }

    //ordena a lista de aresta por peso em ordem crescente
    ArestaSimples aux;
    for (int j = 0; j < quant_aresta; j++)
    {
        for (int k = j + 1; k < quant_aresta; k++)
        {
            if (listaAresta[j].peso > listaAresta[k].peso)
            {
                aux = listaAresta[j];
                listaAresta[j] = listaAresta[k];
                listaAresta[k] = aux;
            }
        }
    }

    ArestaSimples *listaArestasSolucao = new ArestaSimples[quant_aresta];

    //pecorre toda a lista de arestas colocando cada uma no grafo para verificação de ciclos
    //caso o grafo possua ciclo, a aresta é removida e não será colocada na solução
    int quantArestasSolucao = 0;
    int atual = 0;
    int arvore[quant_aresta];

    //inicia o vetor arvore
    for (int i = 0; i < quant_aresta; i++)
    {
        arvore[i] = i;
    }

    //percorre as arestas adicionando-as no vetor arvore e na solução
    for (int i = 0; i < quant_aresta; i++)
    {
        if (arvore[listaAresta[i].origem] != arvore[listaAresta[i].destino])
        {
            listaArestasSolucao[atual] = listaAresta[i];
            atual++;
            quantArestasSolucao++;
            int verticeAntigo = arvore[listaAresta[i].origem];
            int novoVertice = arvore[listaAresta[i].destino];
            for (int j = 0; j < quant_aresta; j++)
            {
                if (arvore[j] == verticeAntigo)
                    arvore[j] = novoVertice;
            }
        }
    }

    //Imprime Solução
    unsigned long long int somatorioPesos = 0;
    arquivo_saida << "---------AGM KRUSKAL---------" << endl;
    arquivo_saida << "[No_Origem -- No_Destino] - Peso" << endl;
    arquivo_saida << "-----------------------------" << endl;
    for (int l = 0; l < quantArestasSolucao; l++)
    {
        if (comecaZero)
        {
            arquivo_saida << "[" << listaArestasSolucao[l].origem << " -> " << listaArestasSolucao[l].destino << "] - " << listaArestasSolucao[l].peso << endl;
        }
        else
        {
            if (listaArestasSolucao[l].origem == 0)
            {
                arquivo_saida << "[" << this->getOrdem() << " -> " << listaArestasSolucao[l].destino << "] - " << listaArestasSolucao[l].peso << endl;
            }
            else if (listaArestasSolucao[l].destino == 0)
            {
                arquivo_saida << "[" << listaArestasSolucao[l].origem << " -> " << this->getOrdem() << "] - " << listaArestasSolucao[l].peso << endl;
            }
            else
            {
                arquivo_saida << "[" << listaArestasSolucao[l].origem << " -> " << listaArestasSolucao[l].destino << "] - " << listaArestasSolucao[l].peso << endl;
            }
        }
        somatorioPesos += listaArestasSolucao[l].peso;
    }
    arquivo_saida << "Somatorio dos Pesos: " << somatorioPesos << endl;
    arquivo_saida << "Quantidade de arestas: " << quantArestasSolucao << endl;
    arquivo_saida << "--------------------------------------------------------------------------------------------------------" << endl
                  << endl;
    delete[] listaAresta;
    delete[] listaArestasSolucao;
}

int Grafo::encontraMaiorGrau(ListaAdjacenteEncadeada *lista)
{
    int max = 0;
    for (NoListaAdj *aux = lista->getPos(0); aux != nullptr; aux = aux->getProx())
    {
        if (aux->getGrau() > max)
            max = aux->getGrau();
    }
    for (NoListaAdj *aux = lista->getPos(0); aux != nullptr; aux = aux->getProx())
    {
        if (aux->getGrau() == max)
            return aux->getId();
    }
    return -1;
}
int Grafo::encontraMaiorGrauRandomizado(ListaAdjacenteEncadeada *lista)
{
    int max = 0;
    ListaEncadeada listaEncadeada;
    int maiorVertice = -1;
    for (NoListaAdj *aux = lista->getPos(0); aux != nullptr; aux = aux->getProx())
    {
        if (aux->getGrau() > max)
            max = aux->getGrau();
    }
    for (NoListaAdj *aux = lista->getPos(0); aux != nullptr; aux = aux->getProx())
    {
        if (aux->getGrau() == max)
        {
            listaEncadeada.adicionaEspecial(aux->getId());
            maiorVertice = aux->getId();
        }
        if (listaEncadeada.getTamanho() > 1)
        {
            maiorVertice = listaEncadeada.getPosicao(rand() % listaEncadeada.getTamanho())->getInfo();
        }
    }
    return maiorVertice;
}

void deletaVizinhos(int no, ListaAdjacenteEncadeada *lista)
{
    NoListaAdj *vertice = lista->getNo(no);
    FilaEncadeada vizinhos;
    for (No *aux = vertice->getVizinhos(); aux != nullptr; aux = aux->getProximoNo())
    {
        vizinhos.enfileira(aux->getNoDestino());
    }
    while (!vizinhos.vazia())
    {
        lista->deletaNo(vizinhos.desenfileira());
    }
}

int Grafo::guloso(ofstream &arquivo_saida)
{
    ListaAdjacenteEncadeada *lista = new ListaAdjacenteEncadeada();
    int verticeAtual;
    ListaEncadeada *dominanteMinimo = new ListaEncadeada();

    for (int i = 0; i < this->getOrdem(); i++)
    {
        //preenche lista de adjacencias
        for (No *aux = &listaAdj[i]; aux != nullptr; aux = aux->getProximoNo())
        {
            lista->adiciona(i, aux->getNoDestino());
        }
    }

    while (lista->getTamanho() > 0)
    {
        verticeAtual = encontraMaiorGrau(lista);

        dominanteMinimo->adiciona(verticeAtual);

        if (lista->getNo(verticeAtual)->getGrau() == 0)
        {
            break;
        }

        deletaVizinhos(verticeAtual, lista);
        lista->deletaNo(verticeAtual);

        if (lista->getTamanho() == 0)
        {
            break;
        }
        //#caso o vetor de vértices tenha tamanho 1 ou 2, um vértice aleatório é incluido e finaliza a solução
        if (lista->getTamanho() == 1)
        {
            dominanteMinimo->adicionaEspecial(lista->getPos(0)->getId());
            break;
        }
        else if (lista->getTamanho() == 2)
        {
            int aleatorio = rand() % 2;
            dominanteMinimo->adicionaEspecial(lista->getPos(aleatorio)->getId());
            break;
        }
        //define o no com maior grau como o próximo no inicial
    }
    ListaEncadeada *valores = new ListaEncadeada();

    for (NoLista *aux = dominanteMinimo->getPosicao(0); aux != nullptr; aux = aux->getProx())
    {
        if (valores->getTamanho() == 0)
        {
            valores->adiciona(aux->getInfo());
        }
        else
        {
            bool verifica = false;
            for (NoLista *aux1 = valores->getPosicao(0); aux1 != nullptr; aux1 = aux1->getProx())
            {
                if (aux->getInfo() == aux1->getInfo())
                {
                    verifica = true;
                }
            }
            if (!verifica)
            {
                valores->adiciona(aux->getInfo());
            }
        }
    }
    int atual = 0;
    for (NoLista *aux = valores->getPosicao(0); aux != nullptr; aux = aux->getProx())
    {
        atual++;
    }
    delete lista;
    delete valores;
    delete dominanteMinimo;
    return atual;
}

int Grafo::gulosoRandomizado(float alfa)
{
    int melhorResultado = this->getOrdem();
    for (int i = 0, semMelhora = 0; i < 500 && semMelhora < 200; i++, semMelhora++)
    {
        ListaAdjacenteEncadeada *lista = new ListaAdjacenteEncadeada();
        //srand(alfa);
        int verticeAtual = rand() % this->getOrdem(), atual = 0;
        ListaEncadeada *dominanteMinimo = new ListaEncadeada();
        ListaEncadeada *valores = new ListaEncadeada();
        for (int i = 0; i < this->getOrdem(); i++)
        {
            //preenche lista de adjacencias
            for (No *aux = &listaAdj[i]; aux != nullptr; aux = aux->getProximoNo())
            {
                lista->adiciona(i, aux->getNoDestino());
            }
        }

        while (lista->getTamanho() > 0)
        {
            dominanteMinimo->adiciona(verticeAtual);

            if (lista->getNo(verticeAtual)->getGrau() == 0)
            {
                break;
            }

            deletaVizinhos(verticeAtual, lista);
            lista->deletaNo(verticeAtual);

            if (lista->getTamanho() == 0)
            {
                break;
            }
            //caso o vetor de vértices tenha tamanho 1 ou 2, um vértice aleatório é incluido e finaliza a solução
            if (lista->getTamanho() == 1)
            {
                dominanteMinimo->adicionaEspecial(lista->getPos(0)->getId());
                break;
            }
            else if (lista->getTamanho() == 2)
            {
                int aleatorio = rand() % 2;
                dominanteMinimo->adicionaEspecial(lista->getPos(aleatorio)->getId());
                break;
            }
            //define o no com maior grau como o próximo no inicial
            verticeAtual = encontraMaiorGrauRandomizado(lista);
        }

        for (NoLista *aux = dominanteMinimo->getPosicao(0); aux != nullptr; aux = aux->getProx())
        {
            if (valores->getTamanho() == 0)
            {
                valores->adiciona(aux->getInfo());
            }
            else
            {
                bool verifica = false;
                for (NoLista *aux1 = valores->getPosicao(0); aux1 != nullptr; aux1 = aux1->getProx())
                {
                    if (aux->getInfo() == aux1->getInfo())
                    {
                        verifica = true;
                    }
                }
                if (!verifica)
                {
                    valores->adiciona(aux->getInfo());
                }
            }
        }
        atual = 0;
        for (NoLista *aux = valores->getPosicao(0); aux != nullptr; aux = aux->getProx())
        {
            atual++;
        }
        if (atual < melhorResultado)
        {
            melhorResultado = atual;
            semMelhora = 0;
        }
        delete lista;
        delete valores;
        delete dominanteMinimo;
    }

    return melhorResultado;
}
