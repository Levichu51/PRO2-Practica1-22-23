
#include "static_list.h"

void createEmptyList(tList* L){
    L->lastPos = LNULL;

    //Objetivo: Crea una Lista vacía de n elementos.
    //Salida: La Lista L vacía.
    //Precondición: -
    //Postcondición: La Lista no contiene datos
}

bool insertItem(tItemL d, tPosL p, tList* L){
    tPosL q;

    if (L->lastPos == MAX - 1)
        return false;

    else{
        L->lastPos++;
        if (p == LNULL)
            L->data[L->lastPos] = d;

        else{
            for (q = L->lastPos; q > p; q--)
                L->data[q] = L->data[q-1];
            L->data[p] = d;

        }
        return true;
    }

    //Objetivo: Iserta el elemento deseado en la posición asignada a la Lista. Si la p es LNULL se añade al final de la Lista.
    //Salida: Devuelve el elemento insertado.
    //Precondición: p tiene que ser una posición válida o LNULL.
    //Postcondición: Las posiciones anteriores de la Lista pueden haber variado.
}

tPosL first(tList L){
    return 0;

    //Objetivo: Devuelve el primero elemento de la Lista.
    //Salida: El primero elemento de la Lista.
    //Precondición: La Lista no puede estar vacía.
    //Postcondición: -
}

tPosL next(tPosL p, tList L){
    if (p == L.lastPos)
        return LNULL;

    else
        return ++p;

    //Objetivo: Devuelve el elemento que está después de la posición introducida.
    //Salida: El elemento siguiente de la posición asginada.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

tPosL previous(tPosL p, tList L){
    if (p == 0)
        return LNULL;

    else
        return --p;

    //Objetivo: Devuelve el elemento anterior de la posición introducida.
    //Salida: El elemento anterior de la posición asignada.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

tPosL last(tList L){
    return L.lastPos;

    //Objetivo: Devuelve el último elemento de Lista.
    //Salida: El último elemento de la Lista.
    //Precondición: La Lista no puede estar vacía.
    //Postcondición: -
}

bool isEmptyList(tList L){
    return L.lastPos == LNULL;

    //Objetivo: Comprueba si la Lista está vacía.
    //Salida: True o False dependiendo de si está vacía o no.
    //Precondición: -
    //Postcondición: -
}

tItemL getItem(tPosL p, tList L){
    return L.data[p];

    //Objetivo: Obtener el elemento de la posición deseada de la Lista.
    //Salida: El elemento deseado de la posición asignada.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

tPosL findItem(tParticipantName d, tList L){
    tPosL p;

    if(L.lastPos == LNULL)
        return LNULL;

    else{
        for (p = 0; (p < L.lastPos) && (strcmp(L.data[p].participantName, d)) != 0; p++);
        if (strcmp(L.data[p].participantName,d) == 0)
            return p;
        else
            return LNULL;
    }

    //Objetivo: Recorre la lista hasta encontrar el elemento de la posición introducida.
    //Salida: La posición del elemento de la Lista que se ha asignado para buscar en ella.
    //Precondición: -
    //Postcondición: -
}

void updateItem(tItemL d, tPosL p, tList* L){
    L->data[p] = d;

    //Objetivo: Actualiza el valor del elemento de la posición indicada.
    //Salida: El propio elemento introducido, pero actualizado.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

void deleteAtPosition(tPosL p, tList* L){
    tPosL q;

    for (q = p; q < L->lastPos; q++)
        L->data[q] = L->data[q + 1];
    L->lastPos--;

    //Objetivo: Borra el elemento de la posición indicada de la Lista.
    //Salida: -
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: Las posiciones de los elementos de la Lista pueden haber variado.
}



