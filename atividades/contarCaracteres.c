#include <stdio.h>

int main () {
    char str[100];
    int i;

    printf("Digite uma string: ");
    fgets(str, sizeof(str), stdin);

    // Contar o número de caracteres
    for (i = 0; str[i] != '\0'; i++);
    printf("Número de caracteres: %d\n", i - 1);

    return 0;
}