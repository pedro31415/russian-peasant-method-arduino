#include <msp430g2553.h>

// Função para implementar o algoritmo de Multiplicação do Campônez Russo
unsigned int russianPeasantMultiplication(unsigned int a, unsigned int b) {
    unsigned int result = 0; // Inicializar o resultado

    while (b > 0) {
        // Se b é ímpar, adicione a ao resultado
        if (b & 1) {
            result += a;
        }

        // Duplique a e divida b por 2
        a <<= 1;
        b >>= 1;
    }

    return result;
}

// função de atraso 
void delay_ms(unsigned ms){
    while (ms--)
    {
        __delay_cycles(1000); // 1 ms delay
    } 
}

void blink(unsigned int times) {
    for(unsigned int i = 0; i < times; i++){
        P1OUT ^= 0x01;
        delay_ms(500);
        P1OUT ^= 0X01;
        delay_ms(500);
    }
    delay_ms(2000);
}

void main(void) {
    // Parar o watchdog timer para evitar reset automático
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= 0x01;

    // Variáveis para armazenar os números a serem multiplicados e o resultado
    unsigned int num1 = 37; // Exemplo de número 1
    unsigned int num2 = 24; // Exemplo de número 2
    unsigned int result;

    // Calcular a multiplicação usando o algoritmo do Campônez Russo
    result = russianPeasantMultiplication(num1, num2);

    // O resultado pode ser utilizado conforme necessário
    // Aqui apenas mantemos a CPU em loop infinito
    while(1){
        blink(result / 100); // Piscar centenas
        blink((result / 10) % 10); // Piscar dezenas
        blink(result % 10); // Piscar unidades
    };
}
