#include <iostream>
#include "header/ListaAdjacenteEncadeada.h"

using namespace std;

ListaAdjacenteEncadeada::ListaAdjacenteEncadeada()
{
    this->noInicio = nullptr; // ponteiro para No do comeco
    this->noFim = nullptr;    // ponteiro para No do fim
    this->tamanho = 0;
}

ListaAdjacenteEncadeada::~ListaAdjacenteEncadeada()
{
    NoListaAdj *p = noInicio;
    while (p != NULL)
    {
        NoListaAdj *t = p->getProx();
        delete p;
        p = t;
    }
}

int ListaAdjacenteEncadeada::getTamanho()
{
    return this->tamanho;
}

void ListaAdjacenteEncadeada::adiciona(int no, int noDestino)
{
    NoListaAdj *p = new NoListaAdj(no, noDestino);
    p->setAnt(noFim);
    if (noInicio == nullptr)
    {
        noInicio = p;
        noFim = p;
        this->tamanho++;
    }
    else
    {
        if (noFim->getId() == no)
        {
            noFim->adicionaVizinho(noDestino);
        }
        else
        {
            noFim->setProx(p);
            noFim = p;
            this->tamanho++;
        }
    }
}
void ListaAdjacenteEncadeada::deletaNo(int no)
{
    if (this->getTamanho() > 0)
    {
        NoListaAdj *p = new NoListaAdj();
        if (tamanho == 1 && noInicio->getId() == no)
        {
            noInicio = nullptr;
            noFim = nullptr;
            this->tamanho--;
        }
        else if (noInicio->getId() == no)
        {
            p = noInicio;
            noInicio = noInicio->getProx();
            noInicio->setAnt(nullptr);
            /*
            p->setProx(nullptr);
            this->tamanho--;*/
        }
        else if (noFim->getId() == no)
        {
            p = noFim;
            noFim = noFim->getAnt();
            noFim->setProx(nullptr);
            /*
            p->setAnt(nullptr);
            this->tamanho--;*/
        }
        else
        {
            for (NoListaAdj *aux = noInicio; aux != nullptr; aux = aux->getProx())
            {
                if (aux->getId() == no)
                {
                    p = aux;
                    break;
                }
            }
        }
        if (tamanho > 0)
        {
            if (p != nullptr)
            {
                if (p->getAnt() != nullptr)
                    p->getAnt()->setProx(p->getProx());
                if (p->getProx() != nullptr)
                    p->getProx()->setAnt(p->getAnt());
                p->setAnt(nullptr);
                p->setProx(nullptr);
                this->tamanho--;
                for (NoListaAdj *aux = noInicio; aux != nullptr; aux = aux->getProx())
                {
                    aux->deletaVizinho(no);
                }
            }
        }
        delete p;
    }
}

NoListaAdj *ListaAdjacenteEncadeada::getNo(int no)
{
    for (NoListaAdj *aux = noInicio; aux != nullptr; aux = aux->getProx())
    {
        if (aux->getId() == no)
        {
            return aux;
        }
    }
    return nullptr;
}
NoListaAdj *ListaAdjacenteEncadeada::getPos(int index)
{
    int cont = 0;
    for (NoListaAdj *aux = noInicio; aux != nullptr; aux = aux->getProx())
    {
        if (cont == index)
        {
            return aux;
        }
        cont++;
    }
    return nullptr;
}

void ListaAdjacenteEncadeada::imprimeLista(bool opcao)
{

    if (opcao)
    {
        cout << "imprimindo lista" << endl;
        for (NoListaAdj *aux = noInicio; aux != nullptr; aux = aux->getProx())
        {
            cout << aux->getId() << "  | ";
            for (No *aux1 = aux->getVizinhos(); aux1 != nullptr; aux1 = aux1->getProximoNo())
            {
                cout << aux1->getNoDestino() << ", ";
            }
            cout << endl;
        }
    }
    else
    {
        for (NoListaAdj *aux = noInicio; aux != nullptr; aux = aux->getProx())
        {
            cout << aux->getGrau() << endl;
        }
        cout << "=====" << endl;
    }
}

void swap(NoListaAdj *a, NoListaAdj *b)
{
    NoListaAdj *t = a;
    a = b;
    b = t;
}

/* This function takes last element as pivot, places  
the pivot element at its correct position in sorted  
array, and places all smaller (smaller than pivot)  
to left of pivot and all greater elements to right  
of pivot */
int partition(ListaAdjacenteEncadeada *arr, int low, int high)
{
    int pivot = arr->getPos(high)->getGrau(); // pivot
    int i = (low - 1);                        // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr->getPos(j)->getGrau() < pivot)
        {
            i++; // increment index of smaller element
            swap(arr->getPos(j), arr->getPos(j));
        }
    }
    swap(arr->getPos(i + 1), arr->getPos(high));
    return (i + 1);
}

/* The main function that implements QuickSort  
arr[] --> Array to be sorted,  
low --> Starting index,  
high --> Ending index */
void quickSort(ListaAdjacenteEncadeada *arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void ListaAdjacenteEncadeada::ordena(float alfa)
{
    quickSort(this, 0, this->getTamanho() - 1);
}
