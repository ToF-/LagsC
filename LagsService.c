#include <stdio.h>
#include <stdlib.h>
#include "ordre.h"

struct Node {
    ORDRE *ordre;
    struct Node* next;
};

void printOrdres(struct Node* n) {
    while (n != NULL) {
        printf(" %04d %7d %6d %6d\n", n->ordre->id, n->ordre->debut, n->ordre->nombreJours, n->ordre->prix);
        n = n->next;
    }
}

void append(struct Node** head_ref, ORDRE* new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    struct Node *last = *head_ref;
    new_node->ordre  = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;
}

void freeOrders(struct Node **head_ref) {
    struct Node* last = *head_ref;
    if (*head_ref == NULL)
        return;
    while (last->next != NULL) {
        free(last->ordre);
        last = last->next;
    }
    return;
}

void deleteList(struct Node **head_ref) {
    if(*head_ref == NULL)
        return;
    while(*head_ref != NULL) {
        struct Node* temp = *head_ref;
        *head_ref = temp->next;
        free(temp);
    }
    return;
}
int main() {
    ORDRE* ordre1 = NULL;
    ORDRE* ordre2 = NULL;
    ORDRE* ordre3 = NULL;
    struct Node* head = NULL;



    ordre1 = (ORDRE *)malloc(sizeof(ORDRE));
    ordre1->id = 1;
    ordre1->debut = 2003056;
    ordre1->nombreJours = 30;
    ordre1->prix = 100;
    append(&head, ordre1);

    ordre2 = (ORDRE *)malloc(sizeof(ORDRE));
    ordre2->id = 2;
    ordre2->debut = 2003078;
    ordre2->nombreJours = 40;
    ordre2->prix = 207;
    append(&head, ordre2);


    ordre3 = (ORDRE *)malloc(sizeof(ORDRE));
    ordre3->id = 2;
    ordre3->debut = 2003120;
    ordre3->nombreJours = 77;
    ordre3->prix = 840;
    append(&head, ordre3);

    printOrdres(head);
    freeOrders(&head);
    deleteList(&head);
    return 0;
}
