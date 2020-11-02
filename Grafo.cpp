#include <iostream>
#include <fstream>
#include <ctime>
#include "Grafo.h"
#include "No.h"
#include <math.h>

using namespace std;

//Construtor
Grafo::Grafo(int ordem, int quantClientes){
    this->ordem = ordem;
    this->primeiro_no = this->ultimo_no = nullptr;
    this->quant_aresta = 0;
    this->quantClientes = quantClientes;
    this->interferenciaTotal = 0;
    tabelaInterferencia[0][0] = 1;
    tabelaInterferencia[0][1] = 0.77;
    tabelaInterferencia[0][2] = 0.54;
    tabelaInterferencia[0][3] = 0.31;
    tabelaInterferencia[0][4] = 0.09;
    tabelaInterferencia[0][5] = 0;
    tabelaInterferencia[0][6] = 0;
    tabelaInterferencia[0][7] = 0;
    tabelaInterferencia[0][8] = 0;
    tabelaInterferencia[0][9] = 0;
    tabelaInterferencia[0][10] = 0;

    tabelaInterferencia[1][0] = 0.77;
    tabelaInterferencia[1][1] = 1;
    tabelaInterferencia[1][2] = 0.77;
    tabelaInterferencia[1][3] = 0.54;
    tabelaInterferencia[1][4] = 0.31;
    tabelaInterferencia[1][5] = 0.09;
    tabelaInterferencia[1][6] = 0;
    tabelaInterferencia[1][7] = 0;
    tabelaInterferencia[1][8] = 0;
    tabelaInterferencia[1][9] = 0;
    tabelaInterferencia[1][10] = 0;

    tabelaInterferencia[2][0] = 0.54;
    tabelaInterferencia[2][1] = 0.77;
    tabelaInterferencia[2][2] = 1;
    tabelaInterferencia[2][3] = 0.77;
    tabelaInterferencia[2][4] = 0.54;
    tabelaInterferencia[2][5] = 0.31;
    tabelaInterferencia[2][6] = 0.09;
    tabelaInterferencia[2][7] = 0;
    tabelaInterferencia[2][8] = 0;
    tabelaInterferencia[2][9] = 0;
    tabelaInterferencia[2][10] = 0;

    tabelaInterferencia[3][0] = 0.31;
    tabelaInterferencia[3][1] = 0.54;
    tabelaInterferencia[3][2] = 0.77;
    tabelaInterferencia[3][3] = 1;
    tabelaInterferencia[3][4] = 0.77;
    tabelaInterferencia[3][5] = 0.54;
    tabelaInterferencia[3][6] = 0.31;
    tabelaInterferencia[3][7] = 0.09;
    tabelaInterferencia[3][8] = 0;
    tabelaInterferencia[3][9] = 0;
    tabelaInterferencia[3][10] = 0;

    tabelaInterferencia[4][0] = 0.09;
    tabelaInterferencia[4][1] = 0.31;
    tabelaInterferencia[4][2] = 0.54;
    tabelaInterferencia[4][3] = 0.77;
    tabelaInterferencia[4][4] = 1;
    tabelaInterferencia[4][5] = 0.77;
    tabelaInterferencia[4][6] = 0.54;
    tabelaInterferencia[4][7] = 0.31;
    tabelaInterferencia[4][8] = 0.09;
    tabelaInterferencia[4][9] = 0;
    tabelaInterferencia[4][10] = 0;

    tabelaInterferencia[5][0] = 0;
    tabelaInterferencia[5][1] = 0.09;
    tabelaInterferencia[5][2] = 0.31;
    tabelaInterferencia[5][3] = 0.54;
    tabelaInterferencia[5][4] = 0.77;
    tabelaInterferencia[5][5] = 1;
    tabelaInterferencia[5][6] = 0.77;
    tabelaInterferencia[5][7] = 0.54;
    tabelaInterferencia[5][8] = 0.31;
    tabelaInterferencia[5][9] = 0.09;
    tabelaInterferencia[5][10] = 0;

    tabelaInterferencia[6][0] = 0;
    tabelaInterferencia[6][1] = 0;
    tabelaInterferencia[6][2] = 0.09;
    tabelaInterferencia[6][3] = 0.31;
    tabelaInterferencia[6][4] = 0.54;
    tabelaInterferencia[6][5] = 0.77;
    tabelaInterferencia[6][6] = 1;
    tabelaInterferencia[6][7] = 0.77;
    tabelaInterferencia[6][8] = 0.54;
    tabelaInterferencia[6][9] = 0.31;
    tabelaInterferencia[6][10] = 0.09;

    tabelaInterferencia[7][0] = 0;
    tabelaInterferencia[7][1] = 0;
    tabelaInterferencia[7][2] = 0;
    tabelaInterferencia[7][3] = 0.09;
    tabelaInterferencia[7][4] = 0.31;
    tabelaInterferencia[7][5] = 0.54;
    tabelaInterferencia[7][6] = 0.77;
    tabelaInterferencia[7][7] = 1;
    tabelaInterferencia[7][8] = 0.77;
    tabelaInterferencia[7][9] = 0.54;
    tabelaInterferencia[7][10] = 0.31;

    tabelaInterferencia[8][0] = 0;
    tabelaInterferencia[8][1] = 0;
    tabelaInterferencia[8][2] = 0;
    tabelaInterferencia[8][3] = 0;
    tabelaInterferencia[8][4] = 0.09;
    tabelaInterferencia[8][5] = 0.31;
    tabelaInterferencia[8][6] = 0.54;
    tabelaInterferencia[8][7] = 0.77;
    tabelaInterferencia[8][8] = 1;
    tabelaInterferencia[8][9] = 0.77;
    tabelaInterferencia[8][10] = 0.54;

    tabelaInterferencia[9][0] = 0;
    tabelaInterferencia[9][1] = 0;
    tabelaInterferencia[9][2] = 0;
    tabelaInterferencia[9][3] = 0;
    tabelaInterferencia[9][4] = 0;
    tabelaInterferencia[9][5] = 0.09;
    tabelaInterferencia[9][6] = 0.31;
    tabelaInterferencia[9][7] = 0.54;
    tabelaInterferencia[9][8] = 0.77;
    tabelaInterferencia[9][9] = 1;
    tabelaInterferencia[9][10] = 0.77;

    tabelaInterferencia[10][0] = 0;
    tabelaInterferencia[10][1] = 0;
    tabelaInterferencia[10][2] = 0;
    tabelaInterferencia[10][3] = 0;
    tabelaInterferencia[10][4] = 0;
    tabelaInterferencia[10][5] = 0;
    tabelaInterferencia[10][6] = 1;
    tabelaInterferencia[10][7] = 0.77;
    tabelaInterferencia[10][8] = 0.54;
    tabelaInterferencia[10][9] = 0.31;
    tabelaInterferencia[10][10] = 0.09;

}

Grafo::Grafo(){

}

// Destrutor
Grafo::~Grafo()
{
    No *proximo_no = this->primeiro_no;

    while (proximo_no != nullptr)
    {
        proximo_no->removerTodasArestas();
        No *aux_no = proximo_no->getProximoNo();
        delete proximo_no;
        proximo_no = aux_no;
    }
}

//Getters
int Grafo::getOrdem(){return this->ordem;}
int Grafo::getQuantAresta(){return this->quant_aresta;}
No *Grafo::getPrimeiroNo(){return this->primeiro_no;}
No *Grafo::getUltimoNo(){return this->ultimo_no;}

float Grafo::interferencia(int canal1, int canal2) {
    return this->tabelaInterferencia[canal1-1][canal2-1];
}

//Retorna um No com o determinado id, caso negativo retorna null
No *Grafo::getNo(int id){
    if(this->primeiro_no != nullptr){
        for(No* aux = primeiro_no; aux != nullptr; aux = aux->getProximoNo())
            if(aux->getId() == id)
                return aux;
    }

    return nullptr;
}

//Outros metodos

void Grafo::inserirNo(int id, int x, int y){
    //Verifica se existe pelo menos um No, caso negativo, o primeiro No sera setado
    if(this->primeiro_no != nullptr){
        No* no = new No(id,x,y);
        this->ultimo_no -> setProximoNo(no);
        this->ultimo_no = no;
    }
    else{
        this->primeiro_no = new No(id,x,y);
        this->ultimo_no = this->primeiro_no;
    }
}

//Add o cliente no ap que possui a menor distancia até ele
void Grafo::inserirCliente(int id, int x, int y){
    int idMenor=0,x1=x,y1=y,x2,y2;
    float menorDistancia;

    No* ap = primeiro_no;
    x2 = ap->getX();
    y2 = ap->getY();

    menorDistancia = distanciaEuclidiana(x1,y1,x2,y2);

    for(ap = ap->getProximoNo(); ap != nullptr; ap = ap->getProximoNo()) {
        x2 = ap->getX();
        y2 = ap->getY();
        if (distanciaEuclidiana(x1, y1, x2, y2) < menorDistancia) {
            menorDistancia = distanciaEuclidiana(x1, y1, x2, y2);
            idMenor = ap->getId();
        }
    }
    getNo(idMenor)->inserirCliente(id, x, y, menorDistancia);
}

float Grafo::distanciaEuclidiana(int x1,int y1,int x2, int y2){
    return sqrt( (float) (pow(x1-x2,2) + pow(y1-y2,2)) );
}

//Verifica qual cliente possui a maior distancia para cada ap essa distancia ira definir a potencia do ap
void Grafo::definePotencia(){
    for(No* ap = primeiro_no; ap != nullptr; ap = ap->getProximoNo())
        ap->atribuirPotenciaTransmissao();
}



void Grafo::criarGrafoConflito(){
    float distancia, somaRaio;

    for(No* ap = primeiro_no; ap != nullptr; ap = ap->getProximoNo()) {

        for(No* ap2 = ap->getProximoNo(); ap2 != nullptr; ap2 = ap2->getProximoNo()) {
            distancia = distanciaEuclidiana(ap->getX(),ap->getY(),ap2->getX(),ap2->getY());
            somaRaio = ap->getPotencia()+ap2->getPotencia();

            if(somaRaio >= distancia){

                if(possuiClientesNaInterseccao(ap,ap2)){
                    ap->inserirAresta(ap2->getId());
                    ap2->inserirAresta(ap->getId());
                    this->quant_aresta++;
                }

            }

        }

    }

}
//Retorna verdadeiro caso possua clientes na interseccao do raio de dois aps
bool Grafo::possuiClientesNaInterseccao(No *ap,No *ap2){

    //Pecorrendo todos os clientes do ap
    for (No* cliente = ap->getPrimeiroCliente(); cliente != nullptr; cliente = cliente->getProximoNo()) {
        if(estaNaInterseccao(cliente,ap,ap2)) return true;
    }

    //Pecorrendo todos os clientes do ap2
    for (No* cliente = ap2->getPrimeiroCliente(); cliente != nullptr; cliente = cliente->getProximoNo()) {
        if(estaNaInterseccao(cliente,ap,ap2)) return true;
    }

    return false;
}




void Grafo::mostrarGrafo(ofstream& arquivo_saida) {
    arquivo_saida<<"-----------GRAFO------------"<<endl;
    for(No* no = primeiro_no; no != nullptr; no = no->getProximoNo()){
        arquivo_saida << no->getId() << ".";
        for(Aresta* aresta = no->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProximaAresta()){
            No* aux = getNo(aresta->getId());
            if(aresta == no->getPrimeiraAresta() )
                arquivo_saida << aux->getId();
            else
                arquivo_saida << "," << aux->getId();
        }
        arquivo_saida<<" Canal: "<<no->getCanal();
        arquivo_saida<<" Interferencia: "<<no->getInterferencia()<<endl;
    }
    arquivo_saida<<" Interferencia Total do Grafo: "<<this->interferenciaTotal<<endl;
    arquivo_saida<<endl<<endl;
}

void Grafo::mostrarNos(ofstream& arquivo_saida) {
    for(No* no = primeiro_no; no != nullptr; no = no->getProximoNo()){
        arquivo_saida<<"-----------AP------------"<<endl;
        arquivo_saida<<"ID. X - Y / Potencia de Transmissao"<<endl;
        arquivo_saida << no->getId() << ". ";
        arquivo_saida << no->getX() << " - ";
        arquivo_saida << no->getY() << " / ";
        arquivo_saida << no->getPotencia();
        arquivo_saida << endl;
        no->mostrarClientes(arquivo_saida);
    }
    arquivo_saida<<endl<<endl;
}

//Define todos os aps possiveis com os canais 1,6 e 11 ao final
//retorna um vetor de ids dos aps sem um canal definido
int* Grafo::baseCanais1611(){
    //zerar todas os canais do grafo
    for (No *ap = primeiro_no; ap != nullptr; ap = ap->getProximoNo())
        ap->setCanal(0);

    int vetorDeCanais[ordem],cont=0,contId=0;
    int* vetorIdsSemCanais = new int[ordem];
    bool canal1,canal6,canal11;

    for(No* ap = primeiro_no; ap != nullptr; ap = ap->getProximoNo()) {
        canal1=false;canal6=false,canal11=false;
        cont=0;
        for(Aresta* aresta = ap->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProximaAresta()) {
            No *ap2 = getNo(aresta->getId());
            vetorDeCanais[cont] = ap2->getCanal();
            cont++;
        }

        for (int i = 0; i < cont; i++) {
            if(vetorDeCanais[i]==1){
                canal1=true;
                break;
            }
        }

        for (int i = 0; i < cont; i++) {
            if(vetorDeCanais[i]==6){
                canal6=true;
                break;
            }
        }

        for (int i = 0; i < cont; i++) {
            if(vetorDeCanais[i]==11){
                canal11=true;
                break;
            }
        }
        if(!canal1) ap->setCanal(1);
        else if(!canal6) ap->setCanal(6);
        else if(!canal11) ap->setCanal(11);
        else{
            vetorIdsSemCanais[contId] = ap->getId();
            contId++;
        }
    }
    vetorIdsSemCanais[contId]=-1;
    return vetorIdsSemCanais;
}

//Define o valor de interferencia para cada ap  do grafo
void Grafo::defineInterferencias(int idsNosInteferencia[]) {
    No* ap;
    No* ap2;
    float somaTotalInteferencias = 0;

    //zerar todas as interferencias do grafo
    for (No *ap = primeiro_no; ap != nullptr; ap = ap->getProximoNo())
        ap->setInterferencia(0);


    for (int i = 0; ;i++) {
        if (idsNosInteferencia[i] == -1) break;
        ap = getNo(idsNosInteferencia[i]);

        //Definindo interferencia dos Aps com canais diferentes de 1,6,11
        for (No *cliente = ap->getPrimeiroCliente(); cliente != nullptr; cliente = cliente->getProximoNo()) {

            for(Aresta* aresta = ap->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProximaAresta()) {
                ap2 = getNo(aresta->getId());

                //verifica se o canal do ap tem interferencia com o canal do ap2
                if(interferencia(ap->getCanal(),ap2->getCanal())!=0){

                    //verifica se o cliente esta na interseccao entre o ap e ap2
                    if(estaNaInterseccao(cliente,ap,ap2)){
                        ap->setInterferencia( ap->getInterferencia() + interferencia(ap->getCanal(),ap2->getCanal()) );
                        somaTotalInteferencias += interferencia(ap->getCanal(),ap2->getCanal());
                    }


                }
            }
        }

        //Definindo interferencia para cada Ap adjacentes
        Aresta *aresta = ap->getPrimeiraAresta();
        No *ap2 = getNo(aresta->getId());
        while(aresta != nullptr){

            for (No *cliente = ap2->getPrimeiroCliente(); cliente != nullptr; cliente = cliente->getProximoNo()) {

                //verifica se o canal do ap tem interferencia com o canal do ap2
                if(interferencia(ap->getCanal(),ap2->getCanal())!=0) {
                    //verifica se o cliente esta na na interseccao entre o ap e ap2
                    if (estaNaInterseccao(cliente, ap, ap2)) {
                        ap2->setInterferencia(ap2->getInterferencia() + interferencia(ap->getCanal(), ap2->getCanal()));
                        somaTotalInteferencias += interferencia(ap->getCanal(), ap2->getCanal());
                    }
                }

            }
            aresta = aresta->getProximaAresta();
            if(aresta != nullptr) ap2 = getNo(aresta->getId());
        }
    }

    interferenciaTotal=(somaTotalInteferencias/quantClientes);
}

//Retorna verdadeiro caso o cliente esteja na interseccao do raio de dois aps
bool Grafo::estaNaInterseccao(No *cliente, No *ap, No*ap2){
    bool contemAP1=false,contemAP2=false;
    if(distanciaEuclidiana(cliente->getX(),cliente->getY(),ap->getX(),ap->getY()) <= ap->getPotencia()) contemAP1=true;
    if(distanciaEuclidiana(cliente->getX(),cliente->getY(),ap2->getX(),ap2->getY()) <= ap2->getPotencia()) contemAP2=true;

    if(contemAP1 && contemAP2) return true;
    else return false;

}

float Grafo::guloso() {
    int *vetorIdsSemCanais = baseCanais1611();
    int vetorCanais[8]={3,8,4,9,2,5,7,10};
    bool atribui;

    for (int i = 0; ;i++) {
        if(vetorIdsSemCanais[i]==-1) break;
        No* ap = getNo(vetorIdsSemCanais[i]);
        for (int canal = 0; canal < 8; canal++) {
            atribui=true;
            for(Aresta* aresta = ap->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProximaAresta()) {
                No *ap2 = getNo(aresta->getId());
                if(ap2->getCanal()==vetorCanais[canal]) {
                    atribui=false;
                    break;
                }
            }
            if(atribui){
                ap->setCanal(vetorCanais[canal]);
                break;
            }
        }
    }

    defineInterferencias(vetorIdsSemCanais);


   return interferenciaTotal;

}

int* Grafo::randomizaVetor(float alfa){

    int vetorCanais[8] = {3,8,4,9,2,5,7,10};
    int posic;
    int tamanho = 8;
    int *aux = new int[8];
    for(int i = 0; i < 8; i++){
        posic = rand()%(int)ceil(tamanho*alfa);
        if (vetorCanais[posic] != -1) {
            aux[i] = vetorCanais[posic];
            vetorCanais[posic] = -1;
        }else{
            for (int j = 0; j < 8; j++) {
                if (vetorCanais[posic] == -1){
                    posic++;
                }else{
                    break;
                }
            }
            aux[i] = vetorCanais[posic];
            vetorCanais[posic] = -1;
        }
        tamanho--;
    }
    return aux;
}


float Grafo::gulosoRandomizado(float alfa, int quantInteracoes) {
    int *vetorIdsSemCanais = baseCanais1611();
    int *vetorCanais = randomizaVetor(alfa);
    bool atribui;
    float melhorResultado = 99999, resultado;

    for (int i = 0; i < quantInteracoes; i++) {
        for (int i = 0; ;i++) {
            if(vetorIdsSemCanais[i]==-1) break;
            No* ap = getNo(vetorIdsSemCanais[i]);
            for (int canal = 0; canal < 8; canal++) {
                atribui=true;
                for(Aresta* aresta = ap->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProximaAresta()) {
                    No *ap2 = getNo(aresta->getId());
                    if(ap2->getCanal()==vetorCanais[canal]) {
                        atribui=false;
                        break;
                    }
                }
                if(atribui){
                    ap->setCanal(vetorCanais[canal]);
                    break;
                }
            }

        }
        defineInterferencias(vetorIdsSemCanais);
        resultado = interferenciaTotal;
        if(resultado < melhorResultado) melhorResultado = resultado;

        vetorCanais = randomizaVetor(alfa);
        vetorIdsSemCanais = baseCanais1611();
    }

    return melhorResultado;

}
float Grafo::randomizaAlfa (float *vetorAlfas, double *probabilidades, double *medias, double melhorSolucao){
    double  aux, acm = 0, q[10] = {0,0,0,0,0,0,0,0,0,0};
    // calcula q
    for (int i = 0; i < 10; ++i) {
        if(medias[i] != 0){
            q[i] = pow(melhorSolucao/medias[i],10);
            acm += q[i];
        }
    }
    // altera a probabilidade de cada alfa ser escolhido com base no q. A soma de todas as posições do vetor é sempre 1.
    for (int i = 0; i < 10; ++i) {
        if(q[i] != 0) probabilidades[i] = q[i]/acm;
    }
    acm = 0;
    // aux recebe um número aleatório entre 0 e 100
    aux = rand()%101;
    //define, de acordo com o vetor de probabilidades e com o valor selecionado, qual será o alfa retornado
    for (int i = 0; i < 10; ++i) {
        acm += probabilidades[i]*100;
        if(aux <= acm) {
            acm = i;
            break;
        }
    }
    return  vetorAlfas[(int)acm];
}

float Grafo::gulosoRandomizadoReativo(int quantInteracoes, float* vetorAlfas)  {
    int *vetorIdsSemCanais = baseCanais1611(),contador[10] = {0,0,0,0,0,0,0,0,0,0};
    double custos[10] = {0,0,0,0,0,0,0,0,0,0}, medias[10] = {0,0,0,0,0,0,0,0,0,0}, probabilidades[10] = {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
    double melhorResultado = 99999, resultado = 0, melhorAlfa = 0,  alfa = vetorAlfas[rand()%10];
    int *vetorCanais = randomizaVetor(alfa);
    bool atribui;

    for (int i = 0, k = 0; i < quantInteracoes; i++, k++) {

        for (int i = 0; ;i++) {
            if(vetorIdsSemCanais[i]==-1) break;
            No* ap = getNo(vetorIdsSemCanais[i]);
            for (int canal = 0; canal < 8; canal++) {
                atribui=true;
                for(Aresta* aresta = ap->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProximaAresta()) {
                    No *ap2 = getNo(aresta->getId());
                    if(ap2->getCanal()==vetorCanais[canal]) {
                        atribui=false;
                        break;
                    }
                }
                if(atribui){
                    ap->setCanal(vetorCanais[canal]);
                    break;
                }
            }
        }
        defineInterferencias(vetorIdsSemCanais);
        resultado = interferenciaTotal;


        float posicao = 10 * alfa - 1;
        custos[(int)posicao] += resultado;
        contador[(int)posicao] += 1;
        //atualiza melhores resultado e alfa
        if(resultado < melhorResultado) {
            melhorResultado = resultado;
            melhorAlfa = alfa;
        }
        //atualiza vetor de médias
        for (int j = 0; j < 10; ++j) {
            if(contador[j] > 0){
                medias[j] = custos[j]/contador[j];
            }
        }
        //as x primeiras interações são feitas com um alfa aleatório para que o vetor de médias esteja
        // completo ao ser passado como parâmetro para a função randomizaAlfa.
        if(i < (int)ceil(quantInteracoes*0.1) ){ //Caso i for menor que 10% da quantidade de iterações
            alfa = vetorAlfas[rand()%10];
        }
        //quando k == 10% da quantidade de interações que deve ser feitas, o alfa é randomizado
        if( k == (int)ceil(quantInteracoes*0.1) ){
            alfa = randomizaAlfa(vetorAlfas, probabilidades, medias, melhorResultado);
            k=0;
        }
        //atualiza vetor de canais de acordo com o alfa passado
        vetorCanais = randomizaVetor(alfa);
        vetorIdsSemCanais = baseCanais1611();
    }

    return melhorResultado;
}




