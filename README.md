# README #
** Visão Geral**
O projeto bares é um programa voltado a avaliação de expressões numéricas
o projeto foi desenvilvido como parte da avaliação das disciplinas de estrura de dados I e Linguagem de programação I
ambas ministradas pelo professor Selan Rodrigues dos Santos pela universidade federal do rio grande do norte (UFRN)

### Membros da equipe ###
* Igor A. Brandão
* Leandro Antonio F. Silva

### Como compilar ###
* Use o makefile digitando o comando **'make'** pelo terminal, após ter navegado para a pasta do projeto.

### COMO EXECUTAR O PROGRAMA ###
Exitem duas formas de se rodar o programa a primeira é executando o programa sem parametros, então ele pedira
ao usuário que digite sua propria expressão, a segunda forma é passando por parametro o arquivo de entrada
exemplos:\n
* ./bin/bares\n
* ./bin/bares input.dat

### LISTA DOS ERROS TRATADOS ###
Os erros tratados pelo programa são os seguintes:

Erro 2 - Falta operando;\n
Erro 3 - Operando inválido;\n
Erro 4 - Operador inválido;\n
Erro 6 - Fechamento de escopo inválido;\n
Erro 7 - Escopo aberto;\n
Erro 8 - Divisão por zero.

### PROBLEMAS E LIMITAÇÕES ###
Tivemos dificuldades em adaptar as classes customizadas Stack e Queue
para funcionar em harmonia com o projeto Bares sem o problema de segmentation fault.