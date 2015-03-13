	Elemente de graficã pe calculator - Tema 1
******************************************************************************************

	Simplified Geometry Dash
	Despa Diana Alexandra 331CA

******************************************************************************************

	Cuprins
1. Cerinta
2. Utilizare
3. Implementare
4. Testare
5. Probleme Aparute
6. Continutul Arhivei
7. Functionalitati
8. Mentiuni

******************************************************************************************

1. Cerinta
	Implementarea unui joc similar cu Geometry Dash, in care jucatorul se deplaseaza
pe o platforma si poate realiza actiunea de JUMP pentru a evita obstacole, sau pentru a
trece de golurile din platforma. In cazul in care jucatorul atinge un obstacol sau cade in
gol, el pierde o viata, numarul maxim de vieti disponibile fiind 3. Pe parcursul jocului,
jucatorul acumuleaza puncte care reprezinta totodata si puncte de intoarcere, scopul final
fiind acumularea a 5 puncte.

******************************************************************************************

2. Utilizare
	Programul se ruleaza prin lansarea executabilului Tema1.exe, din folderul Debug,
sau din interiorul Visual Studio. Interactiunea cu programul se face prin apasarea tastei
SPACE, care face ca jucatorul sa realizeze actiunea de JUMP in cazul in care el se afla pe
platforma.

******************************************************************************************

3. Implementare
	Ca IDE, am folosit Microsoft Visual Studio 2013, instalat pe Windows 7, insa am
implementat aplicatia folosind Visual C++ 2010, ca sa ma asigur ca functioneaza cu
versiuni mai recente de Visual C++.
	Am pornit cu implementarea de la framework-ul laboratorului 2.
	Prin apelul functiei init(), sunt create contextele vizuale pentru scena principala,
particule si pentru textul din partea de sus a ferestrei, sunt instantiate si desenate
obiectele care compun scena - fundalul, avatarul jucatorului, efectul de particule si
decorul scenei. Pentru generarea unui nou frame, in functia onIdle() deplasez fereastra
contextului pentru scena si cea a efectului de particule, astfel incat ele sa urmareasca
miscarea jucatorului. Pozitia acestuia este actualizata in functie de obiectele de pe scena
si felul cum interactioneaza cu ele. De asemenea, textul din partea de sus a ecranului
este actualizat in cazul in care jucatorul castiga un punct sau o viata bonus. Generarea
de noi frame-uri este oprita atunci cand jucatorul nu mai are vieti ramase, caz in care a
pierdut, sau a acumulat 5 puncte, caz in care a castigat.
	Am implementat clase ajutatoare pentru abstractizarea elementelor din scene.
	Clasa Background defineste fundalul scenei, iar in metoda draw() genereaza coloane
de dreptunghiuri de lungime egala pe lungimea intregii scene, cate 3 pe coloana, fiecare
avand o inaltime aleatoare.
	Clasa Stats tine evidenta numarului de puncte acumulate, numarului de vieti ramase,
pozitiilor ultimelor bonusuri atinse de jucator. Ea permite modificarea acestor valori
prin metode de tip getter si setter.
	Clasa Particles pastreaza valorile specifice fiecarei particule care se afla in
scena la un moment dat. Cum particulele au o miscare sinusoidala atenuata, fiecare are
o anumita amplitudine asociata, o pulsatie, un grad de scalare, o pozitie initiala,
deplasamentul fata de pozitia initiala si un obiect 2D reprezentativ. Toate aceste valori
sunt pastrate in vectori. Metoda draw() este apelata doar atunci cand jucatorul este in
contact cu platforma, ea generand noi particule. Metoda move() translateaza si scaleaza
particulele existente si sterge particulele care au amplitudinea miscarii mai mica de 0.5.
Metoda clear() sterge toate particulele din scena.
	Clasa Scene retine toate obiectele din scena prin pozitiile lor, utilizand o
matrice care contine simboluri pentru fiecare tip de obiect ce poate fi generat. Ea
contine metode pentru desenarea si/sau stergerea obiectelor din scena. Prin metoda
move() se realizeaza si miscarea obstacolelor dinamice, in functie de o periodicitate data
de valoarea frames.
	Clasa Icon este cea mai complexa intrucat realizeaza in principal miscarea
iconitei/avatarului jucatorui. Ea contine ca membri poiteri la obiectele de tip scena,
particule si starea jocului(stats) pentru a putea interactiona cu ele; de asemenea,
obiecte 2D pentru trasaturile avatarului, si membri si metode care tin evidenta miscarii
si pozitiei lui. Metoda move() este cea mai importanta deoarece ea realizeaza deplasarea
avatarului, actualizeaza starea jocului prin valoarea intoarsa si foloseste toate metodele
private pentru a realiza asta. In metoda: 
- verific coliziunile cu obstacole sau cu partile laterale ale platformei, iar cand apare
o coliziune resetez iconita la ultimul checkpoint si variabilele de miscare si intorc
simbolul corespunzator;
- activez efectul de particule daca se afla pe platforma, asta insemnand ca avatarul este
rotit la un unghi multiplu de PI / 2 si sub el, in matricea scenei, si afla simbolul
pentru platforma; 
- verific daca atinge un punct, un bonus sau un booster, iar in caz afirmativ actualizez
stats si setez variabilele care imi indica saritura in desfasurare in mod corespunzator;
- verific daca se afla in cadere deasupra unei platforme, caz in care trebuie sa aterizeze,
deci il rotesc la cel mai apropiat multiplu de PI / 2 si actualizez variabilele de miscare;
- actualizez variabilele de miscare in functie de starea in care se afla: in cadere, 
in timpul unei sarituri (saritura este descrisa de o parabola cu functia din metoda
formula), in gol (de exemplu scad unghiul de rotatie).

******************************************************************************************

4. Testare
	Am testat diferite scenarii, generand diverse scene. Nu am utilizat teste automate.
Am utilizat debugger-ul din Visual Studio.

******************************************************************************************

5. Probleme aparute
	Am intampinat ceva probleme cand am implementat caderea libera, sariturile si
coliziunile cu obiecte, inclusiv aterizarea pe platforma, insa am gasit solutia cu matricea
scenei si verificarea colturilor sau centrului iconitei pentru coliziuni.

******************************************************************************************

6. Continutul Arhivei
	main.cpp
	Background.cpp
	Background.h
	Icon.cpp
	Icon.h
	Particles.cpp
	Particles.h
	Scene.cpp
	Scene.h
	Stats.cpp
	Stats.h
	Framework-ul de la laborator.

******************************************************************************************

7. Functionalitati
	Functionalitati Standard
		Miscarea stanga-dreapta constanta a jucatorului
		Actiunea de JUMP cu rotatie
		Obstacole
		Coliziuni cu obstacole
		Acumulare de puncte
		Intoarcere la checkpoint
		Elemente ajutatoare (simbolul JUMP, activeaza auto_jump in Icon)
		Afisaj corespunzator

	Functionalitati Bonus
		Efecte de particule
		Simularea gravitatii
		Scene complexe
		Obstacole dinamice
		Bonusuri pentru jucator:
			- jump booster(BOOST) - dubleaza inaltimea sariturii
			- viata bonus(BONUS, EXTRA_LIFE) - creste numarul de incercari cu 1

	Functionalitati Suplimentare
		Fundal generat random

******************************************************************************************

8. Mentiuni
	Majoritatea comentariilor din cod, in special cele care descriu metode si membri
ale claselor implementate se afla in fisierele de tip header.