#include <stdio.h>

#define MAX_EST 5
#define MAX_ASIG 3

const char *MATERIAS[MAX_ASIG] = {"Matematica", "Lenguaje", "Computacion"};

// Prototipos
float limpiarYValidarEntrada(int num_estudiante);
void registrarMateria(float notas[MAX_EST][MAX_ASIG], int j, int *ap, int *rep, float *max, float *min, float *prom);
void calcularEstudiantes(float notas[MAX_EST][MAX_ASIG]);
void mostrarReporteMaterias(float prom_asig[], float max_asig[], float min_asig[], int aprobados[], int reprobados[]);

int main(){
    float notas[MAX_EST][MAX_ASIG] = {0}, prom_asig[MAX_ASIG];
    float max_asig[MAX_ASIG], min_asig[MAX_ASIG];
    int aprobados[MAX_ASIG] = {0}, reprobados[MAX_ASIG] = {0}, registradas[MAX_ASIG] = {0};
    int opcion, ingresadas = 0;

    printf("--------Sistema de Calificaciones--------\n");

    while (ingresadas < MAX_ASIG) {
        printf("\n--- MENU ---\n");
        for (int i = 0; i < MAX_ASIG; i++) 
            printf("%d. %s %s\n", i + 1, MATERIAS[i], registradas[i] ? "(Ok)" : "");
        
        printf("Seleccione materia (1-3): ");
        
        if (scanf("%d", &opcion) != 1){
            printf("Error: Ingrese solo numeros.\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (opcion < 1 || opcion > MAX_ASIG){
            printf("Opcion fuera de rango (1-3).\n");
            continue;
        }
        
        int j = opcion - 1;

        if (registradas[j] == 1){
            int sobrescribir;
            printf("Esta materia ya fue registrada. Desea modificar las notas? (1 = Si / 0 = No): ");
            if (scanf("%d", &sobrescribir) != 1 || sobrescribir != 1) {
                while (getchar() != '\n'); 
                printf("Operacion cancelada. Seleccione otra materia.\n");
                continue; 
            }
        } else {
            registradas[j] = 1;
            ingresadas++;
        }

        registrarMateria(notas, j, &aprobados[j], &reprobados[j], &max_asig[j], &min_asig[j], &prom_asig[j]);
    }

    // Usamos la nueva función
    mostrarReporteMaterias(prom_asig, max_asig, min_asig, aprobados, reprobados);
    calcularEstudiantes(notas);

    return 0;
}

float limpiarYValidarEntrada(int num_estudiante) {
    float valor;
    while (1) {
        printf(" Alumno %d (0-10): ", num_estudiante);
        if (scanf("%f", &valor) == 1) {
            if (valor >= 0.0 && valor <= 10.0) {
                return valor; 
            } else {
                printf(" Error: La nota debe estar en el rango de 0 a 10.\n");
            }
        } else {
            printf(" Error: Entrada invalida. Ingrese solo numeros.\n");
            while (getchar() != '\n'); 
        }
    }
}

void registrarMateria(float notas[MAX_EST][MAX_ASIG], int j, int *ap, int *rep, float *max, float *min, float *prom) {
    float suma = 0;
    *max = -1.0; *min = 11.0; *ap = 0; *rep = 0;

    printf("\nNotas para %s:\n", MATERIAS[j]);
    for (int i = 0; i < MAX_EST; i++) {
        notas[i][j] = limpiarYValidarEntrada(i + 1);
        float n = notas[i][j];
        suma += n;
        if (n > *max) *max = n;
        if (n < *min) *min = n;
        if (n >= 6.0) (*ap)++; else (*rep)++;
    }
    *prom = suma / MAX_EST;
}

void mostrarReporteMaterias(float prom_asig[], float max_asig[], float min_asig[], int aprobados[], int reprobados[]) {
    printf("\n--------Resultados por Materia--------\n");
    for (int j = 0; j < MAX_ASIG; j++) {
        printf("\n> %s:\n Promedio: %.2f | Max: %.2f | Min: %.2f\n Aprobados: %d | Reprobados: %d\n",
               MATERIAS[j], prom_asig[j], max_asig[j], min_asig[j], aprobados[j], reprobados[j]);
    }
}

void calcularEstudiantes(float notas[MAX_EST][MAX_ASIG]) {
    printf("\n--------Informacion del Estudiante--------\n");
    for (int i = 0; i < MAX_EST; i++) {
        float suma = 0, max = -1.0, min = 11.0;
        for (int j = 0; j < MAX_ASIG; j++) {
            float n = notas[i][j];
            suma += n;
            if (n > max) max = n;
            if (n < min) min = n;
        }
        printf("Estudiante %d -> Promedio: %.2f | Max: %.2f | Min: %.2f\n", i+1, suma / MAX_ASIG, max, min);
    }
}