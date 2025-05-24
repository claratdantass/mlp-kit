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
                cout << "sigma final: " << sigma_final.C << endl;
                cout << "sParcial.valorObj: " << sParcial.valorObj << endl;
                
                //cout << "i: " << sParcial.sequencia[i] << " j: " << sParcial.sequencia[j] << std::endl;

                /*
                for(int i = 0; i < sParcial.sequencia.size(); i++){
                    std::cout << sParcial.sequencia[i] << " ";
                }
                */
                

                std::swap(sParcial.sequencia[i], sParcial.sequencia[j]);

                /*
        
                for(int i = 0; i < sParcial.sequencia.size(); i++){
                    std::cout << sParcial.sequencia[i] << " ";
                }
                */
                
                UpdateAllSubseq(sParcial, subseq_matrix, data);
                //sParcial.valorObj = subseq_matrix[0][sParcial.sequencia.size() - 1].C;
                sParcial.valorObj = sigma_final.C;
                
                return true;
            }
        }
    }
    return false;
}


bool bestImprovement2Opt(Solution& sParcial, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data) {
    Subsequence sigma_1, sigma_2, sigma_final; 
    for (int i = 1; i < sParcial.sequencia.size() - 1; i++) {
        for (int j = i + 2; j < sParcial.sequencia.size() - 1; j++) {
            
            sigma_1 = Subsequence::Concatenate(subseq_matrix[0][i - 1], subseq_matrix[j][i], data);
            sigma_2 = Subsequence::Concatenate(sigma_1, subseq_matrix[j + 1][sParcial.sequencia.size() - 1], data); // the sigma goes to the sigma_2
            
            if (sigma_2.C < sParcial.valorObj) {
                cout << "sigma 2: " << sigma_2.C << endl;
                cout << "sParcial.valorObj: " << sParcial.valorObj << endl;
                
                //cout << "i: " << sParcial.sequencia[i] << " j: " << sParcial.sequencia[j] << std::endl;

                /*
                for(int i = 0; i < sParcial.sequencia.size(); i++){
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << std::endl;

                */
            
                std::reverse(sParcial.sequencia.begin() + i, sParcial.sequencia.begin() + j + 1);

                /*
                for(int i = 0; i < sParcial.sequencia.size(); i++){
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << std::endl;

                */
    
                UpdateAllSubseq(sParcial, subseq_matrix, data);
                sParcial.valorObj = sigma_2.C;
                //sParcial.valorObj = subseq_matrix[0][sParcial.sequencia.size() - 1].C;
                //std::cout << "valorObj novo: " << sParcial.valorObj << std::endl;
                

                return true;
            }
        }
    }
    return false;
}

bool bestImprovementN1(Solution& sParcial, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data) {
    Subsequence sigma_1, sigma_2, sigma_3;

    for (int i = 1; i < sParcial.sequencia.size() - 1; ++i) {
        for (int j = 0; j < sParcial.sequencia.size() - 1; ++j) {
            if (j == i) continue;

            if (j < i) {
                sigma_1 = Subsequence::Concatenate(subseq_matrix[0][j], subseq_matrix[i][i + 1], data);
                sigma_2 = Subsequence::Concatenate(sigma_1, subseq_matrix[j + 1][i - 1], data);
                sigma_3 = Subsequence::Concatenate(sigma_2, subseq_matrix[i + 1][sParcial.sequencia.size() - 1], data);
            } else {
                sigma_1 = Subsequence::Concatenate(subseq_matrix[0][i - 1], subseq_matrix[i + 1][j], data);
                sigma_2 = Subsequence::Concatenate(sigma_1, subseq_matrix[i][i], data);
                sigma_3 = Subsequence::Concatenate(sigma_2, subseq_matrix[j + 1][sParcial.sequencia.size() - 1], data);
            }

            if (sigma_3.C < sParcial.valorObj) {
                cout << "sigma 3: " << sigma_3.C << endl;
                cout << "sParcial.valorObj: " << sParcial.valorObj << endl;
                
                int node = sParcial.sequencia[i];
                
                //cout << "i: " << sParcial.sequencia[i] << " j: " << sParcial.sequencia[j] << std::endl;

                /*
                for(int i = 0; i < sParcial.sequencia.size(); i++) {
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << std::endl;
                
                */
                
                if (j < i) {
                    //cout << "j < i" << endl;
                    sParcial.sequencia.erase(sParcial.sequencia.begin() + i);
                    sParcial.sequencia.insert(sParcial.sequencia.begin() + j, node);
                } else {
                    //cout << "j > i" << endl;
                    sParcial.sequencia.insert(sParcial.sequencia.begin() + j + 1, node);
                    sParcial.sequencia.erase(sParcial.sequencia.begin() + i);
                }

                /*
                for(int i = 0; i < sParcial.sequencia.size(); i++) {
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << std::endl;

                */
                
                UpdateAllSubseq(sParcial, subseq_matrix, data);
                sParcial.valorObj = sigma_3.C;

                return true;
            }
        }
    }
    return false;
}

bool bestImprovementN2(Solution& sParcial, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data) {
    Subsequence sigma_1, sigma_2, sigma_3;

    for(int i = 1; i < sParcial.sequencia.size() - 3; ++i){
        for(int j = 0; j < sParcial.sequencia.size() - 1; ++j){
            if (j == i || j == i + 1) continue;

            if (j < i) {
                sigma_1 = Subsequence::Concatenate(subseq_matrix[0][j], subseq_matrix[i][i + 1], data);
                sigma_2 = Subsequence::Concatenate(sigma_1, subseq_matrix[j + 1][i - 1], data);
                sigma_3 = Subsequence::Concatenate(sigma_2, subseq_matrix[i + 2][sParcial.sequencia.size() - 1], data);
            } else {
                sigma_1 = Subsequence::Concatenate(subseq_matrix[0][i - 1], subseq_matrix[i + 2][j], data);
                sigma_2 = Subsequence::Concatenate(sigma_1, subseq_matrix[i][i + 1], data);
                sigma_3 = Subsequence::Concatenate(sigma_2, subseq_matrix[j + 1][sParcial.sequencia.size() - 1], data);
            }

            if (sigma_3.C < sParcial.valorObj) {
                cout << "sigma 3: " << sigma_3.C << endl;
                cout << "sParcial.valorObj: " << sParcial.valorObj << endl;
                
                std::vector<int> bloco = {sParcial.sequencia[i], sParcial.sequencia[i + 1]};

                //cout << "i: " << sParcial.sequencia[i] << " j: " << sParcial.sequencia[j] << std::endl;

                /*
                for(int i = 0; i < sParcial.sequencia.size(); i++){
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << std::endl;
            
                */
                
                if (j < i) {
                    sParcial.sequencia.erase(sParcial.sequencia.begin() + i, sParcial.sequencia.begin() + i + 2);
                    sParcial.sequencia.insert(sParcial.sequencia.begin() + j, bloco.begin(), bloco.end());
                } else {
                    sParcial.sequencia.insert(sParcial.sequencia.begin() + j + 1, bloco.begin(), bloco.end());
                    sParcial.sequencia.erase(sParcial.sequencia.begin() + i, sParcial.sequencia.begin() + i + 2);
                }

                /*
                for(int i = 0; i < sParcial.sequencia.size(); i++){
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << std::endl;
                
                */
                
                UpdateAllSubseq(sParcial, subseq_matrix, data);
                sParcial.valorObj = sigma_3.C;
                return true;
            }
        }
    }
    return false;
}

bool bestImprovementN3(Solution& sParcial, std::vector<std::vector<Subsequence>>& subseq_matrix, Data& data) {
    Subsequence sigma_1, sigma_2, sigma_3;


    for (int i = 1; i < sParcial.sequencia.size() - 4; ++i){
        for (int j = 0; j < sParcial.sequencia.size() - 1; ++j){  
            if (j == i || j == i + 1 || j == i + 2) continue;
            
            //correct one
            if (j < i) {
                sigma_1 = Subsequence::Concatenate(subseq_matrix[0][j], subseq_matrix[i][i + 2], data);
                sigma_2 = Subsequence::Concatenate(sigma_1, subseq_matrix[j + 1][i - 1], data);
                sigma_3 = Subsequence::Concatenate(sigma_2, subseq_matrix[i + 3][sParcial.sequencia.size() - 1], data);
            } else {
                sigma_1 = Subsequence::Concatenate(subseq_matrix[0][i - 1], subseq_matrix[i + 3][j], data);
                sigma_2 = Subsequence::Concatenate(sigma_1, subseq_matrix[i][i + 2], data);
                sigma_3 = Subsequence::Concatenate(sigma_2, subseq_matrix[j + 1][sParcial.sequencia.size() - 1], data);
            }
    
            if(sigma_3.C < sParcial.valorObj){
                cout << "sigma 3: " << sigma_3.C << endl;
                cout << "sParcial.valorObj: " << sParcial.valorObj << endl;
                
                std::vector<int> bloco = {
                    sParcial.sequencia[i],
                    sParcial.sequencia[i + 1],
                    sParcial.sequencia[i + 2]
                };

                //cout << "i: " << sParcial.sequencia[i] << " j: " << sParcial.sequencia[j] << std::endl;

                /*
                for(int i = 0; i < sParcial.sequencia.size(); i++){
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << std::endl;

                */
                
                if (j < i) {
                    //cout << "j < i" << endl;
                    sParcial.sequencia.erase(sParcial.sequencia.begin() + i, sParcial.sequencia.begin() + i + 3);
                    sParcial.sequencia.insert(sParcial.sequencia.begin() + j + 1, bloco.begin(), bloco.end());
                } else {
                    //cout << "j > i" << endl;
                    sParcial.sequencia.insert(sParcial.sequencia.begin() + j + 1, bloco.begin(), bloco.end());
                    sParcial.sequencia.erase(sParcial.sequencia.begin() + i, sParcial.sequencia.begin() + i + 3);
                }

                /*
                for(int i = 0; i < sParcial.sequencia.size(); i++){
                    std::cout << sParcial.sequencia[i] << " ";
                }
                std::cout << std::endl;

                */
                
                UpdateAllSubseq(sParcial, subseq_matrix, data);
                sParcial.valorObj = sigma_3.C;

                return true;
            }
        }
    }
    return false;
}

void BuscaLocal(Solution& sParcial, Data& data){
    std::vector<int> NL = {1, 2, 3, 4, 5}; 
    bool improved = false;

    while (!NL.empty()) {
        int n = rand() % NL.size();
        
        int num = sParcial.sequencia.size();

        vector<vector<Subsequence>> subseq_matrix(num, vector<Subsequence>(num));

        UpdateAllSubseq(sParcial, subseq_matrix, data);

        sParcial.valorObj = subseq_matrix[0][num - 1].C;

        switch (NL[n]){
            case 1:
                std::cout << "SWAP" << std::endl;
                improved = bestImprovementSwap(sParcial, subseq_matrix, data);
                break;
            case 2:
                std::cout << "2 OPT" << std::endl;
                improved = bestImprovement2Opt(sParcial, subseq_matrix, data);
                break;
            case 3:
                std::cout << "N1" << std::endl;
                improved = bestImprovementN1(sParcial, subseq_matrix, data);
                break;
            case 4: 
                std::cout << "N2" << std::endl;
                improved = bestImprovementN2(sParcial, subseq_matrix, data);
                break;
            case 5: 
                std::cout << "N3" << std::endl;
                improved = bestImprovementN3(sParcial, subseq_matrix, data);
                break;
            
            
        }

        if (improved){
            NL = {1, 2, 3, 4, 5};
        }else{
            NL.erase(NL.begin() + n);
        }
    }
}

