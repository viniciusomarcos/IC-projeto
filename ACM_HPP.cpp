#ifndef ACM_HPP
#define ACM_HPP
#include <iostream>
#include <vector>
#include <array>
#include <string>

using namespace std;

class Grafo {
private:
    int numVertices;
    vector<vector<double>> matrizAdj;

public:
    Grafo(int n);
    void adicionarAresta3(double origem, double destino, double custo); //usado na versão 3 - atualização do algortmo de Prim
    void imprimirGrafo();
    int CalculaCapacidade(int raiz, int antecessor); // usado na versão 3 - atualização do algortmo de Prim
    array<double, 3> MenorCusto3(int raiz, Grafo sol, vector<bool>& marcador, int capacidade); // usado na versão 3 - atualização do algortmo de Prim
    Grafo AMC3(int num_vet, int raiz, vector<int>& capacidade); // usado na versão 3 - atualização do algortmo de Prim
};

#endif
