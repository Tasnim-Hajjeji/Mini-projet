#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct
{
    int minute;
    int heure;
    int jour;
} Horaire;
typedef struct
{
    int id;
    Horaire horaireDateSouhaite;
    Horaire dureeHeureMinute;
    int typeActivite;
    int idZoneSrc;
    int idZoneDest;
    int idLigne;
    int sens;
} Activite;
typedef struct
{
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
} Personne;
typedef struct
{
    int id;
    int row;
    int column;
    int nombrePersonnes;
    Personne personnes[150];
} Zone;
typedef struct
{
    int row;
    int column;
    int codeRue;
} Subdivision;
typedef struct
{
    int idZoneSrc;
    int idZoneDest;
    int distance;
    Horaire dureeApproximative;
    int nombresubdivisions;
    Subdivision parcours[20];
} Troncon;
typedef struct
{
    int id;
    int nombreZones;
    int idZones[10];
} Ligne;
typedef struct
{
    int id;
    int idLigne;
    int sens;
    Horaire horaireDateDepart;
} Tache;
typedef struct
{
    int zoneSrc;
    int zoneDest;
    int idLigne;
    int sens;
    int idBus;
    Horaire dateVente;
    int distance;
    int prix;
} Ticket;
typedef struct
{
    int id;
    int idZoneCourante;
    int row;
    int column;
    int enRoute;
    int idLigneCourante;
    int sensCourant;
    int nombreTaches;
    Tache taches[10];
    int nombrePassagers;
    Personne passagers[40];
    int nombreTickets;
    Ticket tickets[300];
} Bus;
typedef struct
{
    int rue;
    int zone;
    int bus;
} CaseCarte;

void chargerZones(Zone zones[], int *nombreZones)
{
    FILE *file = fopen("zones.txt", "r");
    if (file == NULL)
    {
        printf("Error Zone");
        exit(1);
    }
    while (!feof(file))
    {
        fscanf(file, "%d %d %d", &zones[*nombreZones].id, &zones[*nombreZones].row, &zones[*nombreZones].column);
        zones[*nombreZones].nombrePersonnes = 0;
        (*nombreZones)++;
    }
    fclose(file);
}

void chargerLignes(Ligne lignes[], int *nombreLignes)
{

    FILE *file = fopen("lignes.txt", "r");
    if (file == NULL)
    {
        printf("Error Ligne");
        exit(1);
    }

    while (!feof(file))
    {
        fscanf(file, "%d %d", &lignes[*nombreLignes].id, &lignes[*nombreLignes].nombreZones);
        int i = 0;
        while (i < lignes[*nombreLignes].nombreZones)
        {
            fscanf(file, "%d", &lignes[*nombreLignes].idZones[i]);
            i++;
        }
        (*nombreLignes)++;
    }

    fclose(file);
}

void chargerTroncons(Troncon troncons[], int *nombreTroncons)
{
    FILE *file = fopen("troncons.txt", "r");
    if (file == NULL)
    {
        printf("Error Troncons");
        exit(1);
    }
    int test = 0, i = 0;
    while (!feof(file))
    {
        if (test == 0)
        {
            fscanf(file, "%d %d %d %d %d %d %d", &troncons[*nombreTroncons].idZoneSrc, &troncons[*nombreTroncons].idZoneDest, &troncons[*nombreTroncons].distance, &troncons[*nombreTroncons].dureeApproximative.jour, &troncons[*nombreTroncons].dureeApproximative.heure, &troncons[*nombreTroncons].dureeApproximative.minute, &troncons[*nombreTroncons].nombresubdivisions);
            test = troncons[*nombreTroncons].nombresubdivisions;
        }
        else
        {
            if (test > 1)
            {
                fscanf(file, "%d %d %d", &troncons[*nombreTroncons].parcours[i].row, &troncons[*nombreTroncons].parcours[i].column, &troncons[*nombreTroncons].parcours[i].codeRue);
                test--;
                i++;
            }
            else
            {
                fscanf(file, "%d %d %d", &troncons[*nombreTroncons].parcours[i].row, &troncons[*nombreTroncons].parcours[i].column, &troncons[*nombreTroncons].parcours[i].codeRue);
                test--;
                i = 0;
                (*nombreTroncons)++;
            }
        }
    }
    fclose(file);
}

void chargerFlotteBus(Bus flotteBus[], int *nombreBus)
{
    FILE *file = fopen("flottebus.txt", "r");
    if (file == NULL)
    {
        printf("Error Bus");
        exit(1);
    }
    int test = 0, i = 0;
    while (!feof(file))
    {
        if (test == 0)
        {
            fscanf(file, "%d %d %d %d %d %d %d %d", &flotteBus[*nombreBus].id, &flotteBus[*nombreBus].idZoneCourante, &flotteBus[*nombreBus].row, &flotteBus[*nombreBus].column, &flotteBus[*nombreBus].enRoute, &flotteBus[*nombreBus].idLigneCourante, &flotteBus[*nombreBus].sensCourant, &flotteBus[*nombreBus].nombreTaches);
            test = flotteBus[*nombreBus].nombreTaches;
        }
        else
        {
            if (test > 1)
            {
                fscanf(file, "%d %d %d %d %d %d", &flotteBus[*nombreBus].taches[i].id, &flotteBus[*nombreBus].taches[i].idLigne, &flotteBus[*nombreBus].taches[i].sens, &flotteBus[*nombreBus].taches[i].horaireDateDepart.jour, &flotteBus[*nombreBus].taches[i].horaireDateDepart.heure, &flotteBus[*nombreBus].taches[i].horaireDateDepart.minute);
                i++;
                test--;
            }
            else
            {
                fscanf(file, "%d %d %d %d %d %d", &flotteBus[*nombreBus].taches[i].id, &flotteBus[*nombreBus].taches[i].idLigne, &flotteBus[*nombreBus].taches[i].sens, &flotteBus[*nombreBus].taches[i].horaireDateDepart.jour, &flotteBus[*nombreBus].taches[i].horaireDateDepart.heure, &flotteBus[*nombreBus].taches[i].horaireDateDepart.minute);
                flotteBus[*nombreBus].nombrePassagers = 0;
                for (int j = 0; j < 40; j++)
                {
                    flotteBus[*nombreBus].passagers[j].cin = -1;
                }
                i = 0;
                test--;
                (*nombreBus)++;
            }
        }
    }
    fclose(file);
}

void afficherZones(Zone zones[], int nombreZones)
{
    for (int i = 0; i < nombreZones; i++)
    {
        printf("%d %d %d\n", zones[i].id, zones[i].row, zones[i].column);
    }
}

void afficherLignes(Ligne lignes[], int nombreLignes)
{
    for (int i = 0; i < nombreLignes; i++)
    {
        printf("%d %d\n", lignes[i].id, lignes[i].nombreZones);
        for (int j = 0; j < lignes[i].nombreZones; j++)
        {
            printf(" %d\n", lignes[i].idZones[j]);
        }
    }
}

void afficherTroncons(Troncon troncons[], int nombreTroncons)
{
    for (int i = 0; i < nombreTroncons; i++)
    {
        printf("%d %d %d %d %d %d %d\n", troncons[i].idZoneSrc, troncons[i].idZoneDest, troncons[i].distance, troncons[i].dureeApproximative.jour, troncons[i].dureeApproximative.heure, troncons[i].dureeApproximative.minute, troncons[i].nombresubdivisions);
        for (int j = 0; j < troncons[i].nombresubdivisions; j++)
        {
            printf("%d %d %d\n", troncons[i].parcours[j].row, troncons[i].parcours[j].column, troncons[i].parcours[j].codeRue);
        }
    }
}

void afficherFlotteBus(Bus flotteBus[], int nombreBus)
{
    for (int i = 0; i < nombreBus; i++)
    {
        printf("%d %d %d %d %d %d %d %d\n", flotteBus[i].id, flotteBus[i].idZoneCourante, flotteBus[i].row, flotteBus[i].column, flotteBus[i].enRoute, flotteBus[i].idLigneCourante, flotteBus[i].sensCourant, flotteBus[i].nombreTaches);
        for (int j = 0; j < flotteBus[i].nombreTaches; j++)
        {
            printf("%d %d %d %d %d %d\n", flotteBus[i].taches[j].id, flotteBus[i].taches[j].idLigne, flotteBus[i].taches[j].sens, flotteBus[i].taches[j].horaireDateDepart.jour, flotteBus[i].taches[j].horaireDateDepart.heure, flotteBus[i].taches[j].horaireDateDepart.minute);
        }
    }
}

void sauvegarderZones(Zone zones[], int nombreZones, char *nomFichier)
{
    FILE *file = fopen(nomFichier, "w");
    for (int i = 0; i < nombreZones - 1; i++)
    {
        fprintf(file, "%d %d %d\n", zones[i].id, zones[i].row, zones[i].column);
    }
    fprintf(file, "%d %d %d", zones[nombreZones - 1].id, zones[nombreZones - 1].row, zones[nombreZones - 1].column);
    fclose(file);
}

void sauvegarderLignes(Ligne lignes[], int nombreLignes, char *nomFichier)
{
    FILE *file = fopen(nomFichier, "w");
    for (int i = 0; i < nombreLignes - 1; i++)
    {
        fprintf(file, "%d %d\n", lignes[i].id, lignes[i].nombreZones);
        for (int j = 0; j < lignes[i].nombreZones; j++)
        {
            fprintf(file, "%d\n", lignes[i].idZones[j]);
        }
    }
    fprintf(file, "%d %d\n", lignes[nombreLignes - 1].id, lignes[nombreLignes - 1].nombreZones);
    for (int i = 0; i < (lignes[nombreLignes - 1].nombreZones) - 1; i++)
    {
        fprintf(file, "%d\n", lignes[nombreLignes - 1].idZones[i]);
    }
    fprintf(file, "%d", lignes[nombreLignes - 1].idZones[(lignes[nombreLignes - 1].nombreZones) - 1]);

    fclose(file);
}

void sauvegarderTroncons(Troncon troncons[], int nombreTroncons, char *nomFichier)
{
    FILE *file = fopen(nomFichier, "w");
    for (int i = 0; i < nombreTroncons - 1; i++)
    {
        fprintf(file, "%d %d %d %d %d %d %d\n", troncons[i].idZoneSrc, troncons[i].idZoneDest, troncons[i].distance, troncons[i].dureeApproximative.jour, troncons[i].dureeApproximative.heure, troncons[i].dureeApproximative.minute, troncons[i].nombresubdivisions);
        for (int j = 0; j < troncons[i].nombresubdivisions; j++)
        {
            fprintf(file, "%d %d %d\n", troncons[i].parcours[j].row, troncons[i].parcours[j].column, troncons[i].parcours[j].codeRue);
        }
    }
    fprintf(file, "%d %d %d %d %d %d %d\n", troncons[nombreTroncons - 1].idZoneSrc, troncons[nombreTroncons - 1].idZoneDest, troncons[nombreTroncons - 1].distance, troncons[nombreTroncons - 1].dureeApproximative.jour, troncons[nombreTroncons - 1].dureeApproximative.heure, troncons[nombreTroncons - 1].dureeApproximative.minute, troncons[nombreTroncons - 1].nombresubdivisions);
    for (int i = 0; i < (troncons[nombreTroncons - 1].nombresubdivisions) - 1; i++)
    {
        fprintf(file, "%d %d %d\n", troncons[nombreTroncons - 1].parcours[i].row, troncons[nombreTroncons - 1].parcours[i].column, troncons[nombreTroncons - 1].parcours[i].codeRue);
    }
    fprintf(file, "%d %d %d", troncons[nombreTroncons - 1].parcours[(troncons[nombreTroncons - 1].nombresubdivisions) - 1].row, troncons[nombreTroncons - 1].parcours[(troncons[nombreTroncons - 1].nombresubdivisions) - 1].column, troncons[nombreTroncons - 1].parcours[(troncons[nombreTroncons - 1].nombresubdivisions) - 1].codeRue);
    fclose(file);
}

void sauvegarderFlotteBus(Bus flotteBus[], int nombreBus, char *nomFichier)
{
    FILE *file = fopen(nomFichier, "w");
    for (int i = 0; i < nombreBus - 1; i++)
    {
        fprintf(file, "%d %d %d %d %d %d %d %d\n", flotteBus[i].id, flotteBus[i].idZoneCourante, flotteBus[i].row, flotteBus[i].column, flotteBus[i].enRoute, flotteBus[i].idLigneCourante, flotteBus[i].sensCourant, flotteBus[i].nombreTaches);
        for (int j = 0; j < flotteBus[i].nombreTaches; j++)
        {
            fprintf(file, "%d %d %d %d %d %d\n", flotteBus[i].taches[j].id, flotteBus[i].taches[j].idLigne, flotteBus[i].taches[j].sens, flotteBus[i].taches[j].horaireDateDepart.jour, flotteBus[i].taches[j].horaireDateDepart.heure, flotteBus[i].taches[j].horaireDateDepart.minute);
        }
    }
    fprintf(file, "%d %d %d %d %d %d %d %d\n", flotteBus[nombreBus - 1].id, flotteBus[nombreBus - 1].idZoneCourante, flotteBus[nombreBus - 1].row, flotteBus[nombreBus - 1].column, flotteBus[nombreBus - 1].enRoute, flotteBus[nombreBus - 1].idLigneCourante, flotteBus[nombreBus - 1].sensCourant, flotteBus[nombreBus - 1].nombreTaches);
    for (int i = 0; i < (flotteBus[nombreBus - 1].nombreTaches) - 1; i++)
    {
        fprintf(file, "%d %d %d %d %d %d\n", flotteBus[nombreBus - 1].taches[i].id, flotteBus[nombreBus - 1].taches[i].idLigne, flotteBus[nombreBus - 1].taches[i].sens, flotteBus[nombreBus - 1].taches[i].horaireDateDepart.jour, flotteBus[nombreBus - 1].taches[i].horaireDateDepart.heure, flotteBus[nombreBus - 1].taches[i].horaireDateDepart.minute);
    }
    fprintf(file, "%d %d %d %d %d %d", flotteBus[nombreBus - 1].taches[(flotteBus[nombreBus - 1].nombreTaches) - 1].id, flotteBus[nombreBus - 1].taches[(flotteBus[nombreBus - 1].nombreTaches) - 1].idLigne, flotteBus[nombreBus - 1].taches[(flotteBus[nombreBus - 1].nombreTaches) - 1].sens, flotteBus[nombreBus - 1].taches[(flotteBus[nombreBus - 1].nombreTaches) - 1].horaireDateDepart.jour, flotteBus[nombreBus - 1].taches[(flotteBus[nombreBus - 1].nombreTaches) - 1].horaireDateDepart.heure, flotteBus[nombreBus - 1].taches[(flotteBus[nombreBus - 1].nombreTaches) - 1].horaireDateDepart.minute);
    fclose(file);
}
int rechercherLigneSens(int idZoneSrc, int idZoneDest, Ligne lignes[], int nombreLignes, int idLigne)
{
    int j = 0;
    while (j < lignes[idLigne].nombreZones)
    {
        if (lignes[idLigne].idZones[j] == idZoneSrc)
        {
            return 0;
        }
        else
        {
            if (lignes[idLigne].idZones[j] == idZoneDest)
            {
                return 1;
            }
        }
        j++;
    }
}
void affecterPersonneZone(Zone zones[], Personne pers)
{
    int j = zones[pers.idZoneHabitat].nombrePersonnes;
    zones[pers.idZoneHabitat].personnes[j] = pers;
    zones[pers.idZoneHabitat].nombrePersonnes++;
}

void genererPersonne(Zone zones[], int nombreZones, Ligne lignes[], int nombreLignes)
{
    srand(time(NULL));
    Personne pers;
    for (int i = 0; i < 300; i++)
    {
        pers.cin = i + 1;
        pers.idZoneHabitat = rand() % 10;
        do
        {
            pers.idZoneTravail = rand() % 10;
        } while (pers.idZoneHabitat == pers.idZoneTravail);
        pers.idZoneCourante = pers.idZoneHabitat;
        pers.intentionVoyage = 0;
        pers.idLigneCourante = -1;
        pers.sensCourant = -1;
        pers.nombreActivites = 3;
        pers.activites[0].id = 0;
        pers.activites[0].horaireDateSouhaite.jour = 0;
        pers.activites[0].horaireDateSouhaite.heure = 6 + rand() % 3;
        int nb = rand() % 3;
        int values[] = {0, 15, 30};
        pers.activites[0].horaireDateSouhaite.minute = 0 + values[nb];
        pers.activites[0].dureeHeureMinute.jour = 0;
        pers.activites[0].dureeHeureMinute.heure = 8;
        pers.activites[0].dureeHeureMinute.minute = 0;
        pers.activites[0].typeActivite = 1;
        pers.activites[0].idZoneSrc = pers.idZoneHabitat;
        pers.activites[0].idZoneDest = pers.idZoneTravail;
        int l, s;
        l = 0;
        s = rechercherLigneSens(pers.activites[0].idZoneSrc, pers.activites[0].idZoneDest, lignes, nombreLignes, l);
        pers.activites[0].idLigne = l;
        pers.activites[0].sens = s;

        pers.activites[1].id = 1;
        pers.activites[1].horaireDateSouhaite.jour = 0;
        pers.activites[1].horaireDateSouhaite.heure = 18;
        nb = rand() % 3;
        pers.activites[1].horaireDateSouhaite.minute = 0 + values[nb];
        pers.activites[1].dureeHeureMinute.jour = 0;
        pers.activites[1].dureeHeureMinute.heure = 2;
        pers.activites[1].dureeHeureMinute.minute = 0;
        pers.activites[1].typeActivite = 2;
        pers.activites[1].idZoneSrc = pers.idZoneTravail;
        do
        {
            pers.activites[1].idZoneDest = rand() % 10;

        } while (pers.activites[1].idZoneDest == pers.activites[1].idZoneSrc);

        s = rechercherLigneSens(pers.activites[1].idZoneSrc, pers.activites[1].idZoneDest, lignes, nombreLignes, l);
        pers.activites[1].idLigne = l;
        pers.activites[1].sens = s;

        pers.activites[2].id = 2;
        pers.activites[2].horaireDateSouhaite.jour = 0;
        pers.activites[2].horaireDateSouhaite.heure = 20;
        nb = rand() % 3;
        pers.activites[2].horaireDateSouhaite.minute = 0 + values[nb];
        pers.activites[2].dureeHeureMinute.jour = 0;
        pers.activites[2].dureeHeureMinute.heure = 10;
        pers.activites[2].dureeHeureMinute.minute = 0;
        pers.activites[2].typeActivite = 0;
        pers.activites[2].idZoneSrc = pers.activites[1].idZoneDest;
        pers.activites[2].idZoneDest = pers.idZoneHabitat;

        s = rechercherLigneSens(pers.activites[2].idZoneSrc, pers.activites[2].idZoneDest, lignes, nombreLignes, l);
        pers.activites[2].idLigne = l;
        pers.activites[2].sens = s;

        affecterPersonneZone(zones, pers);
    }
}

void afficherPersonnes(Zone zones[], int nombreZones)
{
    for (int i = 0; i < nombreZones; i++)
    {
        for (int j = 0; j < zones[i].nombrePersonnes; j++)
        {
            printf("%d %d %d %d %d %d %d %d\n", zones[i].personnes[j].cin, zones[i].personnes[j].idZoneHabitat, zones[i].personnes[j].idZoneTravail, zones[i].personnes[j].idZoneCourante, zones[i].personnes[j].intentionVoyage, zones[i].personnes[j].idLigneCourante, zones[i].personnes[j].sensCourant, zones[i].personnes[j].nombreActivites);
            for (int k = 0; k < zones[i].personnes[j].nombreActivites; k++)
            {
                printf("%d %d %d %d %d %d %d %d %d %d %d %d\n", zones[i].personnes[j].activites[k].id, zones[i].personnes[j].activites[k].horaireDateSouhaite.jour, zones[i].personnes[j].activites[k].horaireDateSouhaite.heure, zones[i].personnes[j].activites[k].horaireDateSouhaite.minute, zones[i].personnes[j].activites[k].dureeHeureMinute.jour, zones[i].personnes[j].activites[k].dureeHeureMinute.heure, zones[i].personnes[j].activites[k].dureeHeureMinute.minute, zones[i].personnes[j].activites[k].typeActivite, zones[i].personnes[j].activites[k].idZoneSrc, zones[i].personnes[j].activites[k].idZoneDest, zones[i].personnes[j].activites[k].idLigne, zones[i].personnes[j].activites[k].sens);
            }
        }
    }
}

void sauvegarderPersonnes(Zone zones[], int nombreZones, char *nomFichier)
{
    FILE *file = fopen(nomFichier, "w");
    for (int i = 0; i < nombreZones - 1; i++)
    {
        fprintf(file, "%d %d %d %d\n", zones[i].id, zones[i].row, zones[i].column, zones[i].nombrePersonnes);
        for (int j = 0; j < zones[i].nombrePersonnes; j++)
        {
            fprintf(file, "%d %d %d %d %d %d %d %d\n", zones[i].personnes[j].cin, zones[i].personnes[j].idZoneHabitat, zones[i].personnes[j].idZoneTravail, zones[i].personnes[j].idZoneCourante, zones[i].personnes[j].intentionVoyage, zones[i].personnes[j].idLigneCourante, zones[i].personnes[j].sensCourant, zones[i].personnes[j].nombreActivites);
            for (int k = 0; k < zones[i].personnes[j].nombreActivites; k++)
            {
                fprintf(file, "%d %d %d %d %d %d %d %d %d %d %d %d\n", zones[i].personnes[j].activites[k].id, zones[i].personnes[j].activites[k].horaireDateSouhaite.jour, zones[i].personnes[j].activites[k].horaireDateSouhaite.heure, zones[i].personnes[j].activites[k].horaireDateSouhaite.minute, zones[i].personnes[j].activites[k].dureeHeureMinute.jour, zones[i].personnes[j].activites[k].dureeHeureMinute.heure, zones[i].personnes[j].activites[k].dureeHeureMinute.minute, zones[i].personnes[j].activites[k].typeActivite, zones[i].personnes[j].activites[k].idZoneSrc, zones[i].personnes[j].activites[k].idZoneDest, zones[i].personnes[j].activites[k].idLigne, zones[i].personnes[j].activites[k].sens);
            }
        }
    }
    fprintf(file, "%d %d %d %d\n", zones[nombreZones - 1].id, zones[nombreZones - 1].row, zones[nombreZones - 1].column, zones[nombreZones - 1].nombrePersonnes);
    for (int j = 0; j < zones[nombreZones - 1].nombrePersonnes - 1; j++)
    {
        fprintf(file, "%d %d %d %d %d %d %d %d\n", zones[nombreZones - 1].personnes[j].cin, zones[nombreZones - 1].personnes[j].idZoneHabitat, zones[nombreZones - 1].personnes[j].idZoneTravail, zones[nombreZones - 1].personnes[j].idZoneCourante, zones[nombreZones - 1].personnes[j].intentionVoyage, zones[nombreZones - 1].personnes[j].idLigneCourante, zones[nombreZones - 1].personnes[j].sensCourant, zones[nombreZones - 1].personnes[j].nombreActivites);
        for (int k = 0; k < zones[nombreZones - 1].personnes[j].nombreActivites; k++)
        {
            fprintf(file, "%d %d %d %d %d %d %d %d %d %d %d %d\n", zones[nombreZones - 1].personnes[j].activites[k].id, zones[nombreZones - 1].personnes[j].activites[k].horaireDateSouhaite.jour, zones[nombreZones - 1].personnes[j].activites[k].horaireDateSouhaite.heure, zones[nombreZones - 1].personnes[j].activites[k].horaireDateSouhaite.minute, zones[nombreZones - 1].personnes[j].activites[k].dureeHeureMinute.jour, zones[nombreZones - 1].personnes[j].activites[k].dureeHeureMinute.heure, zones[nombreZones - 1].personnes[j].activites[k].dureeHeureMinute.minute, zones[nombreZones - 1].personnes[j].activites[k].typeActivite, zones[nombreZones - 1].personnes[j].activites[k].idZoneSrc, zones[nombreZones - 1].personnes[j].activites[k].idZoneDest, zones[nombreZones - 1].personnes[j].activites[k].idLigne, zones[nombreZones - 1].personnes[j].activites[k].sens);
        }
    }
    fprintf(file, "%d %d %d %d %d %d %d %d\n", zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].cin, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].idZoneHabitat, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].idZoneTravail, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].idZoneCourante, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].intentionVoyage, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].idLigneCourante, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].sensCourant, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites);
    for (int k = 0; k < (zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites) - 1; k++)
    {
        fprintf(file, "%d %d %d %d %d %d %d %d %d %d %d %d\n", zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[k].id, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[k].horaireDateSouhaite.jour, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[k].horaireDateSouhaite.heure, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[k].horaireDateSouhaite.minute, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[k].dureeHeureMinute.jour, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[k].dureeHeureMinute.heure, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[k].dureeHeureMinute.minute, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[k].typeActivite, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[k].idZoneSrc, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[k].idZoneDest, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[k].idLigne, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[k].sens);
    }
    fprintf(file, "%d %d %d %d %d %d %d %d %d %d %d %d", zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites - 1].id, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites - 1].horaireDateSouhaite.jour, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites - 1].horaireDateSouhaite.heure, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites - 1].horaireDateSouhaite.minute, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites - 1].dureeHeureMinute.jour, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites - 1].dureeHeureMinute.heure, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites - 1].dureeHeureMinute.minute, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites - 1].typeActivite, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites - 1].idZoneSrc, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites - 1].idZoneDest, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites - 1].idLigne, zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].activites[zones[nombreZones - 1].personnes[zones[nombreZones - 1].nombrePersonnes - 1].nombreActivites - 1].sens);

    fclose(file);
}

void chargerPersonnes(Zone zones[], int *nombreZones, char *nomFichier)
{
    FILE *file = fopen(nomFichier, "r");
    if (file == NULL)
    {
        printf("Error ZonePersonne");
        exit(1);
    }
    (*nombreZones) = 0;
    while (!feof(file))
    {
        fscanf(file, "%d %d %d %d", &zones[*nombreZones].id, &zones[*nombreZones].row, &zones[*nombreZones].column, &zones[*nombreZones].nombrePersonnes);
        for (int j = 0; j < zones[*nombreZones].nombrePersonnes; j++)
        {
            fscanf(file, "%d %d %d %d %d %d %d %d", &zones[*nombreZones].personnes[j].cin, &zones[*nombreZones].personnes[j].idZoneHabitat, &zones[*nombreZones].personnes[j].idZoneTravail, &zones[*nombreZones].personnes[j].idZoneCourante, &zones[*nombreZones].personnes[j].intentionVoyage, &zones[*nombreZones].personnes[j].idLigneCourante, &zones[*nombreZones].personnes[j].sensCourant, &zones[*nombreZones].personnes[j].nombreActivites);
            for (int k = 0; k < zones[*nombreZones].personnes[j].nombreActivites; k++)
            {
                fscanf(file, "%d %d %d %d %d %d %d %d %d %d %d %d", &zones[*nombreZones].personnes[j].activites[k].id, &zones[*nombreZones].personnes[j].activites[k].horaireDateSouhaite.jour, &zones[*nombreZones].personnes[j].activites[k].horaireDateSouhaite.heure, &zones[*nombreZones].personnes[j].activites[k].horaireDateSouhaite.minute, &zones[*nombreZones].personnes[j].activites[k].dureeHeureMinute.jour, &zones[*nombreZones].personnes[j].activites[k].dureeHeureMinute.heure, &zones[*nombreZones].personnes[j].activites[k].dureeHeureMinute.minute, &zones[*nombreZones].personnes[j].activites[k].typeActivite, &zones[*nombreZones].personnes[j].activites[k].idZoneSrc, &zones[*nombreZones].personnes[j].activites[k].idZoneDest, &zones[*nombreZones].personnes[j].activites[k].idLigne, &zones[*nombreZones].personnes[j].activites[k].sens);
            }
        }
        (*nombreZones)++;
    }

    fclose(file);
}

void remplissageComplet(Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int *nombreZones, int *nombreLignes, int *nombreTroncons, int *nombreBus)
{
    chargerZones(zones, nombreZones);
    chargerLignes(lignes, nombreLignes);

    chargerTroncons(troncons, nombreTroncons);
    chargerFlotteBus(flotteBus, nombreBus);
}

void affichageComplet(Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus)
{
    afficherZones(zones, nombreZones);
    afficherPersonnes(zones, nombreZones);
    afficherLignes(lignes, nombreLignes);
    afficherTroncons(troncons, nombreTroncons);
    afficherFlotteBus(flotteBus, nombreBus);
}

void sauvegardeComplete(Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus)
{
    sauvegarderZones(zones, nombreZones, "zones_sauv.txt");
    sauvegarderLignes(lignes, nombreLignes, "lignes_sauv.txt");
    sauvegarderTroncons(troncons, nombreTroncons, "troncons_sauv.txt");
    sauvegarderFlotteBus(flotteBus, nombreBus, "flotteBus_sauv.txt");
    sauvegarderPersonnes(zones, nombreZones, "personnes_sauv.txt");
}

int calculerDistance(int idZoneSrc, int idZoneDest, Ligne lignes[], int idLigne, Troncon troncons[], int nombreLignes, int nombreTroncons)
{
    int des = 0, k = 0;

    while (des == 0)
    {
        if (rechercherLigneSens(idZoneSrc, idZoneDest, lignes, nombreLignes, idLigne) == 0)
        {
            while ((k <= nombreTroncons) && (troncons[k].idZoneSrc != idZoneSrc))
            {
                k++;
            }

            while ((k <= nombreTroncons) && (troncons[k].idZoneDest != idZoneDest))
            {
                des += troncons[k].distance;
                k++;
            }
            return des;
        }
        else
        {
            if (rechercherLigneSens(idZoneSrc, idZoneDest, lignes, nombreLignes, idLigne) == 1)
            {
                while ((k <= nombreTroncons) && (troncons[k].idZoneSrc != idZoneDest))
                {
                    k++;
                }

                while ((k <= nombreTroncons) && (troncons[k].idZoneDest != idZoneSrc))
                {
                    des += troncons[k].distance;
                    k++;
                }
                return des;
            }
        }
    }
}

void initialiserCarte(CaseCarte cartegeo[20][20], Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus)
{
    int i, j, r, c;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            cartegeo[i][j].rue = 0;
            cartegeo[i][j].zone = -1;
            cartegeo[i][j].bus = -1;
        }
    }
    for (i = 0; i < nombreTroncons; i++)
    {
        for (j = 0; j < troncons[i].nombresubdivisions; j++)
        {
            r = troncons[i].parcours[j].row;
            c = troncons[i].parcours[j].column;
            cartegeo[r][c].rue = troncons[i].parcours[j].codeRue;
        }
    }
    for (i = 0; i < nombreZones; i++)
    {
        r = zones[i].row;
        c = zones[i].column;
        cartegeo[r][c].zone = zones[i].id;
    }

    for (i = 0; i < nombreBus; i++)
    {
        r = flotteBus[i].row;
        c = flotteBus[i].column;
        if (cartegeo[r][c].bus == -1)
        {
            cartegeo[r][c].bus = flotteBus[i].id;
        }
        else
        {
            cartegeo[r][c].bus = -2;
        }
    }
}

void afficherCarteGeo(CaseCarte cartegeo[20][20], Zone zones[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus)
{
    int i, j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (cartegeo[i][j].zone != -1 && cartegeo[i][j].bus == -1)
            {
                int nb = 0;
                for (int k = 0; k < zones[cartegeo[i][j].zone].nombrePersonnes; k++)
                {
                    if (zones[cartegeo[i][j].zone].personnes[k].cin != -1)
                        nb++;
                }
                if (nb <= 9)
                {
                    printf(" %dZ%d", nb, cartegeo[i][j].zone);
                }
                else
                {
                    printf("%dZ%d", nb, cartegeo[i][j].zone);
                }
            }
            else
            {
                if (cartegeo[i][j].zone != -1 && cartegeo[i][j].bus != -1)
                {
                    if (cartegeo[i][j].bus == -2)
                    {
                        printf("Z%dbM", cartegeo[i][j].zone);
                    }
                    else
                        printf("Z%db%d", cartegeo[i][j].zone, cartegeo[i][j].bus);
                }
                else
                {
                    if (cartegeo[i][j].bus != -1)
                    {
                        if (cartegeo[i][j].bus == -2)
                            printf("[bM]");
                        else
                        {
                            int nb = 0;
                            for (int k = 0; k < flotteBus[cartegeo[i][j].bus].nombrePassagers; k++)
                            {
                                if (flotteBus[cartegeo[i][j].bus].passagers[k].cin != -1)
                                    nb++;
                            }
                            if (nb <= 9)
                            {
                                printf(" %db%d", nb, cartegeo[i][j].bus);
                            }
                            else
                                printf("%db%d", nb, cartegeo[i][j].bus);
                        }
                    }
                    else
                    {
                        if (cartegeo[i][j].rue == 3 || cartegeo[i][j].rue == 2 || cartegeo[i][j].rue == 1)
                            printf("%c%c%c%c", 205, 205, 205, 205);
                        else
                        {
                            if (cartegeo[i][j].rue == 12 || cartegeo[i][j].rue == 4 || cartegeo[i][j].rue == 8)
                                printf("  %c ", 186);
                            else
                            {
                                if (cartegeo[i][j].rue == 7)
                                    printf(" %c%c%c", 205, 203, 205);
                                else
                                {
                                    if (cartegeo[i][j].rue == 9)
                                        printf("%c%c%c ", 205, 205, 188);
                                    else
                                    {
                                        if (cartegeo[i][j].rue == 10)
                                            printf("  %c%c", 200, 205);
                                        else
                                        {
                                            if (cartegeo[i][j].rue == 11)
                                                printf("  %c%c%c", 205, 202, 205);
                                            else
                                            {
                                                if (cartegeo[i][j].rue == 13)
                                                    printf("%c%c%c ", 205, 205, 185);
                                                else
                                                {
                                                    if (cartegeo[i][j].rue == 14)
                                                        printf("  %c%c", 204, 205);
                                                    else
                                                    {
                                                        if (cartegeo[i][j].rue == 15)
                                                            printf("%c%c%c%c", 205, 205, 206, 205);
                                                        else
                                                        {
                                                            if (cartegeo[i][j].rue == 5)
                                                                printf("%c%c%c ", 205, 205, 187);
                                                            else
                                                            {
                                                                if (cartegeo[i][j].rue == 6)
                                                                    printf("  %c%c", 201, 205);
                                                                else
                                                                    printf("    ");
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        printf("\n");
    }
}

int numTacheSuivante(Horaire horaireCourant, int idBusCourant, Bus flotteBus[])
{
    for (int i = 0; i < flotteBus[idBusCourant].nombreTaches; i++)
    {

        if (flotteBus[idBusCourant].taches[i].horaireDateDepart.heure == horaireCourant.heure)
        {
            if (flotteBus[idBusCourant].taches[i].horaireDateDepart.minute == horaireCourant.minute)
            {
                return flotteBus[idBusCourant].taches[i].id;
            }
        }
    }
    return -1;
}

void deplacerPersonne(Personne src[], Personne dest[], int indicePersonneSrc, int *nombrePersonnesSrc, int *nombrePersonnesDest)
{
    int i = 0;
    while (i < 40)
    {
        // printf("test deplacer \n");
        if (dest[i].cin == -1 )
        {

            dest[i].cin = src[indicePersonneSrc].cin;
            dest[i].idLigneCourante = src[indicePersonneSrc].idLigneCourante;
            dest[i].idZoneHabitat = src[indicePersonneSrc].idZoneHabitat;
            dest[i].idZoneTravail = src[indicePersonneSrc].idZoneTravail;
            dest[i].sensCourant = src[indicePersonneSrc].sensCourant;
            dest[i].idZoneCourante = src[indicePersonneSrc].idZoneCourante;
            dest[i].idZoneDest = src[indicePersonneSrc].idZoneDest;
            dest[i].intentionVoyage = src[indicePersonneSrc].intentionVoyage;
            dest[i].nombreActivites = src[indicePersonneSrc].nombreActivites;
            for (int j = 0; j < src[indicePersonneSrc].nombreActivites; j++)
            {
                dest[i].activites[j].id = src[indicePersonneSrc].activites[j].id;
                dest[i].activites[j].horaireDateSouhaite.jour = src[indicePersonneSrc].activites[j].horaireDateSouhaite.jour;
                dest[i].activites[j].horaireDateSouhaite.heure = src[indicePersonneSrc].activites[j].horaireDateSouhaite.heure;
                dest[i].activites[j].horaireDateSouhaite.minute = src[indicePersonneSrc].activites[j].horaireDateSouhaite.minute;
                dest[i].activites[j].dureeHeureMinute.jour = src[indicePersonneSrc].activites[j].dureeHeureMinute.jour;
                dest[i].activites[j].dureeHeureMinute.heure = src[indicePersonneSrc].activites[j].dureeHeureMinute.heure;
                dest[i].activites[j].dureeHeureMinute.minute = src[indicePersonneSrc].activites[j].dureeHeureMinute.minute;
                dest[i].activites[j].typeActivite = src[indicePersonneSrc].activites[j].typeActivite;
                dest[i].activites[j].idZoneSrc = src[indicePersonneSrc].activites[j].idZoneSrc;
                dest[i].activites[j].idZoneDest = src[indicePersonneSrc].activites[j].idZoneDest;
                dest[i].activites[j].idLigne = src[indicePersonneSrc].activites[j].idLigne;
                dest[i].activites[j].sens = src[indicePersonneSrc].activites[j].sens;
            }
            
            (*nombrePersonnesDest)++;
            (*nombrePersonnesSrc)--;
            src[indicePersonneSrc].cin = -1;
            break;
        }
        else
            i++;
    }

    // le mise à jour de l'id de zone courante et destination se fait dans la fonction mére
}

void deplacerBus(CaseCarte cartegeo[20][20], int idBusCourant, Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus, Horaire horaireCourant)
{
    int i = 0, j = 0, dest, k = 0, z = 0, r, c, p = 0;
    while (flotteBus[i].id != idBusCourant)
    {
        i++;
    }
    r = flotteBus[i].row;
    c = flotteBus[i].column;

    if (flotteBus[i].enRoute == 1)
    {
        if (flotteBus[i].sensCourant == 0)
        {
            // recherche de l'emplacement de la zone courante
            while (flotteBus[i].idZoneCourante != lignes[0].idZones[j])
            {
                j++;
            }
            // affectation de la zone destination
            dest = lignes[0].idZones[j + 1];
            // recherche de la zone
            while (flotteBus[i].idZoneCourante != zones[z].id)
            {
                z++;
            }

            // recherche de tronçon
            while (troncons[k].idZoneDest != dest || troncons[k].idZoneSrc != flotteBus[idBusCourant].idZoneCourante)
            {
                k++;
            }

            if (flotteBus[i].row == zones[z].row && flotteBus[i].column == zones[z].column)
            {

                flotteBus[i].row = troncons[k].parcours[0].row;
                flotteBus[i].column = troncons[k].parcours[0].column;
                cartegeo[flotteBus[i].row][flotteBus[i].column].bus = i;
                if (cartegeo[r][c].bus != -2)
                {
                    cartegeo[r][c].bus = -1;
                }
            }
            else
            {

                // recherche dans quelle subdiv
                while ((troncons[k].parcours[p].row != flotteBus[i].row || troncons[k].parcours[p].column != flotteBus[i].column) && p < troncons[k].nombresubdivisions)
                {
                    p++;
                }
                if (p == troncons[k].nombresubdivisions - 1)
                {
                    z = 0;
                    while (dest != zones[z].id)
                    {
                        z++;
                    }
                    flotteBus[i].row = zones[z].row;
                    flotteBus[i].column = zones[z].column;
                    flotteBus[i].idZoneCourante = zones[z].id;
                    if (dest == lignes[0].idZones[lignes[0].nombreZones - 1])
                    {
                        flotteBus[i].enRoute = 0;
                        flotteBus[i].sensCourant = 1;
                        flotteBus[i].nombrePassagers = 0;
                        if (cartegeo[flotteBus[i].row][flotteBus[i].column].bus != -1)
                            cartegeo[flotteBus[i].row][flotteBus[i].column].bus = -2;
                        else
                            cartegeo[flotteBus[i].row][flotteBus[i].column].bus = i;
                        if (cartegeo[r][c].bus == flotteBus[i].id || cartegeo[r][c].bus == -2)
                            cartegeo[r][c].bus = -1;
                        return;
                    }
                }
                else
                {

                    flotteBus[i].row = troncons[k].parcours[p + 1].row;
                    flotteBus[i].column = troncons[k].parcours[p + 1].column;
                }
                if (i > 4)
                {
                    if (cartegeo[flotteBus[i].row][flotteBus[i].column].bus != -1)
                        cartegeo[flotteBus[i].row][flotteBus[i].column].bus = -2;
                    else
                        cartegeo[flotteBus[i].row][flotteBus[i].column].bus = i;
                }
                else
                    cartegeo[flotteBus[i].row][flotteBus[i].column].bus = i;

                if (cartegeo[r][c].bus == flotteBus[i].id || cartegeo[r][c].bus == -2)
                    cartegeo[r][c].bus = -1;
            }
        }
        else
        {
            j = z = p = k = 0;
            // recherche de l'emplacement de la zone courante
            while (flotteBus[i].idZoneCourante != lignes[0].idZones[j])
            {
                j++;
            }
            // affectation de la zone destination
            dest = lignes[0].idZones[j - 1];
            // recherche de la zone
            while (flotteBus[i].idZoneCourante != zones[z].id)
            {
                z++;
            }

            // recherche de tronçon
            while (troncons[k].idZoneSrc != dest || troncons[k].idZoneDest != flotteBus[i].idZoneCourante)
            {
                k++;
            }
            if (flotteBus[i].row == zones[z].row && flotteBus[i].column == zones[z].column)
            {
                flotteBus[i].row = troncons[k].parcours[troncons[k].nombresubdivisions - 1].row;
                flotteBus[i].column = troncons[k].parcours[troncons[k].nombresubdivisions - 1].column;
                cartegeo[flotteBus[i].row][flotteBus[i].column].bus = i;
                if (cartegeo[r][c].bus != -2)
                {
                    cartegeo[r][c].bus = -1;
                }
            }
            else
            {
                // recherche dans quelle subdiv
                while ((troncons[k].parcours[p].row != flotteBus[i].row || troncons[k].parcours[p].column != flotteBus[i].column) && p < troncons[k].nombresubdivisions)
                {
                    p++;
                }
                if (p == 0)
                {
                    z = 0;
                    while (dest != zones[z].id)
                    {
                        z++;
                    }
                    flotteBus[i].row = zones[z].row;
                    flotteBus[i].column = zones[z].column;
                    flotteBus[i].idZoneCourante = zones[z].id;
                    if (dest == lignes[0].idZones[0])
                    {
                        flotteBus[i].enRoute = 0;
                        flotteBus[i].sensCourant = 0;
                        if (cartegeo[flotteBus[i].row][flotteBus[i].column].bus != -1)
                            cartegeo[flotteBus[i].row][flotteBus[i].column].bus = -2;
                        else
                            cartegeo[flotteBus[i].row][flotteBus[i].column].bus = i;
                        if (cartegeo[r][c].bus == flotteBus[i].id || cartegeo[r][c].bus == -2)
                            cartegeo[r][c].bus = -1;
                        return;
                    }
                }
                else
                {
                    flotteBus[i].row = troncons[k].parcours[p - 1].row;
                    flotteBus[i].column = troncons[k].parcours[p - 1].column;
                }
                if (i > 4)
                {
                    if (cartegeo[flotteBus[i].row][flotteBus[i].column].bus != -1)
                        cartegeo[flotteBus[i].row][flotteBus[i].column].bus = -2;
                    else
                        cartegeo[flotteBus[i].row][flotteBus[i].column].bus = i;
                }
                else
                    cartegeo[flotteBus[i].row][flotteBus[i].column].bus = i;

                if (cartegeo[r][c].bus == flotteBus[i].id || cartegeo[r][c].bus == -2)
                    cartegeo[r][c].bus = -1;
            }
        }
    }
}

void majPersonnesUneZone(Horaire horaireCourant, Zone zones[], int idZone, Ligne lignes[], int nombreLignes, Troncon troncons[], int nombreTroncons)
{
    for (int i = 0; i < zones[idZone].nombrePersonnes; i++)
    {
        for (int j = 0; j < zones[idZone].personnes[i].nombreActivites; j++)
        {
            if (horaireCourant.heure == zones[idZone].personnes[i].activites[j].horaireDateSouhaite.heure && horaireCourant.minute == zones[idZone].personnes[i].activites[j].horaireDateSouhaite.minute)
            {
                zones[idZone].personnes[i].intentionVoyage = 1;
            }
        }
    }
}

void majPersonnesToutesZones(Horaire horaireCourant, Zone zones[], int nombreZones, Ligne lignes[], int nombreLignes, Troncon troncons[], int nombreTroncons)
{
    for (int k = 0; k < nombreZones; k++)
    {
        for (int i = 0; i < zones[k].nombrePersonnes; i++)
        {
            for (int j = 0; j < zones[k].personnes[i].nombreActivites; j++)
            {
                if (horaireCourant.heure == zones[k].personnes[i].activites[j].horaireDateSouhaite.heure && horaireCourant.minute == zones[k].personnes[i].activites[j].horaireDateSouhaite.minute)
                {
                    zones[k].personnes[i].intentionVoyage = 1;
                }
            }
        }
    }
}

Ticket venteTicket(Horaire horaireVente, int idZoneSrc, int idZoneDest, int idLigne, int sens, Ligne lignes[], Troncon troncons[], int nombreLignes, int nombreTroncons)
{
    Ticket tic;
    tic.zoneSrc = idZoneSrc;
    tic.zoneDest = idZoneDest;
    tic.idLigne = idLigne;
    tic.sens = sens;
    tic.dateVente.jour = horaireVente.jour;
    tic.dateVente.heure = horaireVente.heure;
    tic.dateVente.minute = horaireVente.minute;
    tic.distance = calculerDistance(idZoneSrc, idZoneDest, lignes, idLigne, troncons, nombreLignes, nombreTroncons);

    if (tic.distance <= 30)
        tic.prix = 300;
    else if (tic.distance <= 60)
        tic.prix = 600;
    else if (tic.distance <= 90)
        tic.prix = 900;
    else
        tic.prix = 1200;

    return tic;
}

void embarquerPersonnes(Zone zones[], Bus flotteBus[], int idZone, int idBus, Horaire horaireCourant, Ligne lignes[], Troncon troncons[], int nombreLignes, int nombreTroncons)
{
    int sens;
    for (int i = 0; i < zones[idZone].nombrePersonnes; i++)
    {
        if (zones[idZone].personnes[i].intentionVoyage == 1 && zones[idZone].personnes[i].cin != -1)
        {
            for (int j = 0; j < zones[idZone].personnes[i].nombreActivites; j++)
            {
                if (zones[idZone].personnes[i].activites[j].horaireDateSouhaite.minute <= horaireCourant.minute && zones[idZone].personnes[i].activites[j].horaireDateSouhaite.heure <= horaireCourant.heure)
                {
                    zones[idZone].personnes[i].idZoneDest = zones[idZone].personnes[i].activites[j].idZoneDest;
                    sens = zones[idZone].personnes[i].activites[j].sens;
                }
            }
            if (sens == flotteBus[idBus].sensCourant)
            {
                if (flotteBus[idBus].nombrePassagers < 24)
                {

                    flotteBus[idBus].tickets[flotteBus[idBus].nombreTickets] = venteTicket(horaireCourant, zones[idZone].personnes[i].idZoneCourante, zones[idZone].personnes[i].idZoneDest, flotteBus[idBus].idLigneCourante, flotteBus[idBus].sensCourant, lignes, troncons, nombreLignes, nombreTroncons);

                    flotteBus[idBus].tickets[flotteBus[idBus].nombreTickets].idBus = idBus;

                    flotteBus[idBus].nombreTickets++;

                    deplacerPersonne(zones[idZone].personnes, flotteBus[idBus].passagers, i, &zones[idZone].nombrePersonnes, &flotteBus[idBus].nombrePassagers);
                }
            }
        }
    }
}

void debarquerPersonnes(Zone zones[], Bus flotteBus[], int idZone, int idBus)
{
    for (int i = 0; i < flotteBus[idBus].nombrePassagers; i++)
    {
        if (flotteBus[idBus].passagers[i].idZoneDest == idZone)
        {
            flotteBus[idBus].passagers[i].idZoneCourante = idZone;
            deplacerPersonne(flotteBus[idBus].passagers, zones[idZone].personnes, i, &flotteBus[idBus].nombrePassagers, &zones[idZone].nombrePersonnes);
        }
    }
}

int calculerGainNet(Bus flotteBus[], int nombreBus, Ligne lignes[], int nombreLignes)
{
    int gain = 0;
    for (int i = 0; i < nombreBus; i++)
    {
        for (int j = 0; j < flotteBus[i].nombreTickets; j++)
        {
            gain += flotteBus[i].tickets[j].prix;
        }
    }
    return gain;
}

/*

void deplacertEtReinitialiserTicketsBus(Bus flotteBus[],int nombreBus, Ticket tickets[],int *nombreTicket)
{

    for(int i=0;i<nombreBus;i++)
    {
        for(int j=0;j<flotteBus[i].nombreTickets;j++)
        {
            tickets[*nombreTicket]=flotteBus[i].tickets[j];
            (*nombreTicket)++;
        }
        flotteBus[i].nombreTickets = 0;
    }
}
*/
void afficherStatistiques(Bus flotteBus[], int nombreBus, Ligne lignes[], int nombreLignes)
{
    printf("Le Gain Total est %d Millimes \n", calculerGainNet(flotteBus, nombreBus, lignes, nombreLignes));
}

void sauvegarderRapport(char *nomFichier, Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus)
{
    FILE *file = fopen(nomFichier, "w");
    fprintf(file, "Le Gain Total est %d Millimes ", calculerGainNet(flotteBus, nombreBus, lignes, nombreLignes));
    fclose(file);
}

void deroulerSemaine(CaseCarte cartegeo[20][20], Ticket tickets[], Zone zones[], Ligne lignes[], Troncon troncons[], Bus flotteBus[], int nombreZones, int nombreLignes, int nombreTroncons, int nombreBus)
{
    int j, h, m, i, idbus, idzone, k, choix;
    Horaire now, next;
    next.jour = 0;
    next.heure = 6;
    next.minute = 0;
    initialiserCarte(cartegeo, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
    for (j = 0; j < 7; j++)
    {
        for (h = 6; h <= 20; h++)
        {
            for (m = 0; m <= 59; m++)
            {

                now.jour = j;
                now.heure = h;
                now.minute = m;
                majPersonnesToutesZones(now, zones, nombreZones, lignes, nombreLignes, troncons, nombreTroncons);

                for (i = 0; i < nombreBus; i++) // préraper le bus qui va démarrer
                {

                    idbus = flotteBus[i].id;
                    k = numTacheSuivante(now, idbus, flotteBus);
                    if (k > -1)
                    {
                        flotteBus[i].enRoute = 1;
                    }


                    if (cartegeo[flotteBus[i].row][flotteBus[i].column].zone != -1)
                    {
                        idzone = cartegeo[flotteBus[i].row][flotteBus[i].column].zone;
                        if (flotteBus[i].enRoute == 1)
                        {
                            debarquerPersonnes(zones, flotteBus, idzone, idbus);
                            
                            embarquerPersonnes(zones, flotteBus, idzone, idbus, now, lignes, troncons, nombreLignes, nombreTroncons);
                            
                        }
                    }

                    deplacerBus(cartegeo, idbus, zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus, now);
                }
                // afficherCarteGeo(cartegeo, zones, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);

                if (now.jour == next.jour && now.heure == next.heure && now.minute == next.minute)
                {
                    printf("\n Le temps est : %d:%d \n", h, m);
                    afficherCarteGeo(cartegeo, zones, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
                    sauvegardeComplete(zones, lignes, troncons, flotteBus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
                    printf("Veuillez choisir l'un des vitesses suivant : \n1 : Une minute \n2 : 10 minutes\n3 : Une heure \n4 : 4 heures \n5 : Un jour \n6 : Quitter \nVotre choix : ");
                    scanf("%d", &choix);

                    switch (choix)
                    {
                    case 1:
                        if (m == 59)
                        {
                            if (h >= 20)
                            {
                                next.jour = now.jour + 1;
                                next.heure = 0;
                                next.minute = 0;
                            }
                            else
                            {
                                next.jour = now.jour;
                                next.heure = now.heure + 1;
                                next.minute = 0;
                            }
                        }
                        else
                        {
                            next.jour = now.jour;
                            next.heure = now.heure;
                            next.minute = now.minute + 1;
                        }
                        break;
                    case 2:

                        if (m + 10 > 59)
                        {
                            if (h >= 20)
                            {
                                next.jour = now.jour + 1;
                                next.heure = 0;
                                next.minute = 10 - (59 - m);
                            }
                            else
                            {
                                next.jour = now.jour;
                                next.heure = now.heure + 1;
                                next.minute = 10 - (59 - m);
                            }
                        }
                        else
                        {
                            next.jour = now.jour;
                            next.heure = now.heure;
                            next.minute = now.minute + 10;
                        }
                        break;
                    case 3:
                        if (h >= 20 )
                        {
                            next.jour = now.jour + 1;
                            next.heure = 0;
                            next.minute = now.minute;
                        }
                        else
                        {
                            next.jour = now.jour;
                            next.heure = now.heure + 1;
                            next.minute = now.minute;
                        }
                        break;
                    case 4:
                        if (h + 4 > 20)
                        {
                            next.jour = now.jour + 1;
                            next.heure = 4 - (20 - h);
                            next.minute = now.minute;
                        }
                        else
                        {
                            next.jour = now.jour;
                            next.heure = now.heure + 4;
                            next.minute = now.minute;
                        }
                        break;
                    case 5:
                        next.jour = now.jour + 1;
                        next.heure = now.heure;
                        next.minute = now.minute;
                        break;
                    case 6:
                        printf("\n");
                        return;
                    default:
                        printf("choix invalide \n");
                    }
                }
            }
        }
    }
}

int main()
{
    CaseCarte cartegeo[20][20];
    Zone zones[10];
    Bus flottebus[10];
    Ligne lignes[5];
    Troncon troncons[10];
    Ticket tickets[10000];
    int nombreZones = 0, nombreLignes = 0, nombreTroncons = 0, nombreBus = 0, distance, choix;

    do
    {
        printf("--------------------------------------------------------------------------\n");
        printf("1: Nouvelle partie \n2: Ancienne partie \n3: Affichage des enregistrements \n4: Quitter \nDonne votre choix :  ");
        scanf("%d", &choix);
        nombreZones = 0;
        nombreLignes = 0;
        nombreTroncons = 0;
        nombreBus = 0;
        chdir("D:\\Iset\\S2\\Mini Projet\\mini projet");
        switch (choix)
        {
        case 1:
            remplissageComplet(zones, lignes, troncons, flottebus, &nombreZones, &nombreLignes, &nombreTroncons, &nombreBus);
            genererPersonne(zones, &nombreZones, lignes, &nombreLignes);
            deroulerSemaine(cartegeo, tickets, zones, lignes, troncons, flottebus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
            sauvegardeComplete(zones, lignes, troncons, flottebus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
            afficherStatistiques(flottebus, nombreBus, lignes, nombreLignes);
            sauvegarderRapport("statistique_sauv.txt", zones, lignes, troncons, flottebus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
            break;
        case 2:
            remplissageComplet(zones, lignes, troncons, flottebus, &nombreZones, &nombreLignes, &nombreTroncons, &nombreBus);
            chargerPersonnes(zones, &nombreZones, "personnes_sauv.txt");
            deroulerSemaine(cartegeo, tickets, zones, lignes, troncons, flottebus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
            sauvegardeComplete(zones, lignes, troncons, flottebus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
            afficherStatistiques(flottebus, nombreBus, lignes, nombreLignes);
            sauvegarderRapport("statistique_sauv.txt", zones, lignes, troncons, flottebus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
            break;
        case 3:
            remplissageComplet(zones, lignes, troncons, flottebus, &nombreZones, &nombreLignes, &nombreTroncons, &nombreBus);
            chargerPersonnes(zones, &nombreZones, "personnes_sauv.txt");
            affichageComplet(zones, lignes, troncons, flottebus, nombreZones, nombreLignes, nombreTroncons, nombreBus);
            break;
        case 4:
            printf("Au revoir !\n ");
            break;
        default:
            printf("Choix invalide \n");
        }
    } while (choix != 4);

    return 0;
}
