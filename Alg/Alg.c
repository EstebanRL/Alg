#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include "math.h"
#include "time.h"
#include "Alg.h"

/*
 * @Author: Esteban Rozas Liñares
 * @Project: Caracterización de elementos constructivos usando datos de escanér láser aerotransportado
 * @Project type: Trabajo de fin de carrera
 * @Organization: Universidad de Santiago de Compostela
 *
 * 
 */


int main(int argc, const char* argv[]) {

    int i = 0, gIdx = 0, type = 0, numPoints = 0, numGroups = 0, k = 0, prevgIdx = -1, prevType = 0, numGroupsBuildings = 0, flag = 0;
    FILE *file = NULL;
    double x = 0.0, y = 0.0, z = 0.0, intensity = 0.0, normal[3], totalX = 0.0, totalY = 0.0, time = 0;
    Lpoint point;
    Group *groups = NULL, *groupsBuildings = NULL, *boundaryGroup = NULL;
    Node aux = NULL;
    char option, c;
    struct timespec start2 = {0, 0}, end = {0, 0};
    char StatisticallyFile[35] = "data/AlgEstadistico.txt";
    char JarvisFile[35] = "data/AlgConvexoJarvis.txt";
    char GrahamFile[35] = "data/AlgConvexoGraham.txt";
    char PortugueseFile[35] = "data/AlgConcavo.txt";
    char ExteriorFile[35] = "data/AlgExterior.txt";
    char VoronoiFile[35] = "data/AlgVoronoi.txt";

    if (argc != 4) {
        printf("Faltan argumentos necesarios para la ejecución.\n");
        printf("Saliendo...\n");
        return (EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Archivo '%s' no encontrado\n", argv[1]);
        printf("Saliendo...\n");
        return (EXIT_FAILURE);
    } else {
        printf("Leyendo %s...\n\n", argv[1]);
    }


    /*************************DATA READ****************************/
    // Read number of points and groups
    numPoints = (int) strtol(argv[2], (char **) NULL, 10);
    numGroups = (int) strtol(argv[3], (char **) NULL, 10);

    printf("Número de puntos: %d\n", numPoints);
    printf("Número de grupos: %d\n\n", numGroups);


    groups = (Group*) malloc(numGroups * sizeof (Group));
    for (i = 0; i < numGroups; i++)
        createGroup(&groups[i], i);
    numGroups = 0;


    //Read data from all points
    for (i = 0; i < numPoints; i++) {
        //fscanf(file, "%lf\t%lf\t%lf\t%lf\t%d\t%d\t%lf\t%lf\t%lf\n", &x, &y, &z, &intensity, &gIdx, &type, &normal[0], &normal[1], &normal[2]);
        fscanf(file, "%lf\t%lf\t%lf\t%lf\t%d\t%d\n", &x, &y, &z, &intensity, &gIdx, &type);
        point = createPoint(i, x, y, z, intensity, normal);
        if (gIdx != prevgIdx) {
            numGroups++;
            if (type == NO_GROUND && x != 0 && y != 0 && z != 0)
                numGroupsBuildings++;

            if (numGroups > 1) {
                groups[numGroups - 2]->totalX = totalX;
                groups[numGroups - 2]->totalY = totalY;
                groups[numGroups - 2]->planar = prevType;
                totalX = 0;
                totalY = 0;
            }
        }

        newNode(&groups[numGroups - 1], point)->elem;
        totalX += x;
        totalY += y;
        prevgIdx = gIdx;
        prevType = type;

    }
    groups[numGroups - 1]->type = UNKNOWN; // Non-segmented points
    numGroups--; // Make last group invisible (non-segmented points)

    fclose(file);



    //Create a structure for only groups of buildings 
    groupsBuildings = (Group*) malloc(numGroupsBuildings * sizeof (Group));
    for (i = 0; i < numGroupsBuildings; i++)
        createGroup(&groupsBuildings[i], i);
    numGroupsBuildings = 0;

    //Store data in a structure for only buildings
    for (i = 0; i < numGroups; i++) {
        if (groups[i]->planar == NO_GROUND && groups[i]->start->elem.x != 0 && groups[i]->start->elem.y != 0 && groups[i]->start->elem.z != 0) {
            groupsBuildings[numGroupsBuildings]->id = groups[i]->id;
            groupsBuildings[numGroupsBuildings]->planar = NO_GROUND;
            aux = groups[i]->start;
            while ((aux->next) != NULL) {
                newNode(&groupsBuildings[numGroupsBuildings], aux->elem)->elem;
                aux = aux->next;
            }
            numGroupsBuildings++;
        }
    }

    boundaryGroup = (Group*) malloc(sizeof (Group));
    createGroup(boundaryGroup, 0);


    /***********************************END OF DATA READ*********************/


    /***********************************MENU*********************************/

    mkdir("data", 0777);

    do {
        printf("\nMenú:\n");
        printf("\t0. Ejecutar todos los algoritmos.\n");
        printf("\t1. Ejecutar algoritmo estadístico.\n");
        printf("\t2. Ejecutar algoritmo convexo Graham.\n");
        printf("\t3. Ejecutar algoritmo convexo Jarvis.\n");
        printf("\t4. Ejecutar algoritmo cóncavo.\n");
        printf("\t5. Ejecutar algoritmo exterior.\n");
        printf("\t6. Ejecutar algoritmo Voronoi.\n");
        printf("\ts. Salir de la aplicación.\n\n");
        printf("Introduzca una opción: ");
        scanf("%c", &option);

        while ((c = getchar()) != '\n' && c != EOF) {
        }

        switch (option) {
            case '0':

                printf("\nEjecutando todos los algoritmos. \n");
                flag = 1;

                if (!flag)
                    break;
            case '1':
                printf("\nEjecutando algoritmo estadístico...\n");

                file = fopen(StatisticallyFile, "w");

                stclock(&start2);
                for (i = 0; i < numGroupsBuildings; i++) {
                    if (groupsBuildings[i]->id != 12392) {
                        calculateAreaVolumeStatistically(&(groupsBuildings[i]), groups, numGroups, 2);
                        fprintf(file, "%d\t%.2lf\t%.2lf\n", groupsBuildings[i]->id, groupsBuildings[i]->area, groupsBuildings[i]->volume);
                    }
                }
                declocksav(&start2, &end, &time);

                fclose(file);

                printf("\nAlgoritmo estadístico: %.2lf s (%.2lf min)\n", time, time / 60.0);
                printf("Algoritmo estadístico media por edificación: %.2lf s (%.2lf min)\n", time / i, (time / 60.0) / i);

                if (!flag)
                    break;
            case '2':
                printf("\nEjecutando algoritmo convexo Graham...\n");

                file = fopen(GrahamFile, "w");

                stclock(&start2);
                for (i = 0; i < numGroupsBuildings; i++) {
                    if (groupsBuildings[i]->id != 12392) {
                        GrahamScan(boundaryGroup, groupsBuildings[i]);
                        groupsBuildings[i]->area = (*boundaryGroup)->area;
                        calculateVolumeStatistically(&(groupsBuildings[i]), groups, numGroups, 2);
                        fprintf(file, "%d\t%.2lf\t%.2lf\n", groupsBuildings[i]->id, groupsBuildings[i]->area, groupsBuildings[i]->volume);
                    }
                }
                declocksav(&start2, &end, &time);

                fclose(file);
                printf("\nAlgoritmo convexo Graham: %.2lf s (%.2lf min)\n", time, time / 60.0);
                printf("Algoritmo convexo Graham media por edificación: %.2lf s (%.2lf min)\n", time / i, (time / 60.0) / i);

                if (!flag)
                    break;
            case '3':
                printf("\nEjecutando algoritmo convexo Jarvis...\n");

                file = fopen(JarvisFile, "w");

                stclock(&start2);
                for (i = 0; i < numGroupsBuildings; i++) {
                    if (groupsBuildings[i]->id != 12392) {
                        JarvisMarch(boundaryGroup, groupsBuildings[i]);
                        groupsBuildings[i]->area = (*boundaryGroup)->area;
                        calculateVolumeStatistically(&(groupsBuildings[i]), groups, numGroups, 2);
                        fprintf(file, "%d\t%.2lf\t%.2lf\n", groupsBuildings[i]->id, groupsBuildings[i]->area, groupsBuildings[i]->volume);
                    }
                }
                declocksav(&start2, &end, &time);

                fclose(file);
                printf("\nAlgoritmo convexo Jarvis: %.2lf s (%.2lf min)\n", time, time / 60.0);
                printf("Algoritmo convexo Jarvis media por edificación: %.2lf s (%.2lf min)\n", time / i, (time / 60.0) / i);

                if (!flag)
                    break;
            case '4':

                do {
                    printf("\n\t¿Valor de k a emplear para el algoritmo cóncavo?: ");
                    scanf("%d", &k);
                    while ((c = getchar()) != '\n' && c != EOF) {
                    }
                    if (k < 3)
                        printf("k debe ser un número entero mayor que 3.\n");
                } while (k < 3);

                printf("\nEjecutando algoritmo cóncavo...\n");

                file = fopen(PortugueseFile, "w");

                stclock(&start2);
                for (i = 0; i < numGroupsBuildings; i++) {
                    if (groupsBuildings[i]->id != 12392) {
                        ConcaveAlgorithm(boundaryGroup, groupsBuildings[i], k);
                        groupsBuildings[i]->area = (*boundaryGroup)->area;
                        calculateVolumeStatistically(&(groupsBuildings[i]), groups, numGroups, 2);
                        fprintf(file, "%d\t%.2lf\t%.2lf\n", groupsBuildings[i]->id, groupsBuildings[i]->area, groupsBuildings[i]->volume);
                    }
                }
                declocksav(&start2, &end, &time);

                fclose(file);
                printf("\nAlgoritmo cóncavo: %.2lf s (%.2lf min)\n", time, time / 60.0);
                printf("Algoritmo cóncavo media por edificación: %.2lf s (%.2lf min)\n", time / i, (time / 60.0) / i);

                if (!flag)
                    break;
            case '5':

                do {
                    printf("\n\t¿Valor de k a emplear para el algoritmo exterior?: ");
                    scanf("%d", &k);
                    while ((c = getchar()) != '\n' && c != EOF) {
                    }
                    if (k < 3)
                        printf("k debe ser un número entero mayor que 3.\n");
                } while (k < 3);

                printf("\nEjecutando algoritmo exterior...\n");

                file = fopen(ExteriorFile, "w");

                stclock(&start2);
                for (i = 0; i < numGroupsBuildings; i++) {
                    if (groupsBuildings[i]->id != 12392) {
                        ExteriorAlgorithm(boundaryGroup, groupsBuildings[i], groups, numGroups, k);
                        groupsBuildings[i]->area = (*boundaryGroup)->area;
                        groupsBuildings[i]->volume = (*boundaryGroup)->area;
                        fprintf(file, "%d\t%.2lf\t%.2lf\n", groupsBuildings[i]->id, groupsBuildings[i]->area, groupsBuildings[i]->volume);
                    }
                }
                declocksav(&start2, &end, &time);

                fclose(file);
                printf("\nAlgoritmo exterior: %.2lf s (%.2lf min)\n", time, time / 60.0);
                printf("Algoritmo exterior media por edificación: %.2lf s (%.2lf min)\n", time / i, (time / 60.0) / i);

                if (!flag)
                    break;
            case '6':

                do {
                    printf("\n\t¿Valor de k a emplear para el algoritmo Voronoi?: ");
                    scanf("%d", &k);
                    while ((c = getchar()) != '\n' && c != EOF) {
                    }
                    if (k < 3)
                        printf("k debe ser un número entero mayor que 3.\n");
                } while (k < 3);

                printf("\nEjecutando algoritmo Voronoi...\n");

                file = fopen(VoronoiFile, "w");

                stclock(&start2);
                for (i = 0; i < numGroupsBuildings; i++) {
                    if (groupsBuildings[i]->id != 12392) {
                        VoronoiAlgorithm(boundaryGroup, groupsBuildings[i], groups, numGroups, k);
                        groupsBuildings[i]->area = (*boundaryGroup)->area;
                        groupsBuildings[i]->volume = (*boundaryGroup)->area;
                        fprintf(file, "%d\t%.2lf\t%.2lf\n", groupsBuildings[i]->id, groupsBuildings[i]->area, groupsBuildings[i]->volume);
                    }
                }
                declocksav(&start2, &end, &time);

                fclose(file);
                printf("\nAlgoritmo Voronoi: %.2lf s (%.2lf min)\n", time, time / 60.0);
                printf("Algoritmo Voronoi media por edificación: %.2lf s (%.2lf min)\n", time / i, (time / 60.0) / i);

                if (!flag)
                    flag = 0;
                break;
            case 's':
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción incorrecta\n");
                break;
        }
    } while (option != 's');



    /*********************************END OF MENU*****************************/


    //Free 
    for (i = 0; i < numGroups; i++) {
        removeGroup(&groups[i]);
    }
    free(groups);

    for (i = 0; i < numGroupsBuildings; i++) {
        removeGroup(&groupsBuildings[i]);
    }
    free(groupsBuildings);

    removeGroup(boundaryGroup);
    free(boundaryGroup);

    return (EXIT_SUCCESS);
}

