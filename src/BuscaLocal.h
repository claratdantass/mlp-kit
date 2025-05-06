#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "Data.h"

struct Subsequence {
    double T, C; // duração e custo acumulado
    int W;       // tempo de atraso (quantidade de nós depois do primeiro)
    int first, last;

    inline static Subsequence Concatenate(Subsequence& sigma_1, Subsequence& sigma_2, Data& data) {
        Subsequence sigma;
        cout << " " << endl;
        double temp = data.getDistance(sigma_1.last, sigma_2.first);
        sigma.W = sigma_1.W + sigma_2.W;
        sigma.T = sigma_1.T + temp + sigma_2.T;
        sigma.C = sigma_1.C + sigma_2.W * (sigma_1.T + temp) + sigma_2.C;
        sigma.first = sigma_1.first;
        sigma.last = sigma_2.last;
        return sigma;
    }
};

void UpdateAllSubseq(Solution& s, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data); 

bool bestImprovementSwap(Solution& sParcial, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data);

bool bestImprovement2Opt(Solution& sParcial, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data);

bool bestImprovementOrOpt2(Solution& sParcial, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data);

void BuscaLocal(Solution& sParcial, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data);
