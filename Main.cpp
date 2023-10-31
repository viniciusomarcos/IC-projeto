#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <array>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <unordered_set>
#include "ACM.cpp"


using namespace std;


double converterValorEspecialParaDouble(const std::string& valorString) {
std::string valorLimpo;  // Armazenará apenas os caracteres permitidos

    // Remove os caracteres não desejados
    for (char c : valorString) {
        if (std::isdigit(c) || c == '.' || c == '-') {
            valorLimpo += c;
        }
    }

    try {
        return std::stod(valorLimpo);
    } catch (const std::invalid_argument&) {
        std::cerr << "Erro ao converter para double: " << valorString << std::endl;
        return 0.0;  // Ou qualquer outro valor padrão que faça sentido para sua aplicação
    }
}

int contarValoresDistintos(const std::vector<std::vector<double>>& dadosDouble) {
    std::unordered_set<double> valoresDistintos;

    for (const auto& linha : dadosDouble) {
        // Verifica se há pelo menos duas colunas
        if (linha.size() >= 2) {
            valoresDistintos.insert(linha[0]);  // Primeira coluna
            valoresDistintos.insert(linha[1]);  // Segunda coluna
        }
    }

    return valoresDistintos.size();
}



int main(){

    std::string arquivoCSV = "alunos_distintos_req.csv";
    std::vector<std::vector<std::string>> dados;
    std::vector<std::vector<double>> dadosDouble;

    std::ifstream arquivo(arquivoCSV);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo CSV." << std::endl;
        return 1;
    }

    std::string linha;

    while (std::getline(arquivo, linha)) {
        std::vector<std::string> linhaDados;
        std::istringstream linhaStream(linha);
        std::string valor;
        int colunaAtual = 1;

        // Lê cada valor e armazena somente as colunas desejadas
        while (std::getline(linhaStream, valor, ',')) {
            if (colunaAtual == 2 || colunaAtual == 3 || colunaAtual == 4) {  // Escolhe as colunas 
                linhaDados.push_back(valor);
            }
            colunaAtual++;
        }

        // Garante que lemos as colunas desejadas
        if (linhaDados.size() == 3) {
            dados.push_back(linhaDados);
        } else {
            std::cerr << "Erro ao ler as colunas desejadas." << std::endl;
        }
    }
    // Converter e imprimir as linhas a partir da segunda (índice 1)
    int contador = 0;
    for (size_t i = 0; i < dados.size(); ++i) {
        std::vector<double> linhaDouble;

        for (size_t j = 0; j < dados[i].size(); ++j) {
            double valorDouble = converterValorEspecialParaDouble(dados[i][j]);
            linhaDouble.push_back(valorDouble);
        }

        // Armazena a linha convertida
        dadosDouble.push_back(linhaDouble);
        contador++;
        // Imprime a linha convertida
        /*
        for (const double& valorDouble : linhaDouble) {
            std::cout << valorDouble << " ";
        }
        std::cout << std::endl;
        */
        
    }

    cout << "Dados lidos com sucesso: " << contador << " linhas" << endl;

    arquivo.close();

    contador = contador/100;
    Grafo Escolas(contador);
    adicionarLinhasComoArestas(Escolas, dadosDouble);

    //rascunho de ideia
    //calcular para cada raiz
    /*
    for(){
        for(){
            int raiz = dadosDouble[i][j];
            Grafo Escola(x); //subgrafo
            //Escolas.AMC3(x, raiz, capacidades).imprimirGrafo();
        }
    }*/

    return 0;
}
