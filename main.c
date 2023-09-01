/*GLODARIU Ana - 311CB*/
#include "tarb.h"
#include "struct.h"
#define N 51

/*parcurgerea de tip SRD va afisa numele 
fisierelor/directoarelor din arborii de cautare in ordine crescatoare
dpdv lexicografic*/
void SRD(TArb a, Afi afisare)
{
	if(a == NULL) {
		return;
	}
	if(a->st == NULL && a->dr == NULL) {
		afisare(a->info); 
		return;
	}
	SRD(a->st, afisare);
	afisare(a->info);
	SRD(a->dr, afisare);
}

TArb Create_root() {
	TArb arb = NULL;
	Director *d = NULL;
	d = AlocDirector("root", arb);
	if (d == NULL) {
		return NULL;
	}
	arb = ConstrFr(d, sizeof(Director));
	if (arb == NULL) {
		free(d->nume);
		free(d);
		return NULL;
	}
	return arb;
}

void afisare_files(void *x) 
{
	Fisier *info = (Fisier *)x;
	printf("%s ", info->nume);
}

void afisare_dir(void *x) 
{
	Director *info = (Director *)x;
	printf("%s ", info->nume);
}

void F_Eliminare_frunza(TArb aux, TArb auxp) 
{
	Fisier *f = (Fisier *)aux->info;
	Fisier *fp = (Fisier *)auxp->info;
	if (compare(f->nume, fp->nume) == 1) {
		auxp->dr = NULL;
	} else {
		auxp->st = NULL;
	}
	free(f->nume);
	free(f);
	free(aux);
}

void D_Eliminare_frunza(TArb aux, TArb auxp) 
{
	Director *d = (Director *)aux->info;
	Director *dp = (Director *)auxp->info;
	if (compare(d->nume, dp->nume) == 1) {
		auxp->dr = NULL;
	} else {
		auxp->st = NULL;
	}
	/*eliberez memoria ocupata de nodul pe care l-am eliminat*/
	if (d->directories != NULL) {
		Distruge(d->directories);
	}		 
	if (d->fisier != NULL) {
		distruge_f(d->fisier);
	}
	free(d->nume);
	free(d);
	free(aux); 
}

void F_Eliminare_Nod_Ordin1(TArb aux, TArb auxp) 
{
	Fisier *f = (Fisier *)aux->info;
	Fisier *fp = (Fisier *)auxp->info;
	int rez = compare(f->nume, fp->nume);
	if (aux->dr != NULL) {
		/*nodul ce trebuie eliminat are doar un fiu drept*/
		if (rez == 1) {
			auxp->dr = aux->dr;
		} else {
			auxp->st = aux->dr;
		}
	} else {
		/*nodul ce trebuie eliminat are doar un fiu stanga*/
		if (rez == 1) {
			auxp->dr = aux->st;
		} else {
			auxp->st = aux->st;
		}
	}
	/*dezalocam memoria ocupata de nodul pe care l-am eliminat*/
	free(f->nume);
	free(f);
	free(aux);
}

void D_Eliminare_Nod_Ordin1(TArb aux, TArb auxp) 
{
	Director *d = (Director *)aux->info;
	Director *dp = (Director *)auxp->info;
	int rez = compare(d->nume, dp->nume);
	if (aux->dr != NULL) {
		/*nodul ce trebuie eliminat are doar un fiu drept*/
		if (rez == 1) {
			auxp->dr = aux->dr;
		} else {
			auxp->st = aux->dr;
		}
	} else {
		/*nodul ce trebuie eliminat are doar un fiu stanga*/
		if (rez == 1) {
			auxp->dr = aux->st;
		} else {
			auxp->st = aux->st;
		}
	}
	if (d->directories != NULL) {
		Distruge(d->directories);
	}		 
	if (d->fisier != NULL) {
		distruge_f(d->fisier);
	}
	free(d->nume);
	free(d);
	free(aux); 
}

/*gaseste fisierul sau directorul cu numele cel mai mic dpdv lexicografic*/
TArb Minimum(TArb a) {
	if (a->st == NULL && a->dr == NULL) {
		return a;
	} 
	if (a->st == NULL && a->dr != NULL) {
		return a;
	}
	return Minimum(a->st);
}

void F_Eliminare_Nod_Ordin2(TArb aux, TArb arb)
{
	Director *d = (Director *)arb->info;
	/*pentru a elimina un nod de ordin 2 procedez astfel:
	pornind pe subarborele drept al nodului care trebuie eliminat
	aleg nodul corespunzator fisierului cu numele cel mai mic dpdv
	lexicografic, adica nodul cel mai din stanga al subarborelui drept*/
	/*dupa ce gasesc acel nod, pun info din el in nodul aux
	si il elimin*/
	Fisier *f = (Fisier *)aux->info;
	TArb min = Minimum(aux->dr);
	Fisier *fmin = (Fisier *)min->info;
	/*caut in campul fisier al directorului curent parintele nodului min,
	pentru ca am nevoie de adresa lui cand fac eliminarea*/
	TArb pmin = Cautaref(d->fisier, fmin->nume);
	/*pastram numele fisierului corespunzator nodului min
	si il atribuim nodului aux dupa ce eliminam nodul min
	din arbore*/
	char *nume = malloc(strlen(fmin->nume) + 1);
	memcpy(nume, fmin->nume, strlen(fmin->nume) + 1);
	if (min->dr != NULL) {
		/*fiind cel mai din stanga nod, poate fi frunza sau nod de ordin 1
		cu un copil in dreapta*/
		F_Eliminare_Nod_Ordin1(min, pmin);
	} else {
		F_Eliminare_frunza(min, pmin);
	}
	memcpy(f->nume, nume, strlen(nume) + 1);
	free(nume);
}

void D_Eliminare_Nod_Ordin2(TArb aux, TArb arb)
{
	Director *D = (Director *)arb->info;
	/*pentru a elimina un nod de ordin 2 procedez astfel:
	pornind pe subarborele drept al nodului care trebuie eliminat
	aleg nodul corespunzator directorului cu numele cel mai mic dpdv
	lexicografic, adica nodul cel mai din stanga al subarborelui drept*/
	/*dupa ce gasesc acel nod, pun info din el in nodul aux
	si elimin nodul gasit*/
	Director *d = (Director *)aux->info;
	TArb min = Minimum(aux->dr);
	Director *dmin = (Director *)min->info;
	/*caut in campul directories al directorului curent parintele nodului min,
	pentru ca am nevoie de adresa lui cand fac eliminarea*/
	TArb pmin = Cautared(D->directories, dmin->nume);
	/*eliberez memoria alocata pentru campurile directories si fisier ale 
	nodului aux si le inlocuiesc cu cele ale nodului min*/
	if (d->directories != NULL) {
		Distruge(d->directories);
	}		 
	if (d->fisier != NULL) {
		distruge_f(d->fisier);
	}
	d->directories = NULL; /*initializez cu NULL pointeri*/
	d->fisier = NULL;			/*pentru a-i refolosi*/
	d->directories = dmin->directories;
	d->fisier = dmin->fisier;
	/*pastrez numele directorului corespunzator nodului min
	si il atrbui nodului aux dupa ce il elimin pe min*/
	char *nume = malloc(strlen(dmin->nume) + 1);
	memcpy(nume, dmin->nume, strlen(dmin->nume) + 1);
	if (min->dr != NULL) {
		/*fiind cel mai din stanga nod, poate fi frunza sau nod de ordin 1
		cu un copil in dreapta*/
		D_Eliminare_Nod_Ordin1(min, pmin);

	} else {
		D_Eliminare_frunza(min, pmin);
	}
	memcpy(d->nume, nume, strlen(nume) + 1);
	free(nume);
}

int Rm(char *nume, TArb arb)
{
	TArb aux = NULL; /*in variabila aux pastrez adresa nodului cautat*/
	Director *d = (Director *)arb->info;
	/*functia Cautaref returneaza parintele nodului cautat,
	pentru ca imi trebuie adresa parintelui la eliminare*/
	TArb auxp = Cautaref(d->fisier, nume);
	if (auxp == NULL) {
		printf("File %s doesn't exist!\n", nume);
		return 0;
	}
	if (auxp == arb) {
		/*daca nodul ce trebuie eliminat 
		este radacina arborelui*/
		aux = d->fisier;
		Fisier *f = (Fisier *)aux->info;
		if (aux->dr == NULL && aux->st == NULL) {
			/*daca radacina este frunza*/
			free(f->nume);
			free(f);
			free(aux);
			d->fisier = NULL;  /*il facem NULL
			pentru a putea folosi din nou pointerul*/
		} else if (aux->dr != NULL && aux->st != NULL) {
			/*daca radacina e de ordin 2*/
			F_Eliminare_Nod_Ordin2(aux, arb);
		} else {
			/*daca radacina are un singur copil*/
			if (aux->dr != NULL) {
				d->fisier = aux->dr;
			} else if (aux->st != NULL) {
				d->fisier = aux->st;
			}
			free(f->nume);
			free(f);
			free(aux);
		}
		return 1;
	}
	/*stiind adresa parintelui
	aflu si adresa nodului care trebuie eliminat*/
	TArb auxd = auxp->dr;
	TArb auxs = auxp->st;
	if (auxd != NULL) {
		Fisier *fd = (Fisier *)auxd->info;
		if (compare(nume, fd->nume) == 0) {
			aux = auxd;
		}
	} 
	if (auxs != NULL) {
		Fisier *fs = (Fisier *)auxs->info;
		if (compare(nume, fs->nume) == 0) {
			aux = auxs;
		}
	}
	
	if (aux->dr == NULL && aux->st == NULL) {
		/*nodul cautat este o frunza*/
		F_Eliminare_frunza(aux, auxp);
	} else if (aux->dr != NULL && aux->st != NULL) {
		/*nodul are 2 fii*/
		F_Eliminare_Nod_Ordin2(aux, arb);
	} else {
		/*nodul are un singur fiu*/
		F_Eliminare_Nod_Ordin1(aux, auxp);
	}
	return 1;
}

int Rmdir(char *nume, TArb arb)
{
	TArb aux = NULL; /*in variabila aux pastrez adresa nodului cautat*/
	Director *D = (Director *)arb->info;
	/*functia Cautared returneaza parintele nodului cautat,
	pentru ca imi trebuie adresa parintelui la eliminare*/
	TArb auxp = Cautared(D->directories, nume);
	if (auxp == NULL) {
		printf("Directory %s doesn't exist!\n", nume);
		return 0;
	}
	if (auxp == arb) {
		/*daca nodul ce trebuie eliminat 
		este radacina arborelui*/
		aux = D->directories;
		Director *d = (Director *)aux->info;
		if (aux->dr == NULL && aux->st == NULL) {
			/*daca radacina este frunza*/
			Distruge(aux);
			D->directories = NULL;  /*il facem NULL
			pentru a putea folosi din nou pointerul*/
		} else if (aux->dr != NULL && aux->st != NULL) {
			/*daca radacina e de ordin 2*/
			D_Eliminare_Nod_Ordin2(aux, arb);
		} else {
			/*daca radacina are un singur copil*/
			if (aux->dr != NULL) {
				D->directories = aux->dr;
				Director *dd = (Director *)aux->dr->info;
				dd->directories = d->directories;
				dd->fisier = d->fisier;
			} else if (aux->st != NULL) {
				D->directories = aux->st;
				Director *dd = (Director *)aux->st->info;
				dd->directories = d->directories;
				dd->fisier = d->fisier;
			}
			free(d->nume);
			free(d);
			free(aux);
		}
		return 1;
	}
	/*stiind adresa parintelui
	aflu si adresa nodului care trebuie eliminat*/
	TArb auxd = auxp->dr;
	TArb auxs = auxp->st;
	if (auxd != NULL) {
		Director *dd = (Director *)auxd->info;
		if (compare(nume, dd->nume) == 0) {
			aux = auxd;
		}
	} 
	if (auxs != NULL) {
		Director *ds = (Director *)auxs->info;
		if (compare(nume, ds->nume) == 0) {
			aux = auxs;
		}
	}
	
	if (aux->dr == NULL && aux->st == NULL) {
		/*nodul cautat este o frunza*/
		D_Eliminare_frunza(aux, auxp);
	} else if (aux->dr != NULL && aux->st != NULL) {
		/*nodul are 2 fii*/
		D_Eliminare_Nod_Ordin2(aux, arb);
	} else {
		/*nodul are un singur fiu*/
		D_Eliminare_Nod_Ordin1(aux, auxp);
	}
	return 1;
}

void Pwd(TArb a) 
{
	Director *d = (Director *)a->info;
	if (d->parinte == NULL) {
		printf("/%s", d->nume);
		return;
	}
	Pwd(d->parinte);
	printf("/%s", d->nume);
}

/*functia cauta un director in campurile
directories ale directoarelor/subdirectoarelor arborelui*/
TArb Finddir(char *nume, TArb a) 
{
	if (a == NULL) {
		return NULL;
	}
	Director *d = (Director *)a->info;
	if (compare(nume, d->nume) == 0) {
		return a;
	} else if (compare(nume, d->nume) == 1) {
		return Finddir(nume, a->dr);
	}
	return Finddir(nume, a->st);

}
/*functia cauta un director in intreg arborele*/
TArb Findd(char *nume, TArb a)
{
	TArb rez = NULL;
	if (a == NULL) {
		return NULL;
	}
	Director *d = (Director *)a->info;
	if (compare(nume, d->nume) != 0) {
	/* pentru a ma asigura ca parcurg tot arborele
	pun valoarea de return in variabila rez*/
	/*astfel recursivitatea se opreste doar dupa ce am parcurs tot arborele
	si a == NULL sau cand am gasit directorul cautat*/
		rez = Findd(nume, a->st);
		if (rez != NULL) {
			return rez;
		}
		rez = Findd(nume, a->dr);
		if (rez != NULL) {
			return rez;
		}
		rez = Findd(nume, d->directories);
		if (rez != NULL) {
			return rez;
		}
	/*parcurg si campul directories al fiecarui director*/
		rez = Finddir(nume, d->directories);
		if (rez == NULL) {
			return rez;	
		}
	}
	return a;
}
/*functia cauta un fisier in campurile
fisier ale directoarelor/subdirectoarelor arborelui*/
TArb Findff(char *nume, TArb a) 
{
	if (a == NULL) {
		return NULL;
	}

	Fisier *f = (Fisier *)a->info;
	if (compare(nume, f->nume) == 0) {
		return a;
	} else if (compare(nume, f->nume) == 1) {
		return Findff(nume, a->dr);
	}
	return Findff(nume, a->st);
}

/*functia cauta un fisier in intreg arborele*/
/*va returna directorul parinte in care se afla fisierul cautat*/
TArb Findf(char *nume, TArb a)
{
	TArb rez = NULL;
	if (a == NULL) {
		return NULL;
	}
	Director *d = (Director *)a->info;
	if (d->fisier != NULL) {
		if (Findff(nume, d->fisier) != NULL) {
			Fisier *f = (Fisier *)d->fisier->info;
			return f->parinte;
		}
	}
	rez = Findf(nume, a->st);
	if (rez != NULL) {
		return rez;	
	}
	rez = Findf(nume, a->dr);
	if (rez != NULL) {
		return rez;	
	}
	rez = Findf(nume, d->directories);
	if (rez == NULL) {
		/*daca rez e NULL continuam parcurgerea, nu vrem sa ne oprim
		din recursivitate decat atunci cand am parcurs tot 
		arborele*/	
	}
	return rez;
}
int main ()
{
	TArb root = NULL;
	TArb current = NULL;
	root = Create_root();
	current = root; /*variabila current va pointa catre 
	directorul curent din arbore la care ne aflam*/
	int l = 0;
	char *line = NULL;
	line = malloc(N * sizeof(char));
	while(fgets(line, N, stdin) != NULL) {
		l = strlen(line);
        if (line[l - 1] == '\n') {
            line[l - 1] = '\0';
        }
		char *cuv= NULL;
        cuv = strtok(line, " ");
		if (strcmp(cuv, "touch") == 0) {
			cuv = strtok(NULL, " ");
			Touch(cuv, current);
		} else if (strcmp(cuv, "ls") == 0) {
			Director *d = (Director *)current->info;
			SRD(d->directories, afisare_dir);	
			SRD(d->fisier, afisare_files);
			printf("\n");
		} else if (strcmp(cuv, "mkdir") == 0) { 
			cuv = strtok(NULL, " ");
			Mkdir(cuv, current);
		} else if (strcmp(cuv, "rm") == 0) {
			cuv = strtok(NULL, " ");
			Rm(cuv, current);
		} else if (strcmp(cuv, "rmdir") == 0) {
			cuv = strtok(NULL, " ");
			Rmdir(cuv, current);
		} else if (strcmp(cuv, "cd") == 0) {
			cuv = strtok(NULL, " ");
			Director *d = (Director *)current->info;
			if (strcmp(cuv, "..") == 0) {
				/*variabila current va pointa inspre campul parinte al 
				directorului curent*/
				Director *d = (Director *)current->info;
				current = d->parinte;
			} else {
				TArb aux = NULL;
				TArb auxp = Cautared(d->directories, cuv);
				/*va returna adresa parintelui nodului corespunzator directorului
				catre care facem cd*/
				if (auxp == current) {
					current = d->directories;
				} else if (auxp == NULL) {
					printf("Directory not found!\n");
				} else {
					TArb auxd = auxp->dr;
					TArb auxs = auxp->st;
					if (auxd != NULL) {
						Director *dd = (Director *)auxd->info;
						if (compare(cuv, dd->nume) == 0) {
							aux = auxd;
						}
					} 
					if (auxs != NULL) {
						Director *ds = (Director *)auxs->info;
						if (compare(cuv, ds->nume) == 0) {
							aux = auxs;
						}
					}
					current = aux;
				}
			}
		} else if (strcmp(cuv,"pwd") == 0) {
			Pwd(current);
			printf("\n");
		} else if (strcmp(cuv, "find") == 0) {
			cuv = strtok(NULL, " ");
			if (strcmp(cuv, "-f") == 0) {
				cuv = strtok(NULL, " ");
				TArb aux = Findf(cuv, root);
				if (aux == NULL) {
					printf("File %s not found!\n", cuv);
				} else {
					printf("File %s found!\n", cuv);
					Pwd(aux);
					printf("\n");
				}
			} else {
				cuv = strtok(NULL, " ");
				TArb aux = Findd(cuv, root);
				if (aux == NULL) {
					printf("Directory %s not found!\n", cuv);
				} else {
					printf("Directory %s found!\n", cuv);
					Pwd(aux);
					printf("\n");
				}
			}
		} else if (strcmp(cuv, "quit") == 0) {
			free(line);
			DistrDir (&root);
			return 0;
		}
	}
	return 0;
}
