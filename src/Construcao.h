#include <cmath>
#include "Data.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <random> 
#include <cstdlib>
#include <ctime>
#pragma once
using namespace std;


struct Solution {
    std::vector<int> sequencia;
    double valorObj;
};

struct InsertionInfo {
    int vertices;       // Nó a ser inserido
    int r;               
    double custo;         // Delta ao inserir o nó na aresta
};

std::vector<InsertionInfo> calcularCustoInsercao(std::vector<int>& CL, Data& data, int r);

std::vector<InsertionInfo> ordenarEmOrdemCrescente(std::vector<InsertionInfo>& beta);

double calcularValorTotal(Solution& s, Data& data);

std::vector<int> inserirNaSolucao(Solution& sParcial, const std::vector<InsertionInfo>& custoInsercao, int selecionado, double alpha);

Solution Construcao(int cidades, Data& data, Solution& vParcial);