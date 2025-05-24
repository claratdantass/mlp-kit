# mlp-kit

como rodar ./tsp instances/instancia.tsp

ils:

Solution ILS(int maxIter, int maxIterIls)
{
    Solution bestOfAll;
    bestOfAll.cost = INFINITY;
    
    for(int i = 0; i < maxIter; i++)
    {
        Solution s = Construcao();
        Solution best = s;

        int iterIls = 0;

        while(iterIls <= maxIterIls)
        {
            BuscaLocal(&s);
            
            if(s.cost < best.cost)
            {
                best = s;
                iterIls = 0;
            }

            s = Perturbacao(best);
            iterIls++;
        }

        if (best.cost < bestOfAll.cost)
            bestOfAll = best;
    }

    return bestOfAll;
}

