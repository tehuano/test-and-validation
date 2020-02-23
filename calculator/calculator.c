#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SUMA             1
#define RESTA            2
#define MULTIPLICACION   3
#define DIVISION         4
#define EXPONENTE        5
#define RAIZ_CUADRADA    6
#define TANTO_POR_CIENTO 7
#define SALIR            8

int obtener_opcion();
float get_number();

void realizar_suma();
void realizar_resta();
void realizar_multiplicacion();
void realizar_division();
void realizar_exponente();
void realizar_raiz_cuadrada();
void realizar_porcentaje();

int main() {
    int menu;
    float a, b, result;
    char operar = 1;
    while (1 == operar) {
        menu = obtener_opcion();
        switch(menu) {
            case SUMA:
                realizar_suma();
                break;
            case RESTA:
                realizar_resta();
                break;
            case MULTIPLICACION:
                realizar_multiplicacion();
                break;
            case DIVISION:
                realizar_division();
                break;
            case EXPONENTE:
                realizar_exponente();
                break;
            case RAIZ_CUADRADA:
                realizar_raiz_cuadrada();
                break;
            case TANTO_POR_CIENTO:
                realizar_porcentaje();
                break;
            case SALIR:
                operar = 0;
                break;
            default:
                printf("Eleccion incorrecta. Use 1 - 8\n");
                break;
        }
    }
    return 0;
}

float get_number() {
    float number;
    int status;
    char temp;
    status = scanf("%f", &number);
    while(status != 1){
        while((temp = getchar()) != EOF && temp != '\n');
        printf("#### Entrada inválida, ingrese un número: ");
        status = scanf("%f", &number);
    }
    return number;
}

void realizar_suma() {
    float a, b, result;
    printf("Eleccion es Suma\n\n");
    printf("Introducir el primer número: ");
    a = get_number();
    printf("Introducir el segundo número: ");
    b = get_number();
    printf("\n");
    result = a + b;
    printf("%.2f + %.2f = %.2f\n\n", a, b, result);
}

void realizar_resta() {
    float a, b, result;
    printf("Eleccion es Resta\n\n");
    printf("Introducir el primer número: ");
    a = get_number();
    printf("Introducir el segundo número: ");
    b = get_number();
    printf("\n");
    result = a - b;
    printf("%.2f - %.2f = %.2f\n", a, b, result);
}

void realizar_multiplicacion() {
    float a, b, result;
    printf("Eleccion es Multiplicación\n\n");
    printf("Introducir el primer número: ");
    a = get_number();
    printf("Introducir el segundo número: ");
    b = get_number();
    printf("\n");
    result = a * b;
    printf("%.2f * %.2f = %.2f\n\n", a, b, result);
}

void realizar_division() {
    float a, b, result;
    printf("Eleccion es División\n\n");
    printf("Introducir el primer número: ");
    a = get_number();
    printf("Introducir el segundo número: ");
    b = get_number();
    printf("\n");
    result = a / b;
    printf("%.2f / %.2f = %.2f\n\n", a, b, result);
}

void realizar_exponente() {
    float a, b, result;
    printf("Eleccion es Exponente\n\n");
    printf("Introducir el número: ");
    a = get_number();
    printf("Introducir el exponente: ");
    b = get_number();
    printf("\n");
    result = pow(a,b);
    printf("%.2f elevado a la potencia de %.2f es %.2f\n\n", a, b, result);
}

void realizar_raiz_cuadrada() {
    float a, b, result;
    printf("Eleccion es Raíz cuadrada\n\n");
    printf("Introducir el número: ");
    a = get_number();
    printf("\n");
    result = sqrt(a);
    printf("La raíz cuadrada de %.2f es %.2f\n", a, result);
}

void realizar_porcentaje() {
    float a, b, result;
    printf("Eleccion Tanto por ciento\n\n");
    printf("Introducir el número: ");
    a = get_number();
    printf("Introducir el porcentaje a calcular: ");
    b = get_number();
    printf("\n");
    result = a * (b/100);
    printf("El %.2f por ciento de %.2f es %.2f\n\n", b, a, result);
}

int obtener_opcion(){
    int menu;
    int status;
    char temp;
    printf("##      MENÚ      ##\n");
    printf("1. Suma\n");
    printf("2. Resta\n");
    printf("3. Multiplicación\n");
    printf("4. División\n");
    printf("5. Exponente\n");
    printf("6. Raiz Cuadrada\n");
    printf("7. Tanto por ciento\n");
    printf("8. Salir\n");
    printf("Elija una de las opciones del menú: ");
    status = scanf("%d", &menu);
    while(status != 1){
        while((temp = getchar()) != EOF && temp != '\n');
        printf("#### Entrada inválida, elija otra opción del menú: ");
        status = scanf("%d", &menu);
    }
    printf("\n");
    return menu;
}
