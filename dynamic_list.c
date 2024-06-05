
#include "dynamic_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void createEmptyList(tList* L){
    *L = LNULL;

    //Objetivo: Crea una Lista vacía de n elementos.
    //Salida: La Lista L vacía.
    //Precondición: -
    //Postcondición: La Lista no contiene datos
}

bool createNode(tPosL* p){
    *p = malloc(sizeof (struct tNode));
    return *p != LNULL;

    //Objetivo: Crea los nodos para enlazar los elementos de la Lista
    //Salida: El puntero (nodo) para poder crear la Lista.
    //Precondición: Debe de haber una Lista inicializada.
    //Postcondición: El nodo no contiene elementos.
}

bool insertItem(tItemL d, tPosL p, tList* L){
    tPosL q, r;

    if (!createNode(&q))
        return false;

    else{
        q->data=d;
        q->next=LNULL;

        if (*L == LNULL)
            *L = q;

        else if (p == LNULL){
            for (r = *L; r->next != LNULL; r = r->next);
            r->next = q;
        }

        else if (p == *L){
            q->next = *L;
            *L = q;

        }

        else {
            q->data = p->data;
            p->data = d;
            q->next = p->next;
            p->next = q;
        }

        return true;
    }
    //Objetivo: Iserta el elemento deseado en la posición asignada a la Lista. Si la p es LNULL se añade al final de la Lista.
    //Salida: Devuelve el elemento insertado.
    //Precondición: p tiene que ser una posición válida o LNULL.
    //Postcondición: Las posiciones anteriores de la Lista pueden haber variado.
}

tPosL first(tList L){
    return L;
    //Objetivo: Devuelve el primero elemento de la Lista.
    //Salida: El primero elemento de la Lista.
    //Precondición: La Lista no puede estar vacía.
    //Postcondición: -
}

tPosL next(tPosL p, tList L){
    return p->next;
    //Objetivo: Devuelve el elemento que está después de la posición introducida.
    //Salida: El elemento siguiente de la posición asginada.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

tPosL last(tList L){
    tPosL p;

    for (p = L; p->next != LNULL; p = p->next);
    return p;

    //Objetivo: Devuelve el último elemento de Lista.
    //Salida: El último elemento de la Lista.
    //Precondición: La Lista no puede estar vacía.
    //Postcondición: -
}

tPosL previous (tPosL p, tList L){

    tPosL q;

    if (p == L)
        return LNULL;
    else {
        for (q = L; q->next != p; q = q->next);
        return q;
    }
    //Objetivo: Devuelve el elemento anterior de la posición introducida.
    //Salida: El elemento anterior de la posición asignada.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

bool isEmptyList(tList L ){
    return L == LNULL;

    //Objetivo: Comprueba si la Lista está vacía.
    //Salida: True o False dependiendo de si está vacía o no.
    //Precondición: -
    //Postcondición: -
}

tItemL getItem (tPosL p, tList L){
    return p->data;

    //Objetivo: Obtener el elemento de la posición deseada de la Lista.
    //Salida: El elemento deseado de la posición asignada.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

tPosL findItem (tParticipantName d, tList L){
    tPosL p;

    for (p = L; (p != LNULL) && (strcmp(p->data.participantName, d)) != 0; p = p->next);
    return p;

    //Objetivo: Recorre la lista hasta encontrar el elemento de la posición introducida.
    //Salida: La posición del elemento de la Lista que se ha asignado para buscar en ella.
    //Precondición: -
    //Postcondición: -
}

void updateItem(tItemL d, tPosL p, tList* L){
    p->data = d;

    //Objetivo: Actualiza el valor del elemento de la posición indicada.
    //Salida: El propio elemento introducido, pero actualizado.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

void deleteAtPosition(tPosL p, tList* L){
    tPosL q;

    if (p == *L)
        *L = (*L)->next;

    else if (p->next == LNULL) {
        for (q = *L; q->next != p; q = q->next);
        q->next = LNULL;
    }

    else{
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }

    free(p);

    //Objetivo: Borra el elemento de la posición indicada de la Lista.
    //Salida: -
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: Las posiciones de los elementos de la Lista pueden haber variado.
}
