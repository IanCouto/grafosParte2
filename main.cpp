#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Grafo.h"
#include <math.h>
#include <ctime>
#include <chrono>
using namespace std::chrono;
using namespace std;
int menu(){

    int selecao;
    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Mostrar Aps e seus clientes" << endl;
    cout << "[2] Mostrar Grafo de conflito" << endl;
    cout << "[3] Guloso" << endl;
    cout << "[4] Guloso Randomizado" << endl;
    cout << "[5] Guloso Randomizado Reativo" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void infoGulosoRandomizado(ofstream& arquivo_saida,Grafo* grafo, int execucoes,int interacoes,float alfa,float vetResultados[]){
    float melhorExecucao=99999,piorExecucao=0,media=0,execucaoAtual;
    float melhorTempo=9999999, piorTempo=0, mediaTempo=0;
    double tempoAtualSegundos;

    arquivo_saida << ">>>>>>>>>>ALFA "<<alfa<<"<<<<<<<<<<" << endl;
    arquivo_saida << "Execucão: Interferencia Total / Tempo de Execução(segundos)" << endl;
    for (int i = 0; i < execucoes; i++){

        auto start = high_resolution_clock::now();
        execucaoAtual=grafo->gulosoRandomizado(alfa,interacoes);
        auto stop = high_resolution_clock::now();

        //INFO DE INTERFERENCIA
        media += execucaoAtual;
        if(execucaoAtual<melhorExecucao) melhorExecucao = execucaoAtual;
        if(execucaoAtual>piorExecucao) piorExecucao = execucaoAtual;

        //INFO DE TEMPO DE EXECUÇÃO
        auto tempoAtual = duration_cast<microseconds>(stop - start);
        tempoAtualSegundos = tempoAtual.count()/1000000.0;
        mediaTempo += tempoAtualSegundos;
        if(tempoAtualSegundos<melhorTempo) melhorTempo = tempoAtualSegundos;
        if(tempoAtualSegundos>piorTempo) piorTempo = tempoAtualSegundos;


        arquivo_saida << i+1 << ": " << execucaoAtual <<" / "<< tempoAtualSegundos << endl;
    }
    arquivo_saida << endl;
    arquivo_saida << "INFO INTERFERENCIA" << endl;
    arquivo_saida << "Melhor: " << melhorExecucao << endl;
    arquivo_saida << "Pior: " << piorExecucao << endl;
    arquivo_saida << "Media: " << media/30 << endl << endl;

    arquivo_saida << "INFO TEMPO" << endl;
    arquivo_saida << "Melhor: " << melhorTempo << endl;
    arquivo_saida << "Pior: " << piorTempo << endl;
    arquivo_saida << "Media: " << mediaTempo/30 << endl << endl;
    arquivo_saida << endl;
    vetResultados[0]+=media;
    vetResultados[1]+=mediaTempo;
}


void selecionar(int selecao, Grafo* grafo, ofstream& arquivo_saida){

    switch (selecao) {
        case 1:{
            grafo->mostrarNos(arquivo_saida);
            break;
        }

        case 2:{
            grafo->mostrarGrafo(arquivo_saida);
            break;
        }

        case 3:{
            arquivo_saida << "-----------GULOSO------------" << endl;
            arquivo_saida << "Interferencia Total / Tempo de Execução(segundos)" <<endl;

            auto start = high_resolution_clock::now();
            float resultado = grafo->guloso();
            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(stop - start);
            double tempoEmSegundos = duration.count()*1000000.0;
            arquivo_saida << resultado<<" / "<< tempoEmSegundos  << endl <<endl;
            break;
        }

        case 4:{
            arquivo_saida << "-----------GULOSO RANDOMIZADO------------" << endl;
            float vetResultados[2] = {0,0};
            infoGulosoRandomizado(arquivo_saida,grafo,30,5,0.2,vetResultados);
            infoGulosoRandomizado(arquivo_saida,grafo,30,5,0.4,vetResultados);
            infoGulosoRandomizado(arquivo_saida,grafo,30,5,0.5,vetResultados);
            arquivo_saida << endl;
            arquivo_saida << "Media de interferencia todos alfas: " << vetResultados[0]/90 << endl;
            arquivo_saida << "Media do tempo de todos alfas: " << vetResultados[1]/30 <<endl;
            break;
        }

        case 5:{
            arquivo_saida << "-----------GULOSO RANDOMIZADO REATIVO------------" << endl;
            float melhorExecucao=99999,piorExecucao=0,media=0,execucaoAtual = 0, vetorAlfas[10] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
            float melhorTempo = 99999,piorTempo=0, mediaTempo=0;
            double tempoAtualSegundos;
            arquivo_saida << "Execucão: Interferencia Total / Tempo de Execução(segundos)" << endl;
            for (int i = 0; i < 100; i++){

                auto start = high_resolution_clock::now();
                execucaoAtual=grafo->gulosoRandomizadoReativo(100,vetorAlfas);
                auto stop = high_resolution_clock::now();

                media += execucaoAtual;
                if (execucaoAtual < melhorExecucao) melhorExecucao = execucaoAtual;
                if (execucaoAtual > piorExecucao) piorExecucao = execucaoAtual;

                //INFO DE TEMPO DE EXECUÇÃO

                auto tempoAtual = duration_cast<microseconds>(stop - start);
                tempoAtualSegundos = tempoAtual.count()/1000000.0;
                mediaTempo += tempoAtualSegundos;
                if(tempoAtualSegundos<melhorTempo) melhorTempo = tempoAtualSegundos;
                if(tempoAtualSegundos>piorTempo) piorTempo = tempoAtualSegundos;
                arquivo_saida << i+1 << ": " << execucaoAtual << " / "<< tempoAtualSegundos << endl;
           }

            arquivo_saida << "Melhor Execucao: " << melhorExecucao << endl;
            arquivo_saida << "Pior Execucao: " << piorExecucao << endl;
            arquivo_saida << "Media: " << media/30 << endl;
            arquivo_saida << endl;
            arquivo_saida << "INFO TEMPO" << endl;
            arquivo_saida << "Melhor: " << melhorTempo << endl;
            arquivo_saida << "Pior: " << piorTempo << endl;
            arquivo_saida << "Media: " << mediaTempo/30 << endl << endl;
            arquivo_saida << endl;
            break;
        }

    }
}


Grafo* leitura(ifstream& arquivo_entrada){

    int quantAps;
    int quantClientes;
    int x,y;

    arquivo_entrada >> quantAps >> quantClientes;
    Grafo* grafo = new Grafo(quantAps,quantClientes);

    //Inserindo aps
    for (int id = 0; id < quantAps; id++) {
        arquivo_entrada >> x >> y;
        grafo->inserirNo(id,x,y);
    }
    //Inserindo clientes
    for (int id = 0; id < quantClientes; id++) {
        arquivo_entrada >> x >> y;
        grafo->inserirCliente(id,x,y);
    }
    //Definindo potencia de cada ap
    grafo->definePotencia();

    //Criar grafo de conflito
    grafo->criarGrafoConflito();

    return grafo;

}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    //Verificação se todos os parâmetros do programa foram encontrados
    if (argc != 3) {

        cout << "ERRO: Esperado: ./<nome_programa> <arquivo_entrada> <arquivo_saida>" << endl;
        return 1;

    }

    //Abrindo arquivo de entrada
    ifstream arquivo_entrada;
    ofstream arquivo_saida;
    arquivo_entrada.open(argv[1], ios::in);
    arquivo_saida.open(argv[2], ios::out | ios::trunc);

	Grafo* grafo = new Grafo();

    if(arquivo_entrada.is_open() )
        grafo = leitura(arquivo_entrada);
    else{
        cout << "Nao foi possivel abrir o arquivo " << argv[1] << endl;
        return 0;
    }



    int selecao = menu();

    while (selecao!=0){
        selecionar(selecao,grafo,arquivo_saida);
        selecao = menu();
    }

    //Fechando arquivo de entrada
    arquivo_entrada.close();

    //Fechando arquivo de saída
    arquivo_saida.close();

    return 0;
}
