#include <iostream>
#include "ListaEncadeada.h"

using namespace std;

/**
 * construtor
 */
ListaEncadeada::ListaEncadeada()
{
    noInicio = nullptr;
    noFim = nullptr;
    tamanho = 0;
}
/**
 * destrutor
 */
ListaEncadeada::~ListaEncadeada()
{
    NoLista* p = noInicio;
    while (p != nullptr)
    {
        NoLista* t = p->getProx();
        delete p;
        p = t;
    }

}

 /**
  * função que insere um No no fim
  * @param val valor do No
  */
void ListaEncadeada::adiciona(int val)
{
    NoLista* p = new NoLista();
    p->setInfo(val);
    p->setProx(nullptr);
    p->setAnt(noFim);
    if (noInicio == nullptr)
    {
        noInicio = p;
        noFim = p;
    }
    else
    {
        noFim->setProx(p);
        noFim = p;
    }
    this->tamanho++;
}
/**
 * função que insere um No no fim
 * @param val valor do No
 */
void ListaEncadeada::adicionaEspecial(int val)
{
    bool existe = false;
    if (tamanho > 1)
    {
        for (NoLista* aux = noInicio; aux != nullptr; aux = aux->getProx())
        {
            if (aux->getInfo() == val)
            {
                existe = true;
                break;
            }
        }
    }

    if (!existe)
    {
        NoLista* p = new NoLista();
        p->setInfo(val);
        p->setProx(nullptr);
        p->setAnt(noFim);
        if (noInicio == nullptr)
        {
            noInicio = p;
            noFim = p;
        }
        else
        {
            noFim->setProx(p);
            noFim = p;
        }
        this->tamanho++;
    }
}

/**
 * função que insere um No no fim
 * @param val valor do No
 * @param info2 valor da segunda informação
 */
void ListaEncadeada::adiciona(int val, int info2)
{
    NoLista* p = new NoLista();
    p->setInfo(val);
    p->setProx(nullptr);
    p->setAnt(noFim);
    p->setInfo2(info2);
    if (noInicio == nullptr)
    {
        noInicio = p;
        noFim = p;
    }
    else
    {
        noFim->setProx(p);
        noFim = p;
    }
    this->tamanho++;
}

/**
 * função que elimina o val encontrado
 * @param val Valor a ser removido
 */
void ListaEncadeada::removeValor(int val)
{
    if (this->getTamanho() > 0) {
        NoLista* p = nullptr;
        if (tamanho == 1 && noInicio->getInfo() == val) {
            delete noInicio;
            noInicio = nullptr;
            noFim = nullptr;
            this->tamanho--;
        }
        else if (noInicio->getInfo() == val) {
            p = noInicio;
            noInicio = noInicio->getProx();
        }
        else if (noFim->getInfo() == val) {
            p = noFim;
            noFim = noFim->getAnt();
        }
        else {
            //Percorre a lista para ver se no é encontrado
            for (NoLista* aux = noInicio; aux != nullptr; aux = aux->getProx()) {
                if (aux->getInfo() == val) {
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
            }
        }
        delete p;
    }
    /*
    int cont = 0;
    NoLista* p = nullptr;
    for (NoLista* aux = noInicio; aux != nullptr; aux = p, cont++)
    {
         p= aux->getProx();
        if (aux->getInfo() == val || aux->getInfo2() == val)
        {
            //Caso base
            if (noInicio == NULL || aux == NULL)
                return;

            //Se o nó aux é o noInicio
            if (noInicio == aux)
                noInicio = aux->getProx();

            //Muda o próximo nó se o aux não for o último
            if (aux->getProx() != NULL)
                aux->getProx()->setAnt(aux->getAnt());

            //Muda o nó anterior se o nó aux não é o primeiro nó
            if (aux->getAnt() != NULL)
                aux->getAnt()->setProx(aux->getProx());
            this->tamanho--;
            free(aux);
        }
    }
    */
}

/**
 * função que verifica se a lista está vazia
 * @return bool
 */
bool ListaEncadeada::isVazio()
{
    if (noInicio == nullptr)
        return true;
    else
        return false;
}

/**
 * função que retorna o número de Nos
 * @return tamanho 
 */
int ListaEncadeada::getTamanho()
{
    return this->tamanho;
}

/*
* Função que imprime a lista
*/
void ListaEncadeada::imprimeLista()
{
    int i = 0;
    for (NoLista* a = this->noInicio; a != nullptr; a = a->getProx())
    {
        if (i > 0)
        {
            cout << ", ";
        }
        i++;
        cout << a->getInfo();
    }
    cout << endl;
}

/*
* Função que retorna uma posição da Lista Encadeada
* @param pos Index da Lista
* @return NoLista 
*/
NoLista* ListaEncadeada::getPosicao(int pos)
{
    if (pos < 0 || pos >= this->tamanho)
    {
        cout << "Erro! " << pos << " eh posicao invalida" << endl;
        exit(1);
    }
    else
    {
        int cont = 0;
        //Percorre a lista até encontrar a posição
        for (NoLista* a = this->noInicio; a != nullptr; a = a->getProx())
        {
            if (cont == pos)
            {
                return a;
            }
            cont++;
        }
    }
    return nullptr;
}

int ListaEncadeada::getUltimo()
{
    return noFim->getInfo();
}

/*
* Função que altera o valor de uma determinada posição da lista
* @param pos Index da posição
* @param val novo valor da posição
*/
void ListaEncadeada::alteraValor(int pos, int val)
{
    if (pos < 0 || pos >= this->tamanho)
    {
        cout << "Erro! " << pos << " eh posicao invalida" << endl;
        exit(1);
    }
    else
    {
        int cont = 0;
        //Percorre a lista até o index da posição a ser alterada
        for (NoLista* a = this->noInicio; a != nullptr; a = a->getProx())
        {
            if (cont == pos)
            {
                a->setInfo(val);
                break;
            }
            cont++;
        }
    }
}

/*
* Verifica se val existe na lista
* @param val Valor a ser verificado
* @return true se for encontrado e false se não foi
*/
bool ListaEncadeada::verificaElemento(int val)
{
    //Percorre a lista para ver se val é encontrado
    for (NoLista* a = this->noInicio; a != nullptr; a = a->getProx())
    {
        if (a->getInfo() == val)
        {
            return true;
        }
    }
    return false;
}
