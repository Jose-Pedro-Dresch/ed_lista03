# Sistema de Matchmaking para Jogos Online

Autores:
- José Pedro Dresch
- Phelipe Gabriel Lima da Silva

## Descrição do Projeto

Nesse trabalho implementamos a base do que é uma fila de espera em um sistema online. No nosso caso, o implementamos ludicamente como um Matchmaking para Jogos Online. Nele conseguimos reforçar e aprender na prática os conceitos de ordenação de estruturas de dados (comparando algoritmos diferentes inclusive, como Insertion e Merge), bem como de algo mais fundamental, que seria o próprio armazenamento e encapsulamento deles em arrays e classes, respectivamente. Desse modo, o programa segue um padrão eficiente e bem estruturado. No mais, divirta-se utilizando nosso sistema!

## Instruções de Compilação e de Execução

Para compilar o projeto, execute no terminal:
```
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
```

Assim, para rodar o executável do programa:
```
./matchmaking
```

Para compilar os testes de desempenho, execute no terminal:
```
g++ desempenho.cpp Matchmaking.cpp Player.cpp -o desempenho_test
```

Dessa forma, para obter o executável dos testes de desempenho:
```
./desempenho_test
```


## Organização dos Arquivos e Execução de Testes

Seguimos a modelagem básica proposta para esse trabalho, dividindo o programa nos seguintes arquivos:
 - ```relatorio.pdf```: Arquivo do relatório em PDF com a análise do projeto, dos custos computacionais, dos algoritmos de ordenação, etc.
 - ```Matchmaking.hpp```: Arquivo de cabeçalho com as assinaturas das funções e variáveis globais
 - ```Matchmaking.cpp```: Implementação das funções definidas no cabeçalho homônimo
 - ```Player.hpp```: Cabeçalho que define a assinatura do objeto ```Player```
 - ```Plater.cpp```: Implementação do código referente ao jogador
 - ```main.cpp```: Este arquivo põe em prática o programa, realizando diversos testes para mostrar seu funcionamento e sua dinâmica
 - ```desempenho.cpp```: Arquivo responsável por gerar os testes de comparação de desempenho dos algoritmos de ordenação

Como dito acima, no arquivo ```main.cpp``` há alguns testes para demonstrar o uso do sistema e sua conformidade com o que foi pedido. Ele é o arquivo do programa em si. Assim, para executá-lo e ver os resultados dos testes no seu terminal, basta seguir as instruções dadas anteriormente.


## Observação 

No modelo para a classe Matchmaking que consta no arquivo de instruções para o projeto, o array de players não é alocado dinamicamente. Por conta disso, houve problemas de esgotamento da stack ao tentar alocar memória para 100.000 jogadores quando tentamos executar os arquivos no Windows. A fim de evitar possíveis problemas, mudou-se o padrão para que o array de Players fosse alocado dinamicamente.