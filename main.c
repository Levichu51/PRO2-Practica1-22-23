
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif


void New(tParticipantName participantName, tNumVotes* nullVotes, tList *L, char *param2){
    tItemL item;

    if(findItem(participantName, *L) != LNULL) {
        printf("+ Error: New not possible\n"); //si ya existe ese participante en la lista, sale el error de New not possible.

    }else if(findItem(participantName, *L) == LNULL){
        strcpy(item.participantName, participantName);
        item.numVotes = 0;
        *nullVotes = 0;

        if(strcmp(param2, "eu") == 0){
            item.EUParticipant = true;
        }else{
            item.EUParticipant = false;
        }//dependiendo de param2 asignamos true o false al campo EUparticipant del item.

        insertItem(item, LNULL, L); //se inserta el item en la siguiente posición vacía.
        //se inserta el partipante con sus campos.

        printf("* New: participant %s location %s\n", item.participantName, param2);
    }
    //Objetivo: Dar de alta la Lista a los países con su nombre y número de votos (nulos y no-nulos) a 0, asignando si son de EU o no. Se isertan en la Lista al principio si está vacia, y en la útima posición si la Lista está llena.
    //Salida: La Lista con los países insertados en ésta.
    //Precondición: Que el nombre del participante no esté ya en la lista.
    //Postcondición: -
}



void Vote(tParticipantName participantName,tNumVotes* nullVotes, tList *L){
    tItemL item;
    tPosL p;
    *nullVotes = 0;

    if(isEmptyList(*L) || findItem(participantName, *L) == LNULL){
        *nullVotes = *nullVotes + 1;
        item.numVotes = 0;
        printf("+ Error: Vote not possible. Participant %s not found. NULLVOTE\n", participantName);
        //si la lista esta vacia o no se encuentra al participante deseado, se anula el voto y pasa a nulo.
    }
    else if(!isEmptyList(*L) && findItem(participantName, *L) != LNULL){
        p = findItem(participantName, *L);
        item = getItem(p, *L);
        item.numVotes = item.numVotes + 1;
        //se coge el item y se suma un voto. Al encontrarlo en la lista.

        if (item.EUParticipant == true) {
            printf("* Vote: participant %s location eu numvotes %d\n", item.participantName, item.numVotes);
        }else if(item.EUParticipant == false){
            printf("* Vote: participant %s location non-eu numvotes %d\n", item.participantName, item.numVotes);
        }
        updateItem(item, p, L);
        //se actualiza el item con su recuento de votos.
    }
    //Objetivo: Se asgina un voto al participante de la Lista si éste se encuentra en ella. Si no estuviese, se le asigna como voto NULO.
    //Salida: Devuelve la Lista con los elementos actualizados (se suma un voto en el campo numVotes) si han ejercido el derecho a voto (si el participantName esta dentro de la Lista)
    //Precondición: Que exista el participante en la Lista.
    //Postcondición: -
}



void Disqualify(tParticipantName participantName, tNumVotes* nullVotes, tList *L){
    tPosL p;
    tItemL item;

    p = findItem(participantName, *L);

    if(!isEmptyList(*L) && p != LNULL){
        item = getItem(p,*L);
        *nullVotes += item.numVotes;
        item.numVotes = 0;
        //Los votos al borrar al participante de la lista pasan a ser nulos. Los votos del participante pasan a 0.

        if(item.EUParticipant == true){
            printf("* Disqualify: participant %s location eu\n", item.participantName);
        }else if(item.EUParticipant == false){
            printf("* Disqualify: participant %s location non-eu\n", item.participantName);
        }
        deleteAtPosition(p, L);

    }else{
        printf("+ Error: Disqualify not possible\n");
    }
    //Objetivo: Se borra al país deseado de la Lista de participantes, asignando sus votos a 0, pasando a ser NULOS.
    //Salida: Nada, se borra el elemento de la Lista. Sólo se contabilizan sus votos como NULOS.
    //Precondición: Que el participante esté en la Lista.
    //Postcondición: Las posiciones de los elementos de la Lista pueden haber variado.
}



void Stats(tList L, const tNumVotes* nullVotes, tPercentage* percentage, tNumVotes* voters, tParticipantName participantName) {
    tPosL p;
    tItemL item;
    tNumVotes votes = 0;
    float totalPercentage;

    if (!isEmptyList(L)) {
        p = first(L);
        *voters = (int)atof(participantName);

        while (p != LNULL) {
            item = getItem(p, L);
            votes += item.numVotes;
            //hacemos recuento de todos los votos para el porcentaje total.

            if(item.numVotes != 0){
                *percentage = ((float) 1 / (float) (item.numVotes)) * 100; //se pone entre uno porque es el propio país el miembro del jurado.
            }else{
                *percentage = 0;
            }
            //si los votos son 0 hay q cubrirse, porque da infinito. Entoces si los votos del participante son 0 directamente es 0 el porcentaje.

            if(item.EUParticipant == true){
                printf("Participant %s location eu numvotes %d (%.2f%%)\n", item.participantName,item.numVotes, *percentage);
                p = next(p, L);
            }else{
                printf("Participant %s location non-eu numvotes %d (%.2f%%)\n", item.participantName,item.numVotes, *percentage);
                p = next(p, L);
            }
            //pasamos al siguinete item en el bucle para recorrer la lista.
        }
        totalPercentage = ((float)(votes + *nullVotes)/ (float)*voters) * 100;
        printf("Null votes %d\n", *nullVotes);
        printf("Participation: %d votes from %d voters (%.2f%%)\n", votes+(*nullVotes), *voters, totalPercentage);

    }else{
        printf("+ Error: Stats not possible\n");
    }
    //Objetivo: Imprime la Lista con toda la información de los participantes, el porcentaje de participación por país, el total de la Lista y el número total de votos NULOS.
    //Salida: La Lista entera.
    //Precondición: Que la Lista no esté vacía.
    //Postcondición: -
}




void processCommand(char *commandNumber, char command, tParticipantName participantName, char* param2, tList *L, tNumVotes* nullVotes, tPercentage* percentage, tNumVotes* voters) {
    printf("********************\n");
    switch (command) {
        case 'N':
            printf("%s %c: participant %s location %s\n", commandNumber, command, participantName, param2);
            New(participantName, nullVotes, L, param2);
            break;

        case 'V':
            printf("%s %c: participant %s\n", commandNumber, command, participantName);
            Vote(participantName, nullVotes, L);
            break;

        case 'D':
            printf("%s %c: participant %s\n", commandNumber, command, participantName);
            Disqualify(participantName, nullVotes, L);
            break;

        case 'S':
            *voters = (int)atof(participantName);
            printf("%s %c: totalvoters %d\n", commandNumber, command, *voters);
            Stats(*L, nullVotes, percentage, voters, participantName);
            break;

        default:
            break;
    }
    //Objetivo: Dependiendo del carácter introducido, realiza la operación deseada.
    //Salida: Dependiendo del comando, devuelve el resultado de una de las operaciones deseadas.
    //Precondición: -
    //Postcondición: -
}



void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];
    tList L;
    tNumVotes nullVotes = 0;
    tPercentage percentage = 0;
    tNumVotes voters = 0;

    f = fopen(filename, "r");

    if (f != NULL) {
        createEmptyList(&L);

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, &L, &nullVotes, &percentage, &voters);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
    //Objetivo: Lee el fichero .txt introducido y asigna un valor a los parámetros de la funcion processCommand.
    //Salida: Los parámetros para asignar el nombre del país, n de comando, letra del comando, si es eu o non-eu...
    //Precondición: Que el fichero .txt exista.
    //Postcondición: -
}


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}






