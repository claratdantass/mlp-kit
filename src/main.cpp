#include "Data.h"
#include <iostream>
#include <vector>
#include "Construcao.h"
#include <chrono>
using namespace std;

int main(int argc, char *argv[]) {
    if(argc < 2){
        std::cout << "Passe caminho para a instancia" << std::endl;
        exit(0);
    }
    {
        auto data = Data(argc, argv[1]);  // Cria o objeto
        data.read();

        const int cidades = data.getDimension();
        std::cout << cidades << std::endl;

        Solution bestOfAll;
        Solution Parcial;
        
        Parcial = Construcao(cidades, data, Parcial);

        return 0;
    }

        
}