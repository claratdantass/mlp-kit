#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include "Data.h"
#include "Construcao.h"
#include "BuscaLocal.h"

void UpdateAllSubseq(Solution& s, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data) {
    int n = s.sequencia.size();

    for (int i = 0; i < n; i++){ 
        int v = s.sequencia[i];
        subseq_matrix[i][i].W = (i > 0);
        subseq_matrix[i][i].C = 0;
        subseq_matrix[i][i].T = 0;
        subseq_matrix[i][i].first = v;
        subseq_matrix[i][i].last = v;
    }

    for (int i = 0; i < n; i++) { 
        for (int j = i + 1; j < n; j++) { 
            subseq_matrix[i][j] = Subsequence::Concatenate(subseq_matrix[i][j - 1], subseq_matrix[j][j], data);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            subseq_matrix[i][j] = Subsequence::Concatenate(subseq_matrix[i][j + 1], subseq_matrix[j][j], data);
        }
    }
}


bool bestImprovementSwap(Solution& sParcial, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data) {
    Subsequence sigma_1, sigma_2, sigma_3, sigma_final;

    for (int i = 1; i < sParcial.sequencia.size() - 1; i++) {
        for (int j = i + 1; j < sParcial.sequencia.size() - 1; j++) {

            sigma_1 = Subsequence::Concatenate(subseq_matrix[0][i - 1], subseq_matrix[j][j], data);
            sigma_2 = Subsequence::Concatenate(sigma_1, subseq_matrix[i + 1][j - 1], data);
            sigma_3 = Subsequence::Concatenate(sigma_2, subseq_matrix[i][i], data);
            sigma_final = Subsequence::Concatenate(sigma_3, subseq_matrix[j + 1][sParcial.sequencia.size() - 1], data);

            if (sigma_final.C < sParcial.valorObj) {
                cout << "entrou no if" << endl;
                std::swap(sParcial.sequencia[i], sParcial.sequencia[j]);

                UpdateAllSubseq(sParcial, subseq_matrix, data);
                sParcial.valorObj = subseq_matrix[0][sParcial.sequencia.size() - 1].C;

                return true;
            }
        }
    }
    return false;
}

bool bestImprovement2Opt(Solution& sParcial, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data) {
    for(int i = 0; i < sParcial.sequencia.size(); i++){
        std::cout << sParcial.sequencia[i] << " ";
    }
    std::cout << std::endl;
    
    for (int i = 1; i < sParcial.sequencia.size() - 1; i++) {
        for (int j = i + 2; j < sParcial.sequencia.size() - 1; j++) {
            
            Subsequence sigma_1 = Subsequence::Concatenate(subseq_matrix[0][i - 1], subseq_matrix[j][i], data);
            Subsequence sigma_2 = Subsequence::Concatenate(sigma_1, subseq_matrix[j + 1][sParcial.sequencia.size() - 1], data); // the sigma goes to the sigma_2

            cout << " " << endl;
            cout << "valorObj: " << sParcial.valorObj << endl;
            cout << "sigma_2.C: " << sigma_2.C << endl;

            if (sigma_2.C < sParcial.valorObj) {
                cout << "is it any better" << endl;
                for(int i = 0; i < sParcial.sequencia.size(); i++){
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << std::endl;

                std::reverse(sParcial.sequencia.begin() + i, sParcial.sequencia.begin() + j + 1);

                for(int i = 0; i < sParcial.sequencia.size(); i++){
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << std::endl;
                
                UpdateAllSubseq(sParcial, subseq_matrix, data);
                sParcial.valorObj = subseq_matrix[0][sParcial.sequencia.size() - 1].C;

                return true;
            }
        }
    }
    return false;
}

bool bestImprovementOrOpt2(Solution& sParcial, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data) {
    for (int i = 1; i < sParcial.sequencia.size() - 3; ++i) {
        for (int j = 1; j < sParcial.sequencia.size() - 1; ++j) {
            if (j == i || j == i + 1) continue;

            Subsequence sigma_1, sigma_2, sigma_3;

            if (j < i) {
                sigma_1 = Subsequence::Concatenate(subseq_matrix[0][j - 1], subseq_matrix[i][i + 1], data);
                sigma_2 = Subsequence::Concatenate(sigma_1, subseq_matrix[j][i - 1], data);
                sigma_3 = Subsequence::Concatenate(sigma_2, subseq_matrix[i + 2][sParcial.sequencia.size() - 1], data);
            } else {
                sigma_1 = Subsequence::Concatenate(subseq_matrix[0][i - 1], subseq_matrix[i + 2][j - 1], data);
                sigma_2 = Subsequence::Concatenate(sigma_1, subseq_matrix[i][i + 1], data);
                sigma_3 = Subsequence::Concatenate(sigma_2, subseq_matrix[j][sParcial.sequencia.size() - 1], data);
            }

            if (sigma_3.C < sParcial.valorObj) {
                std::vector<int> bloco = {sParcial.sequencia[i], sParcial.sequencia[i + 1]};

                if (j < i) {
                    sParcial.sequencia.erase(sParcial.sequencia.begin() + i, sParcial.sequencia.begin() + i + 2);
                    sParcial.sequencia.insert(sParcial.sequencia.begin() + j, bloco.begin(), bloco.end());
                } else {
                    sParcial.sequencia.insert(sParcial.sequencia.begin() + j + 1, bloco.begin(), bloco.end());
                    sParcial.sequencia.erase(sParcial.sequencia.begin() + i, sParcial.sequencia.begin() + i + 2);
                }
                
                UpdateAllSubseq(sParcial, subseq_matrix, data);
                sParcial.valorObj = subseq_matrix[0][sParcial.sequencia.size() - 1].C;
                
                return true;
            }
        }
    }
    return false;
}

void BuscaLocal(Solution& sParcial, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data) {
    std::vector<int> NL = {1};
    bool improved = false;

    while (!NL.empty()) {
        int n = rand() % NL.size();

        switch (NL[n]) {
            case 1:
                cout << " " << endl;
                std::cout << "2_opt" << std::endl;
                improved = bestImprovement2Opt(sParcial, subseq_matrix, data);
                break;
        }

        if (improved) {
            NL = {1}; 
        } else {
            NL.erase(NL.begin() + n);
        }
    }
}
