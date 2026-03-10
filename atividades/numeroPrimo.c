#include <stdio.h>

int main() {
    int n, i;
    int primo = 1; 

    printf("Digite um número inteiro: ");
    scanf("%d", &n);

    if (n <= 1) {
        primo = 0; // Números menores ou iguais a 1 não são primos
    } else {
        for (i = 2; i <= n / 2; i++) {
            if (n % i == 0) {
                primo = 0; // Encontrou um divisor, então não é primo
                break;
            }
        }
    }

    if (primo) {
        printf("%d é um número primo.\n", n);
    } else {
        printf("%d não é um número primo.\n", n);
    }

    return 0;
}