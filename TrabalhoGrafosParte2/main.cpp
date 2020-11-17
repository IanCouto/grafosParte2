#include <iostream>
#include <fstream>
#include <stdlib.h>

#include <chrono>
#include <time.h>
#include <math.h>
#include "Grafo.h"

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
    cout << "  [2]  | Mostrar Nos e seus graus" << endl;
    cout << "  [3]  | Mostrar Arestas" << endl;
    cout << "  [4]  | Guloso" << endl;
    cout << "  [5]  | Guloso randomizado" << endl;
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
        //Guloso
        case 4:
        {
            arquivo_saida << "-----------GULOSO------------" << endl;
            arquivo_saida << "Tamanho / Tempo de Execução(segundos)" << endl;

            //calcula o tempo gasto executar o algoritmo guloso randomizado
            auto start = high_resolution_clock::now();
            int resultado = grafo->guloso(arquivo_saida);
            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(stop - start);
            double tempoEmSegundos = duration.count() / 1000000.0;
            arquivo_saida << resultado << " / " << tempoEmSegundos << "s" << endl
                          << endl;
            break;
        }
        //Guloso randomizado
        case 5:
        {
            int melhorResultado = grafo->getOrdem(), piorResultado = 0, resultados[10];
            float alfas[5] = {0.1, 0.2, 0.3, 0.5, 0.7}, mediaResultado = 0, mediaIteracoesFeitas = 0;
            double mediaTempo = 0;
            arquivo_saida << "-----------GULOSO RANDOMIZADO------------" << endl;
            arquivo_saida << "Execução i: Tamanho / Tempo de Execução(segundos)" << endl;
            //executa o algoritmo guloso randomizado 10 vezes para cada alfa
            for (int j = 0; j < 5; j++, mediaResultado = 0, mediaTempo = 0, mediaIteracoesFeitas = 0)
            {
                arquivo_saida << endl
                              << "=================================================================" << endl
                              << " Alfa: " << alfas[j] << endl
                              << "=================================================================" << endl;

                for (int i = 0; i < 10; i++)
                {
                    arquivo_saida << "Execucao " << i << ": ";
                    //calcula as métricas exigidas para cada execução
                    auto start = high_resolution_clock::now();
                    int *retorno = grafo->gulosoRandomizado(alfas[j]);
                    resultados[i] = retorno[0];
                    mediaIteracoesFeitas += retorno[1];

                    if (resultados[i] < melhorResultado)
                        melhorResultado = resultados[i];
                    if (resultados[i] > piorResultado)
                        piorResultado = resultados[i];

                    auto stop = high_resolution_clock::now();

                    auto duration = duration_cast<microseconds>(stop - start);
                    double tempoEmSegundos = duration.count() / 1000000.0;
                    mediaTempo += tempoEmSegundos;
                    mediaResultado += resultados[i];
                    arquivo_saida << resultados[i] << " / " << tempoEmSegundos << "s"
                                  << endl;
                }
                double desvioPadrao = 0;
                for (int i = 0; i < 10; i++)
                    desvioPadrao += pow(resultados[i] - mediaResultado/10, 2);

                desvioPadrao /= 10;
                desvioPadrao = sqrt(desvioPadrao);
                //salva as métricas em um arquivo de saida
                arquivo_saida << endl << "Melhor resultado: " << melhorResultado << endl;
                arquivo_saida << "Pior resultado: " << piorResultado << endl;
                arquivo_saida << "Desvio padrao dos resultados: " << desvioPadrao << endl;
                arquivo_saida << "Media dos resultados: " << mediaResultado / 10 << endl;
                arquivo_saida << "Media dos tempos: " << mediaTempo / 10 <<"s"<< endl;
                arquivo_saida << "Media da iteracao em que a solocao foi obtida: " << mediaIteracoesFeitas / 10 << endl;
            }
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
    string aux = "";
    //ignora a primeira linha
    arquivo_entrada >> aux;
    arquivo_entrada >> ordem;

    Grafo *grafo = new Grafo(ordem);

    //Leitura do arquivo
    arquivo_entrada >> aux;
    //ignora informações desnecessárias
    while (aux != "*****************CONNECTIONS****************")
    {
        arquivo_entrada >> aux;
    }

    string delimiter = " ";

    size_t pos = 0;
    string token;
    int leitura = -1;
    arquivo_entrada >> leitura;
    for (int i = 0; i < ordem; i++)
    {
        for (int j = 0; j<ordem; j++, arquivo_entrada>> leitura)
        {
            if (leitura == 1 && i != j)
            {
                grafo->inserirAresta(i, j);
            }
        }
    }

    if (grafo->isConexo()) {
        cout << "Grafo eh conexo!" << endl;
    }
    else {
        cout << "Atencao o grafo nao e conexo!" << endl;
        exit(1);
    }
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

    //verifica se o arquivo de entrada foi aberto
    if (arquivo_entrada.is_open())
        grafo = leitura(arquivo_entrada);
    else
        cout << "Nao foi possivel abrir o arquivo " << argv[1] << endl;

    cout << "Carregamento Concluido!" << endl;

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