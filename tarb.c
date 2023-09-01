/*GLODARIU Ana - 311CB*/
#include "tarb.h"
#include "struct.h"

/*aloc informatia de tip director continuta de nodurile arborilor binari*/
Director *AlocDirector(char *nume, TArb parinte) 
{
    Director *d = (Director *)malloc(sizeof(Director));
	if (d == NULL) {
		return NULL;
	}
    d->nume = malloc(sizeof(char) * (strlen(nume) + 1));
	if (d->nume == NULL) {
		free(d);
		return NULL;
	}
    memcpy(d->nume, nume, (strlen(nume) + 1));
    d->parinte = parinte;
    d->fisier = NULL;
    d->directories = NULL;
	return d;
}

/*aloc informatia de tip fisier continuta de nodurile arborilor binari*/
Fisier *AlocFisier(char *nume, TArb parinte) 
{
    Fisier *f = (Fisier *)malloc(sizeof(Fisier));
	if (f == NULL) {
		return NULL;
	}
	f->nume = malloc(sizeof(char) * (strlen(nume) + 1));
	if (f->nume == NULL) {
		free(f);
		return NULL;
	}
    memcpy(f->nume, nume, (strlen(nume) + 1));
    f->parinte = parinte;
	return f;
}

TArb ConstrFr(void *x, size_t dim)  /*adresa frunza cu informatia x, sau
NULL daca nu exista spatiu */
{
	TArb aux = (TArb)malloc (sizeof(TNod));
	if (aux == NULL) {
		return NULL;
	}
	aux->info = x;
	aux->st = aux->dr = NULL;
	return aux;
}

void distruge_f(TArb r) 
{
	if (r == NULL) {
		return;
	}
	distruge_f(r->st);
	distruge_f(r->dr);
	Fisier *f = (Fisier *)r->info;
	/*distrug info din nod*/
	free(f->nume);
	free(f);
	free(r); /*distrug nodul de tip fisier*/
}

void Distruge(TArb r) 
{
	if (r == NULL) {
		return;
	}
	Distruge(r->st);     /*distrug subarborele stang*/
	Distruge(r->dr);     /*distrug subarborele drept*/
	Director *d = (Director *)r->info;
	
	if (d->directories != NULL) {
		Distruge(d->directories);
	}		 
	if (d->fisier != NULL) {
		distruge_f(d->fisier);
	}
	/*distrug info din nod*/
	free(d->nume);
	free(d);
	free(r); 	/*distrug nodul de tip director*/
}

void DistrDir(TArb *a) {
	if ((*a) == NULL) {
		return;
	}
	Distruge(*a); /*distrug toate nodurile*/
	*a = NULL;
}
