#include "Matchmaking.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include <climits> // Para usar o long long e não causar erro por overflow do float

using namespace std;
using namespace std::chrono;

int main()
{
    int tamanhos[] = {1000, 10000, 30000, 50000, 75000, 100000}; // Tamanhos que vamos testar
    int numTestes = 6;
    int numRepeticoes = 5;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distScore(0, 5000);
    uniform_int_distribution<> distTime(0, 100);

    cout << "Tamanho\t\tInsertion min(ms)\tMerge min(ms)\n";
    cout << "--------------------------------------------------------\n";

    for (int i = 0; i < numTestes; i++)
    {
        int n = tamanhos[i];

        long long minInsertion = LLONG_MAX;
        long long minMerge = LLONG_MAX;

        // Loop de repetições para o tamanho atual
        for (int r = 0; r < numRepeticoes; r++)
        {
            Matchmaking *mInsertion = new Matchmaking();
            Matchmaking *mMerge = new Matchmaking();

            for (int j = 0; j < n; j++)
            {
                int score = distScore(gen); // Range de Scores
                int time = distTime(gen);   // Range de Timestamps

                // Colocando os mesmos dados para os dois algoritmos
                mInsertion->insert(Player(j, "Bot", score, time));
                mMerge->insert(Player(j, "Bot", score, time));
            }

            // Medição do Insertion Sort
            auto startInsertion = high_resolution_clock::now();
            mInsertion->sortByScoreInsertion();
            auto endInsertion = high_resolution_clock::now();
            long long durationInsertion = duration_cast<milliseconds>(endInsertion - startInsertion).count();

            // Pega o menor tempo das 5 iterações para evitar ruído
            if (durationInsertion < minInsertion)
            {
                minInsertion = durationInsertion;
            }

            // Medição do Merge Sort
            auto startMerge = high_resolution_clock::now();
            mMerge->sortByScoreMerge();
            auto endMerge = high_resolution_clock::now();
            long long durationMerge = duration_cast<milliseconds>(endMerge - startMerge).count();

            // Pega o menor tempo das 5 iterações para evitar ruído
            if (durationMerge < minMerge)
            {
                minMerge = durationMerge;
            }

            delete mInsertion;
            delete mMerge;
        }

        cout << n << "\t\t" << minInsertion << "\t\t\t" << minMerge << "\n";
    }

    return 0;
}