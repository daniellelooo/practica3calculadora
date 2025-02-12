#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_PILA 100 // Tamaño máximo de la pila

// Estructura para la pila
typedef struct
{
    double pila[MAX_PILA]; // Array para los elementos de la pila
    int cima;              // Índice del elemento superior de la pila
} Pila;

// Función para apilar un valor
void apilar(Pila *p, double valor)
{
    if (p->cima < MAX_PILA)
    {
        p->pila[p->cima++] = valor;
    }
    else
    {
        printf("Error: Desbordamiento de pila\n"); // Mensaje en español
        exit(EXIT_FAILURE);
    }
}

// Función para desapilar un valor
double desapilar(Pila *p)
{
    if (p->cima > 0)
    {
        return p->pila[--p->cima];
    }
    else
    {
        printf("Error: Subdesbordamiento de pila\n"); // Mensaje en español
        exit(EXIT_FAILURE);
    }
}

// Función para evaluar una expresión en notación polaca inversa (RPN)
void evaluar_rpn(char *expr)
{
    Pila p = {.cima = 0};            // Inicializa la pila
    char *token = strtok(expr, " "); // Divide la expresión en tokens
    while (token)
    {
        // Si el token es un número (entero o decimal, incluyendo negativos)
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            apilar(&p, atof(token)); // Convierte el token a double y lo apila
        }
        else if (strlen(token) == 1)
        {                             // Si el token es un operador
            double b = desapilar(&p); // Obtiene el segundo operando
            double a = desapilar(&p); // Obtiene el primer operando
            switch (token[0])
            {
            case '+':
                apilar(&p, a + b);
                break; // Suma
            case '-':
                apilar(&p, a - b);
                break; // Resta
            case '*':
                apilar(&p, a * b);
                break; // Multiplicación
            case '/':
                if (b == 0)
                {
                    printf("Error: División por cero\n"); // Mensaje en español
                    exit(EXIT_FAILURE);
                }
                apilar(&p, a / b); // División
                break;
            default:
                printf("Error: Operador desconocido '%s'\n", token); // Mensaje en español
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("Error: Token inválido '%s'\n", token); // Mensaje en español
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, " "); // Obtiene el siguiente token
    }

    // El resultado final debe quedar en la pila
    if (p.cima == 1)
    {
        printf("Resultado: %lf\n", desapilar(&p)); // Imprime el resultado
    }
    else
    {
        printf("Error: Expresión mal formada\n"); // Mensaje en español
        exit(EXIT_FAILURE);
    }
}

int main()
{
    char expr[256];                                                    // Array para guardar la expresión
    printf("Ingrese la expresión en notación polaca inversa (RPN): "); // Pide la expresión al usuario
    fgets(expr, sizeof(expr), stdin);                                  // Lee la expresión del usuario
    expr[strcspn(expr, "\n")] = 0;                                     // Elimina el salto de línea final
    evaluar_rpn(expr);                                                 // Evalúa la expresión
    return 0;
}
