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
 * @return se o grafo come�a com zero
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
 * fun��o auxiliar para inserir arestas no grafo
 * @param id id do n� de origem
 * @param id_destino id do n� de destino
 * @return true se conseguiu enatualrar o id do n� de destino false caso n�o tenha conseguido
 */
bool Grafo::auxInserirAresta(int id, int id_destino)
{
	//n�o permite self-loops
	if (id == id_destino)
	{
		return true;
	}
	for (No* a = &listaAdj[id]; a != nullptr; a = a->getProximoNo())
	{
		//verifica se o id n� de destino existente no grafo � igual o id do n� de destino a ser inserido
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
	//caso a aresta entre os n� n�o exista
	if (!auxInserirAresta(id, id_destino))
	{
		//tratamento para grafo que come�a com v�rtice igual a 1
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
			No* aux = &this->listaAdj[id];
			while (aux->getProximoNo() != nullptr)
			{
				aux = aux->getProximoNo();
			}
			aux->setProximoNo(new No(id_destino));
		}
		//insere a aresta no n� de destino
		//caso a primeira posi��o esteja vazia
		if (this->listaAdj[id_destino].getNoDestino() == -1)
		{
			this->listaAdj[id_destino].setNoDestino(id);
		}
		else
		{
			No* aux = &this->listaAdj[id_destino];
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
 * mostra os n�s e seus vizinhos de forma ordenada
 * @param arquivo_saida arquivo de sa�da de dados
 */
void Grafo::mostrarGrafo(ofstream& arquivo_saida)
{
	arquivo_saida << "------------GRAFO-------------" << endl;
	arquivo_saida << "  No  |  No(s) Vizinho(s) " << endl;
	arquivo_saida << "------------------------------" << endl;
	int atual = 0;
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
		//percorre o n� imprimindo todas as arestas
		for (No* a = &listaAdj[i]; a != nullptr; a = a->getProximoNo())
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
 * Mostra os n�s e seus pesos de forma ordenada
 * @param arquivo_saida arquivo de saida de dados
 */
void Grafo::mostrarNos(ofstream& arquivo_saida)
{
	arquivo_saida << "-------------NOS--------------" << endl;
	arquivo_saida << "  No  |   Grau " << endl;
	arquivo_saida << "------------------------------" << endl;
	int atual = 0;
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
		for (No* a = &listaAdj[i]; a != nullptr; a = a->getProximoNo())
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
 * Mostra as arestas entre os n�s e seus pesos
 * @param arquivo_saida arquivo de saida de dados
 */
void Grafo::mostrarArestas(ofstream& arquivo_saida)
{
	arquivo_saida << "-----------ARESTAS------------" << endl;
	arquivo_saida << "  No -- No " << endl;
	arquivo_saida << "------------------------------" << endl;
	//percorre o grafo imprimindo as arestas de cada n� de forma ordenada
	for (int i = 0; i < getOrdem(); i++)
	{
		for (No* a = &listaAdj[i]; a != nullptr; a = a->getProximoNo())
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

int Grafo::encontraMaiorGrau(ListaAdjacenteEncadeada* lista)
{
	int max = 0;
	for (NoListaAdj* aux = lista->getPos(0); aux != nullptr; aux = aux->getProx())
	{
		if (aux->getGrau() > max)
			max = aux->getGrau();
	}
	for (NoListaAdj* aux = lista->getPos(0); aux != nullptr; aux = aux->getProx())
	{
		if (aux->getGrau() == max)
			return aux->getId();
	}
	return -1;
}

void deletaVizinhos(int no, ListaAdjacenteEncadeada* lista)
{
	//NoListaAdj* vertice = lista->getNo(no);
	FilaEncadeada* vizinhos = new FilaEncadeada();
	for (No* aux = lista->getNo(no)->getVizinhos(); aux != nullptr; aux = aux->getProximoNo())
	{
		vizinhos->enfileira(aux->getNoDestino());
	}
	while (!vizinhos->vazia())
	{
		lista->deletaNo(vizinhos->desenfileira());
	}
	delete vizinhos;
}

int Grafo::guloso(ofstream& arquivo_saida)
{
	ListaAdjacenteEncadeada* lista = new ListaAdjacenteEncadeada();
	int verticeAtual;
	ListaEncadeada* dominanteMinimo = new ListaEncadeada();

	for (int i = 0; i < this->getOrdem(); i++)
	{
		//preenche lista de adjacencias
		for (No* aux = &listaAdj[i]; aux != nullptr; aux = aux->getProximoNo())
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
		//#caso o vetor de v�rtices tenha tamanho 1 ou 2, um v�rtice aleat�rio � incluido e finaliza a solu��o
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
		//define o no com maior grau como o pr�ximo no inicial
	}
	ListaEncadeada* valores = new ListaEncadeada();

	for (NoLista* aux = dominanteMinimo->getPosicao(0); aux != nullptr; aux = aux->getProx())
	{
		if (valores->getTamanho() == 0)
		{
			valores->adiciona(aux->getInfo());
		}
		else
		{
			bool verifica = false;
			for (NoLista* aux1 = valores->getPosicao(0); aux1 != nullptr; aux1 = aux1->getProx())
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
	for (NoLista* aux = valores->getPosicao(0); aux != nullptr; aux = aux->getProx())
	{
		atual++;
	}
	delete lista;
	delete valores;
	delete dominanteMinimo;
	return atual;
}

struct Vertice {
	public:
		int id;
		int grau;
};

void troca(Vertice* a, Vertice* b)
{
	Vertice t = *a;
	*a = *b;
	*b = t;
}


int particao(Vertice vertices[], int menor, int maior)
{
	int pivo = vertices[maior].grau; // pivo  
	int i = (menor - 1); // Index of smaller element  

	for (int j = menor; j <= maior - 1; j++)
	{
		// If current element is smaller than the pivo  
		if (vertices[j].grau < pivo)
		{
			i++; // increment index of smaller element  
			troca(&vertices[i], &vertices[j]);
		}
	}
	troca(&vertices[i + 1], &vertices[maior]);
	return (i + 1);
}


void quickSort(Vertice vertices[], int menor, int maior)
{
	if (menor < maior)
	{
		int pi = particao(vertices, menor, maior);

		quickSort(vertices, menor, pi - 1);
		quickSort(vertices, pi + 1, maior);
	}
}

int* geraVetorOrdenado(ListaAdjacenteEncadeada* lista, float alfa) {
	int tamanho = lista->getTamanho() * alfa;
	Vertice * vetor = new Vertice[lista->getTamanho()];
	int cont=0;
	int a = -1;
	for (NoListaAdj* aux = lista->getPos(0); aux != nullptr; aux = aux->getProx()) {
		vetor[cont].id = aux->getId();
		vetor[cont].grau = aux->getGrau();
		cont++;
	}
	quickSort(vetor, 0, lista->getTamanho()-1);

	int* melhoresNos = new int[tamanho];
	for (int i = 0; i < tamanho; i++) {
		if(lista->getTamanho() - 1 - i > 0)
			melhoresNos[i] = vetor[lista->getTamanho() - 1 - i].id;
	}

	delete[] vetor;
	return melhoresNos;
}

int Grafo::encontraMaiorGrauRandomizado(ListaAdjacenteEncadeada* lista, float alfa)
{
	int* melhoresNos = geraVetorOrdenado(lista, alfa);
	int i = (lista->getTamanho()- 1) * alfa;
	int escolhido = melhoresNos[rand() % i];
	delete []melhoresNos;
	return escolhido;
}

int* Grafo::gulosoRandomizado(float alfa)
{
	/*
	for (int i = 0, semMelhora = 0; i < 500 && semMelhora < 200; i++, semMelhora++)
	{
		ListaAdjacenteEncadeada* lista = new ListaAdjacenteEncadeada();
		ListaEncadeada* dominanteMinimo = new ListaEncadeada();
		NoListaAdj* vetorNo = new NoListaAdj();
		//lista->adiciona(1,1);
		for (int i = 0; i < this->getOrdem(); i++)
		{
			//preenche lista de adjacencias
			for (No* aux = &listaAdj[i]; aux != nullptr; aux = aux->getProximoNo())
			{
				lista->adiciona(i, aux->getNoDestino());
				if(!dominanteMinimo->verificaElemento(i))
					dominanteMinimo->adiciona(i);
				vetorNo->adicionaVizinho(aux->getNoDestino());
				dominanteMinimo->adicionaEspecial(i);
			}
		}
		for (int i = 0; i < this->getOrdem(); i++) {
			deletaVizinhos(i, lista);
			//lista->deletaNo(i);
			//vetorNo->deletaVizinho(i);
		}
		delete vetorNo;
		delete dominanteMinimo;
		delete lista;
	}

	return -1;
	*/
	int melhorResultado = this->getOrdem(), atual = 0;
	int *resultados = new int[2];
	for (int i = 0, semMelhora = 0; i < 500 && semMelhora < 200; i++, semMelhora++)
	{
		ListaAdjacenteEncadeada* lista = new ListaAdjacenteEncadeada();
		for (int i = 0; i < this->getOrdem(); i++)
		{
			//preenche lista de adjacencias
			for (No* aux = &listaAdj[i]; aux != nullptr; aux = aux->getProximoNo())
			{
				lista->adiciona(i, aux->getNoDestino());
			}
		}
		
		int verticeAtual = encontraMaiorGrauRandomizado(lista, alfa);
		ListaEncadeada* dominanteMinimo = new ListaEncadeada();
		ListaEncadeada* valores = new ListaEncadeada();


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
			//caso o vetor de v�rtices tenha tamanho 1 ou 2, um v�rtice aleat�rio � incluido e finaliza a solu��o
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
			//define o no com maior grau como o pr�ximo no inicial
			verticeAtual = encontraMaiorGrauRandomizado(lista, alfa);
		}

		for (NoLista* aux = dominanteMinimo->getPosicao(0); aux != nullptr; aux = aux->getProx())
		{
			if (valores->getTamanho() == 0)
			{
				valores->adiciona(aux->getInfo());
			}
			else
			{
				bool verifica = false;
				for (NoLista* aux1 = valores->getPosicao(0); aux1 != nullptr; aux1 = aux1->getProx())
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
		for (NoLista* aux = valores->getPosicao(0); aux != nullptr; aux = aux->getProx())
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
		resultados [1] = semMelhora; 
	}
	resultados[0] = melhorResultado;
	return resultados;
	
}
