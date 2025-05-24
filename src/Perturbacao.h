#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Data.h"
#include "Construcao.h"
#include "BuscaLocal.h"

Solution Perturbacao(Solution& sParcial, Data& data); 
bool isValidSwap(int index1, int tam1, int index2, int tam2, int tamanho);