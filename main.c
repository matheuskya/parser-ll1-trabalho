
#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];   
int top = -1;   

void push(char symbol) {
    stack[++top] = symbol;
}

char pop() {
    return stack[top--];
}

int isTerminal(char c) {
    return (c == 'a' || c == 'b' || c == '$');
}

void parse(char* input) {
    int i = 0;
    char lookahead = input[i];

    top = -1;

    push('$');
    push('S');

    while (top >= 0) {

        char X = stack[top];

        printf("pilha topo=%c lookahead: %c\n", X, lookahead);

        if (X == lookahead && X == '$') {
            printf("aceito: fim da entrada.\n");
            pop();
            break;
        }

        if (isTerminal(X)) {
            if (X == lookahead) {
                printf("casando terminal '%c'\n", X);
                pop();
                lookahead = input[++i];
            } else {
                printf("Erro: esperado '%c', encontrado '%c'\n", X, lookahead);
                return;
            }
        } 
        else if (X == 'S') {

            if (lookahead == 'a') {
                printf("Regra usada: S -> aA\n");
                pop();
                push('A');
                push('a');
            } else {
                printf("Erro: esperado 'a' no início\n");
                return;
            }

        } 
        else if (X == 'A') {

            if (lookahead == 'b') {
                printf("regra usada: A->b\n");
                pop();
                push('b');
            } 
            //aqui, vazio eh representado por v, o simbolo de epsilon causa alguns erros esquisitos
            else if (lookahead == '$') {
                printf("regra usada: A-> v\n");
                pop();
            } 
            else {
                printf("erro: esperado 'b' ou vazia em A\n");
                return;
            }

        }
        else {
            printf("rrro: simbolo desconhecido '%c'\n", X);
            return;
        }
    }

    if (lookahead == '$')
        printf("palavra aceita!\n");
    else
        printf("rrro: entrada restante nao consumida.\n");
}
int main() {
    char input[MAX];

    printf("digite a palavra: ");
    scanf("%s", input);

    strcat(input, "$");

    parse(input);

    return 0;
}
