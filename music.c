#include <stdio.h>
#include <stdlib.h>
#include <string.h> // biblioteca pt strcpy si strcmp

struct Melodie {
    char titlu[50];
    char artist[50];
    struct Melodie* prev;
    struct Melodie* next;
};

// initial lista e goala
struct Melodie* head = NULL;  
struct Melodie* tail = NULL;  

void adaugaMelodie(char titlu[], char artist[]) {
    //aloc dinamic memorie pt noua melodie
    struct Melodie* nouaMelodie = (struct Melodie*)malloc(sizeof(struct Melodie));
    //folosim strcpy pt a copia valoarea din sirul titlu in sirul titlu al melodiei noi
    strcpy(nouaMelodie->titlu, titlu);
    strcpy(nouaMelodie->artist, artist);
    
    //initializam vecinii noii melodii cu NULL pt ca e prima in lista
    nouaMelodie->prev = NULL;
    nouaMelodie->next = NULL;

    if (head == NULL) {
        // lista este goala
        // adaugam prima melodie ca fiind atat prima cat si singura
        head = tail = nouaMelodie;
    } else {
        // adaugam la sfarsitul listei
        nouaMelodie->prev = tail;
        tail->next = nouaMelodie;
        tail = nouaMelodie;
    }
}

void stergeMelodie(char titlu[]) {
    // initializam pointerul cu head pt a parcurge lista
    struct Melodie* curent = head;

    while (curent != NULL) {
        // verificam daca titlul melodiei curente e cel pe care il cautam
        // strcmp compara sirurile de caractere
        if (strcmp(curent->titlu, titlu) == 0) {
            //verificam daca exista piesa inaintea elementului curent
            if (curent->prev != NULL) {
                //daca da, actualizam legatura 
                curent->prev->next = curent->next;
            } else {
                // stergerea e la inceputul listei
                head = curent->next;
            }

            //verificam daca exista vecin ulterior
            if (curent->next != NULL) {
                //daca da, inseamna ca nu e ultimul elem din lista
                //actualizam legatura vecinului ulterior pt a sari peste melodia curenta
                curent->next->prev = curent->prev;
            } else {
                //daca melodia e la final
                //actualizam sfarsitul listei 
                tail = curent->prev;
            }

            // eliberam memoria
            free(curent);
            printf("Melodia %s a fost stearsa cu succes!\n", titlu);
            return;
        }

        curent = curent->next;
    }

    printf("Melodia %s nu a fost gasita.\n", titlu);
}

// parcurge si afiseaza lista
void afiseazaMelodii() {
    struct Melodie* curent = head;

    while (curent != NULL) {
        printf("Titlu: %s, Artist: %s\n", curent->titlu, curent->artist);
        curent = curent->next;
    }
}

void cautaMelodie(char criteriu[]) {
    struct Melodie* curent = head;
    int gasit = 0;

    while (curent != NULL) {
        // strcmp compara 2 siruri de caractere, caracter cu caracter
        // comparam titlul melodiei curente cu criteriul sau artistul melodiei curente cu criteriul
        // daca titlul/artistul coincide cu criteriul, rezultatul returnat e 0
        if (strcmp(curent->titlu, criteriu) == 0 || strcmp(curent->artist, criteriu) == 0) {
            printf("Melodie gasita:\n");
            printf("Titlu: %s, Artist: %s\n", curent->titlu, curent->artist);
            // marcam faptul ca am gasit melodia
            gasit = 1;
        }

        curent = curent->next;
    }

    // daca nu am gasit titlul/artistul, returnam un mesaj de eroare
    if (!gasit) {
        printf("Nicio melodie nu a fost gasita cu criteriul: '%s'.\n", criteriu);
    }
}

void modificaMelodie(char titlu[]) {
    //initializam pointer pt a parcuge lista de la inceput
    struct Melodie* curent = head;
    int gasit = 0;

    while (curent != NULL) {
        //comparam titlul curent cu titlul introdus
        if (strcmp(curent->titlu, titlu) == 0) {
            printf("Melodie gasita:\n");
            printf("Titlu: %s, Artist: %s\n", curent->titlu, curent->artist);

            printf("Introdu noul titlu: ");
            scanf("%s", curent->titlu);

            printf("Introdu noul artist: ");
            scanf("%s", curent->artist);

            printf("Melodie modificata cu succes.\n");
            gasit = 1;
            break;
        }

        curent = curent->next;
    }

    if (!gasit) {
        printf("Nicio melodie nu a fost gasita cu titlul '%s'.\n", titlu);
    }
}

int main() {
    int optiune;

    adaugaMelodie("Ploua", "Holy_Molly");

    while (1) {
        printf("\nMeniu:\n");
        printf("1. Afiseaza lista de melodii\n");
        printf("2. Adauga o melodie\n");
        printf("3. Sterge o melodie\n");
        printf("4. Cauta o melodie\n");
        printf("5. Modifica o melodie\n");
        printf("0. Iesire\n");
        printf("Alege o optiune: ");
        scanf("%d", &optiune);

        switch (optiune) {
            case 1:
                printf("\nLista de melodii:\n");
                afiseazaMelodii();
                break;

            case 2:
                printf("\nAdauga o melodie:\n");
                {
                    char titlu[50];
                    char artist[50];

                    printf("Introdu numele melodiei: ");
                    scanf("%s", titlu);

                    printf("Introdu numele artistului: ");
                    scanf("%s", artist);

                    adaugaMelodie(titlu, artist);
                }
                break;

            case 3:
                printf("\nSterge o melodie:\n");
                {
                    char titlu[50];

                    printf("Introdu numele melodiei pe care vrei sa o stergi: ");
                    scanf("%s", titlu);

                    stergeMelodie(titlu);
                }
                break;

            case 4:
                printf("\nCauta o melodie:\n");
                {
                    char criteriu[50];

                    printf("Introdu numele melodiei sau artistului: ");
                    scanf("%s", criteriu);

                    cautaMelodie(criteriu);
                }
                break;

            case 5:
                printf("\nModifica o melodie:\n");
                {
                    char titlu[50];

                    printf("Introdu numele melodiei pe care vrei sa o modifici: ");
                    scanf("%s", titlu);

                    modificaMelodie(titlu);
                }
                break;

            case 0:
                printf("Iesire din program.\n");
                exit(0); 
                break;

            default:
                printf("Optiune invalida. Te rog sa alegi din nou.\n");
        }
    }

    return 0;
}