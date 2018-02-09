#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct a{
    char name[32];
    char squadra[16];
    char ruolo;
    int prezzo_iniziale;
    int prezzo_finale;
    double moltiplicatore;
}roster;

int findAndPrint(roster *calciatore, int max_lungh, char * nome, int price){
    int i;
    for (i=0;i<max_lungh;i++){
        if (strcmp(calciatore[i].name,nome)==0){
            printf("Calciatore %s\nPrezzo di settembre:%d\tPrezzo attuale:%d\n",
                    calciatore[i].name,price,(int)(price*calciatore[i].moltiplicatore));
            return 0;
        }
    }
    printf("Calciatore %s non trovato!\n",nome);
    return 1;
}

//parametri: nome del file
int main(int argc, char * argv[]) {
    unsigned int num_players=0;
    int id, delta,i,inputPrice,matches;
    char inputPlayer[32];
    bool flag = true;

    //inizializzo memoria dinamica
    roster *calciatore = (roster*) calloc(num_players, sizeof(roster));

    //apro il file
    FILE *fp;
    if ((fp=fopen(argv[1],"r"))==NULL){
        printf("File %s not found\n",argv[1]);
        return 1;
    }

    //importo il file
    do {
        num_players++;
        calciatore = realloc (calciatore, num_players*sizeof(roster));
    }
    while (fscanf(fp,"%d %c %s %s %d %d %d\n",&id,&calciatore[num_players-1].ruolo,calciatore[num_players-1].name,
                  calciatore[num_players-1].squadra, &calciatore[num_players-1].prezzo_finale,&calciatore[num_players-1].prezzo_iniziale, &delta)!=EOF);

    //calcolo moltiplicatore
    for (i=0;i<num_players-1;i++){
        calciatore[i].moltiplicatore=(double)calciatore[i].prezzo_finale/calciatore[i].prezzo_iniziale;
    }

    //prendo input da user
    printf("Scrivere #NOME #PREZZO_INIZIALE o \"stop\" per interrompere\nad esempio ZAPATAD 10\n");
    while (flag){
        if (scanf("%s %d",inputPlayer,&inputPrice)!=2){
            printf("Errore nell'input, riprovare.\n");
        } else if (strcmp(inputPlayer,"stop")==0){
            flag = false;
        } else {
            findAndPrint(calciatore,num_players-1,inputPlayer,inputPrice);
        }
    }
    return 0;
}