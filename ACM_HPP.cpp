#ifndef ACM_HPP
#define ACM_HPP
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Grafo {
private:
    int numVertices;
    vector<vector<int>> matrizAdj;

public:
    Grafo(int n);
    void adicionarAresta(int origem, int destino, int custo);
    void imprimirGrafo();
    int MenorCusto(int vertice, Grafo sol, vector<bool>& marcador, int option);
    int gerarCustoAleatorio(int valorMaximo);
    Grafo AMC(int num_vet, int capacidade);
}

#endif