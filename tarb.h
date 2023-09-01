/*GLODARIU Ana - 311CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef ARBORE_BINAR
#define ARBORE_BINAR

typedef struct nod {
	void *info;
	struct nod *st, *dr;
} TNod, *TArb, **AArb;

TArb ConstrFr(void *x, size_t);
void distruge_f(TArb r);
void Distruge(TArb r);
void DistrDir(TArb *a);

#endif
