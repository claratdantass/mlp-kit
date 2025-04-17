#include "Construcao.h"

std::vector<InsertionInfo> calcularCustoInsercao(std::vector<int>& CL, Data& data, int r){
    std::vector<InsertionInfo> custoInsercao = std::vector<InsertionInfo>(CL.size());

    int l = 0;
    for(auto k : CL){
        custoInsercao[l].custo = data.getDistance(k, r);
        custoInsercao[l].vertices = k;
        custoInsercao[l].r = r;
        l++;
        
    }
    return custoInsercao;
}

std::vector<InsertionInfo> ordenarEmOrdemCrescente(std::vector<InsertionInfo>& beta) {
    std::sort(beta.begin(), beta.end(), [](const InsertionInfo& a, const InsertionInfo& b) {
        return a.custo < b.custo; 
    });
    return beta; 
}

double escolherAlpha(std::vector<double> R) {
    std::srand(std::time(0));

    int index = std::rand() % R.size();

    return R[index];
}

Solution Construcao(int cidades, Data& data, Solution& vParcial){
    std::vector<int> CL; //candidate list
    std::vector<double> R;
    Solution s;
    int r;

    for(double i = 0.00; i <= 0.26; i += 0.01) {
        R.push_back(i);
    }

    for (double value : R) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    double alphaEscolhido = escolherAlpha(R);
    std::cout << "alpha:" << alphaEscolhido << std::endl;

    for(int i = 2; i <= cidades; ++i){
        CL.push_back(i);
    }

    s.sequencia.push_back(1); // adicionando o primeiro vértice a sequencia s 
    
    r = 1;
    
    while(!CL.empty()){
        std::vector<int> RCL;

        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(CL, data, r); // retorna um vector de insertioninfo, com as informacoes do novo vertice, do atual r e do custo

        custoInsercao = ordenarEmOrdemCrescente(custoInsercao); //ordena os custo em ordem crescente 
        for(int i = 0; i < custoInsercao.size(); i++){
            std::cout << custoInsercao[i].vertices << " ";
        }
        std::cout << std::endl;

        int numRCL = std::ceil(alphaEscolhido * custoInsercao.size());
        std::cout << "numRCL:" << numRCL << std::endl;

        for(int i = 0; i < numRCL; ++i) {
            RCL.push_back(custoInsercao[i].vertices);  
        }

        cout << "RCL:" << endl;
        for(int i = 0; i < RCL.size(); i++){
            std::cout << RCL[i] << " ";
        }
        std::cout << std::endl;


        std::srand(std::time(0));
        int index = std::rand() % RCL.size();
        std::cout << "index: " << index << std::endl;
        int r = RCL[index];
        std::cout << "rzinho:" << r << std::endl;

        s.sequencia.push_back(r);
    
        CL.erase(std::remove(CL.begin(), CL.end(), r), CL.end());
    }   
    
    for(int i = 0; i < s.sequencia.size(); i++){
        std::cout << s.sequencia[i] << " ";
    }
    std::cout << std::endl;
    return s;
}
