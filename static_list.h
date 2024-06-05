
#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"
#include <stdbool.h>
#include <string.h>
#define LNULL -1
#define MAX 25

typedef int tPosL;

typedef struct {
    tItemL data[MAX];
    tPosL lastPos;
}tList;

void createEmptyList(tList* L);
bool isEmptyList(tList L );
tPosL first(tList L);
tPosL last(tList L);
tPosL next(tPosL p, tList L);
tPosL previous (tPosL p, tList L);
bool insertItem(tItemL d, tPosL p, tList* L);
void deleteAtPosition(tPosL p, tList* L);
tItemL getItem (tPosL p, tList L);
void updateItem(tItemL d, tPosL p, tList* L);
tPosL findItem (tParticipantName d, tList L);


#endif
