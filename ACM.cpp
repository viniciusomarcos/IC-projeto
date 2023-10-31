#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <array>
#include "ACM.hpp"

using namespace std;


Grafo::Grafo(int n) {
    numVertices = n;
    matrizAdj.resize(numVertices, vector<double>(numVertices, 0));

}

//usado na versão 3 - atualização do algortmo de Prim
void Grafo::adicionarAresta3(double origem, double destino, double custo) {
    matrizAdj[origem][destino] = custo;
}

void Grafo::imprimirGrafo() {
    cout << "  ";
    for(int i=0; i<numVertices; i++){
        if(i<10){
            cout << " 0" << i << " ";
        }
        else cout << " " << i << " ";
    }
    cout << endl;
    for (int i = 0; i < numVertices; i++) {
        if(i<10){
            cout << "0" << i;
        }
        else cout << i;
        for (int j = 0; j < numVertices; j++) {
            if(matrizAdj[i][j]<10){
                cout << " 0" << matrizAdj[i][j] << " ";
            }
            else cout << " " << matrizAdj[i][j] << " ";
        }
        cout << endl;
    }
}

// usado na versão 3 - atualização do algortmo de Prim
int Grafo::CalculaCapacidade(int raiz, int antecessor){
    int capacidade = 1;
    //int antecessor = int(aresta[0]);
    while(antecessor!=raiz){
        for(int i=0; i<numVertices; i++){
            if(matrizAdj[i][antecessor]!=0){
                antecessor = i;
                capacidade++;
            }
        }
    }
    return capacidade;
}
// usado na versão 3 - atualização do algortmo de Prim
array<double, 3> Grafo::MenorCusto3(int raiz, Grafo sol, vector<bool>& marcador, int capacidade){
    double menor_custo = -1;
    double vtc, vtc_par;
    int tamanho = marcador.size();
    if(marcador[raiz]==false){
        for(int i=raiz+1; i<tamanho; i++){
            if((matrizAdj[raiz][i]<menor_custo || menor_custo == -1)&& marcador[i] == false){
                menor_custo = matrizAdj[raiz][i];
                vtc = raiz;
                vtc_par = i;
            }
        }
        for(int j=1; j<raiz; j++){
            if((matrizAdj[j][raiz]<menor_custo || menor_custo == -1) && marcador[j] == false){
                menor_custo = matrizAdj[j][raiz];
                vtc = raiz;
                vtc_par = j;
            }
        }
        marcador[raiz] = true;
    }else{
        for(int vertice=0; vertice<tamanho; vertice++){
            if(marcador[vertice]==true){
                for(int j=vertice+1; j<tamanho; j++){
                    if((matrizAdj[vertice][j]<menor_custo || menor_custo == -1) && marcador[j] == false
                        && capacidade>=sol.CalculaCapacidade(raiz, vertice)){                       
                        menor_custo = matrizAdj[vertice][j];
                        vtc = vertice;
                        vtc_par = j;
                    }
                }
                for(int k=0; k<vertice; k++){
                    if((matrizAdj[k][vertice]<menor_custo || menor_custo == -1) && marcador[k] == false
                       && capacidade>=sol.CalculaCapacidade(raiz, vertice)){
                        menor_custo = matrizAdj[k][vertice];
                        vtc = vertice;
                        vtc_par = k;
                    }
                }
            }
        }
    
    }
    array<double, 3> aresta = {vtc, vtc_par, menor_custo};
    return aresta;
}

// usado na versão 3 - atualização do algortmo de Prim
Grafo Grafo::AMC3(int num_vet, int raiz, vector<int>& capacidade){
    Grafo amc(num_vet);
    int num_vet_atual = 1;
    int i=0, cap_atual = 0;
    double vtc, vtc_par, menor_custo;
    vector<bool> marcador(num_vet, false);
    array<double, 3> aresta;
    while (num_vet_atual<num_vet)
    {
        aresta = MenorCusto3(raiz, amc, marcador, capacidade[i]);
        vtc = aresta[0];
        vtc_par = aresta[1];
        menor_custo = aresta[2];
        amc.adicionarAresta3(vtc, vtc_par, menor_custo);
        marcador[vtc_par] = true;
        num_vet_atual++;
        cap_atual = amc.CalculaCapacidade(raiz, vtc);
        if(cap_atual==capacidade[i]){
            i++;
        }
    }
    return amc;
}

//Funções fora da classe

double gerarCustoAleatorio(double valorMaximo){
    double randomFraction = static_cast<double>(std::rand()) / RAND_MAX;
    double randomValue = 10.0 + randomFraction * (valorMaximo - 10.0);
    return randomValue;
}

Grafo criarGrafoCompletoAleatorio(int numVertices, double valorMaximo){
    Grafo grafo_al(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) { // Preenche apenas a parte triangular superior.
            double custo = gerarCustoAleatorio(valorMaximo);
            grafo_al.adicionarAresta(i, j, custo);
        }
    }
    return grafo_al;
}


// outras funções
void adicionarLinhasComoArestas(Grafo& grafo, const vector<vector<double>>& dadosDouble) {
    // Percorre os dadosDouble e adiciona cada linha como uma aresta
    int tamanho = (dadosDouble.size())/100;
    for (int i=0; i< tamanho; i++) {
        // Verifica se algum dos valores é nulo
        bool temNulo = false;
        for (int j=0; j<3; j++) {
            if (std::isnan(dadosDouble[i][j])) {  // Verifica se é um NaN (representando um valor nulo)
                temNulo = true;
                break;
            }
        }
        if (!temNulo) {
            double origem = dadosDouble[i][0];
            double destino = dadosDouble[i][1];
            double custo = dadosDouble[i][2];

            grafo.adicionarAresta3(origem, destino, custo);
        }
    }
}
