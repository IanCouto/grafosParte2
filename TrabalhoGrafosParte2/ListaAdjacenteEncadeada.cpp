#include <iostream>
#include "ListaAdjacenteEncadeada.h"

using namespace std;

/*
* Construtor
*/
ListaAdjacenteEncadeada::ListaAdjacenteEncadeada() {
	this->noInicio = nullptr; // ponteiro para No do comeco
	this->noFim = nullptr; // ponteiro para No do fim
	this->tamanho = 0;
}

/*
 * Destrutor
 */
ListaAdjacenteEncadeada::~ListaAdjacenteEncadeada() {
	NoListaAdj* p = noInicio;
	while (p != nullptr)
	{
		NoListaAdj* t = p->getProx();
		delete p;
		p = t;
	}
}


/*
* Retorna o tamanho da lista
* @return tamanho
*/
int ListaAdjacenteEncadeada::getTamanho() {
	return this->tamanho;
}

/*
* Adiciona um vértice e seu vizinho
* @param no ID do vértice
* @param noDestino ID do vértice vizinho
*/
void ListaAdjacenteEncadeada::adiciona(int no, int noDestino) {
	//Se lista vazia
	if (noInicio == nullptr) {
		NoListaAdj* p = new NoListaAdj(no, noDestino);
		p->setAnt(noFim);
		noInicio = p;
		noFim = p;
		this->tamanho++;
	}
	else {
		//Se o último nó é igual ao nó passado pelo parametro, só é adicionado seu vizinho
		if (noFim->getId() == no) {
			noFim->adicionaVizinho(noDestino);
		}
		else {
			NoListaAdj* p = new NoListaAdj(no, noDestino);
			p->setAnt(noFim);
			noFim->setProx(p);
			noFim = p;
			this->tamanho++;
		}
	}
}

/*
* Função que deleta um nó
* @param no ID do nó a ser deletado
*/
void ListaAdjacenteEncadeada::deletaNo(int no) {
	if (this->getTamanho() > 0) {
		NoListaAdj* p=nullptr;
		if (tamanho == 1 && noInicio->getId() == no) {
			delete noInicio;
			noInicio = nullptr;
			noFim = nullptr;
			this->tamanho--;
		}
		else if (noInicio->getId() == no) {
			p = noInicio;
			noInicio = noInicio->getProx();
		}
		else if (noFim->getId() == no) {
			p = noFim;
			noFim = noFim->getAnt();
		}
		else {
			//Percorre a lista para ver se no é encontrado
			for (NoListaAdj* aux = noInicio; aux != nullptr; aux = aux->getProx()) {
				if (aux->getId() == no) {
					p = aux;
					break;
				}
			}
		}
		if (tamanho > 0) {
			if (p != nullptr) {
				if (p->getAnt() != nullptr)
					p->getAnt()->setProx(p->getProx());
				if (p->getProx() != nullptr)
					p->getProx()->setAnt(p->getAnt());
				this->tamanho--;
				//Percorre os vértices para deletar o no na lista de viznhos
				for (NoListaAdj* aux = noInicio; aux != nullptr; aux = aux->getProx()) {
					aux->deletaVizinho(no);
				}
			}
		}
		delete p;
	}
}

/*
* Função que retorna um nó a partir de seu id
* @param no ID do nó a ser retornado
* @return NoListaAdj retorna o nó se foi encontrado ou nullptr se não foi encontrado
*/
NoListaAdj* ListaAdjacenteEncadeada::getNo(int no) {
	for (NoListaAdj* aux = noInicio; aux != nullptr; aux = aux->getProx()) {
		if (aux->getId() == no) {
			return aux;
		}
	}
	return nullptr;
}

/*
* Função que retorna um índice da lista
* @param index índice da lista
* @return NoListaAdj retorna o nó se foi encontrado ou nullptr se não foi encontrado
*/
NoListaAdj* ListaAdjacenteEncadeada::getPos(int index) {
	if (index >= 0 && index < tamanho) {
		int cont = 0;
		//Percorre a lista para encontrar o índice
		for (NoListaAdj* aux = noInicio; aux != nullptr; aux = aux->getProx()) {
			if (cont == index) {
				return aux;
			}
			cont++;
		}
	}
	return nullptr;
}

/*
* Função que imprime o conteúdo da lista
*/
void ListaAdjacenteEncadeada::imprimeLista() {
	cout << "imprimindo lista" << endl;
	//Percorre a lista de vértices
	for (NoListaAdj* aux = noInicio; aux != nullptr; aux = aux->getProx()) {
		cout << aux->getId() << "  | ";
		//Percorre a lista de vizinhos do vértice
		for (No* aux1 = aux->getVizinhos(); aux1 != nullptr; aux1 = aux1->getProximoNo()) {
			cout << aux1->getNoDestino() << ", ";
		}
		cout << endl;
	}
}
