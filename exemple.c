#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
typedef struct {
    int minute;
    int heure;
    int jour;
}Horaire ;
typedef struct {
    int id;
    Horaire horaireDateSouhaite;
    Horaire dureeHeureMinute;
    int typeActivite;
    int idZoneSrc;
    int idZoneDest;
    int idLigne;
    int sens;
} Activite ;
typedef struct {
    int cin;
    int idZoneHabitat;
    int idZoneTravail;
    int idZoneCourante;
    int intentionVoyage;
    int idLigneCourante;
    int sensCourant;
    int idZoneDest;
    int nombreActivites;
    Activite activites[8];
} Personne ;
typedef struct {
    int id;
    int row;
    int column;
    int nombrePersonnes;
    Personne personnes[100];
} Zone ;
void chargerZones(Zone zones[], int *nombreZones)
{
    FILE *file = fopen("zones.txt", "r");
    if (file == NULL) {
        printf("Error Zone");
        exit(1);
    }
    while (fscanf(file, "%d %d %d", &zones[*nombreZones].id, &zones[*nombreZones].row, &zones[*nombreZones].column) == 3) {
            zones[*nombreZones].nombrePersonnes=0;
            (*nombreZones)++;
    }
    fclose(file);
}
void afficherZones(Zone zones[], int nombreZones)
{
    for(int i =0;i<nombreZones;i++){
        printf("%d %d %d\n",zones[i].id,zones[i].row,zones[i].column);
    }

}
int main()
{
    
    Zone zones [10];
    
    int nombreZones=0;

    /*setlocale(LC_ALL, "");
    SetConsoleOutputCP(CP_UTF8);*/
    chdir("D:\\Iset\\S2\\Mini Projet\\mini projet");

    chargerZones(zones, &nombreZones);
    

    afficherZones(zones, nombreZones);
    return 0;
}