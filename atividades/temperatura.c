#include <stdio.h>

int main () {
    //Declaração de variáveis
    float celsius, fahrenheit;

    printf("Digite a temperatura em Celsius: ");
    scanf("%f", &celsius);

    printf("Digite a temperatura em Firenheit: ");
    scanf("%f", &fahrenheit);

    //Cálculo das conversões
    fahrenheit = celsius * (9.0 / 5.0) + 32.0;
    celsius = (fahrenheit - 32.0) * (5.0 / 9.0);

    //Saída de dados
    printf("Temperatura em Fahrenheit: %.1f °F\n", fahrenheit);
    printf("Temperatura em Celsius: %.1f °C\n", celsius);

    return 0;
}