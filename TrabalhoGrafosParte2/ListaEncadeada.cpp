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
 */
void ListaEncadeada::removeValor(int val)
{
    int cont = 0;
    for (NoLista* aux = noInicio; aux != nullptr; aux = aux->getProx(), cont++)
    {
        if (aux->getInfo() == val || aux->getInfo2() == val)
        {
            /* base case */
            if (noInicio == NULL || aux == NULL)
                return;

            /* If node to be auxeted is head node */
            if (noInicio == aux)
                noInicio = aux->getProx();

            /* Change next only if node to be
            auxeted is NOT the last node */
            if (aux->getProx() != NULL)
                aux->getProx()->setAnt(aux->getAnt());

            /* Change getAnt() only if node to be
            auxeted is NOT the first node */
            if (aux->getAnt() != NULL)
                aux->getAnt()->setProx(aux->getProx());
            this->tamanho--;
            free(aux);
        }
    }
}

/**
 * função que verifica se a lista está vazia
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
 */
int ListaEncadeada::getTamanho()
{
    return this->tamanho;
}

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

bool ListaEncadeada::verificaElemento(int val)
{
    for (NoLista* a = this->noInicio; a != nullptr; a = a->getProx())
    {
        if (a->getInfo() == val)
        {
            return true;
        }
    }
    return false;
}
