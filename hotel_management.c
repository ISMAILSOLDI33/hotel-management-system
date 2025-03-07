#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_CHAMBRES 100
#define MAX_RESERVATIONS 100

// Structure pour repr senter une chambre
typedef struct {
    int numero;
    char type[10];       // "simple", "double", "suite"
    float prix_par_nuit;
    char statut[10];     // "disponible", "occup e"
} Chambre;

// Structure pour repr senter une r servation
typedef struct {
    int numero;
    int numeroChambre;
    char nomClient[50];
    int nombreNuits;
    float montantTotal;
} Reservation;

// Prototypes des fonctions
void ajouter_chambre(Chambre chambres[], int *nb_chambres);
void modifier_chambre(Chambre chambres[], int nb_chambres);
void supprimer_chambre(Chambre chambres[], int *nb_chambres);
void afficher_chambres_disponibles(Chambre chambres[], int nb_chambres);
void reserverChambre(Chambre chambres[], Reservation reservations[], int *nb_chambres, int *nb_reservations);
void etat_reservation(Reservation reservations[], int nb_reservations);
void genererRapportRevenus(Reservation reservations[], int nb_reservations);

// Programme principal
int main() {
    Chambre chambres[MAX_CHAMBRES];
    Reservation reservations[MAX_RESERVATIONS];
    int nb_chambres = 0;
    int nb_reservations = 0;
    int choix;


    do {
        printf("\n--- Gestion des Chambres ---\n");
        printf("1. Ajouter une chambre\n");
        printf("2. Modifier une chambre\n");
        printf("3. Supprimer une chambre\n");
        printf("4. Afficher les chambres disponibles\n");
        printf("\n--- reservation du chamber ---\n");
        printf("5. Reserver une chambre\n");
        printf("\n--- etat de la reservation ---\n");
        printf("8. etat de la reservation\n");
        printf("9. Generer rapport des revenus\n");
        printf("\n6. Quitter \n");
        printf("\nVotre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_chambre(chambres, &nb_chambres);
                break;
            case 2:
                modifier_chambre(chambres, nb_chambres);
                break;
            case 3:
                supprimer_chambre(chambres, &nb_chambres);
                break;
            case 4:
                afficher_chambres_disponibles(chambres, nb_chambres);
                break;
            case 5:
                reserverChambre(chambres, reservations, &nb_chambres, &nb_reservations);
                break;
            case 6:
                printf("Au revoir !\n");
                break;
            case 8:
                etat_reservation(reservations, &nb_reservations);
                break;
            case 9:
                genererRapportRevenus(reservations, nb_reservations);
                break;
            default:
                printf("Choix invalide !\n");
        }
    } while (choix != 6);

    return 0;
}

// Fonction pour ajouter une chambre
void ajouter_chambre(Chambre chambres[], int *nb_chambres) {
    if (*nb_chambres >= MAX_CHAMBRES) {
        printf("Nombre maximum de chambres atteint !\n");
        return;
    }

    int numero, existe = 0;
    char type[10];
    float prix_par_nuit;

    printf("Numero de la chambre : ");
    scanf("%d", &numero);

    // V rifier l'unicit  du num ro
    for (int i = 0; i < *nb_chambres; i++) {
        if (chambres[i].numero == numero) {
            existe = 1;
            break;
        }
    }

    if (existe) {
        printf("Erreur : Une chambre avec ce num ro existe d j  !\n");
        return;
    }

    printf("Type de chambre (simple/double/suite) : ");
    scanf("%s", type);
    printf("Prix par nuit : ");
    scanf("%f", &prix_par_nuit);

    chambres[*nb_chambres].numero = numero;
    strcpy(chambres[*nb_chambres].type, type);
    chambres[*nb_chambres].prix_par_nuit = prix_par_nuit;
    strcpy(chambres[*nb_chambres].statut, "disponible");

    (*nb_chambres)++;

    printf("Chambre ajout e avec succ s !\n");
}

// Fonction pour modifier une chambre
void modifier_chambre(Chambre chambres[], int nb_chambres) {
    int numero, trouve = 0;
    char nouveau_type[10];
    float nouveau_prix;

    printf("Num ro de la chambre   modifier : ");
    scanf("%d", &numero);

    for (int i = 0; i < nb_chambres; i++) {
        if (chambres[i].numero == numero) {
            printf("Nouveau type (simple/double/suite) : ");
            scanf("%s", nouveau_type);
            printf("Nouveau prix par nuit : ");
            scanf("%f", &nouveau_prix);

            strcpy(chambres[i].type, nouveau_type);
            chambres[i].prix_par_nuit = nouveau_prix;
            trouve = 1;

            printf("Chambre modifi e avec succ s !\n");
            break;
        }
    }

    if (!trouve) {
        printf("Erreur : Chambre introuvable !\n");
    }
}

void supprimer_chambre(Chambre chambres[], int *nb_chambres) {
    int numero, trouve = 0, index = -1;

    printf("Num ro de la chambre   supprimer : ");
    scanf("%d", &numero);

    for (int i = 0; i < *nb_chambres; i++) {
        if (chambres[i].numero == numero) {
            // V rifier si la chambre est r serv e
            if (strcmp(chambres[i].statut, "occup e") == 0) {
                printf("Erreur : Impossible de supprimer une chambre occup e !\n");
                return;
            }

            index = i;
            break;
        }
    }

    if (index != -1) {
        // Supprimer la chambre en d calant les  l ments
        for (int j = index; j < *nb_chambres - 1; j++) {
            chambres[j] = chambres[j + 1];
        }
        (*nb_chambres)--;

        printf("Chambre supprim e avec succ s !\n");
    } else {
        printf("Erreur : Chambre introuvable !\n");
    }
}

// Fonction pour afficher les chambres disponibles
void afficher_chambres_disponibles(Chambre chambres[], int nb_chambres) {
    printf("\n--- Chambres disponibles ---\n");
    int disponible = 0;
    for (int i = 0; i < nb_chambres; i++) {
        if (strcmp(chambres[i].statut, "disponible") == 0) {
            printf("Num ro : %d | Type : %s | Prix : %.2f EUR\n",
                   chambres[i].numero, chambres[i].type, chambres[i].prix_par_nuit);
            disponible = 1;
        }
    }

    if (!disponible) {
        printf("Aucune chambre disponible.\n");
    }
}

// Fonction pour r server une chambre
void reserverChambre(Chambre chambres[], Reservation reservations[], int *nb_chambres, int *nb_reservations) {
    if (*nb_reservations >= MAX_RESERVATIONS) {
        printf("Nombre maximum de r servations atteint.\n");
        return;
    }

    int numeroChambre, nombreNuits, chambreTrouvee = 0;
    char nomClient[50];

    // Afficher les chambres disponibles
    afficher_chambres_disponibles(chambres, *nb_chambres);

    // V rifier s'il y a des chambres disponibles
    int disponible = 0;
    for (int i = 0; i < *nb_chambres; i++) {
        if (strcmp(chambres[i].statut, "disponible") == 0) {
            disponible = 1;
            break;
        }
    }

    if (!disponible) {
        printf("Aucune chambre disponible.\n");
        return;
    }

    // Demander le num ro de chambre avec validation
    do {
        printf("Entrez le num ro de chambre : ");
        if (scanf("%d", &numeroChambre) != 1) {
            printf("Num ro de chambre invalide.\n");
            while (getchar() != '\n');
            continue;
        }

        // V rifier si la chambre existe et est disponible
        for (int i = 0; i < *nb_chambres; i++) {
            if (chambres[i].numero == numeroChambre &&
                strcmp(chambres[i].statut, "disponible") == 0) {
                chambreTrouvee = 1;

                // Vider le buffer avant la prochaine saisie
                while (getchar() != '\n');

                // Demander les informations du client
                printf("Entrez le nom du client : ");
                if (fgets(nomClient, sizeof(nomClient), stdin) == NULL) {
                    printf("Erreur de saisie du nom.\n");
                    break;
                }

                // Supprimer le newline du nom
                nomClient[strcspn(nomClient, "\n")] = 0;

                if (strlen(nomClient) == 0) {
                    printf("Nom invalide.\n");
                    break;
                }

                // Saisie du nombre de nuits
                printf("Entrez le nombre de nuits : ");
                if (scanf("%d", &nombreNuits) != 1 || nombreNuits <= 0) {
                    printf("Nombre de nuits invalide.\n");
                    while (getchar() != '\n');
                    break;
                }

                // Cr er la r servation
                reservations[*nb_reservations].numero = *nb_reservations + 1;
                reservations[*nb_reservations].numeroChambre = numeroChambre;
                strcpy(reservations[*nb_reservations].nomClient, nomClient);
                reservations[*nb_reservations].nombreNuits = nombreNuits;

                // Trouver l'index de la chambre pour calculer le prix
                for (int j = 0; j < *nb_chambres; j++) {
                    if (chambres[j].numero == numeroChambre) {
                        reservations[*nb_reservations].montantTotal =
                            chambres[j].prix_par_nuit * nombreNuits;

                        // Mettre   jour le statut de la chambre
                        strcpy(chambres[j].statut, "occup e");
                        break;
                    }
                }

                printf("R servation effectu e avec succ s ! Num ro de r servation : %d\n",
                       reservations[*nb_reservations].numero);
                (*nb_reservations)++;
                return;
            }
        }

        if (!chambreTrouvee) {
            printf("Chambre non disponible ou inexistante.\n");
        }
    } while (!chambreTrouvee);

}
 // Fonction pour afficher letat de la reservation
void etat_reservation(Reservation reservations[], int nb_reservations) {
    int numeroReservation,i;
    int trouve = 0;


    printf("Donner le numéro de réservation : ");
    scanf("%d", &numeroReservation);

    for (i=0; i<nb_reservations; i++)
        {
        if (reservations[i].numero == numeroReservation) {
            printf("Numéro de réservation : %d\n", reservations[i].numero);
            printf("Numéro de chambre : %d\n", reservations[i].numeroChambre);
             printf("Nom du client : %s\n", reservations[i].nomClient);
            printf("Nombre de nuits : %d\n", reservations[i].nombreNuits);
            printf("Montant total : %.2f\n", reservations[i].montantTotal);
            trouve = 1;
                 break;
            }
    }

    if (!trouve) {
        printf("Réservation non trouvée.\n");
    }
}
// Fonction pour générer un rapport des revenus journaliers
void genererRapportRevenus(Reservation reservations[], int nb_reservations) {
    float revenus_journaliers = 0.0;
    int nb_reservations_jour = 0;
    time_t now;
    struct tm *current_time;

    // Obtenir la date actuelle
    time(&now);
    current_time = localtime(&now);

    printf("\n--- Rapport des Revenus Journaliers ---\n");
    printf("Date : %02d/%02d/%04d\n",
           current_time->tm_mday,
           current_time->tm_mon + 1,
           current_time->tm_year + 1900);

    // Parcourir toutes les réservations
    for (int i = 0; i < nb_reservations; i++) {
        // Dans un système réel, vous ajouteriez une date à la structure Reservation
        // Ici, on somme simplement tous les revenus
        revenus_journaliers += reservations[i].montantTotal;
        nb_reservations_jour++;
    }

    printf("Nombre de réservations : %d\n", nb_reservations_jour);
    printf("Revenus totaux : %.2f EUR\n", revenus_journaliers);

    // Statistiques supplémentaires
    if (nb_reservations_jour > 0) {
        float revenu_moyen = revenus_journaliers / nb_reservations_jour;
        printf("Revenu moyen par réservation : %.2f EUR\n", revenu_moyen);
    }
}
