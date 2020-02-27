// Maquina expendedora
// - referescos
// - monedas
//     1, 5, 10
// - billetes
//     20, 50, 100, 200
// - tres productos
//     12, 17, 23
// - Dar cambio
// - Proceso de llenado
//     tanto de producto
// - Recuperacion de dinero
//     $1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT_VALUE 10000000

#define COST_PA 12
#define COST_PB 17
#define COST_PC 23

#define SELECT_PA   1
#define SELECT_PB   2
#define SELECT_PC   3
#define SELECT_DONE 4

#define IN_COIN_A      1
#define IN_COIN_B      2
#define IN_COIN_C      3
#define IN_BILL_A      4
#define IN_BILL_B      5
#define IN_BILL_C      6
#define IN_BILL_D      7
#define MONEY_RETURN   8

#define INSERT_MONEY   1
#define SELECT_PRODUCT 2
#define CANCEL_OP      3
#define ADMIN          4
#define EXIT_VENDING   5

#define INSERT_PRODUCTS 2
#define GET_MONEY       3
#define GET_PRODUCTS    4
#define ADMIN_DONE      5

#define COST_COIN_A 1
#define COST_COIN_B 5
#define COST_COIN_C 10
#define COST_BILL_A 20
#define COST_BILL_B 50
#define COST_BILL_C 100
#define COST_BILL_D 200

#define clear() printf("\033[H\033[J")

int denominaciones[] = {COST_COIN_A, COST_COIN_B, COST_COIN_C, COST_BILL_A, COST_BILL_B, COST_BILL_C, COST_BILL_D};

typedef struct {
    char pa;
    char pb;
    char pc;
    char coina;
    char coinb;
    char coinc;
    char billa;
    char billb;
    char billc;
    char billd;
} state_t;

int obtener_opcion_menu_principal();
int obtener_opcion_ingresar_pago();
void procesar_ingresar_dinero(state_t *, state_t *, char);
int obtener_opcion_administrar(state_t *);
void procesar_administrar();
int obtener_opcion_seleccionar_producto();
void procesar_seleccionar_producto_compra(state_t *, state_t *);
/* cargar y guardar estado del sistema */
void cargar_estado(state_t *);
void guardar_estado(state_t *);
/* mostrar contenido de la máquina */
void mostrar_productos(state_t *);
void mostrar_dinero(state_t *);
/* calcular */
int calcular_total(state_t *);
/* limpiar estructura */
void limpiar_estado_dinero(state_t *); 
void limpiar_estado_productos(state_t *);
int obtener_confirmacion();
void mostrar_cantidad(state_t *);
void agregar_dinero_estados(state_t *, state_t *);
void quitar_dinero_estados(state_t *, state_t *);
/* lógica de ejecución de compras */
int ejecutar_compra(state_t *, state_t *);
/* lógica para saber el cambio que se dará al cliente */
unsigned char es_pagable(state_t *estado, state_t *estado_int, int costo);
/* calcula el minimo de monedas para dar cambio */
int encontrar_cambio(int num_denom, int cantidad_f, state_t *estado, int **lista, int *elements);
/* mostrar monedas a retornar */
void devolver_dinero();
/* quitar un moneda a la vez del estado indicado */
void quitar_moneda(state_t *s, int moneda);

int main() {
    int en_ejecucion = 1;
    int cantidad_actual = 0;
    state_t estado;
    state_t estado_usuario;
    cargar_estado(&estado);
    limpiar_estado_dinero(&estado_usuario);
    limpiar_estado_productos(&estado_usuario);
    while(1 == en_ejecucion) {
        //clear();
        mostrar_productos(&estado);
        mostrar_cantidad(&estado_usuario);
        switch(obtener_opcion_menu_principal()){
        case INSERT_MONEY:
            procesar_ingresar_dinero(&estado, &estado_usuario, 1);
            break;
        case SELECT_PRODUCT:
            procesar_seleccionar_producto_compra(&estado, &estado_usuario);
            break;
        case CANCEL_OP:
            //procesar_seleccionar_producto_compra(&estado);
            break;
        case ADMIN:
            procesar_administrar(&estado);
            break;
        case EXIT_VENDING:
            guardar_estado(&estado);
            en_ejecucion = 0;
            break;
        default:
            printf("Elegir otra opción. Use 1 - 9\n");
            break;
        }
    }
    return 0;
}

void procesar_administrar(state_t *estado) {
    char en_ejecucion = 1;
    while(1 == en_ejecucion) {
        //clear();
        mostrar_productos(estado);
        mostrar_dinero(estado);
        switch(obtener_opcion_administrar(estado)) {
            case INSERT_MONEY:
                break;
            case INSERT_PRODUCTS:
                break;
            case GET_MONEY:
                break;
            case GET_PRODUCTS:
                break;
            case ADMIN_DONE:
                en_ejecucion = 0;
                break;
            default:
                break;
        }
    }
}

/* procesa las opciones de selección de producto */
void procesar_seleccionar_producto_compra(state_t *estado, state_t *estado_int) {
    char en_ejecucion = 1;
    int producto = 0;
    while (1 == en_ejecucion) {
        //clear();
        mostrar_productos(estado);
        mostrar_cantidad(estado_int);
        producto = obtener_opcion_seleccionar_producto();
        switch(producto){
            case SELECT_PA:
            case SELECT_PB:
            case SELECT_PC:
                if (SELECT_PA == producto) {
                    estado_int->pa = 1;
                } else if (SELECT_PB == producto) {
                    estado_int->pb = 1;
                } else if (SELECT_PC == producto) {
                    estado_int->pc = 1;
                }
                if (obtener_confirmacion() == 1) {
                    if (ejecutar_compra(estado, estado_int) == 1) {
                        en_ejecucion = 0;
                    }
                }
                break;
            case SELECT_DONE:
                en_ejecucion = 0;
                break;
            default:
                break;
        }
    }
}

/* lógica para el ingreso de dinero del cliente y el admin */
void procesar_ingresar_dinero(state_t *estado, state_t *estado_int, char es_cliente) {
    char en_ejecucion = 1;
    state_t estado_local;
    if (!estado) return;
    limpiar_estado_dinero(&estado_local);
    agregar_dinero_estados(&estado_local, estado_int);
    limpiar_estado_dinero(estado_int);
    while(1 == en_ejecucion) {
        //clear();
        if (1 == es_cliente) {
            mostrar_productos(estado);
        }
        mostrar_cantidad(&estado_local);
        switch(obtener_opcion_ingresar_pago()) {
            case IN_COIN_A:
                estado_local.coina++;
                break;
            case IN_COIN_B:
                estado_local.coinb++;
                break;
            case IN_COIN_C:
                estado_local.coinc++;
                break;
            case IN_BILL_A:
                estado_local.billa++;
                break;
            case IN_BILL_B:
                estado_local.billb++;
                break;
            case IN_BILL_C:
                estado_local.billc++;
                break;
            case IN_BILL_D:
                estado_local.billd++;
                break;
            case MONEY_RETURN:
                agregar_dinero_estados(estado_int, &estado_local);
                en_ejecucion = 0;
                break;
            default:
                break;
        }
    }
}

/* suma dinero de un estado 2 a un estado 1 */
void agregar_dinero_estados(state_t *estado1, state_t *estado2) {
    estado1->coina += estado2->coina;
    estado1->coinb += estado2->coinb;
    estado1->coinc += estado2->coinc;
    estado1->billa += estado2->billa;
    estado1->billb += estado2->billb;
    estado1->billc += estado2->billc;
    estado1->billd += estado2->billd;
}

/* quitar productos de un estado 2 a un estado 1 */
void quitar_producto_estados(state_t *estado1, state_t *estado2) {
    estado1->pa -= estado2->pa;
    estado1->pb -= estado2->pb;
    estado1->pc -= estado2->pc;
}

/* confirma la opción del usuario */
int obtener_confirmacion() {
    int status = 0;
    char tmp = 0;
    int menu = 0;
    printf("Está seguro de su elección? (1 para Sí/0 para No): ");
    status = scanf("%d", &menu);
    while(status != 1 || (menu > 4) || (menu < 1)){
        while((tmp = getchar()) != EOF && tmp != '\n');
        printf("Entrada inválida !!, Está seguro de su elección? (1 para Sí/0 para No): ");
        status = scanf("%d", &menu);
    }
    return menu;

}

/* muestra los productos con precio y existencia */
void mostrar_productos(state_t *estado) {
    if (!estado) return;
    printf("============== Productos ===============\n");
    printf("| Producto\tExistencia\tPrecio |\n");
    printf("| A\t\t%d\t\t$%0.2f |\n", estado->pa, (float)COST_PA);
    printf("| B\t\t%d\t\t$%0.2f |\n", estado->pb, (float)COST_PB);
    printf("| C\t\t%d\t\t$%0.2f |\n", estado->pc, (float)COST_PC);
    printf("========================================\n");
}

/* muestra el dinero en un estado */
void mostrar_dinero(state_t *estado) {
    if (!estado) return;
    int total = 0;
    total = calcular_total(estado);
    printf("========== Dinero ==========\n");
    printf("| Tipo\t\tExistencia |\n");
    printf("| Moneda $%0.2f\t\t%d |\n", (float)COST_COIN_A, estado->coina);
    printf("| Moneda $%0.2f\t\t%d |\n", (float)COST_COIN_B, estado->coinb);
    printf("| Moneda $%0.2f\t\t%d |\n", (float)COST_COIN_C, estado->coinc);
    printf("| Billete $%0.2f\t\t%d |\n", (float)COST_BILL_A, estado->billa);
    printf("| Billete $%0.2f\t\t%d |\n", (float)COST_BILL_B, estado->billb);
    printf("| Billete $%0.2f\t\t%d |\n", (float)COST_BILL_C, estado->billc);
    printf("| Billete $%0.2f\t\t%d |\n", (float)COST_BILL_D, estado->billd);
    printf("============================\n");
    printf("Total: %0.2f\n", (float)total);
    printf("============================\n");
}

/* retorna el total de dinero en un estado */
int calcular_total(state_t *estado) {
    int total = 0;
    total += COST_COIN_A * estado->coina;
    total += COST_COIN_B * estado->coinb;
    total += COST_COIN_C * estado->coinc;
    total += COST_BILL_A * estado->billa;
    total += COST_BILL_B * estado->billb;
    total += COST_BILL_C * estado->billc;
    total += COST_BILL_D * estado->billd;
    return total;
}

void mostrar_cantidad(state_t *estado) {
    printf("----------------------------\n");
    printf("Cantidad Ingresada: %0.2f\n", (float)calcular_total(estado));
    printf("----------------------------\n");
}

int obtener_opcion_menu_principal() {
    int status = 0;
    char tmp = 0;
    int menu = 0;
    printf("====== Menú Principal ======\n");
    printf("1. Ingresar Dinero\n");
    printf("2. Elegir Producto\n");
    printf("3. Cancelar Compra\n");
    printf("4. Administrar Maquina\n");
    printf("5. Apagar\n\n");
    printf("Elegir opción: ");
    status = scanf("%d", &menu);
    while(status != 1 || (menu > 5) || (menu < 1)){
        while((tmp = getchar()) != EOF && tmp != '\n');
        printf("# Entrada inválida, elija otra opción del menú: ");
        status = scanf("%d", &menu);
    }
    return menu;
}

int obtener_opcion_seleccionar_producto() {
    int status = 0;
    char tmp = 0;
    int menu = 0;
    printf("=== Seleccionar Producto ===\n");
    printf("1. Producto A\n");
    printf("2. Producto B\n");
    printf("3. Producto C\n");
    printf("4. Regresar\n\n");
    printf("Elegir opción: ");
    status = scanf("%d", &menu);
    while(status != 1 || (menu > 4) || (menu < 1)){
        while((tmp = getchar()) != EOF && tmp != '\n');
        printf("# Entrada inválida, elija otra opción del menú: ");
        status = scanf("%d", &menu);
    }
    return menu;
}

int obtener_opcion_administrar(state_t *estado) {
    int status = 0;
    char tmp = 0;
    int menu = 0;
    printf("\n===== Menú Administrar =====\n");
    printf("1. Ingresar Dinero\n");
    printf("2. Ingresar Producto\n");
    printf("3. Recuperar Dinero\n");
    printf("4. Recuperar Producto\n");
    printf("5. Salir\n\n");
    printf("Elegir opción: ");
    status = scanf("%d", &menu);
    while(status != 1 || (menu > 5) || (menu < 1)){
        while((tmp = getchar()) != EOF && tmp != '\n');
        printf("# Entrada inválida, elija otra opción del menú: ");
        status = scanf("%d", &menu);
    }
    return menu;
}

/* muestra los tipos de monedas y obtiene la opción del cliente */
int obtener_opcion_ingresar_pago() {
    int cantidad = 0;
    int status = 0;
    int menu = 0;
    char tmp;
    printf("====== Ingresar Dinero =====\n");
    printf("1.  Moneda  $%0.2f\n",(float)COST_COIN_A);
    printf("2.  Moneda  $%0.2f\n",(float)COST_COIN_B);
    printf("3.  Moneda  $%0.2f\n",(float)COST_COIN_C);
    printf("4.  Billete $%0.2f\n",(float)COST_BILL_A);
    printf("5.  Billete $%0.2f\n",(float)COST_BILL_B);
    printf("6.  Billete $%0.2f\n",(float)COST_BILL_C);
    printf("7.  Billete $%0.2f\n",(float)COST_BILL_D);
    printf("8.  Regresar al menú principal\n\n");
    printf("Elegir Opcion: ");
    status = scanf("%d", &menu);
    while(status != 1 || (menu > 8) || (menu < 1)){
        while((tmp = getchar()) != EOF && tmp != '\n');
        printf("Entrada inválida !!, elija otra opción del menú: ");
        status = scanf("%d", &menu);
    }
    return menu;
}

/* realiza la lógica de compra de producto y actualización del estado */
int ejecutar_compra(state_t *estado, state_t *estado_int) {
    int ret = 0, costo = 0;
    if (!estado_int) return 0;

    /* verifica qué producto se está tratando de comprar */
    if (1 == estado_int->pa) {
        costo = COST_PA;
    } else if (1 == estado_int->pb) {
        costo = COST_PB;
    } else if (1 == estado_int->pc) {
        costo = COST_PC;
    }
    /* verifica si se puede pagar el producto con el dinero ingresado */
    if (es_pagable(estado, estado_int, costo) == 1) {
        ret = 1;
    }
    return ret;
}

/* verifica si la compra se puede realizar,
 * identifica el cambio a retornar
 */
unsigned char es_pagable(state_t *estado, state_t *estado_int, int costo) {
    unsigned char ret = 0x00;
    int cambio = 0;
    int result = 0;
    state_t estado_local;
    int m = sizeof(denominaciones) / sizeof(denominaciones[0]);
    int total = calcular_total(estado_int);
    int *l_cambio = NULL;
    int l_csize = 0;
    int cur_amt = 0, contador = 0;

    limpiar_estado_dinero(&estado_local);
    if (total >= costo) {
        cambio = total - costo;
        agregar_dinero_estados(&estado_local, estado);
        agregar_dinero_estados(&estado_local, estado_int);
        result = encontrar_cambio(m, cambio, &estado_local, &l_cambio, &l_csize);
        if (result != 0 && result != MAX_INT_VALUE) {
            agregar_dinero_estados(estado, estado_int);
            /*print the chosen denominations to get the final amount*/
            cur_amt = cambio;
            printf("Su cambio.\n");
            while (cur_amt > 0 && (contador < l_csize)) {
                if (l_cambio[cur_amt] > COST_COIN_C) {
                    printf("Billete de: $%d \n", l_cambio[cur_amt]);
                } else {
                    printf("Moneda de: $%d \n", l_cambio[cur_amt]);
                }
                quitar_moneda(estado, l_cambio[cur_amt]);
                cur_amt = cur_amt - l_cambio[cur_amt];
                contador = contador + 1;
            }
            /* limpiar el estado actual y quitar el producto */
            if (l_cambio) {
                free(l_cambio);
            }
            quitar_producto_estados(estado, estado_int); 
            limpiar_estado_dinero(estado_int);
            limpiar_estado_productos(estado_int);
            ret = 0x01;
        } else {
            printf("No es posible dar cambio. Ingrese cantidad exacta.\n");
            devolver_dinero();
        }
    } else {
        printf("No se puede realizar la compra. Ingrese suficiente dinero.\n");
    }
    return ret;
}

/* quitar moneda del estado general, después de dar cambio */
void quitar_moneda(state_t *s, int moneda) {
    if (moneda == COST_COIN_A) s->coina--;
    if (moneda == COST_COIN_B) s->coinb--;
    if (moneda == COST_COIN_C) s->coinc--;
    if (moneda == COST_BILL_A) s->billa--;
    if (moneda == COST_BILL_B) s->billb--;
    if (moneda == COST_BILL_C) s->billc--;
    if (moneda == COST_BILL_D) s->billd--;
}

/* carga la información de estado de la máquina desde memoria no volátil */
void cargar_estado(state_t *estado_vending) {
    FILE* archivo = fopen("estado.dat", "r");
    int cantidad;
    char linea[1024]; 
    char* lexema1;
    char* lexema2;

    while(fgets(linea,sizeof(linea),archivo) !=  NULL) {
        lexema1 = strtok(linea, ",\n");
        lexema2 = strtok(NULL, ",\n");
        cantidad = atoi(lexema2);
        //printf("%s - %d\n", lexema1, cantidad);
        //getchar();
        if (strcmp("coina", lexema1) == 0) {
            estado_vending->coina = cantidad;
        } else if(strcmp("coinb", lexema1) == 0) {
            estado_vending->coinb = cantidad;
        } else if(strcmp("coinc", lexema1) == 0) {
            estado_vending->coinc = cantidad;
        } else if(strcmp("billa", lexema1) == 0) {
            estado_vending->billa = cantidad;
        } else if(strcmp("billb", lexema1) == 0) {
            estado_vending->billb = cantidad;
        } else if(strcmp("billc", lexema1) == 0) {
            estado_vending->billc = cantidad;
        } else if(strcmp("billd", lexema1) == 0) {
            estado_vending->billd = cantidad;
        } else if(strcmp("producta", lexema1) == 0) {
            estado_vending->pa = cantidad;
        } else if(strcmp("productb", lexema1) == 0) {
            estado_vending->pb = cantidad;
        } else if(strcmp("productc", lexema1) == 0) {
            estado_vending->pc = cantidad;
        }
    }
    if(archivo) fclose(archivo);
}

void guardar_estado(state_t *estado) {
    FILE *fileName;
    fileName = fopen("estado.dat","w");
    fprintf(fileName, "%s,%d\n","coina",estado->coina);
    fprintf(fileName, "%s,%d\n","coinb",estado->coinb);
    fprintf(fileName, "%s,%d\n","coinc",estado->coinc);
    fprintf(fileName, "%s,%d\n","billa",estado->billa);
    fprintf(fileName, "%s,%d\n","billb",estado->billb);
    fprintf(fileName, "%s,%d\n","billc",estado->billc);
    fprintf(fileName, "%s,%d\n","billd",estado->billd);
    fprintf(fileName, "%s,%d\n","producta",estado->pa);
    fprintf(fileName, "%s,%d\n","productb",estado->pb);   
    fprintf(fileName, "%s,%d","productc",estado->pc);
    fclose(fileName);
}

/* se asignan los atributos de una estructura de tipo state_t a 0 para dinero */
void limpiar_estado_dinero(state_t *estado) {
    if (!estado) return;
    estado->coina = 0;
    estado->coinb = 0;
    estado->coinc = 0;
    estado->billa = 0;
    estado->billb = 0;
    estado->billc = 0;
    estado->billd = 0;
}

/* se asignan los atributos de una estructura de tipo state_t a 0 para productos */
void limpiar_estado_productos(state_t *estado) {
    if (!estado) return;
    estado->pa = 0;
    estado->pb = 0;
    estado->pc = 0;
}

int encontrar_cambio(int num_denom, int cantidad_f, state_t *estado, int **l_cambio, int *l_csize) {
    /*Array for storing the minimum number of coins for an amount*/
    int *min_num_coins = (int*) malloc( (cantidad_f+1) * sizeof(int));
     
    /*Array for storing the coin denomination chosen for an amount*/
    int *chosen_denom = (int*) malloc( (cantidad_f+1) * sizeof(int));
    int i, cur_amt, smaller_amt, result;
         
    min_num_coins[0] = 0;
    for (cur_amt = 1; cur_amt <= cantidad_f; cur_amt++) {
        min_num_coins[cur_amt] = MAX_INT_VALUE;
        for (i = 0; i < num_denom; ++i) {
            if (denominaciones[i] <= cur_amt) {
                smaller_amt = cur_amt - denominaciones[i];
                if ((1 + min_num_coins[smaller_amt]) < min_num_coins[cur_amt]) {
                    min_num_coins[cur_amt] = 1 + min_num_coins[smaller_amt];
                    chosen_denom[cur_amt] = denominaciones[i];
                }
            }
        }
    }
 
    result = min_num_coins[cantidad_f];
    //printf("Minimum number of coins = %d\n", result);
 
    /*print the chosen denominations to get the final amount*/
    //cur_amt = cantidad_f;
    //while (cur_amt > 0) {
    //    printf("%d ", chosen_denom[cur_amt]);
    //    cur_amt = cur_amt - chosen_denom[cur_amt];
    //}
    //printf(" = %d\n", cantidad_f);
    free(min_num_coins);
    if (l_cambio) {
        *l_cambio = chosen_denom;
    }
    if (l_csize) {
        *l_csize = cantidad_f + 1;
    }
    //free(chosen_denom);
    return result;
}


void devolver_dinero() {

}
