#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "ordre.h"
#include "LagsService.h"
#define MAXLIGNE 80


void printOrdres(struct Node* n) {
    while (n != NULL) {
        printf(" %10s %7d %6d %10f\n", n->ordre->id, n->ordre->debut, n->ordre->nombreJours, n->ordre->prix);
        n = n->next;
    }
}
void Liste(struct Node **head_ref) {
    printf("LISTE DES ORDRES\n");
    printf("%8s %7s %5s %10s\n", "ID", "DEBUT", "DUREE", "PRIX");
    printf("%8s %7s %5s %10s\n", "--------", "-------", "-----", "----------");

    struct Node* n = *head_ref;
    while (n != NULL) {
        printf("%-8s %7d %5d %10.2f\n", n->ordre->id, n->ordre->debut, n->ordre->nombreJours, n->ordre->prix);
        n = n->next;
    }
    printf("%8s %7s %5s %10s\n", "--------", "-------", "-----", "----------");
}

void writeOrdres(struct Node **head_ref, char *fileName) {
    FILE *fichier;
    char buffer[MAXLIGNE];
    fichier = fopen("ORDRES.CSV","w");
    struct Node *n = *head_ref;
    while(n != NULL) {
        sprintf(buffer,"%s;%d;%d;%f\n", n->ordre->id, n->ordre->debut, n->ordre->nombreJours, n->ordre->prix);
        fputs(buffer, fichier);
        n = n->next;
    }
    fclose(fichier);
}
void getFichierOrder(struct Node **head_ref, char *fileName) {
    FILE * fichier;
    char buffer[MAXLIGNE];
    fichier = fopen("ORDRES.CSV", "r");
    if(fichier == NULL) {
        printf("FICHIER ORDRES.CSV NON TROUVE. CREATION FICHIER.");
        writeOrdres(head_ref, fileName);
        return;
    }
    while(fgets(buffer, MAXLIGNE, fichier)) {
        ORDRE *ordre = (ORDRE *)malloc(sizeof(ORDRE));
        char* tmp = strdup(buffer);
        char* tok;
        tok = strtok(tmp, ";");
        strncpy(ordre->id, tok, 10);
        tok = strtok(NULL, ";");
        ordre->debut = atoi(tok);
        tok = strtok(NULL, ";");
        ordre->nombreJours = atoi(tok);
        tok = strtok(NULL, ";");
        ordre->prix = atof(tok);
        free(tmp);
        append(head_ref, ordre);
    }
    fclose(fichier);
    return;
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
/* Ajoute un ordre; le CA est recalculé en conséquence */
void AjouterOrdre(struct Node **head_ref)
{
    char line[MAXLIGNE];
    printf("AJOUTER UN ORDRE\n");
    printf("FORMAT = ID DEBUT FIN PRIX\n");
    fflush(stdin);
    fgets(line,MAXLIGNE,stdin);
    char id[10];
    for(int i=0; i<10; id[i++] = '\0');
    int dep;
    int dur;
    float prx;
    sscanf(line, "%s %d %d %f", id, &dep, &dur, &prx);
    for(int i=0; i<10; i++)
        id[i] = toupper(id[i]);
    ORDRE *ordre = (ORDRE *)malloc(sizeof(ORDRE));
    strncpy(ordre->id, id, 10);
    ordre->debut = dep;
    ordre->nombreJours = dur;
    ordre->prix = prx;
    append(head_ref, ordre);
    writeOrdres(head_ref, "ORDRES.CSV");
    return;
}
void deleteNode_withId(struct Node **head_ref, char *id) {
    if(*head_ref == NULL)
        return;
    struct Node* temp = *head_ref;
    if (strncmp(temp->ordre->id, id, 10) == 0) {
        *head_ref = temp->next;
        free(temp->ordre);
        free(temp);
        return;
    }
    while(temp->next != NULL && strncmp(temp->next->ordre->id, id, 10) != 0) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Ordre %s inconnu.", id);
        return;
    }
    struct Node *next = temp->next->next;
    free(temp->next->ordre);
    free(temp->next);
    temp->next = next;
}

/* MAJ du fichier */
void Suppression(struct Node **head_ref) {
    char line[MAXLIGNE];
    for(int i=0; i<MAXLIGNE; line[i++] = '\0');
    printf("SUPPRIMER UN ORDRE\n");
    printf("ID:");
    fflush(stdin);
    fgets(line,MAXLIGNE,stdin);
    for(int i=0; i<MAXLIGNE; i++)
        line[i] = toupper(line[i]);
    for(int i=0; i<MAXLIGNE; i++) {
        if(line[i] == '\n')
            line[i] = '\0';
    }
    deleteNode_withId(head_ref, line);
    writeOrdres(head_ref, "ORDRES.CSV");
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
