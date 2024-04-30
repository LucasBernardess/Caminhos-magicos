# Caminhos Mágicos de Mysthollow para Luminae

## Descrição do Projeto
Este repositório contém a implementação de um programa em C que resolve o problema dos caminhos mágicos entre as cidades de Mysthollow e Luminae, conforme especificado no Trabalho Prático 1 da disciplina de Projeto e Análise de Algoritmos.

### Autores
- Lucas Eduardo Bernardes de Paula
- Messias Feres Curi Melo

### Período
2024.1

## Introdução
O problema consiste em encontrar os k caminhos mágicos mais curtos de Mysthollow para Luminae em um cenário fantástico de um reino encantado. Os caminhos são atravessados por poderosos encantamentos e desafios, requerendo uma abordagem algorítmica eficiente para sua resolução.

## Estrutura do Repositório
- `src/`: Contém o código fonte do programa implementado em C.
- `include/`: Contém os arquivos de cabeçalho necessários para compilar o programa.
- `Makefile`: Arquivo de configuração para compilar o programa.
- `input/`: Diretório opcional para armazenar arquivos de entrada.
- `output/`: Diretório opcional para armazenar arquivos de saída.
- `README.md`: Este arquivo que fornece informações sobre o projeto.

## Compilação e Execução
Para compilar o programa, basta executar o comando `make` na raiz do repositório. Isso produzirá um executável chamado `caminhos_magicos`.

Para executar o programa, utilize o seguinte formato de linha de comando:

./caminhos_magicos -i <arquivo_entrada> -o <arquivo_saida>

Substitua `<arquivo_entrada>` pelo caminho do arquivo de entrada contendo os dados do problema e `<arquivo_saida>` pelo caminho do arquivo onde os resultados serão salvos.

## Arquivo de Entrada
O arquivo de entrada deve seguir o seguinte formato:
n m k
a1 b1 c1
a2 b2 c2
...
am bm cm


Onde:
- `n`: Número de cidades.
- `m`: Número de voos.
- `k`: Parâmetro k para os caminhos mais curtos.
- `ai bi ci`: Descrição de cada voo, onde `ai` é a cidade de origem, `bi` é a cidade de destino e `ci` é o preço do voo.

## Arquivo de Saída
O programa gera um arquivo de saída contendo os preços dos k caminhos mais baratos, ordenados de acordo com seus preços.

## Estrutura do Programa
O programa foi implementado utilizando a linguagem C e está dividido em módulos para facilitar a manutenção e compreensão do código. As estruturas de dados são alocadas dinamicamente e liberadas após o processamento para evitar vazamentos de memória.


## Testes
O programa foi testado utilizando diferentes conjuntos de dados de entrada para verificar a correção e eficiência da solução. Foram realizadas análises de tempo de execução para avaliar o desempenho do algoritmo em diferentes cenários.

## Referências
1. Thomas H. Cormen. Algoritmos: Teoria e Prática. LTC, 2012.
2. Nivio Ziviani. Projetos de Algoritmos em C e Pascal. 2. ed. São Paulo: Cengage Learning, 2006.
3. Diogo Haruki Kykuta. Comparação de algoritmos para o Problema dos K Menores Caminhos. Dissertação de Mestrado, Instituto de Matemática e Estatística, Universidade de São Paulo, 2018.
4. Jiménez, Víctor M. and Marzal, Andrés. ”A Lazy Version of Eppstein’s K Shortest Paths Algorithm.”

