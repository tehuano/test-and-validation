// Maquina expendedora
// - referescos
// - monedas
//     1 (100), 5 (50), 10 (20)
// - billetes
//     20, 50, 100, 200 - 20 each
// - tres productos
//     12, 17, 23 - 10 each
// - Dar cambio
// - Proceso de llenado
//     tanto de producto
// - Recuperacion de dinero
//     $1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT_VALUE 10000000

#define ZERO 0
#define UNO  1
#define DIEZ 10
#define DOS  2
#define TRES 3
#define DIEZ 10
#define CINCUENTA 50
#define VEINTE 20
#define CIEN 100

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
void procesar_ingresar_dinero(state_t *, state_t *, int);
int obtener_opcion_administrar(state_t *);
void procesar_administrar(state_t *);
int obtener_opcion_seleccionar_producto();
void procesar_seleccionar_producto(state_t *, state_t *, int);
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
void procesar_cancelar_compra();
/* quitar un moneda a la vez del estado indicado */
void quitar_moneda(state_t *s, int moneda);
/* identifica si la cantidad está en rango para dinero */
int en_rango(int x, int max);
/* mostrar cambio a los clientes */
void mostrar_cambio(state_t *estado, int cambio, int *l_cambio, int l_csize, int flag); 
/* detiene momentaneamente el programa */
void presionar_tecla_para_continuar();
/* calcular la cantidad mínima de mownedas si existe */
void cargar_existencia(state_t *s, int ex[]);

int main() {
    int en_ejecucion = 1;
    int cantidad_actual = ZERO;
    state_t estado;
    state_t estado_usuario;
    cargar_estado(&estado);
    limpiar_estado_dinero(&estado_usuario);
    limpiar_estado_productos(&estado_usuario);
    while(1 == en_ejecucion) {
        clear();
        mostrar_productos(&estado);
        mostrar_cantidad(&estado_usuario);
        switch(obtener_opcion_menu_principal()){
        case INSERT_MONEY:
            procesar_ingresar_dinero(&estado, &estado_usuario, UNO);
            break;
        case SELECT_PRODUCT:
            procesar_seleccionar_producto(&estado, &estado_usuario, UNO);
            break;
        case CANCEL_OP:
            procesar_cancelar_compra(&estado, &estado_usuario);
            break;
        case ADMIN:
            procesar_administrar(&estado);
            break;
        case EXIT_VENDING:
            guardar_estado(&estado);
            en_ejecucion = ZERO;
            break;
        default:
            printf("Elegir otra opción. Use 1 - 9\n");
            presionar_tecla_para_continuar();
            break;
        }
    }
    return ZERO;
}

/* administrar el contenido de la máquina, monedas y productos */
void procesar_administrar(state_t *estado) {
    char en_ejecucion = 1;
    state_t estado_admin;
    limpiar_estado_dinero(&estado_admin);    
    limpiar_estado_productos(&estado_admin);    
    while(1 == en_ejecucion) {
        clear();
        mostrar_productos(estado);
        mostrar_dinero(estado);
        switch(obtener_opcion_administrar(estado)) {
            case INSERT_MONEY:
                procesar_ingresar_dinero(estado, &estado_admin, DOS);
                break;
            case INSERT_PRODUCTS:
                procesar_seleccionar_producto(estado, &estado_admin, DOS);
                break;
            case GET_MONEY:
                procesar_ingresar_dinero(estado, &estado_admin, TRES);
                break;
            case GET_PRODUCTS:
                procesar_seleccionar_producto(estado, &estado_admin, TRES);
                break;
            case ADMIN_DONE:
                en_ejecucion = ZERO;
                break;
            default:
                break;
        }
    }
}

/* procesa las opciones de selección de producto */
void procesar_seleccionar_producto(state_t *estado, state_t *estado_int, int modo) {
    char en_ejecucion = 1;
    int producto = ZERO;
    int delta = 1;
    state_t *estado_tmp = NULL;

    estado_tmp = estado_int;
    if (TRES == modo || DOS == modo) {
        estado_tmp = estado;
    }
    if (TRES == modo) {
        delta = -1;
    }
    while (1 == en_ejecucion) {
        clear();
        if (UNO == modo) {
            mostrar_productos(estado);
            mostrar_cantidad(estado_tmp);
        } else if (TRES == modo || DOS == modo) {
            mostrar_productos(estado);
        }
        producto = obtener_opcion_seleccionar_producto();
        switch(producto){
            case SELECT_PA:
                if ((modo != UNO) && (en_rango(estado_tmp->pa + delta, DIEZ) == 1)) {
                    estado_tmp->pa += delta;
                } else if ((UNO == modo) && (en_rango(estado->pa + estado_tmp->pa + delta, DIEZ) == 1)) {
                    estado_tmp->pa += delta;
                    if (obtener_confirmacion() == 1) {
                        if (ejecutar_compra(estado, estado_tmp) == 1) {
                            en_ejecucion = ZERO;
                        }
                    }
                } else {
                    printf("Cantidad fuera de rango para Producto A.\n");
                    presionar_tecla_para_continuar();
                }
                break;
            case SELECT_PB:
                if ((modo != UNO) && (en_rango(estado_tmp->pb + delta, DIEZ) == 1)) {
                    estado_tmp->pb += delta;
                } else if ((UNO == modo) && (en_rango(estado->pb + estado_tmp->pb + delta, DIEZ) == 1)) {
                    estado_tmp->pb += delta;
                    if (obtener_confirmacion() == 1) {
                        if (ejecutar_compra(estado, estado_tmp) == 1) {
                            en_ejecucion = ZERO;
                        }
                    }
                } else {
                    printf("Cantidad fuera de rango para Producto B.\n");
                    presionar_tecla_para_continuar();
                }
                break;
            case SELECT_PC:
                if ((modo != UNO) && (en_rango(estado_tmp->pc + delta, DIEZ) == 1)) {
                    estado_tmp->pc += delta;
                } else if ((UNO == modo) && (en_rango(estado->pc + estado_tmp->pc + delta, DIEZ) == 1)) {
                    estado_tmp->pc += delta;
                    if (obtener_confirmacion() == 1) {
                        if (ejecutar_compra(estado, estado_tmp) == 1) {
                            en_ejecucion = ZERO;
                        }
                    }
                } else {
                    printf("Cantidad fuera de rango para Producto C.\n");
                    presionar_tecla_para_continuar();
                }
                break;
            case SELECT_DONE:
                en_ejecucion = ZERO;
                break;
            default:
                break;
        }
    }
}

/* lógica para el ingreso de dinero del cliente y el admin */
void procesar_ingresar_dinero(state_t *estado, state_t *estado_int, int modo) {
    char en_ejecucion = 1;
    state_t estado_local;
    state_t *estado_tmp;
    int delta = UNO;

    if (!estado || !estado_int) return;
    if (TRES == modo) {
        delta = -1;
    }
    estado_tmp = estado;
    limpiar_estado_dinero(&estado_local);
    if (UNO == modo) {
        estado_tmp = &estado_local;
        agregar_dinero_estados(estado_tmp, estado_int);
        limpiar_estado_dinero(estado_int);
    }
    while(1 == en_ejecucion) {
        clear();
        if (UNO == modo) {
            mostrar_productos(estado);
            mostrar_cantidad(&estado_local);
        } else if (TRES == modo || DOS == modo) {
            mostrar_dinero(estado);
        }
        switch(obtener_opcion_ingresar_pago()) {
            case IN_COIN_A:
                if ((modo != UNO) && (en_rango(estado_tmp->coina + delta, CIEN) == 1)) {
                    estado_tmp->coina += delta;
                } else if ((UNO == modo) && (en_rango(estado->coina + estado_tmp->coina + delta, CIEN) == 1)) {
                    estado_tmp->coina += delta;
                } else {
                    printf("Cantidad fuera de rango para monedas tipo A.\n");
                    presionar_tecla_para_continuar();
                }
                break;
            case IN_COIN_B:
                if ((modo != UNO) && (en_rango(estado_tmp->coinb + delta, CINCUENTA) == 1)) {
                    estado_tmp->coinb += delta;
                } else if ((UNO == modo) && (en_rango(estado->coinb + estado_tmp->coinb + delta, CINCUENTA) == 1)) {
                    estado_tmp->coinb += delta;
                } else {
                    printf("Cantidad fuera de rango para monedas tipo B.\n");
                    presionar_tecla_para_continuar();
                }
                break;
            case IN_COIN_C:
                if ((modo != UNO) && (en_rango(estado_tmp->coinc + delta, VEINTE) == 1)) {
                    estado_tmp->coinc += delta;
                } else if ((UNO == modo) && (en_rango(estado->coinc + estado_tmp->coinc + delta, VEINTE) == 1)) {
                    estado_tmp->coinc += delta;
                } else {
                    printf("Cantidad fuera de rango para monedas tipo C.\n");
                    presionar_tecla_para_continuar();
                }
                break;
            case IN_BILL_A:
                if ((modo != UNO) && (en_rango(estado_tmp->billa + delta, VEINTE) == 1)) {
                    estado_tmp->billa += delta;
                } else if ((UNO == modo) && (en_rango(estado->billa + estado_tmp->billa + delta, VEINTE) == 1)) {
                    estado_tmp->billa += delta;
                } else {
                    printf("Cantidad fuera de rango para Billete A.\n");
                    presionar_tecla_para_continuar();
                }
                break;
            case IN_BILL_B:
                if ((modo != UNO) && (en_rango(estado_tmp->billb + delta, VEINTE) == 1)) {
                    estado_tmp->billb += delta;
                } else if ((UNO == modo) && (en_rango(estado->billb + estado_tmp->billb + delta, VEINTE) == 1)) {
                    estado_tmp->billb += delta;
                } else {
                    printf("Cantidad fuera de rango para Billete B.\n");
                    presionar_tecla_para_continuar();
                }
                break;
            case IN_BILL_C:
                if ((modo != UNO) && (en_rango(estado_tmp->billc + delta, VEINTE) == 1)) {
                    estado_tmp->billc += delta;
                } else if ((UNO == modo) && (en_rango(estado->billc + estado_tmp->billc + delta, VEINTE) == 1)) {
                    estado_tmp->billc += delta;
                } else {
                    printf("Cantidad fuera de rango para Billete C.\n");
                    presionar_tecla_para_continuar();
                }
                break;
            case IN_BILL_D:
                if ((modo != UNO) && (en_rango(estado_tmp->billd + delta, VEINTE) == 1)) {
                    estado_tmp->billd += delta;
                } else if ((UNO == modo) && (en_rango(estado->billd + estado_tmp->billd + delta, VEINTE) == 1)) {
                    estado_tmp->billd += delta;
                } else {
                    printf("Cantidad fuera de rango para Billete D.\n");
                    presionar_tecla_para_continuar();
                }
                break;
            case MONEY_RETURN:
                if (UNO == modo) {
                    agregar_dinero_estados(estado_int, estado_tmp);
                }
                en_ejecucion = 0;            
                break;
            default:
                break;
        }
    }
}

/* funcion que define el comportamiento del límite de los rangos*/
int en_rango(int x, int max) {
    int ret = 0;
    if (x >= 0 && x <= max) {
        ret = 1;
    }
    return ret;
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
    int status = ZERO;
    char tmp = ZERO;
    int menu = ZERO;
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
    int total = ZERO;
    total = calcular_total(estado);
    printf("========== Dinero ==========\n");
    printf("| Tipo\t\tExistencia |\n");
    printf("| Moneda $%d\t\t%d |\n", COST_COIN_A, estado->coina);
    printf("| Moneda $%d\t\t%d |\n", COST_COIN_B, estado->coinb);
    printf("| Moneda $%d\t\t%d |\n", COST_COIN_C, estado->coinc);
    printf("| Billete $%d\t\t%d |\n", COST_BILL_A, estado->billa);
    printf("| Billete $%d\t\t%d |\n", COST_BILL_B, estado->billb);
    printf("| Billete $%d\t\t%d |\n", COST_BILL_C, estado->billc);
    printf("| Billete $%d\t\t%d |\n", COST_BILL_D, estado->billd);
    printf("============================\n");
    printf("Total: %0.2f\n", (float)total);
    printf("============================\n");
}

/* retorna el total de dinero en un estado */
int calcular_total(state_t *estado) {
    int total = ZERO;
    total += COST_COIN_A * estado->coina;
    total += COST_COIN_B * estado->coinb;
    total += COST_COIN_C * estado->coinc;
    total += COST_BILL_A * estado->billa;
    total += COST_BILL_B * estado->billb;
    total += COST_BILL_C * estado->billc;
    total += COST_BILL_D * estado->billd;
    return total;
}

/* muestra el total del dinero ingresado por el cliente */
void mostrar_cantidad(state_t *estado) {
    printf("----------------------------\n");
    printf("Cantidad Ingresada: %0.2f\n", (float)calcular_total(estado));
    printf("----------------------------\n");
}

/* obtiene la opción del producto seleccionado */
int obtener_opcion_menu_principal() {
    int status = ZERO;
    char tmp = ZERO;
    int menu = ZERO;
    printf("\n====== Menú Principal ======\n");
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

/* optiene producto seleccionado */
int obtener_opcion_seleccionar_producto() {
    int status = ZERO;
    char tmp = ZERO;
    int menu = ZERO;
    printf("\n=== Seleccionar Producto ===\n");
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

/* obtener la opción de administración */
int obtener_opcion_administrar(state_t *estado) {
    int status = ZERO;
    char tmp = ZERO;
    int menu = ZERO;
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
    int cantidad = ZERO;
    int status = ZERO;
    int menu = ZERO;
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
    int ret = ZERO, costo = ZERO;
    if (!estado_int) return ZERO;

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
    int cambio = ZERO;
    int result = ZERO;
    state_t estado_local;
    int m = sizeof(denominaciones) / sizeof(denominaciones[ZERO]);
    int total = calcular_total(estado_int);
    int *l_cambio = NULL;
    int l_csize = ZERO;
    int cur_amt = ZERO, contador = ZERO;

    limpiar_estado_dinero(&estado_local);
    if (total >= costo) {
        cambio = total - costo;
        agregar_dinero_estados(&estado_local, estado);
        agregar_dinero_estados(&estado_local, estado_int);
        result = encontrar_cambio(m, cambio, &estado_local, &l_cambio, &l_csize);
        if (result != MAX_INT_VALUE) {
            agregar_dinero_estados(estado, estado_int);
            mostrar_cambio(estado, cambio, l_cambio, l_csize, 1);
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
            presionar_tecla_para_continuar();
        }
    } else {
        printf("No se puede realizar la compra. Ingrese suficiente dinero.\n");
        presionar_tecla_para_continuar();
    }
    return ret;
}
/* mostrar el cambio al usuario */
void mostrar_cambio(state_t *estado, int cambio, int *l_cambio, int l_csize, int flag) {
    int cur_amt = cambio;
    int contador = 0;
    printf("Su cambio: $%d\n", cambio);
    while (cur_amt > ZERO && (contador < l_csize)) {
        if (l_cambio[cur_amt] > COST_COIN_C) {
            printf("Dar Billete de: $%d \n", l_cambio[cur_amt]);
        } else {
            printf("Dar Moneda de: $%d \n", l_cambio[cur_amt]);
        }
        if (1 == flag) {
            quitar_moneda(estado, l_cambio[cur_amt]);
        }
        cur_amt = cur_amt - l_cambio[cur_amt];
        contador = contador + 1;
    }
    presionar_tecla_para_continuar();
}

void presionar_tecla_para_continuar() {
    char ch;
    printf("Presione una tecla para continuar ...");
    ch = getchar();
    if (ch == '\n') ch = getchar();
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
        if (strcmp("coina", lexema1) == ZERO) {
            estado_vending->coina = cantidad;
        } else if(strcmp("coinb", lexema1) == ZERO) {
            estado_vending->coinb = cantidad;
        } else if(strcmp("coinc", lexema1) == ZERO) {
            estado_vending->coinc = cantidad;
        } else if(strcmp("billa", lexema1) == ZERO) {
            estado_vending->billa = cantidad;
        } else if(strcmp("billb", lexema1) == ZERO) {
            estado_vending->billb = cantidad;
        } else if(strcmp("billc", lexema1) == ZERO) {
            estado_vending->billc = cantidad;
        } else if(strcmp("billd", lexema1) == ZERO) {
            estado_vending->billd = cantidad;
        } else if(strcmp("producta", lexema1) == ZERO) {
            estado_vending->pa = cantidad;
        } else if(strcmp("productb", lexema1) == ZERO) {
            estado_vending->pb = cantidad;
        } else if(strcmp("productc", lexema1) == ZERO) {
            estado_vending->pc = cantidad;
        }
    }
    if(archivo) fclose(archivo);
}

/* salva el estado de la vending machine */
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

/* se asignan los atributos de una estructura de tipo state_t a ZERO para dinero */
void limpiar_estado_dinero(state_t *estado) {
    if (!estado) return;
    estado->coina = ZERO;
    estado->coinb = ZERO;
    estado->coinc = ZERO;
    estado->billa = ZERO;
    estado->billb = ZERO;
    estado->billc = ZERO;
    estado->billd = ZERO;
}

/* se asignan los atributos de una estructura de tipo state_t a ZERO para productos */
void limpiar_estado_productos(state_t *estado) {
    if (!estado) return;
    estado->pa = ZERO;
    estado->pb = ZERO;
    estado->pc = ZERO;
}

/* calcula la mejor solución para dar cambio */
int encontrar_cambio(int num_denom, int cantidad_f, state_t *estado, int **l_cambio, int *l_csize) {
    int *min_num_coins = (int*) malloc( (cantidad_f+1) * sizeof(int));
    int *chosen_denom = (int*) malloc( (cantidad_f+1) * sizeof(int));
    int ex[] = {0,0,0,0,0,0,0};
    int i, cur_amt, smaller_amt, result;
    cargar_existencia(estado,ex);
    //for (i=0;i<7;i++) printf("%d\n", ex[i]);
    min_num_coins[ZERO] = ZERO;
    for (cur_amt = 1; cur_amt <= cantidad_f; cur_amt++) {
        min_num_coins[cur_amt] = MAX_INT_VALUE;
        for (i = ZERO; i < num_denom; ++i) {
            if ((ex[i] > 0) && (denominaciones[i] <= cur_amt)) {
                smaller_amt = cur_amt - denominaciones[i];
                if ((1 + min_num_coins[smaller_amt]) < min_num_coins[cur_amt]) {
                    min_num_coins[cur_amt] = 1 + min_num_coins[smaller_amt];
                    chosen_denom[cur_amt] = denominaciones[i];
                    ex[i]--;
                }
            }
        }
    }
 
    result = min_num_coins[cantidad_f];
    free(min_num_coins);
    if (l_cambio) {
        *l_cambio = chosen_denom;
    }
    if (l_csize) {
        *l_csize = cantidad_f + 1;
    }
    return result;
}

void cargar_existencia(state_t *s, int ex[]) {
    ex[0] = s->coina;
    ex[1] = s->coinb;
    ex[2] = s->coinc;
    ex[3] = s->billa;
    ex[4] = s->billb;
    ex[5] = s->billc;
    ex[6] = s->billd;
}

/* utilizada para devolver cambio */
void procesar_cancelar_compra(state_t *estado, state_t *estado_int) {
    int cantidad, ret, l_size, cur_amt, contador = 0;
    int *l_cambio = NULL;
    int m = sizeof(denominaciones) / sizeof(denominaciones[ZERO]);
    agregar_dinero_estados(estado, estado_int);
    cantidad = calcular_total(estado_int);
    limpiar_estado_dinero(estado_int);
    limpiar_estado_productos(estado_int);
    ret = encontrar_cambio(m, cantidad, estado, &l_cambio, &l_size);
    if (ret != MAX_INT_VALUE) {
        mostrar_cambio(estado, cantidad, l_cambio, l_size, 1);
        /*print the chosen denominations to get the final amount*/
        /*
        cur_amt = cantidad;
        printf("Su cambio.\n");
        while (cur_amt > ZERO && (contador < l_size)) {
            if (l_cambio[cur_amt] > COST_COIN_C) {
                printf("Billete de: $%d \n", l_cambio[cur_amt]);
            } else {
               printf("Moneda de: $%d \n", l_cambio[cur_amt]);
            }
            quitar_moneda(estado, l_cambio[cur_amt]);
            cur_amt = cur_amt - l_cambio[cur_amt];
            contador = contador + 1;
        }
        */
        if (l_cambio) {
            free(l_cambio);
        }
    }
}
