/*
#include "Data.h"
#include <iostream>
#include <vector>
#include "Construcao.h"
#include "BuscaLocal.h"
#include "Perturbacao.h"
#include <chrono>
using namespace std;

double calcularCusto(Data& data, vector<int>& v);

int main(int argc, char *argv[]) {
    if(argc < 2){
        std::cout << "Passe caminho para a instancia" << std::endl;
        exit(0);
    }
    {
        auto data = Data(argc, argv[1]); 
        data.read();

        auto start = std::chrono::high_resolution_clock::now();
        const int cidades = data.getDimension();
        std::cout << cidades << std::endl;

        Solution bestOfAll;
        Solution Parcial;
        bestOfAll.valorObj = INFINITY;
        int maxIterIls;
        int maxIter = 50;
    
        if(cidades >= 150){
            maxIterIls = (cidades/2);
        }else{
            maxIterIls = cidades;
        }          

        for(int i = 0; i < maxIter; i++){
            Parcial = Construcao(cidades, data, Parcial); 

            Solution best = Parcial;

            int iterIls = 0;

            while(iterIls <= maxIterIls){
                BuscaLocal(Parcial, data);
                
                if(Parcial.valorObj < best.valorObj){
                    best = Parcial;
                    iterIls = 0;
                }
                Parcial = Perturbacao(best, data); 
                iterIls = iterIls + 1;
            }
            if (best.valorObj < bestOfAll.valorObj)
                bestOfAll = best;
        }

        cout << "Custo total: " << bestOfAll.valorObj << std::endl;

        return 0;
    }    
}
*/


#include "Data.h"
#include <iostream>
#include <vector>
#include "Construcao.h"
#include "BuscaLocal.h"
#include "Perturbacao.h"
#include <chrono>
using namespace std;

double calcularCusto(Data& data, vector<int>& v);

int main(int argc, char *argv[]) {
    if(argc < 2){
        std::cout << "Passe caminho para a instancia" << std::endl;
        exit(0);
    }
    {
        auto data = Data(argc, argv[1]); 
        data.read();

        auto start = std::chrono::high_resolution_clock::now();
        const int cidades = data.getDimension();
        std::cout << cidades << std::endl;

        Solution bestOfAll;
        Solution Parcial;
        bestOfAll.valorObj = INFINITY;
        
        Parcial = Construcao(cidades, data, Parcial);

        int n = Parcial.sequencia.size();

        vector<vector<Subsequence>> subseq_matrix(n, vector<Subsequence>(n));

        UpdateAllSubseq(Parcial, subseq_matrix, data);

        Parcial.valorObj = subseq_matrix[0][n - 1].C;
        
        cout << "custo da sequencia na construcao: " << Parcial.valorObj << std::endl;


        //BuscaLocal(Parcial, subseq_matrix, data);
            
        BuscaLocal(Parcial, data);

        //cout << "Custo total: " << bestOfAll.valorObj << std::endl;

        return 0;
    }    
}

