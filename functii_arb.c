/*GLODARIU Ana - 311CB*/
#include "tarb.h"
#include "struct.h"

int compare(char *nume1, char *nume2) 
{
	if (strcmp(nume1, nume2) == 0) {
		return 0; /*numele sunt egale dpdv lexicografic*/
	} 
	if (strcmp(nume1, nume2) > 0) { 
		return 1; /*nume1 este mai mare dpdv lexicografic decat nume2*/
	} 
	return 2; /*nume1 este mai mic dpdv lexicografic decat nume2*/
}

/*daca nu exista numele directorului care trebuie creat in arborele de 
subdirectoare al directorului curent, returnez nodul parintele dupa care
trebuie adaugat noul director, altfel returnez NULL*/
TArb Cauta_director(TArb a, char *nume)
{
	Director *d = (Director *)a->info;
	int rez = compare(nume, d->nume);
	if (a->dr == NULL && rez == 1) {
		return a; /*daca ajungem la un nod care n-are fiu drept si functia 
		de compare arata ca noul nod trebuie adaugat la dreapta lui inseamna ca
		am gasit parintele dupa care trebuie adaugat noul nod*/

	}
	if (a->st == NULL && rez == 2) {
		return a; /*daca ajungem la un nod care n-are fiu stang si functia 
		de compare arata ca noul nod trebuie adaugat la stanga lui inseamna ca
		am gasit parintele dupa care trebuie adaugat noul nod*/
	}
	if (rez == 0) { /*nodul exista deja in arbore*/
		return NULL;
	}
	/*in functie de valoarea returnata de functia de compare ne deplasam pe dr
	sau st prin arbore*/
	if (rez == 1) { 
		return Cauta_director(a->dr, nume);
	}
	return Cauta_director(a->st, nume);
}

/*daca nu exista numele fisierului care trebuie creat in arborele de fisiere
al directorului curent, returnez nodul parinte dupa care trebuie adaugat, 
altfel returnez NULL*/
TArb Cauta_fisier(TArb a, char *nume)
{
	Fisier *f = (Fisier *)a->info;
	int rez = compare(nume, f->nume);
	if (a->dr == NULL && rez == 1) {
		return a; /*daca ajungem la un nod care n-are fiu drept si functia 
		de compare arata ca noul nod trebuie adaugat la dreapta lui inseamna ca
		am gasit parintele dupa care trebuie adaugat noul nod*/

	}
	if (a->st == NULL && rez == 2) {
		return a; /*daca ajungem la un nod care n-are fiu stang si functia 
		de compare arata ca noul nod trebuie adaugat la stanga lui inseamna ca
		am gasit parintele dupa care trebuie adaugat noul nod*/
	}
	if (rez == 0) { /*nodul exista deja in arbore*/
		return NULL;
	}
	/*in functie de valoarea returnata de functia de compare ne deplasam pe dr
	sau st prin arbore*/
	if (rez == 1) { 
		return Cauta_fisier(a->dr, nume);
	}
	return Cauta_fisier(a->st, nume);
}
/*functie care imi va returna adresa parintelui nodului pe care il caut*/
/*se aplica pe arbori de fisiere*/
TArb Cautaref(TArb a, char *nume) {
	if (a == NULL) {
		return NULL; /*daca am parcurs tot arborele si nu am 
		gasit nodul, inseamna ca nu exista*/
	}
	Fisier *f = (Fisier *)a->info;
	if (a->dr != NULL) {
		/*daca nodul curent are copil dreapta*/
		Fisier *cd = (Fisier *)a->dr->info;
		/*daca copilul nodului a e nodul cautat, returnez a*/
		if (compare(nume, cd->nume) == 0) {
			return a;
		}
	}
	
	if (a->st != NULL) {
		/*daca nodul curent are copil stanga*/
		Fisier *cs = (Fisier *)a->st->info;
		/*daca copilul nodului a e nodul cautat, returnez a*/
		if (compare(nume, cs->nume) == 0) {
			return a;
		}
	}
	/*daca nu am gasit parintele nodului cautat, continui parcurgerea
	prin arbore*/
	int rez = compare(nume, f->nume);
	if (rez == 0) { /*daca e radacina arborelui*/
		return f->parinte;
	} else if (rez == 1) {
		return Cautaref(a->dr, nume);
	} 
	return Cautaref(a->st, nume);
}

/*functie care imi va returna adresa parintelui nodului pe care il caut*/
/*se aplica pe arbori de directoare*/
TArb Cautared(TArb a, char *nume) {
	if (a == NULL) {
		return NULL; /*daca am parcurs tot arborele si nu am 
		gasit nodul, inseamna ca nu exista*/
	}
	Director *d = (Director *)a->info;
	if (a->dr != NULL) {
		/*daca nodul curent are copil dreapta*/
		Director *cd = (Director *)a->dr->info;
		/*daca copilul nodului a e nodul cautat, returnez a*/
		if (compare(nume, cd->nume) == 0) {
			return a;
		}
	}
	
	if (a->st != NULL) {
		/*daca nodul curent are copil stanga*/
		Director *cs = (Director *)a->st->info;
		/*daca copilul nodului a e nodul cautat, returnez a*/
		if (compare(nume, cs->nume) == 0) {
			return a;
		}
	}
	/*daca nu am gasit parintele nodului cautat, continui parcurgerea
	prin arbore*/
	int rez = compare(nume, d->nume);
	if (rez == 0) { /*daca e radacina arborelui*/
		return d->parinte;
	} else if (rez == 1) {
		return Cautared(a->dr, nume);
	} 
	return Cautared(a->st, nume);
}

int Mkdir(char *nume, TArb arb) 
{
	TArb aux = NULL, p1 = NULL, p = NULL;
	Director *D = (Director *)arb->info;
	/*vedem daca in arborele de fisiere al directorului curent
	exista deja numele directorului pe care vrem sa-l adaugam*/
	if (D->fisier != NULL) {
		p = Cauta_fisier(D->fisier, nume);
		if (p == NULL) {
			printf("File %s already exists!\n", nume);
			return 0; /*creare director esuata*/
		}
	}		
	/*vedem daca in arborele de subdirectoare al directorului curent
	exista deja numele directorului pe care vrem sa-l adaugam*/
	if (D->directories != NULL) {
		p1 = Cauta_director(D->directories, nume);
		if (p1 == NULL) {
			printf("Directory %s already exists!\n", nume);
			return 0; /*creare fisier esuata*/
		}
	}
	/*daca nu am gasit numele directorului care trebuie adaugat
	in directorul curent*/
	Director *d = NULL;
	d = AlocDirector(nume, arb);
	if (d == NULL) {
		return 0;
	}
	/*daca arborele din campul directories al directorului curent este vid*/
	if (D->directories == NULL) {
		D->directories = ConstrFr(d, sizeof(Director)); /*creez radacina campului
	 	directories al directorului curent*/
		if (D->directories == NULL) {
			free(d->nume);
			free(d);
			return 0;
		}
		return 1; /*director creat cu succes*/
	}
	aux = ConstrFr(d, sizeof(Director));
	if (aux == NULL) {
		free(d->nume);
		free(d);
		return 0;
	}
	/*adaug dupa nodul parinte noul director*/
	Director *pd = (Director *)p1->info; 
	if (compare(nume, pd->nume) == 2) {
		p1->st = aux;
	} else {
		p1->dr = aux;
	}
	return 1;
}

int Touch(char *nume, TArb arb) 
{
	TArb aux = NULL, p1 = NULL, p = NULL;
	Director *d = (Director *)arb->info;
	/*vedem daca in arborele de fisiere al directorului curent
	exista deja numele fisierului pe care vrem sa-l adaugam*/
	if (d->fisier != NULL) {
		p = Cauta_fisier(d->fisier, nume);
		if (p == NULL) {
			printf("File %s already exists!\n", nume);
			return 0; /*creare fisier esuata*/
		}
	}		
	/*vedem daca in arborele de subdirectoare al directorului curent
	exista deja numele fisierului pe care vrem sa-l adaugam*/
	if (d->directories != NULL) {
		p1 = Cauta_director(d->directories, nume);
		if (p1 == NULL) {
			printf("Directory %s already exists!\n", nume);
			return 0; /*creare fisier esuata*/
		}
	}
	/*daca nu am gasit numele fisierului care trebuie adaugat
	in directorul curent*/
	Fisier *f = NULL;
	f = AlocFisier(nume, arb);
	if (f == NULL) {
		return 0;
	}
	if (d->fisier == NULL) {
		/*daca arborele din campul fisier al directorului curent este vid*/
		d->fisier = ConstrFr(f, sizeof(Fisier)); /*creez radacina campului
	 	fisier al directorului curent*/
		if (d->fisier == NULL) {
			free(f->nume);
			free(f);
			return 0;
		}
		return 1; /*fisier creat cu succes*/
	}
	aux = ConstrFr(f, sizeof(Fisier));
	if (aux == NULL) {
		free(f->nume);
		free(f);
		return 0;
	}
	/*adaug dupa nodul parinte noul fisier*/
	Fisier *pf = (Fisier *)p->info;
	if (compare(nume, pf->nume) == 2) {
		p->st = aux;
	} else {
		p->dr = aux;
	}
	return 1;
}
