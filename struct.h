/*GLODARIU Ana - 311CB*/
#include "tarb.h"

typedef struct {
    char *nume;
    TArb parinte;
    TArb fisier;
    TArb directories;
} Director;

typedef struct {
    char *nume;
    TArb parinte;
} Fisier;

int compare(char *, char *);
Director *AlocDirector(char *, TArb);
Fisier *AlocFisier(char *, TArb);
TArb Cauta_director(TArb, char *);
TArb Cauta_fisier(TArb, char *);
TArb Cautaref(TArb , char *);
TArb Cautared(TArb , char *);
int Mkdir(char *, TArb);
int Touch(char *, TArb);
void afisare_dir(void *x);
void afisare_files(void *x);
typedef void Afi(void *); /*afisare info noduri*/
