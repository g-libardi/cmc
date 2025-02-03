# Como compilar

Para compilar o projeto, é necessário ter o `bison` instalado.

Para compilar facilmente, basta executar o script `build.sh` na raiz do projeto.

```bash
$ ./build.sh
```

Ou, se preferir, pode compilar manualmente com os comandos abaixo.

```bash

rm -rf build/*
mkdir -p build/src

gcc -c src/lexer.c -Iinclude -o build/lexer.o
gcc -c src/scanner.c -Iinclude -o build/scanner.o
bison -d src/parser.y -o build/src/parser.c
rm include/parser.h
mv build/src/parser.h include/parser.h
gcc -c build/src/parser.c -Iinclude -o build/parser.o
gcc -c src/main.c -Iinclude -o build/main.o

gcc build/main.o build/scanner.o build/lexer.o build/parser.o -o build/cmc
```

# Como executar
Para executar o programa, basta executar o arquivo `build/cmc` gerado, com a flag `-l|L <arquivo>` para rodar o lexer ou `-p|P <arquivo>` para rodar o parser.

```bash
$ ./build/cmc -l|L <arquivo>
$ ./build/cmc -p|P <arquivo>
```

# Exemplos
Existem arquivos de teste na pasta 'examples/' que podem ser usados para testar o programa.

# Requisitos
O projeto não foi concluido. Foi feito o Lexer e o Parser, no entanto não foi gerada a AST e nem a análise semântica. O projeto foi feito em C, o Lexer foi implementado com uma estratégia baseada em tabelas de transição, com o auxílio de um script desenvolvido para ler um csv representando os estados e gerar o código C da tabela. O Parser foi implementado com o auxílio do Bison, que gera o código C- a partir da gramática definida na bibliografia da disciplina de Kenneth C. Louden.

# Documentação
A documentação foi gerada com auxílio do Doxygen, e pode ser acessada pelo navegador ao abrir o arquivo `docs/html/index.html`.

