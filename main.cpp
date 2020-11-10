#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <time.h>
#include "header/Grafo.h"

using namespace std::chrono;
using namespace std;
/**
 * Trabalho de grafos do GRUPO 9
 * 
 * @author ANTÔNIO HENRIQUE PASSAMAI PENIZOLLO
 * @author IAN COUTO DE PAULA
 * @author LEONARDO AZALIM DE OLIVEIRA
 * @author MARCELO GONÇALVES DE SOUZA COSTA
 * @author RAÍH CÉSAR SILVA DE LIMA
 */

/**
 * Função utilizada para imprimir o menu e computar a funcionalidade escolhida pelo usuário
 * @return int escolha do usuário
 */
int menu()
{

    int selecao;
    cout << "----------------------------------" << endl;
    cout << "   Subconjunto dominante minimo" << endl;
    cout << "----------------------------------" << endl;
    cout << "               MENU" << endl;
    cout << "----------------------------------" << endl;
    cout << " Opcao | Descricao" << endl;
    cout << "----------------------------------" << endl;
    cout << "  [1]  | Mostrar Grafo" << endl;
    cout << "  [2]  | Mostrar Nos e suas informacoes" << endl;
    cout << "  [3]  | Mostrar Arestas e suas informacoes" << endl;
    cout << "  [4]  | Caminhamento em largura" << endl;
    cout << "  [5]  | Caminhamento em profundidade" << endl;
    cout << "  [6]  | Dijkstra: caminho minimo" << endl;
    cout << "  [7]  | Floyd: caminho minimo" << endl;
    cout << "  [8]  | Arvore Geradora Minima - Prim" << endl;
    cout << "  [9]  | Arvore Geradora Minima - Kruskal" << endl;
    cout << "  [10] | Guloso" << endl;
    cout << "  [11] | Guloso randomizado" << endl;
    cout << "  [0]  | Sair" << endl;
    cout << "----------------------------------" << endl;
    cin >> selecao;

    return selecao;
}
/**
 * função utilizada para selecionar a funcionalidade escolhida pelo usuário
 * @param selecao funcionalidade escolhida pelo usuário
 * @param grafo grafo
 * @param arquivo_saida arquivo de saída de dados
 */
void selecionar(int selecao, Grafo *grafo, ofstream &arquivo_saida)
{

    switch (selecao)
    {

        //mostrar grafo
    case 1:
    {
        grafo->mostrarGrafo(arquivo_saida);
        break;
    }
        //mostrar nos
    case 2:
    {
        grafo->mostrarNos(arquivo_saida);
        break;
    }
        //mostrar arestas
    case 3:
    {
        grafo->mostrarArestas(arquivo_saida);
        break;
    }
        //Caminhamento em largura
    case 4:
    {
        int idOrigem;
        cout << "Digite o id do no inicial: ";
        cin >> idOrigem;
        if (grafo->isComecaZero())
        {
            if (!(idOrigem < 0 || idOrigem >= grafo->getOrdem()))
            {
                grafo->caminhamentoLargura(idOrigem, arquivo_saida);
            }
            else
                cout << endl
                     << "Id inexistente!" << endl;
        }
        else
        {
            if (!(idOrigem <= 0 || idOrigem > grafo->getOrdem()))
            {
                if (idOrigem == grafo->getOrdem())
                {
                    idOrigem = 0;
                }
                grafo->caminhamentoLargura(idOrigem, arquivo_saida);
            }
            else
                cout << endl
                     << "Id inexistente!" << endl;
        }
        break;
    }
        //Caminhamento em profundidade
    case 5:
    {
        int idOrigem;
        cout << "Digite o id do no inicial: ";
        cin >> idOrigem;

        if (grafo->isComecaZero())
        {
            if (!(idOrigem < 0 || idOrigem >= grafo->getOrdem()))
            {
                grafo->caminhamentoProfundidade(idOrigem, arquivo_saida);
            }
            else
                cout << endl
                     << "Id inexistente!" << endl;
        }
        else
        {
            if (!(idOrigem <= 0 || idOrigem > grafo->getOrdem()))
            {
                if (idOrigem == grafo->getOrdem())
                {
                    idOrigem = 0;
                }
                grafo->caminhamentoProfundidade(idOrigem, arquivo_saida);
            }
            else
                cout << endl
                     << "Id inexistente!" << endl;
        }
        break;
    }
        //Dijkstra: caminho minimo
    case 6:
    {
        int idOrigem, idDestino;
        cout << "Digite o id do no inicial: ";
        cin >> idOrigem;
        cout << "Digite o id do no de destino: ";
        cin >> idDestino;
        if (grafo->isComecaZero())
        {
            if (!(idOrigem < 0 || idOrigem >= grafo->getOrdem()) || !(idDestino < 0 || idDestino >= grafo->getOrdem()))
            {
                grafo->dijkstra(idOrigem, idDestino, arquivo_saida);
            }
            else
            {
                cout << endl
                     << "Id inexistente!" << endl;
            }
        }
        else
        {
            if (!(idOrigem <= 0 || idOrigem > grafo->getOrdem()) || !(idDestino <= 0 || idDestino > grafo->getOrdem()))
            {
                if (idOrigem == grafo->getOrdem())
                {
                    idOrigem = 0;
                }
                if (idDestino == grafo->getOrdem())
                {
                    idDestino = 0;
                }
                grafo->dijkstra(idOrigem, idDestino, arquivo_saida);
            }
            else
            {
                cout << endl
                     << "Id inexistente!" << endl;
            }
        }
        break;
    }
        //Floyd: caminho minimo
    case 7:
    {
        int idOrigem, idDestino;
        cout << "Digite o id do no inicial: ";
        cin >> idOrigem;
        cout << "Digite o id do no de destino: ";
        cin >> idDestino;
        if (grafo->isComecaZero())
        {
            if (!(idOrigem < 0 || idOrigem >= grafo->getOrdem()) || !(idDestino < 0 || idDestino >= grafo->getOrdem()))
            {
                grafo->floyd(idOrigem, idDestino, arquivo_saida);
            }
            else
                cout << endl
                     << "Id inexistente!" << endl;
        }
        else
        {
            if (!(idOrigem <= 0 || idOrigem > grafo->getOrdem()) || !(idDestino <= 0 || idDestino > grafo->getOrdem()))
            {
                if (idOrigem == grafo->getOrdem())
                {
                    idOrigem = 0;
                }
                if (idDestino == grafo->getOrdem())
                {
                    idDestino = 0;
                }
                grafo->floyd(idOrigem, idDestino, arquivo_saida);
            }
            else
                cout << endl
                     << "Id inexistente!" << endl;
        }

        break;
    }
        //Arvore Geradora Minima - Prim
    case 8:
    {
        grafo->AGMPrim(arquivo_saida);
        break;
    }
        //Arvore Geradora Minima - Kruskal
    case 9:
    {
        grafo->AGMKruskal(arquivo_saida);
        break;
    }
    case 10:
    {
        arquivo_saida << "-----------GULOSO------------" << endl;
        arquivo_saida << "Tamanho / Tempo de Execução(segundos)" << endl;

        auto start = high_resolution_clock::now();
        int resultado = grafo->guloso(arquivo_saida);

        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        double tempoEmSegundos = duration.count() / 1000000.0;
        arquivo_saida << resultado << " / " << tempoEmSegundos << endl
                      << endl;
        break;
    }
    case 11:
    {

        int melhorResultado = grafo->getOrdem(), piorResultado = 0;
        float alfas[5] = {0.1, 0.2, 0.3, 0.5, 0.7};
        for (int j = 0; j < 1; j++)
        {
            for (int i = 0; i < 10; i++)
            {
                arquivo_saida << endl
                     << "=================================================================" << endl
                     << "Execucao: " << i + 1 << " Alfa: " << alfas[j]<<endl
                     << "=================================================================" << endl;

                arquivo_saida << "-----------GULOSO RANDOMIZADO------------" << endl;
                arquivo_saida << "Tamanho / Tempo de Execução(segundos)" << endl;

                auto start = high_resolution_clock::now();
                int resultado = grafo->gulosoRandomizado(alfas[j]);

                if (resultado < melhorResultado)
                    melhorResultado = resultado;
                if (resultado > piorResultado)
                    piorResultado = resultado;

                auto stop = high_resolution_clock::now();

                auto duration = duration_cast<microseconds>(stop - start);
                double tempoEmSegundos = duration.count() / 1000000.0;
                arquivo_saida << resultado << " / " << tempoEmSegundos << endl
                              << endl;
            }
        }
        arquivo_saida << "Melhor resultado: " << melhorResultado << endl;
        arquivo_saida << "Pior resultado: " << piorResultado << endl;
        break;
    }
    //opção inválida
    default:
    {
        cout << "Opcao invalida" << endl;
        break;
    }
    }
}

/**
 * função para ler os dados do arquivo de entrada e armazenados na estrutura de um grafo
 * @param arquivo_entrada arquivo de entrada de dados
 * @return Grafo*
 */
Grafo *leitura(ifstream &arquivo_entrada)
{
    int ordem;
    int idNoOrigem;
    int idNoDestino;

    arquivo_entrada >> ordem;

    Grafo *grafo = new Grafo(ordem);

    //Leitura do arquivo
    float pesoAresta;

    while (arquivo_entrada >> idNoOrigem >> idNoDestino >> pesoAresta)
        grafo->inserirAresta(idNoOrigem, idNoDestino, pesoAresta);

    return grafo;
}

/**
 * função principal, que gerencia todas as funcionalidades do código
 * @param argc tamanho do vetor argv
 * @param argv parâmetros a serem passados pelo terminal ao executar o programa.
 * argv[0]: nome do executável;
 * argv[1]: nome do arquivo de entrada;
 * argv[2]: nome do arquivo de saida.
 */
int main(int argc, char *argv[])
{

    srand(time(NULL));
    cout << "Carregando... " << endl;

    //Verificação se todos os parâmetros do programa foram encontrados
    if (argc != 3)
    {
        cout << "ERRO: Esperado: ./<nome_programa> <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;
    }

    //Abrindo arquivo de entrada
    ifstream arquivo_entrada;
    ofstream arquivo_saida;
    arquivo_entrada.open(argv[1], ios::in);
    arquivo_saida.open(argv[2], ios::out | ios::trunc);

    Grafo *grafo = new Grafo();

    if (arquivo_entrada.is_open())
        grafo = leitura(arquivo_entrada);
    else
        cout << "Nao foi possivel abrir o arquivo " << argv[1] << endl;

    cout << "Carregamento Concluido!" << endl;

    grafo->gerarResultadosGrafo(arquivo_saida);

    arquivo_saida << endl
                  << "------------------------------" << endl
                  << "        FUNCIONALIDADES" << endl
                  << "------------------------------" << endl;
    for (int selecao = menu(); selecao != 0; selecao = menu())
    {
        selecionar(selecao, grafo, arquivo_saida);
    }

    //Fechando arquivo de entrada
    arquivo_entrada.close();

    //Fechando arquivo de saída
    arquivo_saida.close();

    delete grafo;
    return 0;
}