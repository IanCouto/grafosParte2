#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <string.h>
#include <chrono>
#include <limits>
#include <math.h>
#include "Grafo.h"
#include "FilaEncadeada.h"
#include "ListaEncadeada.h"
#include "ListaAdjacenteEncadeada.h"

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
* Função que faz busca em profundidade
* @param v vértice atual
* @param visitados vetor de vértices visitados
* @param lista lista com vértices para serem visitados
*/
void Grafo::buscaEmProfundidade(int v, bool visitados[], ListaEncadeada *lista)
{
	//Marca o vértice atual como visitado
	visitados[v] = true;

	//Percorre os vizinhos do vértice atual e coloca na lista para serem visitados
	for (No* aux = &listaAdj[v]; aux != nullptr; aux = aux->getProximoNo()) {
		if (!visitados[aux->getNoDestino()]) {
			lista->adicionaEspecial(aux->getNoDestino());
		}
	}
	
	while (lista->getTamanho() > 0) {
		int x = lista->getUltimo();
		lista->removeValor(x);
		buscaEmProfundidade(x, visitados, lista);
	}
}

/*
* Função para verificar se o grafo é conexo
* @return bool 
*/
bool Grafo::isConexo() {
	bool* visitados = new bool[this->getOrdem()];
	// Marca todos os vértices como não visitados
	for (int i = 0; i < this->getOrdem(); i++)
		visitados[i] = false;
	ListaEncadeada * lista= new ListaEncadeada();
	buscaEmProfundidade(0, visitados,lista);

	for (int i = 0; i < this->getOrdem(); i++) {
		if (visitados[i] == false)
			return false;
	}
	delete lista;
	return true;
}

/**
 * fun��o auxiliar para inserir arestas no grafo
 * @param id id do nó de origem
 * @param id_destino id do nó de destino
 * @return true se conseguiu enatualrar o id do n� de destino false caso n�o tenha conseguido
 */
bool Grafo::auxInserirAresta(int id, int id_destino)
{
	//n�o permite self-loops
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
 * @param id id do n� de origem
 * @param id_destino id do n� de destino
 * @param peso peso da aresta entre os n�s
 */
void Grafo::inserirAresta(int id, int id_destino)
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
		//insere a aresta no n� de origem;
		//caso a primeira posi��o esteja vazia
		if (this->listaAdj[id].getNoDestino() == -1)
		{
			this->listaAdj[id].setNoDestino(id_destino);
		}
		else
		{
			No *aux = &this->listaAdj[id];
			while (aux->getProximoNo() != nullptr)
			{
				aux = aux->getProximoNo();
			}
			aux->setProximoNo(new No(id_destino));
		}
		//insere a aresta no nó de destino
		//caso a primeira posição esteja vazia
		if (this->listaAdj[id_destino].getNoDestino() == -1)
		{
			this->listaAdj[id_destino].setNoDestino(id);
		}
		else
		{
			No *aux = &this->listaAdj[id_destino];
			while (aux->getProximoNo() != nullptr)
			{
				aux = aux->getProximoNo();
			}
			aux->setProximoNo(new No(id));
		}
		this->quant_aresta++;
	}
}

/**
 * mostra os nós e seus vizinhos de forma ordenada
 * @param arquivo_saida arquivo de sa�da de dados
 */
void Grafo::mostrarGrafo(ofstream &arquivo_saida)
{
	arquivo_saida << "------------GRAFO-------------" << endl;
	arquivo_saida << "  No  |  No(s) Vizinho(s) " << endl;
	arquivo_saida << "------------------------------" << endl;
	int vertices = 0;
	int arestas = 0;
	//acertar a posição dos elementos a serem imprimidos
	for (int i = 0; i < getOrdem(); i++)
	{
		vertices++;
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
			arestas++;
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

	arquivo_saida << "Número de vértices: " << vertices<<endl;
	arquivo_saida << "Número de arestas: " <<arestas<< endl;
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
	int arestas = 0;
	//acertar a posi��o dos elementos a serem imprimidos
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
			arestas++;
			atual++;
		}
		arquivo_saida << atual << endl;
		atual = 0;
	}
	arquivo_saida << "Número de arestas: " << arestas << endl;
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
	arquivo_saida << "  No -- No " << endl;
	arquivo_saida << "------------------------------" << endl;
	//percorre o grafo imprimindo as arestas de cada n� de forma ordenada
	for (int i = 0; i < getOrdem(); i++)
	{
		for (No *a = &listaAdj[i]; a != nullptr; a = a->getProximoNo())
		{
			if (!comecaZero && i == 0)
			{
				arquivo_saida << this->getOrdem() << " -- " << a->getNoDestino() << endl;
			}
			else
			{
				if (!comecaZero && a->getNoDestino() == 0)
				{
					arquivo_saida << i << " -- " << this->getOrdem() << endl;
				}
				else
				{
					arquivo_saida << i << " -- " << a->getNoDestino() << endl;
				}
			}
		}
	}
	arquivo_saida << "--------------------------------------------------------------------------------------------------------" << endl
				  << endl;
}

/*
 * Encontra o maior grau de uma lista de vértices
 * @param lista
 */
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

/*
 * Deleta os vizinhos de um vértice
 * @param no 
 * @param lista
 */
void deletaVizinhos(int no, ListaAdjacenteEncadeada *lista)
{
	//NoListaAdj* vertice = lista->getNo(no);
	FilaEncadeada *vizinhos = new FilaEncadeada();
	for (No *aux = lista->getNo(no)->getVizinhos(); aux != nullptr; aux = aux->getProximoNo())
	{
		vizinhos->enfileira(aux->getNoDestino());
	}
	while (!vizinhos->vazia())
	{
		lista->deletaNo(vizinhos->desenfileira());
	}
	delete vizinhos;
}

/*
 * Algoritmo Guloso do Conjunto Dominante Mínimo
 * @param arquivo_saida Arquivo de resultados
 */
int Grafo::guloso(ofstream &arquivo_saida)
{
	ListaAdjacenteEncadeada *lista = new ListaAdjacenteEncadeada();
	int verticeAtual;
	ListaEncadeada *dominanteMinimo = new ListaEncadeada();

	//preencher a lista de adjacencias
	for (int i = 0; i < this->getOrdem(); i++)
	{
		for (No *aux = &listaAdj[i]; aux != nullptr; aux = aux->getProximoNo())
		{
			lista->adiciona(i, aux->getNoDestino());
		}
	}

	while (lista->getTamanho() > 0)
	{
		//define o primeiro nó de maior grau encontrado como vértice escolhido e o adiciona na solução
		verticeAtual = encontraMaiorGrau(lista);
		dominanteMinimo->adiciona(verticeAtual);

		//caso o vértice escolhido não tenha mais vizinhos, uma solução foi encontrada
		if (lista->getNo(verticeAtual)->getGrau() == 0)
		{
			break;
		}

		//remove o vértice atual e os seus vizinhos da lista de candidatos
		deletaVizinhos(verticeAtual, lista);
		lista->deletaNo(verticeAtual);

		//caso a lista esteja vazia, uma solução foi encontrada
		if (lista->getTamanho() == 0)
		{
			break;
		}
		//caso o vetor de vértices tenha tamanho 1 ou 2, um vértices aleatório é incluido e finaliza a solução
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
	}
	ListaEncadeada *valores = new ListaEncadeada();

	//verifica se a solução encontrada é uma solução válida
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
	//salva o tamanho da solução atual para poder deletar a lista verificada
	int atual = valores->getTamanho();
	delete lista;
	delete valores;
	delete dominanteMinimo;
	return atual;
}

/*
 * Estrutura auxiliar para ordenação no quick sort
 */
struct Vertice
{
public:
	int id;
	int grau;
};

/*
 * Função para trocar de posição dois vértices
 * @param *a Vertice a
 * @param *b Vertice b
 */
void troca(Vertice *a, Vertice *b)
{
	Vertice t = *a;
	*a = *b;
	*b = t;
}

/*
 * Função auxiliar do quick sort
 * @param vertices[] vetor de vertices
 * @param menor index do menor elemento
 * @param maior index do maior elemento
 */
int particao(Vertice vertices[], int menor, int maior)
{
	int pivo = vertices[maior].grau; // pivo
	int i = (menor - 1);			 // Indice do menor elemento

	for (int j = menor; j <= maior - 1; j++)
	{
		// Se o elemento é menor que o pivô
		if (vertices[j].grau < pivo)
		{
			i++; // incrementa o index do menor elemento
			troca(&vertices[i], &vertices[j]);
		}
	}
	troca(&vertices[i + 1], &vertices[maior]);
	return (i + 1);
}

/*
 * Função quick sort para ordenar um vetor de vertices
 * @param vertices[] vetor de vertices
 * @param menor index do menor elemento
 * @param maior index maior elemento
 */
void quickSort(Vertice vertices[], int menor, int maior)
{
	if (menor < maior)
	{
		int pi = particao(vertices, menor, maior);

		quickSort(vertices, menor, pi - 1);
		quickSort(vertices, pi + 1, maior);
	}
}

/*
 * Função que retorna uma lista de melhores resultados a partir de um alfa
 * @param lista Lista de Adjacencias
 * @param alfa Alfa
 */
int *geraVetorOrdenado(ListaAdjacenteEncadeada *lista, float alfa)
{
	int tamanho = lista->getTamanho() * alfa;
	if (tamanho == 0)
	{
		tamanho = 1;
	}
	//um vetor auxiliar é criado para ser ordenado
	Vertice *vetor = new Vertice[lista->getTamanho()];
	int cont = 0;
	int a = -1;
	for (NoListaAdj *aux = lista->getPos(0); aux != nullptr; aux = aux->getProx())
	{
		vetor[cont].id = aux->getId();
		vetor[cont].grau = aux->getGrau();
		cont++;
	}
	//ordena o vetor auxiliar
	quickSort(vetor, 0, lista->getTamanho() - 1);

	//transfere os valores ordenados para a lista
	int *melhoresNos = new int[tamanho];
	for (int i = 0; i < tamanho; i++)
	{
		if (lista->getTamanho() - 1 - i > 0)
			melhoresNos[i] = vetor[lista->getTamanho() - 1 - i].id;
	}

	delete[] vetor;
	return melhoresNos;
}

/*
 * Função que encontra um vértice a partir de uma lista
 * @param lista Lista de Adjacencias
 * @param alfa Alfa
 */
int Grafo::encontraMaiorGrauRandomizado(ListaAdjacenteEncadeada *lista, float alfa)
{
	//alfa representa a porcentagem da lista ordenada que pode ser escolhida
	int *melhoresNos = geraVetorOrdenado(lista, alfa);
	int i = (lista->getTamanho() - 1) * alfa;
	int escolhido;
	if (i != 0)
		escolhido = melhoresNos[rand() % i];
	else
		escolhido = melhoresNos[0];
	delete[] melhoresNos;
	return escolhido;
}

/*
 * Algoritmo Guloso Randomizado do Conjunto Dominante Mínimo
 * @param alfa Alfa
 */
int *Grafo::gulosoRandomizado(float alfa)
{
	int melhorResultado = this->getOrdem(), atual = 0;
	int *resultados = new int[2];
	//casos de parada do algoritmo randomizado, 500 iterações ou 200 iterações seguidas sem melhora no resultado
	for (int i = 0, semMelhora = 0; i < 500 && semMelhora < 200; i++, semMelhora++)
	{
		//preencher a lista de adjacencias
		ListaAdjacenteEncadeada *lista = new ListaAdjacenteEncadeada();
		for (int i = 0; i < this->getOrdem(); i++)
		{
			for (No *aux = &listaAdj[i]; aux != nullptr; aux = aux->getProximoNo())
			{
				lista->adiciona(i, aux->getNoDestino());
			}
		}
		//é definido como vértice atual um nó aleatório da sublista ordenada de melhores candidatos
		int verticeAtual = encontraMaiorGrauRandomizado(lista, alfa);
		ListaEncadeada *dominanteMinimo = new ListaEncadeada();
		ListaEncadeada *valores = new ListaEncadeada();

		while (lista->getTamanho() > 0)
		{
			//caso não existam mais nós a serem inseridos, uma solução foi encontrada
			if (verticeAtual == -1)
			{
				break;
			}
			//adiciona o vértice atual ao conjunto solução
			dominanteMinimo->adiciona(verticeAtual);

			//caso o vértice atual não tenha vizinhos uma solução foi encontrada
			if (lista->getNo(verticeAtual)->getGrau() == 0)
			{
				break;
			}

			//remove o vértice atual e os seus vizinhos da lista de candidatos
			deletaVizinhos(verticeAtual, lista);
			lista->deletaNo(verticeAtual);

			//caso a lista esteja vazia, uma solução foi encontrada
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

			//é definido como vértice atual um nó aleatório da sublista ordenada de melhores candidatos
			verticeAtual = encontraMaiorGrauRandomizado(lista, alfa);
		}

		//verifica se a solução encontrada é válida
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
		atual = valores->getTamanho();
		if (atual < melhorResultado)
		{
			melhorResultado = atual;
			semMelhora = 0;
		}
		delete lista;
		delete valores;
		delete dominanteMinimo;
		resultados[1] = semMelhora;
	}
	resultados[0] = melhorResultado;
	return resultados;
}
