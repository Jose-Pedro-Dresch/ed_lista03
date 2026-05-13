#include "Player.hpp"
#include "Matchmaking.hpp"
#include <iostream>
using namespace std;


// Construtor padrão de um sistema de Matchmaking
// É inicializado com size = 0
Matchmaking::Matchmaking()
{
    players = new Player[MAX_PLAYERS];
    size = 0;
}

// Destrutor de um sistema de Matchmaking
Matchmaking::~Matchmaking() {
    delete[] players;
}

// Método para inserir um novo jogador na lista de espera, 
// caso ainda haja disponibilidade
bool Matchmaking::insert(Player player)
{
    if (size < MAX_PLAYERS) // verifica se há espaço disponível
    {
        players[size++] = player; //adiciona o novo jogador e incrementa o atributo size
        return true;
    }
    else
    {
        return false; 
    }
}

// Método para remover um jogador da lista de espera dado o seu id
bool Matchmaking::removePlayer(int id)
{
    for (int i = 0; i < size; i++) // percorre a lista para ver se encontra tal jogador
    {
        if (players[i].getId() == id) // Se encontrou o jogador com id correspondente
        {
            for (int j = i; j < size - 1; j++) // percorre até o último Player presente, deslocando os jogadores para esquerda
            {
                players[j] = players[j + 1];
            }
            size--; // diminui o size
            return true;
        }
    }
    return false;
}

// Método para ordenar os jogadores com o algoritmo do Insertion Sort
void Matchmaking::sortByScoreInsertion()
{
    Player current;
    for (int i = 1; i < size; i++) 
    {
        int j = i - 1;
        current = players[i]; // armazena o jogador atual que será posicionado

        while (j >= 0 &&  
               (players[j].getScore() > current.getScore() || // Se estiverem desordenados por score
                (players[j].getScore() == current.getScore() &&  
                 players[j].getTimestamp() > current.getTimestamp()))) // Se tiverem o mesmo score, mas timestamps diferentes
        {
            // Desloca o jogador para a direita
            players[j + 1] = players[j];
            j = j - 1;
        }
        players[j + 1] = current; // Insere current na posição correta
    }
}

// Combina dois arrays ordenados em um novo ordenado
Player *Matchmaking::merge(Player arr1[], int m1, Player arr2[], int m2)
{
    Player *merged = new Player[m1 + m2]; // Aloca espaço para o array combinado
    int i = 0, j = 0;
    while (i < m1 && j < m2) // Enquanto há elementos para percorrer nos dois subarrays
    {
        Player p1 = arr1[i];
        Player p2 = arr2[j];

        if (p1.getScore() > p2.getScore() ||  // Verifica diferença de score entre os jogadores
            (p1.getScore() == p2.getScore() && p1.getTimestamp() > p2.getTimestamp())) // Se houver mesmo score, desempata com timestamp
        {
            merged[i + j] = p2; // insere o jogador do segundo subarray se este for o menor
            j++;
        }
        else
        {
            merged[i + j] = p1; // insere o jogador do primeiro subarray se este for o menor
            i++;
        }
    }
    while (i < m1) // Se o segundo subarray acabou apenas insere os elementos restantes do primeiro
    {
        merged[i + j] = arr1[i];
        i++;
    }
    while (j < m2) // Se o primeiro subarray acabou apenas insere os elementos restantes do segundo
    {
        merged[i + j] = arr2[j];
        j++;
    }
    return merged; 
}

// Implementação do algoritmo do merge sort com chamadas recursivas
Player *Matchmaking::mergeSort(Player *plays, int n)
{
    // Caso base: um array de um elemento já está ordenado
    if (n == 1)
    {
        Player *single = new Player[1];
        single[0] = plays[0];
        return single;
    }
    // Divide o array na metade e faz chamadas recursivas em cada uma
    int mid = n / 2;
    Player *left = mergeSort(plays, mid);
    Player *right = mergeSort(plays + mid, n - mid);
    Player *sorted = merge(left, mid, right, n - mid); // combina as duas metades, agora ordenadas, usando a auxiliar merge

    // libere os subarrays temporários
    delete[] left; 
    delete[] right;

    return sorted; 
}

// Método para ordenar os jogadores da lista de players usando o algoritmo Merge Sort
void Matchmaking::sortByScoreMerge()
{
    if (size == 0) // se não há jogadores não há o que fazer
    {
        return;
    }
    Player *aux = mergeSort(players, size); // aloca os jogadores ordenados em um array temporário 

    for (int i = 0; i < size; i++) // copia os elementos agora ordenados
    {
        players[i] = aux[i];
    }

    // libera o array auxiliar
    delete[] aux;
}

// Método para formar um grupo de jogadores do matchmaking, se possível
Player *Matchmaking::formGroup(int groupSize, int delta, int *n)
{
    if (size == 0 || groupSize > size) // Se não há ninguém na fila e espera ou não jogadores suficientes para tal grupo
    {
        *n = 0;
        return nullptr;
    }
    for (int i = 0; i < size - groupSize + 1; i++) 
    {
        // Assumindo o array já ordenado, verifica se há um intervalo de groupSize jogadores tais que 
        // seja satisfeita a condição de que o menor (o que vem primeiro na ordem na lista) e o maior
        // tenham diferença de score no máximo igual a delta
        if ((players[i + groupSize - 1].getScore() - players[i].getScore()) <= delta)
        {
            Player *group = new Player[groupSize]; // Cria um novo array para armazenar o grupo formado
            for (int j = i; j <= i + groupSize - 1; j++)
            {
                group[j - i] = players[j]; // Armazena os jogadores no grupo
            }

            // remove os jogadores do grupo da lista de espera
            for (int k = i; k < size - groupSize; k++) 
            {
                // desloca os jogadores para esquerda, que significar remover os jogadores do grupo da lista
                players[k] = players[k + groupSize];  
            }
            size -= groupSize; // atualiza a quantidade de jogadores da lista

            *n = groupSize; // Associa à variável n o tamanho do grupo formado
            return group;
        }
    }
    // Caso não tenha sido possível formar grupo 
    *n = 0;
    return nullptr;
}

// Método que copia os Players atualmente na lista de espera 
// em um array alocado dinamicamente
Player *Matchmaking::getWaitingPlayers(int *n)
{
    *n = size; // Associa à variável n a quantidade de jogadores
    if (*n == 0) // Se a lista está vazia
    {
        return nullptr;
    }
    // Cria uma lista alocada dinamicamente e armazena as cópias dos jogadores
    Player *plays = new Player[size]; 
    for (int i = 0; i < *n; i++)
    {
        plays[i] = players[i];
    }
    return plays;
}

// Método para exibir os jogadores atualmente na lista de espera
void Matchmaking::printWaitingPlayers()
{
    if (size == 0) // Se a lista está vazia 
    {
        cout << "(empty)";
    }
    else
    {
        // Se houver jogadores exibe cada um no formato
        // [id | nome | score | timestamp]
        cout << "Waiting Players: \n";
        for (int i = 0; i < size; i++)
        {
            Player p = players[i];
            cout << "[ " << p.getId() << " | " << p.getName() << " | " << p.getScore() << " | " << p.getTimestamp() << " ]\n";
        }
        cout << endl;
    }
}
