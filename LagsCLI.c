#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ordre.h"
#include "LagsService.h"
#include "LagsCLI.h"

int lags_CLI(struct Node **head_ref, int argc, char *argv[]) {
    if(!strcmp(argv[1], "-a")) {
        if(argc < 6) {
            fprintf(stderr,"usage: lags -a ID DEBUT FIN PRIX\n");
            return 1;
        }
        char id[11];
        int deb;
        int dur;
        float prx;
        for(int i=0; i<11; id[i++]='\0');
        strncpy(id, argv[2], 10);
        deb = atoi(argv[3]);
        dur = atoi(argv[4]);
        prx = atof(argv[5]);
        for(int i=0; i<10; i++)
            id[i] = toupper(id[i]);
        ORDRE *ordre = (ORDRE *)malloc(sizeof(ORDRE));
        strncpy(ordre->id, id, 10);
        ordre->debut = deb;
        ordre->nombreJours = dur;
        ordre->prix = prx;
        append(head_ref, ordre);
        writeOrdres(head_ref, "ORDRES.CSV");
        return 0;
    }
    if(!strcmp(argv[1], "-l")) {
        Liste(head_ref);
        return 0;
    }
    if(!strcmp(argv[1], "-s")) {
        if(argc < 3) {
            fprintf(stderr, "usage: lags -s ID\n");
            return 1;
        }
        deleteNode_withId(head_ref, argv[2]);
        writeOrdres(head_ref, "ORDRES.CSV");
        return 0;
    }
    if(!strcmp(argv[1], "-c")) {
        printf("CA:%10.2f\n", CA(*head_ref));
    }

}

