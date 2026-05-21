#include <stdio.h>

int main () {

    float notas[5][3];
    float promestudiantes[5], promasignaturas[3];
    float maxasig[3], minasig[3];
    float maxest[5], minest[5];
    
    int aprobados[3] = {0, 0, 0};
    int reprobados[3] = {0, 0, 0};

    printf ("--------Sistema de calificaciones--------\n");

    for (int j = 0; j < 3; j++) {
        printf ("\nSeleccione la materia deseada: ");
        switch (j) {
            case 0: printf ("matematica\n"); break;
            case 1: printf ("lenguaje\n"); break;
            case 2: printf ("computacion\n"); break;
        }

            float sumacol = 0;
            maxasig[j] = -20;
            minasig[j] = 20;

            for (int i = 0; i < 5; i++) {
                float temp;
                do {
                    printf ("Ingrese la nota del estudiante %d: ", i + 1);
                    scanf ("%f", &temp);
                    if (temp < 0 || temp > 10)
                        printf ("Error la nota debe estar en el rango de 0-10.\n");
                }   while (temp < 0 || temp > 10);

                notas[i][j] = temp;
                sumacol += temp;

                if(temp > maxasig[j]) maxasig[j] = temp;
                if(temp < minasig[j]) minasig[j] = temp;
                if(temp >= 6) aprobados[j]++;
                else reprobados[j]++;
            }
            promasignaturas[j] = sumacol / 5;
        }

        for (int i = 0; i < 5; i++) {
            float sumafila = 0;
            maxest[i] = -20;
            minest[i] = 20;
            for (int j = 0; j < 3; j++) {
                sumafila += notas [i][j];
                if(notas[i][j] > maxest[i]) maxest[i] = notas[i][j];
                if(notas[i][j] < minest[i]) minest[i] = notas[i][j];
            }
            promestudiantes[i] = sumafila / 3;
        }
        
        printf ("\n--------Resultados obtenidos--------\n");
        for (int j = 0; j < 3; j++){
            printf ("\nmateria: ");
            switch (j) {
                case 0: printf ("matematica\n"); break;
                case 1: printf ("lenguaje\n"); break;
                case 2: printf ("computacion\n"); break;
            }
            printf ("promedio grupal: %.2f\n", promasignaturas[j]);
            printf ("nota mas alta: %.2f\n", maxasig[j]);
            printf ("nota mas baja: %.2f\n", minasig[j]);
            printf ("estudiantes aprobados: %d\n", aprobados[j]);
            printf ("estudiantes reprobados: %d\n", reprobados[j]);
        }

        printf ("\n--------informacion del estudiante--------\n");
        for (int i = 0; i < 5; i++) {
            printf("Estudiante %d\tPromedio: %.2f\tMax: %.2f\tMin: %.2f\n", 
            i + 1, promestudiantes[i], maxest[i], minest[i]);
        }

        return 0;
    }
