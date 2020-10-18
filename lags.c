#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ordre.h"
#include "LagsService.h"

int main() {
    struct Node* head = NULL;
    getFichierOrder(&head, "ORDRES.CSV");
    Liste(&head);
    bool flag = false;
    /* tant que ce n'est pas la fin du programme */
    while(!flag) {
        /* met la commande à Z */
        char commande = 'Z';
        printf("A)JOUTER UN ORDRE  L)ISTER   C)ALCULER CA  S)UPPRIMER  Q)UITTER\n");
        while(commande!='A' && commande!='L' && commande!='Q' && commande!='S' && commande!='C') {
            fflush(stdin);
            commande = toupper(getc(stdin));
            switch(commande) {
                case 'Q':
                    flag = true;
                    break;
                case 'L':
                    Liste(&head);
                    break;
                case 'A':
                    AjouterOrdre(&head);
                    break;
                case 'S':
                    Suppression(&head);
                    break;
                case 'C':
                    printf("CA:%10.2f\n", CA(head));
                    break;
                default:
                    printf("%c ?\n", commande);
                    break;
            }
        }
    }
    freeOrders(&head);
    deleteList(&head);
    return 0;
}
