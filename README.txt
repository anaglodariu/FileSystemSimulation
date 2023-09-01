 In headerul tarb.h am definit structura pentru arborele de cautare, cu un 
camp in care vom tine informatia din noduri si campurile cu adresele 
subarborilor stang si drept al fiecarui nod din arbore.

 In headerul struct.sh am definit 2 structuri pentru informatia din nodul unui 
arbore :
- informatie de tip director
- informatie de tip fisier

 Prima oara creez radacina arborelui de directoare (root) cu functia 
Create_root.
 Variabila de tip TArb current o sa pointeze mereu catre directorul curent la
care ne aflam.

 Pentru comanda TOUCH: am functia Touch, care, atunci cand adauga un fisier in
directorul curent, mai intai verifica daca a mai fost creat pana atunci un 
fisier sau director cu acelasi nume ; verificarea se face cu functiile 
Cauta_fisier si Cauta_director, care returneaza adresa nodului dupa care
trebuie adaugat nodul corespunzator fisierului sau NULL, daca deja exista.
Daca nu exista fisierul in arbore, aloc memorie pentru informatia de tip
fisier (cu functia AlocFisier) si pentru nod (cu functia ConstrFr) ; apoi noul
nod il leg in arborele de fisiere, folosindu-ma de adresa returnata de functia
Cauta_fisier.

 Pentru comanda MKDIR: am functia Mkdir, care functioneaza la fel ca functia 
Touch, doar ca adauga un subdirector in directorul curent, iar nodul nou creat
cu informatia de tip director este legat in arborele de directoare,
folosindu-ma de adresa returnata de functia Cauta_director.

 Pentru comanda LS: am functia SRD, care imi va face o parcurgere de tip SRD
prin arbore si imi va afisa numele fisierelor/subdirectoarelor din campurile
fisier/directories din directorul curent in ordine crescatoare dpdv
lexicografic ; am 2 functii separate de afisare a informatiei din noduri :
- afisare_files (pentru info de tip fisier)
- afisare_dir (pentru info de tip director)

 Pentru comenzile RM si RMDIR: am functiile Rm si Rmdir si in fiecare iau in
calcul 3 cazuri :
- daca nodul care trebuie eliminat este frunza
- daca nodul care trebuie eliminat este de ordin 1
- daca nodul care trebuie eliminat este de ordinul 2
 De asemenea, iau separat cazul in care nodul este radacina unui arbore de tip 
fisier sau de tip director, pentru ca trebuie modificat in plus campul fisier
sau directories al directorului curent.
 Mereu ma asigur ca dezaloc memoria cand elimin ; pentru directoare trebuind 
dezalocate si campurile fisier si directories.
 Pentru functiile de eliminare ma folosesc de functiile Cautaref si Cautared, 
care imi cauta fisierul sau directorul care trebuie eliminat si imi returneaza 
adresa nodului parinte al acestuia pentru ca am nevoie de el la eliminare, 
iar daca stim parintele putem afla usor si nodul pe care il elminam.
 Pentru eliminarea unui nod de ordin 2 procedez astfel: pentru ca arborele sa
ramana echilibrat, pornind pe subarborele drept al nodului care trebuie 
eliminat caut nodul corespunzator fisierului/directorului cu numele cel mai mic
dpdv lexicografic (cu functia Minimum) si interschimb informatiile din cele 2
noduri intre ele, iar totul se va reduce la eliminarea nodului cautat care 
poate fi o frunza sau un nod de ordin 1.

 Pentru comanda PWD, am functia Pwd, care merge recursiv pe directoarele 
parinte ale subdirectoarelor pana ajunge la parintele NULL al lui ROOT.

 Pentru comanda FIND, am functiile Findd, Finddir (pentru "find -d") si
functiile Findf, Findff (pentru "find -f"). Incepand de la ROOT ma pot deplasa
pe campurile dr si st ale nodurilor sau pe campul fisier/directories, pentru a
ma asigura ca trec prin toate fisierele si directoarele, din care pleaca la 
randul lor alte fisiere si subdirectoare. Cautarea prin campul 
fisier/directories este facuta de functiile Findff si Finddir.
Valorile de return ale functiilor recursive Findd si Findf sunt pastrate in
variabila rez, pentru a ma asigura ca trec prin tot arborele.

 Pentru dezalocarea memoriei intregului arbore, ma asigur, ca la functiile de
find, ca parcurg tot arborele, elimininand pentru fiecare director mai intai
campurile fisier si directories cu functiile distruge_f (distrugerea arborilor 
de fisiere) si Distruge (distrugerea arborilor de directoare/sudirectoare).

Punctaj obtinut pe teste:

ana@DESKTOP-RPATT8R:~/sda/tema3$ ./check.sh 
gcc -g -Wall main.c functii_arb.c tarb.c -o tema3

                        = Tema 3 SD SistemFisiere =

[output1.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output2.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output3.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output4.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output5.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output6.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output7.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output8.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output9.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output10.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output11.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output12.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output13.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output14.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output15.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output16.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output17.txt]...........................................passed  [04/135]
[VALGRIND: PASSED]....................................passed

[output18.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output19.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output20.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output21.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output22.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output23.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output24.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output25.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output26.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output27.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output28.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output29.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed

[output30.txt]...........................................passed  [05/135]
[VALGRIND: PASSED]....................................passed


                                           Total: [135/135]

                                           Bonus: [22/20]

