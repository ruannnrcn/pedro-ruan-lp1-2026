#include <stdio.h>

int main() {
    int n;
    int fatorial = 1;

    printf("Digite um número inteiro: ");
    scanf("%d", &n);

    for (int i = n; i >= 1; i--) {
        fatorial *= i;
    }

    printf("O fatorial é %d\n", fatorial);

    return 0;
}