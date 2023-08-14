#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "ACM.hpp"

using namespace std;


Grafo::Grafo(int n) {
    numVertices = n;
    matrizAdj.resize(numVertices, vector<int>(numVertices, 0));

}

void Grafo::adicionarAresta(int origem, int destino, int custo) {
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

int Grafo::MenorCusto(int vertice, Grafo sol, vector<bool>& marcador, int option){
    int menor_custo = -1;
    int vtc_par = vertice+1;

    for(int i=vertice+1; i<numVertices; i++){
        if((matrizAdj[vertice][i]<menor_custo || menor_custo == -1)&& matrizAdj[vertice][i] != sol.matrizAdj[vertice][i]
            && marcador[i] == false){
            menor_custo = matrizAdj[vertice][i];
            vtc_par = i;
        }
    }
    for(int j=1; j<vertice; j++){
        if((matrizAdj[j][vertice]<menor_custo || menor_custo == -1) && matrizAdj[j][vertice] != sol.matrizAdj[j][vertice]
            && marcador[j] == false){
            menor_custo = matrizAdj[j][vertice];
            vtc_par = j;
        }
    }
    if(option == 1) return vtc_par; //retorna o vétice par de menor custo
    else if(option == 2) return menor_custo; //retorna o valor do menor custo
    else return -1;
}

// Função para gerar números aleatórios entre 10 e o valor máximo.
int Grafo::gerarCustoAleatorio(int valorMaximo) {
    return 10 + (std::rand() % (valorMaximo - 10 + 1));
}

void Grafo::criarGrafoCompletoAleatorio(int valorMaximo) {
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) { // Preenche apenas a parte triangular superior.
            int custo = gerarCustoAleatorio(valorMaximo);
            adicionarAresta(i, j, custo);
        }
    }
}

//começar pela raiz
Grafo Grafo::AMC(int num_vet, int capacidade){
    Grafo amc(num_vet);
    int raiz = 0;
    int cap_atual = 0;
    int num_vet_atual = 1;
    int vtc_mc, menor_custo, aux;
    vector<bool> marcador(num_vet, false);
    aux = raiz;
    while (cap_atual<capacidade && num_vet_atual<num_vet)
    {
        vtc_mc = MenorCusto(aux, amc, marcador, 1);
        menor_custo = MenorCusto(aux, amc, marcador, 2);
        if(amc.matrizAdj[aux][vtc_mc]==0 && marcador[vtc_mc] == false){
            amc.adicionarAresta(aux, vtc_mc, menor_custo);
            aux = vtc_mc;
            cap_atual++;
            num_vet_atual++;
            marcador[vtc_mc] = true;

        }
        if(cap_atual==capacidade){
            aux = raiz;
            cap_atual = 0;
        }

    }
    return amc;
}
