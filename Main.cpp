#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "ACM.cpp"


int main() {

    std::srand(static_cast<unsigned int>(std::time(0))); // Inicializa a semente para gerar números aleatórios diferentes em cada execução.

    int numVertices = 800; // número de vértices.
    int valorMaximo = 90; //  número máximo para o custo da aresta.
    int capacidade = 50;

    Grafo grafo(numVertices);
    grafo.criarGrafoCompletoAleatorio(valorMaximo);
    // Marca o tempo de início.
    clock_t inicio = clock();
    grafo.AMC(numVertices, capacidade);
    // Marca o tempo de término.
    clock_t fim = clock();

    // Calcula a duração do intervalo de tempo em segundos.
    double duracao = static_cast<double>(fim - inicio) / CLOCKS_PER_SEC;

    // Imprime o tempo de execução em segundos.
    cout << "Tempo de execucao para " << numVertices << " vertices com capacidade de " << capacidade << ": " << duracao << " segundos." << endl;

    return 0;
}
