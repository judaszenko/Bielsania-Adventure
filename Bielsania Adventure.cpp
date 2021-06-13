#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <locale.h>
#include <sstream>
#include <time.h>
using namespace std;
	
    int pl_hp = 100;   //punkty zycia
    int pl_dmg = 10;   //sila ataku
    int pl_rep = 0;    //reputacja 
    int pl_cash = 100; //w sensie zlotowki
    int pl_kev = 0;	   //zbroja gracza
    int pl_kev_health = 0; //zdrowie zbroi gracza
    int pl_weap = 0;   //bron gracza
    int pl_food = 0;   //ile jedzenia ma gracz (kebabow), 1 kebab = 20 HP
    int pl_map = 0;	   //okresla czy gracz posiada mape
    int pl_stal = 0;   //ile kawalkow stali ma gracz, przydatne przy kowalu
    
    int pass = 0;      //jezeli =1 to znaczy ze zaczyna sie gra
    int ending = 0;    //zakonczenie zalezne od rozmowy
    int wyjdz = 0;	   //zeby wyjsc z menu
    int tajm = 40;     //czas miedzy kreskami w tytule
    string HUD = "ON";  //czy HUD ma byc wyswietlany
    
	int miedz = 0; //miedziana ruda ktora ma byc dostarczona kowalowi
	int kowal = 0; //liczba wizyt u kowala    
	int ch2 = 0; //zmienna do rozdzialu 2, pomaga w petlowaniu godziburga
	int innos = 0;  //ilosc blogoslawienstw boga, zabezpieczenie
	int adanos = 0; //zabezpieczenie blogoslawienstwa ksiedza
	int bindar_cash = 0;
	int michniard_tip = 0;
	int wola_zajaslawa = 1;
	
void kreska() { 		//rysowanie kreski, element GUI
    cout<<"______________________________________________"<<endl;
}
void stats() {
	if (HUD == "ON"){
	cout<<"\n| HP "<<pl_hp<<" | KEV "<<pl_kev_health<<" | DMG "<<pl_dmg<<" | REP "<<pl_rep<<" | CASH "<<pl_cash<<" |\n";
	} else {
		cout<<"";
	}
}
int check(int odpowiedz, int ile_pytan){ //zabezpieczenie GUI i rozmow
	
	if (odpowiedz == 9){
		kreska();
		cout<<"| 1. HP\n";
		cout<<"| 2. DMG\n";
		cout<<"| 3. CASH\n";
		kreska();
		int hack1;
		cin>>hack1;
		switch (hack1){
			case 1:
				cout<<"| Add HP: ";
				int HP;
				cin>>HP;
				pl_hp = pl_hp + HP;
				break;
			case 2:
				cout<<"| Add DMG: ";
				int DMG;
				cin>>DMG;
				pl_dmg = pl_dmg + DMG;
				break;
			case 3:
				cout<<"| Add CASH: ";
				int CASH;
				cin>>CASH;
				pl_cash = pl_cash + CASH;
				break;
		}
	}
	
	if (odpowiedz > ile_pytan || odpowiedz == 0){
		kreska();
		cout<<"\n| To nie jest prawidlowa odpowiedz, napisz jeszcze raz \n";
		kreska();
		odpowiedz = 0;
		do {
			cin>>odpowiedz;
		}while(odpowiedz > ile_pytan || odpowiedz == 0);
	}
	return odpowiedz;
}
void mapa(){
	cout<<"______________________________________________\n";
	cout<<"|                                            |\n";
	cout<<"|                       CZECHIGROD           |\n";
	cout<<"|                        ___________         |\n";
	cout<<"|          ____________ / O  o o  __|        |\n";
	cout<<"| SPORDAN | ___________    o   O /           |\n";
	cout<<"|      \\ _| |          |O O O O |            |\n";
	cout<<"|       |o  |          \\_______/             |\n";
	cout<<"|       |_  |                                |\n";
	cout<<"|         | |                  ___________   |\n";
	cout<<"|         | |                 /  o o  o  o|  |\n";
	cout<<"|        _| |_               |o           |  |\n";
	cout<<"|       |o   o|_____         |  BIELOGROD |  |\n";
	cout<<"|       |O  O  ___  |        | o          |  |\n";
	cout<<"|       |_____|   | |        | O O   O O o|  |\n";
	cout<<"|      /          | |         \\  __      o|  |\n";
	cout<<"|     LITYNIA     | |         / /  \\ o   o|  |\n";
	cout<<"|           ______| |_      / /     \\  o o|  |\n";
	cout<<"|          / O  O    /     | |       \\___/   |\n";
	cout<<"|         /O   o   O/______| |               |\n";
	cout<<"|        |O  O o   ________  |     SERWENIA  |\n";
	cout<<"|        \\________/        | |           \\_  |\n";
	cout<<"|             /            | |__________|  | |\n";
	cout<<"|     GODZIBURG            |_______________| |\n";
	cout<<"______________________________________________\n\n  ";
	system("pause");
	system("cls");
	stats();
	kreska();
	cout<<"|\n";
}
void tytul(){			//wypisanie tytulu
	cout<<" ____________________________________________\n";
	Sleep(tajm);
	cout<<" |  ____         _                 _        |\n";
	Sleep(tajm);
	cout<<" | |  _ \\(_)    | |               (_)       |\n";
	Sleep(tajm);
	cout<<" | | |_) |_  ___| |___  __ _ _ __  _  __ _  |\n";
	Sleep(tajm);
	cout<<" | |  _ <| |/ _ \\ / __|/ _` | '_ \\| |/ _` | |\n";
	Sleep(tajm);
	cout<<" | | |_) | |  __/ \\__ \\ (_| | | | | | (_| | |\n";
	Sleep(tajm);
	cout<<" | |____/|_|\\___|_|___/\\__,_|_| |_|_|\\__,_| |\n";
	Sleep(tajm);
	cout<<" ____________________________________________\n";
	Sleep(tajm);
}
void disclaimer(){
	cout<<"\n         UWAGA, GRA WYMAGA MINIMALNIE \n            TAKIEJ SZEROKOSCI OKNA\n";
	cout<<"<____________________________________________>"<<endl;
	cout<<"\n       DOSTOSUJ SWOJE USTAWIENIA OKNA\n\n       ";
	system("pause");
}
int walka(int enemy){	//modul walki
	srand(time(NULL));
	int en_hp;			//HP wroga
	int en_dmg;			//DMG wroga
	int en_kev;			//zbroja wroga
	int en_kev_health; 	//stan zbroi wroga
	int en_weap;		//bron wroga
	string name;		//nazwa wroga
	int win = 0;		//zwyciezca (1=wrog, 2=Player)
	cout<<"|                 WALKA          \n|\n";
	if (enemy == 1){
		name = "STEBENIA";
		en_hp = 70;
		en_dmg = 6;
		en_kev = 0;
		en_weap = 0;
	} else if (enemy == 2){
		name="SPORDAN";
		en_hp = 200;
		en_dmg = 30;
		en_kev = 2;
		en_weap = 2;
	} else if (enemy == 3){
		name="BINDAR";
		en_hp = 120;
		en_dmg = 50;
		en_kev = 2;
		en_weap = 2;
	} else if (enemy == 4){
		name="ZAJ�S�AW";
		en_hp = 240;
		en_dmg = 70;
		en_kev = 2;
		en_weap = 2;
	} else if (enemy == 5){
		name="STEFIR";
		en_hp = 180;
		en_dmg = 80;
		en_kev = 3;
		en_weap = 2;
	} else if (enemy == 6){
		name="GADZIMYS�";
		en_hp = 200;
		en_dmg = 40;
		en_kev = 2;
		en_weap = 1;
	} else if (enemy == 7){
		name="SKRETKOWY POTW�R";
		en_hp = 100;
		en_dmg = 35;
		en_kev = 1;
		en_weap = 0;	
	} else if (enemy == 8){
		name="WOJMIR";
		en_hp = 200;
		en_dmg = 100;
		en_kev = 4;
		en_weap = 2;	
	}

	if (pl_kev == 1){pl_kev_health = 40;}
		else if (pl_kev == 2){pl_kev_health = 100;}
 		else if (pl_kev == 3){pl_kev_health = 160;}
		else if (pl_kev == 5){pl_kev_health = 500;}
	else {pl_kev_health = 0;}
		
	if (en_kev == 1){en_kev_health = 40;}
		else if (en_kev == 2){en_kev_health = 100;}
 		else if (en_kev == 3){en_kev_health = 160;}
 		else if (en_kev == 4){en_kev_health = 350;}
	else {en_kev_health = 0;}
	war:
	system("cls");
	stats();
	kreska();
	cout<<"\n PLAYER      "<<name<<"   ";
	cout<<"\n                       |";
	cout<<" TWOJE HP: "<<pl_hp<<"\n";
	cout<<"   O            O      |";
	cout<<" TWOJ KEVLAR: "<<pl_kev_health<<"\n";
	cout<<"  /";
	if (pl_kev == 1){cout<<"T";} else if (pl_kev == 2) {cout<<"H";}else if (pl_kev == 5) {cout<<"X";}else if (pl_kev == 3) {cout<<"W";}else if(pl_kev == 0){cout<<"|";}
	cout<<"\\";
 	if (pl_weap == 1 || pl_weap == 2){cout<<"/";} else {cout<<" ";}
	cout<<"        ";
	if (en_weap == 1 || en_weap == 2){cout<<"\\";} else {cout<<" ";}
	cout<<"/";
	if (en_kev == 1){cout<<"T";} else if (en_kev == 2) {cout<<"H";}else if (en_kev == 3) {cout<<"W";}else if (en_kev == 4) {cout<<"X";}else {cout<<"|";}
	cout<<"\\     |";
	cout<<" HP PRZECIWNIKA: "<<en_hp<<"\n";
	cout<<"  / \\          / \\     |";
	cout<<" KEVLAR WROGA: "<<en_kev_health<<"\n";
	kreska();
	cout<<"| 1. Atak \n";
	cout<<"| 2. Obrona \n";
	cout<<"| 3. Regeneruj HP \n";
	cout<<"| 4. Uciekaj \n";
	kreska();
	int walka;
	cin>>walka;
	switch (check(walka, 4)){
		case 1:
    		if (pl_kev == 0){
    			if ((pl_hp - en_dmg) <= 0){
					win = 2;
				} else {
    				pl_hp = pl_hp - rand() % en_dmg + 1;
				}
			}else {  
				if ((pl_kev_health - en_dmg) <= 0){
					pl_kev_health = pl_kev_health - rand() % en_dmg + 1;
					pl_hp = pl_hp + pl_kev_health;
					pl_kev = 0;
					pl_kev_health = 0;
	  	    	} else {
				  pl_kev_health = pl_kev_health - rand() % en_dmg + 1;
  	  	  	    }	
			}
			
    		if (en_kev == 0){
    			if ((en_hp - pl_dmg) <= 0){
					win = 1;
				} else {
    				en_hp = en_hp - rand() % pl_dmg + 1;
				}
			}else {  
				if ((en_kev_health - pl_dmg) <= 0){
					en_kev_health = en_kev_health - rand() % pl_dmg + 1;
					en_hp = en_hp + en_kev_health;
					en_kev = 0;
					en_kev_health = 0;
	  	    	} else {
				  en_kev_health = en_kev_health - rand() % pl_dmg + 1;
  	  	  	    }	
			}
			break;
		case 2:
			system("cls");
    		if (pl_kev == 0){
    			if ((pl_hp - (rand() % en_dmg + 1 / 10)) <= 0){
					win = 2;
				} else {
    				pl_hp = pl_hp - ((rand() % en_dmg + 1 / 10) / 10);
				}
			}else {  
				if ((pl_kev_health - (en_dmg / 10)) <= 0){
					pl_kev_health = pl_kev_health - ((rand() % en_dmg + 1 / 10) / 10);
					if ((pl_hp + pl_kev_health) <= 0){
						win = 2;
					} else {
						pl_hp = pl_hp + pl_kev_health;
						pl_kev = 0;
						pl_kev_health = 0;
					}
	  	    	} else {
				  pl_kev_health = pl_kev_health - (en_dmg / 10);
  	  	  	    }	
			}
			break;
 		case 3:
	 	 	if (pl_food >= 1){
	 	 		system("cls");
				  pl_hp = pl_hp + 20;
				  pl_food = pl_food - 1;
	  	    }
			break;
		case 4:
			win = 3;
			break;	 
	}
	if (win != 0){		
	return win;
	}else {goto war;}
}
void spordan(){
	cout<<"| Spordan: Podejd� tu, mam towar z najwy�szej \n";
	cout<<"| 	   p�ki. Wybierz sobie co�!\n|\n";
	handel:
	cout<<"| 1. Lekka zbroja Spartanina: 70$  +40 KEV \n";
	cout<<"| 2. Miecz wyzwolenia Aten:   100$ +7  DMG \n";
	cout<<"| 3. Krzy� krzy�akow:         40$  +2  REP\n";
	cout<<"| 4. Pasza (Kebab)    	      15$  +1  FOOD\n";
	if (pl_map == 0){
		cout<<"| 5. Mapa:		      60$  +1  MAPA\n";
	} else {
		cout<<"| 5. Zobacz mape\n";
	}
	cout<<"| 6. okradnij Spordana\n";
	cout<<"| 7. chyba jednak podzi�kuj�...\n";
	cout<<"|\n| Portfel: "<<pl_cash<<"\n";
	kreska();
	int handel;
	cin>>handel;
	switch (check(handel,7)){
		case 1:
			system("cls");
			if (pl_kev == 1){
				stats();
				kreska();
				cout<<"|\n| Spordan: Przecie� juz masz t� zbroj�! \n|\n";
				goto handel;
			}
			if (pl_cash < 60){
				stats();
				kreska();
				cout<<"|\n| Spordan: Przykro mi, ale nie sta� ci�. \n|\n";
				goto handel;
			} else {
			pl_cash = pl_cash - 60;
			pl_kev = 1;
			pl_kev_health = pl_kev_health + 40;
			stats();
			kreska();
			cout<<"|\n| Spordan: Pasuje jak ula�! Taka plandeka wytrzyma wiele.\n|          �yczysz sobie czego� jeszcze? \n|\n";
			goto handel;
			}
        case 2:
        	system("cls");
        	if (pl_weap >= 1){
        		stats();
				kreska();
				cout<<"|\n| Spordan: Przecie� masz lepszy miecz! \n|\n";
				goto handel;
			}
        	if (pl_weap == 1){
        		stats();
				kreska();
				cout<<"|\n| Spordan: Przecie� juz masz ten miecz! \n|\n";
				goto handel;
			}
			if (pl_cash < 100){
				stats();
				kreska();
				cout<<"|\n| Spordan: Przykro mi, ale nie sta� cie. \n|\n";
				goto handel;
			} else {
			pl_cash = pl_cash - 100;
        	pl_weap = 1;
        	pl_dmg = pl_dmg + 7;
			stats();
			kreska();	
        	cout<<"|\n| Spordan: Jeste� teraz o wiele silniejszy. Chcesz co� jeszcze?\n|\n";
        	goto handel;
			}
        case 3:
        	system("cls");
			if (pl_cash < 60){
				stats();
				kreska();
				cout<<"|\n| Spordan: Przykro mi, ale nie sta� cie. \n|\n";
				goto handel;
			} else {
			pl_cash = pl_cash - 40;
        	pl_rep = pl_rep + 2;
			stats();
			kreska();
        	cout<<"|\n| Spordan: Z nim zyskasz szacunek ludzi.\n|           Potrzebujesz czego� jeszcze?\n|\n";
        	goto handel;
			}
        case 4:
        	system("cls");
			if (pl_cash < 15){
				stats();
        		kreska();
				cout<<"|\n| Spordan: Przykro mi, ale nie sta� cie. \n|\n";
				goto handel;
			} else {
        	pl_cash = pl_cash - 15;
        	pl_food = pl_food + 1;
        	stats();
			kreska();
        	cout<<"|\n| Spordan: Ten kebab postawi ci� na nogi! \n|\n";
        	goto handel;
			}
		case 5:
			system("cls");
			if (pl_map == 1){
				stats();
        		mapa();
				goto handel;
			}	
			if (pl_cash < 60){
				stats();
        		kreska();
				cout<<"|\n| Spordan: Przykro mi, ale nie sta� cie. \n|\n";
				goto handel;
			}
			pl_map = 1;
			pl_cash = pl_cash - 60;
			stats();
        	kreska();
				cout<<"|\n| Spordan: Z ni� nigdy si� nie zgubisz\n|\n";
				goto handel;
		case 6:
			system("cls");
			stats();
			kreska();
			cout<<"|\n";
			switch (walka(2)){
				case 1:
					system("cls");
					pl_cash = pl_cash + 200;
					stats();
					kreska();
					cout<<"|\n| Spordan: b�d� ci� mia� na oku gnojku...\n";
					cout<<"|\n| Ukradziono 200$\n";
					if(pl_kev == 0){
						pl_kev = 1;
						pl_kev_health = 40;
						cout<<"|\n| Otrzymano: Lekka zbroja spartanina\n";
					} else if (pl_weap == 0){
						pl_weap = 1;
						pl_dmg = pl_dmg + 7;
						cout<<"|\n| Otrzymano: Miecz wyzwolenia Aten\n";
					}
					break;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Spordan: Nastepnym razem ci� zabije. \n";
					break;
				case 3:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Spordan: Haha, uciekaj!\n";
					break;
			}
			break;
		case 7:
			system("cls");
			stats();
			kreska();
			cout<<"|\n| Spordan: Jeszcze si� spotkamy! \n|\n";	
			break;
	}
}
void start () {			//prolog
    stats();
	kreska();
	cout<<"\n| --- Kraina Bielsania, wiek XVI --- \n|\n";
    cout<<"| Wchodzisz do miejscowosci Czechigr�d \n|\n";
    cout<<"| Stebenia: Ca�e szcz�cie ze jeste�! \n|\n";
    cout<<"| 1. Co si� sta�o? \n";
    cout<<"| 2. Nie ciesz� sie z twojej obecno�ci  \n";
    cout<<"| 3. Oddawaj mi wszystko co masz kobieto! \n";
    kreska();
    int odp1;
    cin>>odp1;
    switch (check(odp1,3)){
        case 1: {
        	system("cls");
        	stats();
            kreska();
            cout<<"|\n| Stebenia: W�asnie ca�a nasza wioska \n";
			cout<<"| zosta�a obrabowana. Od czasu gdy \n";
			cout<<"| Wojmir zacz�� wysy�a� do naszej wioski \n";
			cout<<"| swoje wojska, wszyscy mamy obowi�zek sie \n";
			cout<<"| mu podporz�dkowa�, inaczej nas zabije \n|\n";
            cout<<"| 1. Mog� wam w jaki� spos�b pom�c? \n";
            cout<<"| 2. Nie interesuje mnie �e macie z nim \n";
			cout<<"|    problem. Mam wa�niejsze sprawy \n";
            kreska();
            int odp2;
            cin>>odp2;
                switch (check(odp2,2)){
                    case 1:
                    	system("cls");
                    	stats();
                        kreska();
                        cout<<"|\n| Stebenia: Jedyna opcja to pokona� Wojmira,\n";
						cout<<"| a droga do jego zamku jest niebezpieczna\n|\n";
                        cout<<"| 1. Nie wa�ne jak ci�ka b�dzie droga, \n|    podejm� tego wyzwania \n";
                        cout<<"| 2. Chyba jednak si� rozmy�li�em..."<<endl;
                        kreska();
                        int odp4;
                        cin>>odp4;
                            switch (check(odp4,2)){
                                case 1:
                                	system("cls");
                                	stats();
                                    kreska();
                                    cout<<"|\n| Nasz bohaterze! Musz� powiedzie� o tym \n| wszystkim w wiosce! \n";
                                    pl_rep = pl_rep + 2;
                                    pass = 1;
                                    goto po_starcie;
                                case 2:
                                	system("cls");
                                	stats();
                                    kreska();
                                    cout<<"|\n| Stebenia: B�agam ci�, pom�z nam! Nasze plony\n";
									cout<<"|     	    zosta�y ca�kowicie zrabowane \n|\n";
                                    cout<<"| 1. No dobra, wespr� was, ale chce pieni�dze \n";
                                    cout<<"| 2. Niech b�dzie, pomog� \n";
                                    cout<<"| 3. Id� precz \n";
                                    kreska();
                                    int odp5;
                                    cin>>odp5;
									switch (check(odp5,3)){
                                        case 1:
                                        	money:
                                        	system("cls");
                                        	stats();
                                            kreska();
                                            cout<<"|\n| Stebenia: Mamy jedynie 30 z�otych... \n|\n";
                                            cout<<"| 1. Wy biedaki, nie pomoge wam \n";
                                            cout<<"| 2. Przyjm� datek i zrobi� co w mojej mocy \n";
                                            cout<<"| 3. Zostawcie pieni�dze, zrobi� to za darmo. \n";
                                            kreska();
                                            int odp6;
                                            cin>>odp6;
                                            switch (check(odp6,3)){
                                                case 1:
                                                	system("cls");
                                                	stats();
                                                    kreska();
                                                    cout<<"|\n| Stebenia: B�d� przekl�ty!\n";
                                                    ending = 1;
                                                    goto po_starcie;
                                                case 2:
                                                	system("cls");
                                                	stats();
                                                    kreska();
                                                    cout<<"| Stebenia: Wi�c te 30z� jest teraz twoje, liczymy na ciebie! \n";
                                                    pl_rep = pl_rep + 1;
                                                    pl_cash = pl_cash + 30;
                                                    pass = 1;
                                                    goto po_starcie;
                                                case 3:
                                                	system("cls");
                                                	stats();
                                                    kreska();
                                                    cout<<"| Stebenia: Naprawd�? Liczymy na ciebie dzielny wojaku! \n";
                                                    pl_rep = pl_rep + 2;
                                                    pass = 1;
                                                    goto po_starcie;
                                            }
                                        case 2:
                                        	system("cls");
                                        	stats();
                                            kreska();
                                            cout<<"| Stebenia: Ca�e szczescie! Musz� powiedzie� wszystkim w wiosce! \n";
                                            pl_rep = pl_rep + 2;
                                            pass = 1;
                                            goto po_starcie;
                                        case 3:
                                        	system("cls");
                                        	stats();
                                            kreska();
                                            cout<<"|\n| Stebenia: B�d� przekl�ty!\n";
                                            ending = 2;
                                            goto po_starcie;
									}
                            }      
                    case 2:
                    	system("cls");
                    	stats();
                        kreska();
                        cout<<"|\n| Stebenia: Sugerujesz �e jest co�\n|           wa�niejszego od zniszczenia\n|           Bielsanii? \n|\n";
                        cout<<"| 1. Tak, na przyk�ad ciekawsze gry \n";
                        cout<<"| 2. No, no nie. Jednak wam pomog� \n";
                        cout<<"| 3. Nie widz� w twoich r�kach sakiewki \n";
                        kreska();  
                        int odp7;
                        cin>>odp7;
                        switch (check(odp7,3)){
                            case 1:
                            	system("cls");
                            	stats();
                                kreska();
                                cout<<"| Stebenia: No to id� se pograj i wyginaj mi z wioski natychmiast \n";
                                ending = 4;
                                goto po_starcie;
                            case 2:
                            	system("cls");
                            	stats();
                                kreska();
                                cout<<"| Stebenia: To wspaniale! musz� powiedzie� o tym wszystkim!";
                                pl_rep = pl_rep + 2;
                                pass = 1;
                                goto po_starcie;
                            case 3:
                            	goto money;
                        }
                        
				}
        }
        case 2:
			system("cls"); 
			stats();
            kreska();
            cout<<"|\n| Stebenia: Wygl�dasz na s�abeusza, ale\n|           wys�uchaj mnie. Kr�l Wojmir od\n";
            cout<<"|           jakiego� czasu atakuje wioski w \n|           krainie i kradnie wszystko co mamy.\n|           Potrzebujemy pomocy \n|\n";
            cout<<"| 1. I dlaczego akurat ja mam temu podo�a�? \n";
            cout<<"| 2. Pieni�dze nie rosn� na drzewach \n";
            cout<<"| 3. Nie mam zamiaru sie miesza� w wasze \n|    ch�opskie zabawy \n";
            kreska();
            int odp10;
            cin>>odp10;
            switch (check(odp10,3)){
                case 1:
                	system("cls");
                	stats();
                    kreska();
                    cout<<"|\n| Stebenia: Poniewa� masz tyle odwagi,\n|           �eby go ubi� \n|\n";
                    cout<<"| 1. Dobra, wchodz� w to \n";
                    cout<<"| 2. We�cie se kogos innego\n";
                    kreska();
                    int odp11;
                    cin>>odp11;
                    switch (check(odp11,2)){
                        case 1:
                        	system("cls");
                        	stats();
                            kreska();
                            cout<<"| Stebenia: Dzi�kuj�, musz� powiedzie� o tym ca�ej wiosce! \n";
                            pl_rep = pl_rep + 2;
                            pass = 1;
                            goto po_starcie;
                        case 2:
                        	system("cls");
                        	stats();
                            kreska();
                            cout<<"|\n| Stebenia: Badz przeklety!\n";
                            ending = 1;
                            goto po_starcie;
                    }
                case 2:
					goto money;
                case 3:
                	system("cls");
                	stats();
                    kreska();
                    cout<<"| Stebenia: W takim razie panu dzi�kujemy \n";
                    ending = 2;
                    goto po_starcie;
            }
        case 3:
        	system("cls");
        	stats();
        	kreska();
        	cout<<"| Stebenia: Odejdz ode mnie zwyrolu \n|\n";
        	int stebenia = walka(1);
        	system("cls");
        	stats();
     		kreska();
        	switch (stebenia){
            	case 1:
					pl_cash = pl_cash + 30;
            		pass = 1;
            		cout<<"|\n| Stebenia: Niech ci� piorun strzeli! \n| Ukradziono 30$\n";
            		break;
   				case 2: 
					cout<<"|\n| Stebenia: Nawet ze mn� przegra�e�? XD wypad mi st�d\n";
					pass = 1;
					break;
				case 3:
					cout<<"|\n| Stebenia: Uciekasz? Masz ty rozum i godno��\n|           cz�owieka? XD\n";
					pass = 1;	
					break;
			}
            goto po_starcie;    
    }
    po_starcie:
        if (pass != 0){  //miejsce ktore konczy petle dialogu wstepnego gdy powiedzie sie on
        	cout<<"| \n";
            Sleep(2000);
            cout<<"| Historia zaczyna sie w�a�nie tutaj";
            for (int i=1; i<6; i++){
                Sleep(700);
                cout<<".";
            }
            system("cls"); 
    }  
}
int litynia(){
		system("pause");
		litynia:
		system("cls");
		stats();
		kreska();
		cout<<"|\n| Gdzie chcesz si� uda�?\n";
		cout<<"|\n| 1. Rozmawiaj z Bindarem\n";
		cout<<"| 2. Kantyna\n";
		cout<<"| 3. Wyjd� z Litynii\n";
		kreska();
		int lit;
		cin>>lit;
		switch (check(lit,3)){
			case 1:
			system("cls");
			stats();
			kreska();
			cout<<"|\n| Bindar: W czym mog� ci pom�c?\n";
			cout<<"|\n| 1. Kto mo�e mnie czego� nauczy�?\n";
			cout<<"| 2. Potrzebuj� pieni�dzy\n";
			cout<<"| 3. Jeszcze tu wr�c�..\n";
			kreska();
			int odp6;
			cin>>odp6;
			switch (check(odp6,3)){
				case 1:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Bindar: W kantynie spotkasz Zaj�s�awa\n";	
					cout<<"|         kt�ry pomo�e ci zwi�kszy� swoj� si��.\n";
					cout<<"|         On napewno ci pomo�e. Powodzenia!\n";
					kreska();
					system("pause");
					goto litynia;
				case 2:
					system("cls");
					if (pl_rep > 2){
						if (bindar_cash == 1){
							stats();
							kreska();	
							cout<<"|\n| Bindar: Ju� ci da�em pieni�dze.\n";	
							kreska();
							system("pause");
						} else {
							pl_cash = pl_cash + 50;
							bindar_cash = 1;
							stats();
							kreska();
							cout<<"|\n| Bindar: Mog� ci da� 50 z�otych\n";
							cout<<"|\n| Otrzymano 50 z�otych\n";
							kreska();	
							system("pause");
						}
					} else {	
						system("cls");
						stats();
						kreska();
						cout<<"|\n| Bindar: Nie ufam ci, udowodnij\n";
						cout<<"|         mi �e nie wydasz ich na piwo\n";
						cout<<"|\n| Brak ci reputacji\n";
						kreska();
						system("pause");
					}
					goto litynia;	
				case 3:
					goto litynia;	
					break;
			}
			case 2:
				kantyna:		
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Wchodzisz do kantyny Pod Drabin�\n";			
				cout<<"|\n| 1. Podejd� do lady\n";
				cout<<"| 2. Rozmawiaj z Zaj�s�awem\n";
				cout<<"| 3. Wyjd�\n";
				kreska();
				int odp7;
				cin>>odp7;
				switch (check(odp7,3)){
					case 1:
						system("cls");
						stats();
						kreska();
						cout<<"|\n| Michniard: Witaj nieznajomy! Co ci�\n";
						cout<<"|            do nas sprowadza?\n";
						michniart:
						cout<<"|\n| 1. O czym m�wi� ludzie?\n";
						cout<<"| 2. Napi�bym si� piwa (10$)\n";
						cout<<"| 3. Gdzie znajd� kowala?\n";
						cout<<"| 4. Wr�c� p�niej..\n";
						kreska();
						int odp8;
						cin>>odp8;
						switch (check(odp8,4)){
							case 1:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Michniard: Wiem wiele, ale nie widz�\n";
								cout<<"|            w twoich r�kach sakiewki\n";
								cout<<"|\n| 1. Kup info (20$)\n";
								cout<<"| 2. Odpuszcz� sobie...\n";
								kreska();
								int odp9;
								cin>>odp9;
								switch (check(odp9,2)){
									case 1:
										if (pl_cash > 20){
											if (michniard_tip == 0){
												system("cls");
												pl_cash = pl_cash - 20;
												stats();
												kreska();
								   	   	   		cout<<"|\n| Michniard: Kr�l Wojmir stacjonuje w\n";
											   	cout<<"|            centrum krainy Bielsanii,\n";
												cout<<"|            w Bielogrodzie\n";
											   	kreska();
											   	michniard_tip++;
											   	goto michniart;
											} else if (michniard_tip == 1){
												system("cls");
												pl_cash = pl_cash - 20;
												stats();
												kreska();
								   	   	   		cout<<"|\n| Michniard: Kr�l Wojmir jest podatny\n";
												cout<<"|            na obra�enia z w��czni,\n";
												cout<<"|            miedzianej. Sprzedaje tak� kowal\n";
												kreska();
												michniard_tip++;
											   	goto michniart;
											} else if (michniard_tip == 2){
												system("cls");
												pl_cash = pl_cash - 20;
												stats();
												kreska();
								   	   	   		cout<<"|\n| Michniard: Kr�l Wojmir nie spodziewa\n";
												cout<<"|            si� ataku z kuchni. Zakradnij\n";
												cout<<"|            si� i wykorzystaj chwil�!\n";
												kreska();
												michniard_tip++;
											   	goto michniart;
											} else if (michniard_tip == 3){
												system("cls");
												stats();
												kreska();
								   	   	   		cout<<"|\n| Michniard: Powiedzia�em ci ju� wszystko!\n";
												kreska();
											   	goto michniart;
											}
										} else {
											system("cls");
											stats();
											kreska();
								   	   	   	cout<<"|\n| Michniard: Nie mog� ci niczego\n";
											cout<<"|            powiedzie�, brak ci\n";
											cout<<"|            pieni�dzy. Wr�� p�niej\n";
											kreska();
											goto michniart;
										}
									case 2:
										system("cls");
										stats();
										kreska();
										cout<<"|\n| Michniard: Jak sobie chcesz!\n";
										goto michniart;
								}
							case 2:	
								system("cls");
								if (pl_cash > 10){
									pl_cash = pl_cash - 10;
									pl_hp = pl_hp + 8;
									stats();
									kreska();
								   	cout<<"|\n| Michniard: Zdrowie!\n";
									cout<<"|            W czym mog� pom�c?\n";
									goto michniart;
								} else {
									stats();
									kreska();
									cout<<"|\n| Michniard: Przykro mi, nie sta� ci�!\n";
									goto michniart;	
								}
							case 3:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Michniard: Kowal stacjonuje w\n";
								cout<<"|            Godziburgu. Ma bardzo tanie,\n";
								cout<<"|            trwa�e zbroje i miecze.\n";
								goto michniart;
							case 4:	
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Michniard: Do zobaczenia!\n";
								kreska();
								system("pause");
								goto kantyna;
						}
					case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Zaj�s�aw: Streszczaj si�, czego chcesz?\n";
					cout<<"|\n| 1. Chc� sta� si� silniejszym..\n";
					cout<<"| 2. Co ty mi bedziesz rozkazywa�\n";
					cout<<"| 3. Wr�c� tu jeszcze\n";
					kreska();
					int odp10;
					cin>>odp10;
					switch (check(odp10,3)){
						case 1:
							system("cls");
							stats();
							kreska();
							cout<<"|\n| Zaj�s�aw: I dlaczego s�dzisz �e ci pomog�?\n";
							zajas:
							cout<<"|\n| 1. Chce zat�uc kr�la, pomo�esz?\n";
							cout<<"| 2. <potrz��nij sakiewk� z pieni�dzmi>\n";
							cout<<"| 3. Chyba przywale ci w mord�\n";
							cout<<"| 4. Wr�c� tu p�niej\n";
							kreska();
							int odp11;
							cin>>odp11;
							switch (check(odp11,4)){
								case 1:
									if (wola_zajaslawa == 1){
										system("cls");
										pl_dmg = pl_dmg + 10;
										wola_zajaslawa = 0;
									   	stats();
									   	kreska();
										cout<<"|\n| Zaj�s�aw: Z dobrej woli tyle ci� naucz�.\n";
										cout<<"|           Je�li chcesz wi�cej sypnij z�otem\n";
										cout<<"|\n| Nauczono +10 DMG\n";
										kreska();
										goto zajas;
									} else {
									   	system("cls");
									   	stats();
									   	kreska();
									   	cout<<"|\n| Zaj�s�aw: Moja dobro� si� sko�czy�a,\n";
										cout<<"|           Chcesz umie�? To dawaj kas�\n"; 
										kreska();
										goto zajas;  	
									}
								case 2:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Zaj�s�aw: Widz� �e si� rozumiemy hehe\n";
									cout<<"|\n| 1. 10 DMG - 50$\n";
									cout<<"| 2. 5 DMG - 25$\n";
									cout<<"| 3. Kurde nie mam przy sobie z�ota\n";
									kreska();
									int odp12;
									cin>>odp12;
									switch (check(odp12,3)){
										case 1:
											system("cls");
											if (pl_cash >= 50){
												pl_dmg = pl_dmg + 10;
											   	pl_cash = pl_cash - 50;
									   		   	stats();
									   			kreska();
												cout<<"|\n| Zaj�s�aw: Jeste� teraz o wiele silniejszy\n";
											   	kreska();
												goto zajas;
											} else {
									   		   	stats();
									   		   	kreska();
												cout<<"|\n| Zaj�s�aw: Nie masz tyle z�ota\n";
												kreska();
												goto zajas;	
											}
										case 2:
											system("cls");
											if (pl_cash >= 25){
												pl_dmg = pl_dmg + 5;
											   	pl_cash = pl_cash - 25;
									   		   	stats();
									   			kreska();
												cout<<"|\n| Zaj�s�aw: Jeste� teraz silniejszy\n";
											   	kreska();
												goto zajas;
											} else {
									   		   	stats();
									   		   	kreska();
												cout<<"|\n| Zaj�s�aw: Nie masz tyle z�ota\n";
												kreska();
												goto zajas;	
											}
										case 3:
											system("cls");
											stats();
											kreska();
											goto zajas;	
									}
								case 3:
								zajas_war:	
								switch (walka(4)){
									case 1:
										system("cls");
										pl_cash = pl_cash + 400;
										stats();
										kreska();
										cout<<"|\n| Zaj�s�aw: Nie powiedzia�em ostatniego s�owa\n";
										cout<<"|\n| Ukradziono 400$\n";
										goto zajas;
									case 2:	
										system("cls");
										stats();
										kreska();
										wola_zajaslawa = 0;
										cout<<"|\n| Zaj�s�aw: Zniknij mi z oczu natychmiast.\n";
										goto zajas;
									case 3:
										system("cls");
										stats();
										kreska();
										cout<<"|\n| Zaj�s�aw: Ty tch�rzu!\n";
										goto zajas;
								}
								case 4:
									  goto kantyna;	
							}
						case 2:
							goto zajas_war;
						case 3:
							goto kantyna;
					}
					case 3:
						goto litynia;
				}
			case 3:	
				system("cls");
				ch1ptl:
	   	   	   	stats();
				kreska();
				cout<<"|\n| Dok�d chcesz si� uda�?\n";
				cout<<"|\n| 1. Litynia\n";
	   	   	   	cout<<"| 2. Odwied� Spordana\n";
	   	   	   	cout<<"| 3. Godziburg\n";
				kreska();
				int wander;
				cin>>wander;
				switch (check(wander,3)){
					case 1:
						goto litynia;
					case 2:
						system("cls");
						stats();
						kreska();
						cout<<"|\n";
						spordan();
						system("pause");
						system("cls");
						goto ch1ptl;
					case 3:
						system("cls");
						stats();
						kreska();
						break;
				}
		}
ch1end:;
			
}
void house(){
	system("cls");
	stats();
	kreska();
	srand(time(NULL));
	int money = rand() % 500 + 50;
	int rep = rand() % 3 + 0;
	cout<<"|\n| Do ukradni�cia: "<<money<<"$\n";
	cout<<"| Szansa na zwyci�stwo: "<<rand() % 100 + 1<<"%\n";
	cout<<"| Ujemna reputacja: -"<<rep<<" REP\n";
	kreska();
	cout<<"|\n";
	cout<<"|                __\n";
	cout<<"|               _||____\n";
	cout<<"|              / ||    \\\n";
	cout<<"|             /_________\\\n";
	cout<<"|             |  _   _  |\n";
	cout<<"|   O         | | | | | |\n";
	cout<<"|  /|\\        | /// | | |\n";
	cout<<"|  / \\        ===========\n";
	kreska();
	cout<<"|\n| 1. Kradnij\n";
	cout<<"| 2. Odpu�� sobie\n";
	kreska();
	int rob;
	cin>>rob;
	switch(check(rob,2)){
		case 1:
			switch(rand() % 2 + 0){
				case 0:
					system("cls");
					pl_cash = pl_cash + money;
					pl_rep = pl_rep - rep;
					stats();
					kreska();
					cout<<"|\n| Ukradiono pomy�lnie "<<money<<"$\n";
					cout<<"|\n| Utracono "<<rep<<" REP\n";
					kreska();
					break;
				case 1:
					system("cls");
					pl_rep = pl_rep - rep;
					stats();
					kreska();
					cout<<"|\n| Nie uda�o ci si� okra�� domu\n";
					cout<<"|\n| Utracono "<<rep<<" REP\n";
					kreska();
					break;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Nie uda�o ci si� okra�� domu\n";
					cout<<"| Ale uda�o ci si� uciec\n";
					cout<<"|\n| Utracono 0 REP\n";
					kreska();
					break;					
			}
			break;
		case 2:
			break;
	}
	system("pause");
}
void godziburg() {
	
	godziburg:
	system("cls");
	stats();
	kreska();
	cout<<"|\n| Gdzie chcesz si� uda�?\n";
	cout<<"|\n| 1. Kowal\n";
	cout<<"| 2. Ko�ci�\n";
	cout<<"| 3. Okradnij dom\n";
	cout<<"| 4. Wyjd�\n";
	kreska();
	int odp1;
	cin>>odp1;
	switch (check(odp1,4)){
		case 1:
			system("cls");
			stats();
			kreska();
			if (kowal == 0){
				kowal = 1;	
				cout<<"|\n| Wchodzisz do izby kowalskiej. �ar bucha ci\n";
				cout<<"| w twarz. Odzywa si� jeden z dw�ch kowali\n";
				cout<<"| stoj�cych nad rozgrzanym piecem\n";
				cout<<"|\n| Stefir: Dzie� niehandlowy, nie przyjmujemy\n";
				cout<<"|         nowych zam�wie�\n";
				cout<<"|\n| 1. Mo�e zrobicie wyj�tek dla wybawiciela?\n";
				cout<<"| 2. Kto� tutaj chyba chce dosta� w szcz�k�\n";
				cout<<"| 3. A-aha.. a kiedy mo�na przyj��?\n";
				kreska();
				int odp2;
				cin>>odp2;
				switch (check(odp2,3)){
					case 1:
						system("cls");
						stats();
						kreska();
						cout<<"|\n| Stefir odwraca si� na pi�cie i spogl�da\n";
						cout<<"| na ciebie z pogard�\n";
						cout<<"|\n| Stefir: Ty? haha! Od czego takie co�\n";
						cout<<"|         mo�e nas wybawi�?\n";
						cout<<"|\n| 1. Od najazd�w Wojmira\n";
						cout<<"| 2. Ciebie chyba delikatnie z�by sw�dz�\n";
						kreska();
						int odp3;
						cin>>odp3;
						switch (check(odp3,2)){
							case 1:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Stefir: Strasznie zaci�ty jeste� jak na\n";
								cout<<"|         niedzielnego �owc� zwierzyn\n";
								cout<<"|\n| 1. Kurdi balans b�dziesz komplikowa� czy\n";
								cout<<"|    pomo�esz?\n";
								cout<<"| 2. Masz z tym jaki� problem?\n";
								kreska();
								int odp4;
								cin>>odp4;
								switch (check(odp4,2)){
									case 1:
									stefir_szyderczy:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Stefir: Widz� �e dobrze wiesz czego chcesz\n";
									cout<<"|\n| W tej chwili odwr�ci� si� drugi kowal\n";
									cout<<"|\n| Kopbard: No prosz�, wygl�da na to �e mamy\n";
									cout<<"|          do czynienia z buntownikiem.\n";
									cout<<"|          Dlaczego s�dzisz �e ci si� uda?\n";
									cout<<"|\n| 1. Poniewa� wiem �e mi pomo�ecie\n";
									cout<<"| 2. Poniewa� wiem jak go przechytrzy�\n";
									cout<<"| 3. Bo tylko ja mog� po�wi�ci� �ycie za wolno�c\n";
									kreska();
									int odp5;
									cin>>odp5;
									switch (check(odp5,3)){
										case 1:
											system("cls");
											stats();
									   	   	kreska();
									   	   	cout<<"|\n| Stefir: Cholera sk�d ty wszystko wiesz.\n";
									   	   	cout<<"|         S�uchaj, masz o tym nikomu nie m�wi�\n";
									   	   	miecz:
									   	   	cout<<"|\n| Drugi kowal Kopbard podchodzi i chwyta\n| ci� za ramiona\n";
									   	   	cout<<"|\n| Kopbard: Je�li chcesz bro�, kt�r� napewno\n";
									   	   	cout<<"|          pokonasz Wojmira, musisz uda� si�\n";
									   	   	cout<<"|          na wypraw� do podziemnego miasta w\n";
									   	   	cout<<"|          kt�rym czas p�ynie wolniej. Mam na\n";
									   	   	cout<<"|          my�li Serweni�. Wej�cie do niej\n";
									   	   	cout<<"|          jest strze�one, a �rodek pe�en jest\n";
									   	   	cout<<"|          niebezpiecznych pu�apek, ale w\n";
						   	   				cout<<"|          grocie kt�ra podpisana b�dzie cyfr�\n";
						   	   				cout<<"|          211, odnajdziesz rud� miedzi dzi�ki\n";
											cout<<"|	   kt�rej wykuj� ci miecz lepszy od\n";
											cout<<"|          tego kt�ry ma Wojmir\n";
											cout<<"|\n| 1. Zdob�d� miedzian� rud�!\n";
											cout<<"| 2. Dacie mi jakie� wyposa�enie na\n";
											cout<<"|    t� wypraw�? Mog� zgin��.\n";
						   	   				kreska();
						   	   				int odp6;
						   	   				cin>>odp6;
						   	   				switch(check(odp6,2)){
											case 1:
												system("cls");
												pl_rep = pl_rep + 2;
												stats();
												kreska();
												cout<<"|\n| Stefir: Wspaniale! Ruszaj jak najszybciej\n";
												cout<<"|         kolejny konw�j Wojmira nied�ugo tu b�dzie!\n";
												kreska();
												cout<<"\n ";
												system("pause");
												system("cls");
												stats();
												kreska();
												goto godziburg;
											case 2:
												system("cls");
												stats();
												kreska();
												cout<<"|\n| Stefir: <westchn��> niech ci b�dzie.\n";
												if (pl_dmg >= 25){
													pl_kev = 3;
													pl_kev_health = 160;
													cout<<"|\n| Stefir: Jeste� do�� silny wi�c\n";
													cout<<"|         dostaniesz lepsz� zbroj�\n";
													kreska();
													system("pause");
												} else {
													pl_weap = 2;
													pl_dmg = pl_dmg + 10;
													cout<<"|\n| Stefir: Trzymaj ten miecz, nim\n";
													cout<<"|         pokonasz niemal ka�dego\n";
													kreska();
													system("pause");
												}
												system("cls");
												stats();
												kreska();
												goto godziburg;	  		  
											}
										case 2:
											system("cls");
											stats();
											kreska();
											cout<<"|\n| Stefir: Dobra zasadzka nie wystarczy\n";
											goto miecz;
										case 3:
											system("cls");
											stats();
											kreska();
											cout<<"|\n| Stefir: Ohoho no jaki z ciebie bohater hehe\n";
											goto miecz;
									}
									case 2:
										system("cls");
										stats();
										kreska();
										cout<<"|\n| Stefir: Dziwi mnie to �e tak ci zale�y\n";
										cout<<"|         na czyim� �yciu, r�wnie dobrze mo�esz\n";
										cout<<"|         okrada� domy razem z lud�mi kr�la\n";
										cout<<"|\n| 1. Musz� go pokona�!\n";
										cout<<"| 2. Serio? jak do niego do��czy�??\n";
										kreska();
										int odp7;
										cin>>odp7;
										switch (check(odp7,2)){
											case 1:
												system("cls");
												stats();
												kreska();
												goto miecz;
											case 2:
												woymir:
												system("cls");
												stats();
												kreska();
												cout<<"|\n| Stefir: Ty pijawko!\n";
												cout<<"|\n| Zosta�e� wygoniony\n";
												kreska();
												system("pause");
												system("cls");
												stats();
												kreska();
												goto godziburg;
										}
										break;
								}
							case 2:	
								kowal_walka:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Stefir: Ty sie dobrze czujesz? Jestem\n";
								cout<<"|         kowalem, jak ci przywale to ci�\n";
								cout<<"|         wywali na plantacj� betonu w\n";
								cout<<"|         Czechigrodzie\n";
								cout<<"|\n| 1. Zapomnijmy o sprawie, mo�ecie mi pom�c?\n";
								cout<<"| 2. Pracujesz tu tylko dlatego �eby m�c\n";
								cout<<"|    poca�owa� Wojmira w dup�!\n";
								kreska();
								int odp8;
								cin>>odp8;
								switch (check(odp8,2)){
									case 1:
										system("cls");
										stats();
										kreska();
										goto miecz;
									case 2:
										switch (walka(5)){
											case 1:
												system("cls");
												pl_cash = pl_cash + 600;
												stats();
												kreska();
												cout<<"|\n| Stefir: Nie doceni�em ci�\n";
												cout<<"|\n| Ukradziono 600$\n";
												kreska();
												system("pause");
												system("cls");
												stats();
												kreska();
												cout<<"|\n";
												goto godziburg;
											case 2:
												system("cls");
												stats();
												kreska();
												cout<<"|\n| Stefir: Jeszcze raz wpadniesz mi pod\n";
												cout<<"|         r�k� a rozwa�kuj� ci mord�\n";
												kreska();
												system("pause");
												system("cls");
												stats();
												kreska();
												goto godziburg;
											case 3:
												system("cls");
												stats();
												kreska();
												cout<<"|\n| Stefir: �ebym ci� tu wi�cej nie widzia�!\n";
												kreska();
												system("pause");
												system("cls");
												stats();
												kreska();
												goto godziburg;
										}
								}
						}
					case 2:
					goto kowal_walka;
					case 3:
						system("cls");
						stats();
						kreska();
						cout<<"|\n| Stefir: Nie jeste� ca�kiem bystry, co?\n";
						cout<<"|\n| 1. Mo�esz m�wi� wprost o co ci chodzi?\n";
						cout<<"| 2. Sugerujesz �e NIC NIE UMIEM?\n";
						cout<<"| 3. Skoro tutaj trafi�em to znaczy �e my�l�\n";
						kreska();
						int odp9;
						cin>>odp9;
						system("cls");
						stats();
						kreska();
						switch(check(odp9,3)){
							case 1:
								cout<<"|\n| Stefir: To tylko niepoznaka �eby\n";
								cout<<"|         ludzie Wojmira si� nas nie czepiali\n";
								cout<<"|\n| 1. A ja w�a�nie chce go pokona�!\n";
								cout<<"| 2. Jestem ciekaw co na to �o�nierze Wojmira\n";
								kreska();
								int odp10;
								cin>>odp10;
								system("cls");
								stats();
								kreska();
								switch (check(odp10,2)){
									case 1:
										goto stefir_szyderczy;
									case 2:
										goto woymir;
								}
							case 2:
								cout<<"|\n| Stefir: TAK!!\n";
								cout<<"|\n| 1. JA CI ZARA..!\n";
								cout<<"| 2. Spostrzegawczy jeste�.\n";
								kreska();
								int odp11;
								cin>>odp11;
								switch(check(odp11,2)){
									case 1:
										goto kowal_walka;
									case 2:
										system("cls");
										stats();
										kreska();
										cout<<"|\n| Stefir: Co nie zmienia faktu �e mo�esz\n";
										cout<<"|         nam si� przyda�\n";
										goto miecz;
								}
							case 3:
								cout<<"|\n| Stefir: To fakt, wytrzyma� w Bielsanii\n";
								cout<<"|         wi�cej ni� godzin� to ju� jazda bez\n";
								cout<<"|         trzymanki\n";
								cout<<"|\n| 1. Dlatego chc� wam pom�c i obali� kr�la\n";
								cout<<"| 2. Chyba przywal� ci w mord�\n";
								kreska();
								int odp12;
								cin>>odp12;
								switch(check(odp12,2)){
									case 1:
										goto stefir_szyderczy;
									case 2:
										goto kowal_walka;
								}
						}
				}
			} else {
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Stefir: Czego potrzeba?\n";
				coval:
				cout<<"| 1. Jeszcze tu wr�ci�\n";
				kreska();
				int odp13;
				cin>>odp13;
				switch(check(odp13,1)){
					case 1:
						system("cls");
						stats();
						kreska();
						goto godziburg;
				}
			}
		case 2:; //kosciol
			system("cls"); 
			stats();
			kreska();
			cout<<"|\n| Wchodzisz do ko�cio�a. Wyra�nie czu�\n";
			cout<<"| kadzid�o. Co chcesz zrobi�?\n";
			church:
			cout<<"|\n| 1. M�dl si�\n";
			cout<<"| 2. Rozmawiaj z kap�anem\n";
			cout<<"| 3. Wyjd�\n";
			kreska();
			int odp13;
			cin>>odp13;
			switch (check(odp13,3)){
				case 1:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Innos dzi�kuje ci za modlitw�\n";
					if (innos <= 2){
					innos++;
					pl_rep = pl_rep + 2;
					cout<<"|\n| Otrzymano +2 REP\n";
					}
					goto church;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Ks. Stanomir: �wiat�y w�drowcze\n";
					cout<<"|               b�d� pochwalony!\n";
					ksiadz:
					cout<<"|\n| 1. Mo�esz mnie pob�ogos�awi�?\n";
					cout<<"| 2. Gomez nie wiedzia� o zab�jstwie\n";
					cout<<"|    mag�w ognia\n";
					cout<<"| 3. Jeszcze tu wr�c�\n";
					kreska();
					int ks1;
					cin>>ks1;
					switch(check(ks1,3)){
						case 1:
							if (adanos == 2){
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Stanomir: Adanos ju� ci�\n";
								cout<<"|           nie blogos�awi! ��dasz\n";
								cout<<"|           zbyt wiele!\n";
								goto ksiadz;
							}
							if (pl_rep > 5){
								adanos++;
								system("cls");
								pl_hp = pl_hp + 30;
								stats();
								kreska();
								cout<<"|\n| Stanomir: B�ogos�awi� ci� w\n";
								cout<<"|           imieniu Adanosa\n";
								goto ksiadz;
								
							} else {
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Stanomir: Przykro mi ale\n";
								cout<<"|           nie ufam ci.\n";
								cout<<"|\n| Masz za ma�o reputacji\n";
								goto ksiadz;
							}
						case 2:
							system("cls");
							stats();
							kreska();
							cout<<"|\n| Stanomir: WIEDZIA� TYLKO\n";
							cout<<"|           STARY OB�Z WSZYSTKO\n";
							cout<<"|           TUSZUJE!\n";
							goto ksiadz;
						case 3:
							system("cls");
							stats();
							kreska();
							cout<<"|\n| Stanomir: Oby� wr�ci� ca�y\n";
							cout<<"|           i zdrowy.\n";
							goto godziburg;
						
					}
				case 3:
					system("cls");
					stats();
					kreska();
					goto godziburg;
				
			}
		case 3://kradziez domu
		   	house();
			goto godziburg; 			
		case 4:  //wyjscie
			system("cls"); 
			stats();
			kreska();
			godziburg_rozstaj:
	   	   	cout<<"|\n| Dok�d chcesz si� uda�?\n";
			cout<<"|\n| 1. Litynia\n";
	   	   	cout<<"| 2. Serwenia/Bielenia\n";
	   	   	cout<<"| 3. Godziburg\n";
	   	   	kreska();
			int wander;
			cin>>wander;
			switch (check(wander,3)){
				case 1:
					litynia();
					break;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Rozpocznie si� kolejny rozdzia�,\n";
					cout<<"| nie b�dzie mo�liwo�ci �atwego powrotu\n";
					cout<<"|\n| 1. Zrozumia�em\n";
					cout<<"| 2. Nie zrozumia�em\n";
					int alert;
					cin>>alert;
					switch (check(alert,2)){
						case 1:
							break;
						case 2:	
							system("cls");
							stats();
							kreska();
							goto godziburg_rozstaj;
					}
					ch2 = 1;
					break;
				case 3:	
					goto godziburg;	
			}
	}
}
void chapter1(){		//rozdzial 1
	tytul();
	cout<<"\n|    ROZDZIAL 1: W DRODZE DO LITYNII \n";
	kreska();
	cout<<"\n  ";
	system("pause");
	system("cls");
	stats();
	kreska();
	cout<<"|\n| Przemierzasz drog� z Czechigrodu do Litynii\n|\n";
	cout<<"| Spotka�e� handlarza\n|\n";
	spordan();
	Sleep(3000);
	system("cls");
	stats();
	kreska();
	cout<<"|\n| Docierasz do Litynii. Wioska jest pogr��ona\n";
	cout<<"| w chaosie. W bramie spotykasz Bindara\n";
	cout<<"|\n| Bindar: Ach moje ramie!\n";
	cout<<"|\n| 1. Cholera cz�owieku co ty narobi�e�?\n";
	cout<<"| 2. Nie przejmuj si� r�k�, najwy�ej\n";
	cout<<"|    zrobimy now� z drewna\n";
	kreska();
	int odp1;
	cin>>odp1;
	switch (check(odp1,2)){
		case 1:
			system("cls");
			stats();
			kreska();
			cout<<"|\n| Bindar: Chcia�em z�apa� chocia�by jednego\n";
			cout<<"|         z tych skurczybyk�w Wojmira ale on\n";
			cout<<"|         wyj�� miecz szybciej i mnie obi�\n";
			cout<<"|\n| 1. <pom� zabanda�owa� ran�>\n";
			cout<<"| 2. Jakim kalek� trzeba by� �eby\n|    przegra� z jakim� pionkiem kr�la?\n";
			kreska();
			int odp2;
			cin>>odp2;
			switch (check(odp2,2)){
				case 1:
					bandaz:
					system("cls");
					pl_rep = pl_rep + 1;
					stats();
					kreska();
					cout<<"|\n| Bindar: Oh dzi�kuj� ci... Nast�pnym razem\n";
					cout<<"|         pozabijam ich wszystkich moim\n";
					cout<<"|         bagnetem francuskim\n";
					cout<<"|\n| 1. Nie szalej, prawie sie wykrwawi�e�\n";
					cout<<"| 2. Mo�esz mi pom�c w wyprawie na\n|    kr�la Wojmira?\n";
					cout<<"| 3. Drzewo podwa�a mur korzeniami\n";
					kreska();
					int odp3;
					cin>>odp3;
					switch (check(odp3,3)){
						case 1:
							system("cls");
							stats();
							kreska();
							cout<<"|\n| Bindar: Mn� si� nie przejmuj. Co tu robisz?\n";
							cout<<"|\n| 1. Id� zabi� Kr�la\n";
							cout<<"| 2. Zbieram maliny\n";
							cout<<"| 3. Przysy�a mnie siara, mam odebra� \n|    ostatni� rat�\n";
							kreska();
							int odp4;
							cin>>odp4;
							switch(check(odp4,3)){
								case 1:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Bindar: Cholera niez�y jeste�. Je�li chcesz\n";
									cout<<"|         zwi�kszy� swoj� si��, udaj si� do\n";
									cout<<"|         Zaj�s�awa. Siedzi w kantynie.\n";
									cout<<"|         Powodzenia!\n";
									kreska();
									goto litynia;
								case 2:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Bindar: Maliny czy ostr�yny?\n";
									cout<<"|\n| 1. Maliny.\n";
									cout<<"| 2. Ostr�yny.\n";
									kreska();
									int picture;
									cin>>picture;
									switch (check(picture,2)){
										case 1:
											system("cls");
											pl_hp = 1;
											stats();
											kreska();
											cout<<"|\n| Bindar: ZGINIESZ\n";
											cout<<"|\n| Bindar: Jeszcze raz powiesz komu� takie bzdury \n";
											cout<<"|        a ci� osobi�cie powiesz�\n";
											kreska();
											goto litynia;
										case 2:
											system("cls");
											stats();
											kreska();
											cout<<"|\n| Bindar: Wi�c trzymaj. Czuj\n";
											cout<<"|         si� u nas jak u siebie!\n|\n| Otrzymano koszyk ostr�yn\n";
											kreska();
											pl_food = pl_food + 1;
											goto litynia;										
									}
								case 3:
									system("cls");
									pl_cash = pl_cash + 50;
									stats();
									kreska();
									cout<<"|\n| Bindar: n-nie chcia�em niepokoi� Pana\n|         Siarzewskiego, prosz�...\n";
									cout<<"|\n| Otrzymano 50$\n";
									kreska();		
									goto litynia;							
							}
						case 2:
							system("cls");
							stats();
							kreska();
							cout<<"|\n| Bindar: C�, ja wiele nie mog� ci da�\n";
							cout<<"|         ale w kantynie spotkasz Zaj�s�awa\n";	
							cout<<"|         kt�ry pomo�e ci zwi�kszy� swoj� si��.\n";
							cout<<"|         On napewno ci pomo�e. Powodzenia!\n";
							kreska();
							goto litynia;
						case 3:
							system("cls");
							stats();
							kreska();	
							cout<<"|\n| Bindar: Wyja�ni�bym ci co� ale s�siedzi.\n";
							cout<<"|         Bierz te 2 kebaby i id� w swoj� strone\n";
							pl_food = pl_food + 2;
							kreska();
							goto litynia;
					}
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Bindar: Ten kaleka mo�e ci zaraz\n";
					cout<<"|         wybi� wszystkie z�by\n";
					cout<<"|\n| 1. Spokojnie, poka� mi t� r�k�\n";
					cout<<"| 2. Tak? To zobaczymy kto straci z�by\n";
					kreska();
					int odp5;
					cin>>odp5;
					switch (check(odp5,2)){
						case 1:
							goto bandaz;
						case 2:
							bindar_war:
							switch (walka(3)){
								case 1: 
									system("cls");
									pl_cash = pl_cash + 50;
									pl_food = pl_food + 2;
									stats();
									kreska();
									cout<<"|\n| Bindar: Zapami�tam sobie twoj�\n";
									cout<<"|         bu�k� cwaniaku...\n";
									cout<<"|\n| Ukradziono 50$\n";
									cout<<"| Otrzymano: 2 koszyki ostr�yn\n";
									kreska();
									goto litynia;
								case 2:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Bindar: Nigdy wi�cej tego\n";
									cout<<"|         nie pr�buj.\n";
									kreska();
									goto litynia;
								case 3:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Bindar: Jeszcze cie dorw�!\n";
									kreska();
									goto litynia;	
							}
					}
			}		
			case 2:
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Bindar: Chcesz dosta� w szcz�k�?\n";
				cout<<"|\n| 1. Nie.. <pom� opatrzy� ran�>\n";
				cout<<"| 2. Poka� mi na co ci� sta�\n";
				kreska();
				int odp6;
				cin>>odp6;
				switch (check(odp6,2)){
					case 1:
						goto bandaz;
						break;
					case 2:
						goto bindar_war;
						break;
				}
	}		
	litynia:
	litynia();
					
}
void chapter2 (){
	system("cls");
	tytul();
	cout<<"\n|   ROZDZIA� 2: GODZIBURG - W STRON� KR�LA \n";
	kreska();
	cout<<"\n  ";
	system("pause");
	system("cls");
	stats();
	kreska();
	cout<<"|\n| Docierasz do Godziburga. Osada s�ynie\n";
	cout<<"| z wysokiej przest�pczo�ci, poniewa�\n";
	cout<<"| w wysokim tempie kwitnie tu przemys�\n";
	kreska();
	system("pause");
	do {
	system("cls");
	stats();
	kreska();	
	godziburg();
	} while (ch2 == 0);
}
void chapter3(){
	
	int helfen = 0; //zmienna okresla czy kubis�awa i lesniomir pomoga nam w serwenii
	int grota21 = 0; //okresla czy user byl juz w tej grocie
	int grota211 = 0; //okresla czy user byl juz w tej grocie
	int grota213 = 0; //okresla czy user byl juz w tej grocie
	int ruda211 = 0; //okresla czy wykopano rude w grocie 211
	int ruda213 = 0;//okresla czy wykopano rude w grocie 213
	
	system("cls");
	tytul();
	kreska();
	cout<<"\n|  ROZDZIA� 3: DO MISTYCZNEJ KRAINY SERWENII  \n";
	kreska();
	system("pause");
	system("cls");
	stats();
	kreska();
	rozstaj:
	cout<<"|\n| 1. Bielogr�d\n";
	cout<<"| 2. Serwenia\n";
	cout<<"| 3. Zobacz map�\n";
	kreska();
	int odp1;
	cin>>odp1;
	switch (check(odp1,3)){
		case 1:
			system("cls");
			stats();
			kreska();
			cout<<"|\n| To zbyt niebezpieczne,\n";
			cout<<"| masz za s�aby sprz�t.\n";
			goto rozstaj;
		case 2:
			system("cls");
			stats();
			kreska();
			cout<<"|\n| Docierasz do wr�t podziemnej\n";
			cout<<"| osady. Zatrzymuje ci� Le�niomir z Kubis�aw�\n";
			cout<<"|\n| Le�niomir: O ch�opie ty si� dobrze czujesz?\n";
			cout<<"|\n| 1. Spokojnie, wiem co mnie czeka\n";
			cout<<"| 2. O czym ty do mnie govorisz?\n";
			kreska();
			int odp2;
			cin>>odp2;
			switch (check(odp2,2)){
				case 1:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Le�niomir: Nie wiesz! Za bram�\n";
					cout<<"|            dzieje si� istne piek�o!\n";
					cout<<"|\n| 1. Rozja�nisz?\n";
					cout<<"| 2. Nie interesuje mnie to, wchodz�\n";
					kreska();
					int odp3;
					cin>>odp3;
					switch (check(odp3,2)){
						case 1:
							kubislawa:
							system("cls");
							stats();
							kreska();
							cout<<"|\n| Kubis�awa: Stoimy na stra�y tych wr�t\n";
							cout<<"|            poniewa� od 2 tygodni nie\n";
							cout<<"|            wr�ci�a stamt�d pewna mieszczanka \n";
							cout<<"|            wi�c nie mo�emy pozwoli� �eby\n";
							cout<<"|            ludzie gin�li w niewyja�nionych\n";
							cout<<"|            okoliczno�ciach.\n";
							cout<<"|\n| 1. Co mog�o j� zabi�?\n";
							cout<<"| 2. Nic sie nie b�j to jest przeb�j\n";
							kreska();
							int odp4;
							cin>>odp4;
							switch (check(odp4,2)){
								case 1:
									system("cls");
									stats();
									kreska();
									cout<<"|\n| Le�niomir: Wedle poda�, Serwenia\n";
									cout<<"|            opanowana jest przez stworzenia\n";
									cout<<"|            kt�re skr�caj� sobie cia�a z \n";
									cout<<"|            miedzi kt�ra ro�nie w tutejszych\n";
									cout<<"|            jaskiniach. To bardzo wymagaj�cy\n";
									cout<<"|            wrogowie, nie ka�dy da se z nimi rad�\n";
									cout<<"|\n| 1. Pomogliby�cie mi?\n";
									cout<<"| 2. Wystarczy, wchodz�\n";
									kreska();
									int odp5;
									cin>>odp5;
									switch (check(odp5,2)){
										case 1:
											system("cls");
											stats();
											kreska();
											cout<<"|\n| Oboje spojrzeli na siebie i kiwn�li\n";
											cout<<"|\n| Kubis�awa: Wi�c chod�my!\n";
											kreska();
											cout<<"\n  ";
											helfen = 1;
											goto serwenia;
										case 2:
											samozwaniec:
											system("cls");
											stats();
											kreska();
											cout<<"|\n| Le�niomir: �ycz� mi�ej �mierci!\n";
											kreska();
											cout<<"\n  ";
											goto serwenia;
									}
								case 2:
									goto samozwaniec;
							}
						case 2:
							goto samozwaniec;
					}
				case 2:	
					goto kubislawa;
			}
		case 3:
			if (pl_map == 0){
				system("cls");
				stats();
				kreska();
				cout<<"| Nie masz mapy!\n";
				goto rozstaj;
			} else {
				system("cls");
				stats();
				mapa();
				goto rozstaj;
			}
	}
	serwenia:
	system("pause");
	system("cls");
	cout<<"\n   ";
	Sleep(700);
	cout<<"c ";
	Sleep(700);
	cout<<"i ";
	Sleep(700);
	cout<<"s ";
	Sleep(700);
	cout<<"z ";
	Sleep(700);
	cout<<"a ";
	Sleep(700);
	cout<<". ";
	Sleep(700);
	cout<<". ";
	Sleep(700);
	cout<<". ";
	Sleep(2000);
	system("cls");
	cout<<"\n  Serwenia to niesamowite miejsce, pe�ne\n";
	cout<<"  grot, ciszy oraz";
	Sleep(2000);
	cout<<"...";
	Sleep(2000);
	cout<<" miedzi";
	Sleep(2000);
	cout<<"...";
	Sleep(2000);
	system("cls");
	stats();
	kreska();
	if (helfen == 1){
	   	cout<<"|\n| Trafiacie na rozstaj\n";
	   	cout<<"|\n| Kubis�awa: My przeszukamy grot� 21,\n|          wygl�da podejrzanie\n";
	} else {
		cout<<"|\n| Trafiasz na rozstaj\n";
	}	
	rozjazd:
	cout<<"|\n| 1. W stron� groty 211\n";
	cout<<"| 2. W stron� groty 21\n";
	cout<<"| 3. W stron� groty 213\n";
	cout<<"| 4. Wyjd�\n";
	kreska();
	int serw1;
	cin>>serw1;
	switch (check(serw1,4)){
		case 1:
			if (ruda211 == 1){
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Ju� przeszuka�e� ten rejon!";
				goto rozjazd;
			}
			if (grota211 == 1){
				goto grot211;
			}
			grota211 = 1;
			system("cls");
			Sleep(2000);
			cout<<"\n  powoli idziesz w kierunku groty 211\n";
			Sleep(4000);
			system("cls");
			Sleep(1200);
			cout<<"\n  A N I";
			Sleep(700);
			cout<<"   K R O K U";
			Sleep(700);
			cout<<"   D A L E J\n\n";
			Sleep(1200);
			cout<<" 1. ...\n";
			cin>>serw1;
			system("cls");
			Sleep(1000);
			cout<<"tup.";
			Sleep(1000);
			system("cls");
			Sleep(1000);
			cout<<"tup.";
			Sleep(1000);
			system("cls");
			Sleep(1000);
			cout<<"tup.";
			Sleep(1000);
			system("cls");
			cout<<"\n oj arturze... czeg� mo�esz szkua� w takim miejscu?\n";
			Sleep(4000);
			cout<<"\n  z mroku wyjawia si� ludzka sylwetka\n";
			Sleep(2000);
			cout<<"\n chyba nie s�dzi�e� �e p�jdzie tak �atwo?\n";
			Sleep(2000);
			cout<<"\n  zaczynasz rozpoznawa� jego rysy twarzy, to cz�owiek\n";
			Sleep(2000);
			cout<<"\n 1. Gadzimy�le...\n";
			cin>>serw1;
			system("cls");
			cout<<"\n Gadzimys�: Pami�� jeszcze pracuje, jaka szkoda\n";
			cout<<"            �e na niewiele ci si� ju� zda\n\n";
			cout<<" 1. <zainicjuj gard�>\n";
			cin>>serw1;
			switch (walka(6)){
				case 1:
					system("cls");
					cout<<" Gadzimys�: Ogl�daj si� za plecy...\n";
					Sleep(4000);
					system("cls");
					stats();
					kreska();
					goto grot211;
				case 2:
					if (helfen == 1){
						system("cls");
						cout<<"\n  Na miejsce przybieg� Le�niomir\n";
						cout<<"  i dobi� Gadzimys�a\n";
						cout<<"\n Le�niomir: Cz�owieku uwa�aj bardziej!\n";	
						system("pause");
						goto grot211;
					} else {
						lachudra:
						system("cls");
						cout<<"\n Gadzimys�: i ty chcesz pokona� Wojmira?\n";
						cout<<"            haha! ty �achudro!\n";
						cout<<"\n  1. <zaufaj mi>\n";
						cin>>serw1;
						system("cls");
						Sleep(1000);
						cout<<"\n  cofasz si� ";
						Sleep(700);
						cout<<"i bierzesz rozp�d ";
						Sleep(2000);
						system("cls");
						cout<<" ~AAAA!";
						Sleep(1000);
						cout<<"\n\n oboje upadacie";
						Sleep(1000);
						cout<<", zauwa�asz ka�u�� krwi";
						Sleep(2000);
						cout<<"\n\n Gadzimys�: ty....";
						Sleep(2000);
						cout<<"\n\n umar�.";
						Sleep(2000);
						system("cls");
						cout<<"\n Podnosisz si� i zmierzasz ku grocie 211";
						Sleep(3000);
						system("cls");
						switch (walka(7)){
							case 1:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Docierasz do groty 211, po\n";
								cout<<"| lewej stronie �wieci si� ruda,\n";
								cout<<"| na wprost za� stoi biurko\n";
								grot211:
								cout<<"|\n| 1. Id� po rud�\n";
								cout<<"| 2. Id� do biurka\n";
								cout<<"| 3. Wracaj na rozstaj\n";
								kreska();
								int serw2;
								cin>>serw2;
								switch (check(serw2,3)){
									case 1:
										if (ruda211 == 1){
											system("cls");
											stats();
											kreska();
											cout<<"|\n| Ju� wykopa�e� t� rud�!\n";
											goto grot211;
										}
										system("cls");
										stats();
										kreska();
										ruda211 = 1;
										cout<<"|\n| Uda�o ci si� wykopa� rud�\n";
										goto grot211;
									case 2:
										system("cls");
										stats();
										kreska();
										cout<<"|\n| Przy biurku siedz� Wronis�aw i Biergar\n";
										cout<<"| Graj� w szachy\n";
										cout<<"|\n| 1. Tam ch�op mnie prawie rozwa�kowa�\n";
										cout<<"|    a wy se w szachy gracie?\n";
										cout<<"| 2. Mog� si� do��czy�?\n";
										kreska();
										int serw4;
										cin>>serw4;
										switch(check(serw4,2)){
											case 1:
												system("cls");
												stats();
												kreska();
												cout<<"|\n| Wronis�aw u�miech�� sie i powiedzia�:\n";
												cout<<"|\n| Jak nasz wybawca m�g�by zgin�� w drodze tutaj\n";
												cout<<"| Arturze, jeste�my wi�niami tej krainy.\n";
												cout<<"| Nigdy jej nie opu�cimy dlatego prosz�,\n";
												cout<<"| Zr�b wszystko �eby uwolni� Bielsani�\n";
												kreska();
												system("pause");
												system("cls");
												stats();
												kreska();
												goto grot211;
											case 2:
												system("cls");
												stats();
												kreska();
												cout<<"|\n| Biergar: Nie, nie dlatego �e jeste� s�aby\n";
												cout<<"|          ale twoim zadaniem jest nas ocali�.\n";
												cout<<"|          A teraz id� i ocal krain�!\n";
												kreska();
												system("pause");
												system("cls");
												stats();
												kreska();
												goto grot211;
										}
										case 3:
											goto rozjazd;
								}
							case 2:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Potw�r przewr�ci� sie i umar�\n";
								goto grot211;
							case 3:
								system("cls");
								stats();
								kreska();
								cout<<"|\n| Potw�r wystraszy� si� ciebie gdy\n";
								cout<<"| ucieka�e� i sam uciek�\n";
								goto grot211;
						}
					}
					break;
				case 3:
					goto lachudra;
			}
		case 2:;
			if (helfen == 1){
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Kubis�awa: My tam idziemy, nie \n|            musisz nam pomaga�!\n";
				goto rozjazd;
			} else {
				system("cls");
				cout<<"\n Grota wydaje si� pusta. Zawracasz...\n\n  ";
				system("pause");
				switch (walka(7)){
					case 1:
						system("cls");
						stats();
						kreska();
						goto rozjazd;
					case 2:
						system("cls");
						stats();
						kreska();
						cout<<"|\n| Da�e� si� pobi� potworowi...\n";
						goto rozjazd;
					case 3:
						system("cls");
						stats();
						kreska();
						goto rozjazd;
				}
			}
		case 3:
			if (ruda213 == 1){
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Ju� przeszuka�e� ten rejon!";
				goto rozjazd;
			}
			grota213 = 1;
			system("cls");
			Sleep(2000);
			cout<<"\n  <kaszel>";
			Sleep(1000);
			system("cls");
			cout<<"\n  c-cz�owiek..?";
			Sleep(1000);
			system("cls");
			cout<<"\n  naprawd� kto� mnie znalaz�?";
			Sleep(2000);
			cout<<"\n\n jaka� kobieta le�y pod grot�";
			Sleep(2000);
			cout<<"\n\n obok niej le�y miecz i zw�j";
			Sleep(3000);
			system("cls");
			Sleep(1000);
			cout<<"\n to �migienia.";
			Sleep(2000);
			cout<<"\n podbiegasz do niej\n";
			cout<<"\n 1. co ci si� sta�o?\n";
			cin>>serw1;
			system("cls");
			cout<<"\n �migienia: planowa�am powstrzyma� Wojmira\n";
			cout<<"            przed obj�ciem tronu, dlatego wyruszy�am\n";
			cout<<"            w stron� groty 213 poniewa� jest tam";
			Sleep(6000);
			cout<<".";
			Sleep(1000);
			cout<<".";
			Sleep(1000);
			cout<<".";
			Sleep(1000);
			system("cls");
			cout<<"\n ...";
			Sleep(3000);
			cout<<"\n �migienia osun곹 si� na ziemi�.\n";
			Sleep(3000);
			cout<<"\n 1. Podnie� zw�j\n";
			cin>>serw1;
			system("cls");
			kreska();
			cout<<"\n        LEGENDA O SKR�TKOWYM KSI�CIU\n\n";
			cout<<"\n| Dawno dawno temu �y� sobie w Bielsanii\n";
			cout<<"| Skr�tkowy Ksi��e kt�ry kocha� swoich ludzi\n";
			cout<<"| a oni kochali jego. Lecz pewnego dnia\n";
			cout<<"| Margniew bardzo si� zdenerwowa� na to,\n";
			cout<<"| jak wszystko dzia�a w idealnej harmonii.\n";
			cout<<"| Postanowi� on podst�pem zabi� ksi�cia tak,\n";
			cout<<"| aby to on zosta� w�adc�, i �eby m�g�\n";
			cout<<"| wprowadzi� chaos w ca�ej krainie. Ale\n";
			cout<<"| Skr�tkowy Ksi��e obawia� si�, �e pewnego\n";
			cout<<"| dnia, kto� zbuntuje si� przeciwko �adowi,\n";
			cout<<"| dlatego uprosi� najlepszego maga w ca�ej\n";
			cout<<"| krainie, niejakiego Parchewita, by ten\n";
			cout<<"| zostawi� cz�� swej mocy dla cz�owieka\n";
			cout<<"| kt�ry b�dzie chcia� uratowa� krain� przed\n";
			cout<<"| z�em, kt�re kiedy� nadejdzie. Tak oto\n";
			cout<<"| powsta�a miedziana ruda, kt�r� postanowlil\n";
			cout<<"| ulokowa� w jaskini, w kt�rej wszystko \n";
			cout<<"| wygl�da jak miedziana ruda. Jedynie \n";
			cout<<"| wyzwoliciel, osoba,kt�ra ma serce czyste,\n";
			cout<<"| i wiedz� ca�ego �wiata jest w stanie \n";
			cout<<"| prawdziwie znale�� magiczn� rud�. Ten kto\n";
			cout<<"| posiadnie obie rudy i przekuje je na miecz\n";
			cout<<"| i zbroj�, mo�e powstrzyma� z�o na wieki.\n";
			kreska();
			cout<<"\n ";
			system("pause");
			system("cls");
			cout<<"\n W�drujesz dalej wg��b jaskini\n";
			Sleep(3000);
			system("cls");
			switch (walka(7)){
				case 1:
					system("cls");
					stats();
					kreska();
					grot213:
					cout<<"|\n| Docierasz do Groty 213. Na wprost\n";
					cout<<"| widzisz �wiec�c� si� rud� miedzi\n";
					cout<<"| 1. Wykop j�\n";
					kreska();
					int serw3;
					cin>>serw3;
					system("cls");
					stats();
					kreska();
					ruda213 = 1;
					cout<<"|\n| Zdobywasz: Magiczna ruda miedzi\n";
					kreska();
					system("pause");
					system("cls");
					stats();
					kreska();
					goto rozjazd;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Potw�r przewr�ci� si� i umar�\n";
					goto grot213;
				case 3:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Potw�r przestraszy� sie uciekaj�cego\n";
					cout<<"| ciebie i sam uciek�\n";
					goto grot213;
			}
		case 4:
			if (ruda211 == 0 || ruda213 == 0){
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Nie mo�esz opu�ci� Serwenii dop�ki nie\n";
				cout<<"| zdob�dziesz dw�ch rud miedzi\n";
				goto rozjazd;
			}	
	}
}
void chapter4() {
	system("cls");
	tytul();
	kreska();
	cout<<"|\n|             ROZDZIA� 4: FINA�\n";
	kreska();
	cout<<"\n ";
	system("pause");
	system("cls");
	stats();
	kreska();
	cout<<"|\n| Przy wyj�ciu z Serwenii spotykasz \n| Kubis�aw� i Le�niomira\n";
	cout<<"|\n| Kubis�awa: Ca�kiem nie�le ci posz�o! Teraz\n";
	cout<<"| bierz te rudy i le�my do kowala w Godziburgu!\n";
	kreska();
	cout<<"\n ";
	system("pause");
	system("cls");
	stats();
	kreska();
	cout<<"|\n| Kubis�awa wraz z Le�niomirem przetransportowali\n";
	cout<<"| ci� do Godziburga, prosto do kowala\n";
	cout<<"|\n| Stefir: Niesamowite! Zdoby�e� a� dwie??\n";
	cout<<"|\n| 1. Znalaz�em te� Gadzimys�a i �migieni�...\n";
	cout<<"| 2. Dobra nie gadaj tylko r�b ten miecz i zbroj�\n";
	kreska();
	int odp1;
	cin>>odp1;
	switch (check(odp1,2)){
		case 1:
			system("cls");
			stats();
			kreska();
			cout<<"|\n| Stefir: Gadzimys� zosta� porwany\n";
			cout<<"|         i przeszkolony do bycia po stronie\n";
			cout<<"|         kr�la. Szkoda �e tak sko�czy�, ale\n";
			cout<<"|         co ze �migieni�?\n";
			cout<<"|\n| 1. Nie �yje...\n";
			cout<<"| 2. Zosta�a uwi�ziona\n";
			kreska();
			int odp4;
			cin>>odp4;
			switch(check(odp4,2)){
				case 1:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Niech Innos ma j� w swojej opiece...\n";
					kreska();
					Sleep(4000);
					goto robienie_miecza;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Obawiam si� �e jej ju� nie uratujemy...\n";
					kreska();
					Sleep(4000);
					goto robienie_miecza;
			}
		case 2:	
			robienie_miecza:
			system("cls");
			pl_dmg = pl_dmg + 100;
			pl_kev = 5;
			pl_kev_health = 500;
			stats();
			kreska();
			cout<<"|\n| Kopbard: Daj mi t� mied�.\n";
			cout<<"|\n| Po sali roznosi� si� zapach\n";
			cout<<"| gor�cego metalu i spalonych przewod�w\n";
			cout<<"|\n| Kopbard: Uda�o si�!\n";
			cout<<"|\n| Otrzymujesz: Miedziany Rozpo�awiacz\n";
			cout<<"| Otrzymujesz: Miedziana zbroja skr�tkowca\n";
			cout<<"|\n| 1. Dzi�kuj�! <wyjd�>\n";
			cout<<"| 2. Ciekawe czy teraz m�g�bym obrabowa� wiosk�\n";
			kreska();
			int odp2;
			cin>>odp2;
			switch (check(odp2,2)){
				case 1:
					system("cls");
					stats();
					kreska();
					eksit:
					cout<<"|\n| Wychodz�c za rami� chwyta ci� Kubis�awa\n";
					cout<<"|\n| Kubis�awa: Nie p�jdziesz sam.\n";
					cout<<"|\n| Przed kowalem stan�li: Stebenia, Spordan\n";
					cout<<"| Michniard, Zaj�s�aw, Bindar i ks. Stanomir\n";
					cout<<"|\n| Kubis�awa: Zrobimy to razem\n";
					cout<<"| 1. Wi�c zr�bmy dym w Bielogrodzie!\n";
					kreska();
					int odp3;
					cin>>odp3;
					goto bielogrod;
				case 2:
					system("cls");
					stats();
					kreska();
					cout<<"|\n| Stefir: Tylko spr�buj a znikniesz na zawsze\n";
					goto eksit;
			}
	}
	bielogrod:
		system("cls");
		tytul();
		kreska();
		cout<<"\n|           DYM W BIELOGRODZIE\n";
		kreska();
		cout<<"\n ";
		system("pause");
		system("cls");
		stats();
		kreska();
		cout<<"|\n| Docieraj�c do Bielogrodu musicie\n| powstrzyma� stra�nik�w.\n";
		cout<<"|\n| Spordan wyj�� �uk i odstrzeli� ich obu.\n";
		cout<<"|\n| Spordan: Ruszcie si�, ja obstawi� ty�y.\n";
		kreska();
		cout<<"\n ";
		system("pause");
		system("cls");
		stats();
		kreska();
		cout<<"|\n| W Bielogrodzie rozp�ta�y si� zamieszki, wszyscy\n";
		cout<<"| poczuli wol� walki i postanowili obali� kr�la. Ten\n";
		cout<<"| jednak nie dawa� za wygran� i wysy�a� coraz ci�sze\n";
		cout<<"| jazdy na buntuj�cych si� mieszka�c�w\n";
		cout<<"|\n| Michniard: Zorganizuj� ludzi i otoczymy zamek\n";
		kreska();
		cout<<"\n ";
		system("pause");
		system("cls");
		cout<<"\n S�UCHAJCIE S�UCHAJCIE MIESZKA�CY BIELOGRODU\n";
		cout<<" NA ROZKAZ WIELMO�NEGO KR�LA WOJMIRA OG�ASZA SI�\n";
		cout<<" STAN WOJENNY NA TERENIE CA�EJ KRAINY\n";
		cout<<"\n Bindar: To dzia�a! Boj� si� nas! Szybko, musimy\n";
		cout<<" wykorzysta� ich s�abo��!\n\n ";
		system("pause");
		system("cls");
		stats();
		kreska();
		cout<<"|\n| Docieracie do zamku Wojmira. Konstrukcja\n";
		cout<<"| solidna, nie do rozwalenia byle armat�\n";
		cout<<"|\n| 1. Zaatakuj g�owne wej�cie\n";
		cout<<"| 2. Wejd� od kuchni\n";
		cout<<"| 3. Id� od piwnic\n";
		kreska();
		int odp5;
		cin>>odp5;
		switch (check(odp5,3)){
			case 1:
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Zaj�s�aw: nie, to zbyt ryzykowne!\n";
				cout<<"|           Tam zastawiona jest ca�a gwardia.\n";
				cout<<"|           Chod�my kuchni�\n";
				kreska();
				system("pause");
				goto kuchnia;
			case 2:
				kuchnia:
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Wchodzicie kuchni�. W niej jest 20 kucharzy\n";
				cout<<"| i ka�dy z nich ma tasak\n";
				cout<<"|\n| Bindar: Zostawcie to mi!\n";
				kreska();
				cout<<"\n ";
				system("pause");
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Trafiacie na g�owny korytarz.\n";
				cout<<"| jeszcze jest pusty.\n\n";
				cout<<"| Stebenia: Na g�r�! Tam napewno jest Wojmir!\n";
				cout<<"|           Ja zostan� tutaj na czatach\n";
				kreska();
				cout<<"\n ";
				system("pause");
				system("cls");
				cout<<"\n docierasz na g�r�\n";
				Sleep(2000);
				cout<<"\n tabliczka: DR. GRO�NY, NIE WCHODZI�\n";
				Sleep(2000);
				cout<<"\n 1. wejd�.";
				Sleep(2000);
				cin>>odp5;
				system("cls");
				cout<<"\n Prosz� prosz�... Artur! �miesz tak\n";
				cout<<" po prostu wchodzi� mi do zamku i mnie\n";
				cout<<" pokonywa�?\n\n";
				cout<<" 1. Dawaj dawaj nie udawaj\n";
				cin>>odp5;
				system("cls");
				cout<<"\n  Ludzie nie rozumiej� wiedzy... Te ksi�gi i\n";
				cout<<"  zwoje to wieczna m�dro��\n";
				cout<<"\n 1. Sko�cz ju� gada� i wyci�gaj bro�\n";
				cin>>odp5;
				system("cls");
				cout<<"\n Wojmir: Zm�w pacierz!\n";
				Sleep(5000);
				switch (walka(8)){
					case 1:
						system("cls");
						cout<<"\n NIE! MOJA BIELSANIA! TY MENDO!!!\n";
						cout<<"\n 1. Zdejmuj t� plandek� i ulotnij\n";
						cout<<"   si�. Skubana rasa...\n";
						cin>>odp5;
						system("cls");
						koncowka:
						cout<<"\n <Wojmir zostaje uwi�ziony i sprowadzony\n";
						cout<<"  do serwenii na wieczne wi�zienie>\n";
						Sleep(4000);
						system("cls");
						cout<<"\n Wr�ci�e� do reszty. Nie ma si� czego ba�.\n";
						cout<<" Bielsania jest zn�w wolna. Kr�lem zostaje \n";
						cout<<" Artur I, �wiat�y W�dz\n";
						kreska();
						cout<<"\n ";
						system("pause");
						goto koniec;
					case 2:	
						system("cls");
						cout<<"\n Wojmir: Ty parchu! Nie umiesz nawet";
						Sleep(1000);
						cout<<".";
						Sleep(1000);
						cout<<".";
						Sleep(1000);
						cout<<".";
						Sleep(1000);
						cout<<"\n\n Wojmir opad� na ziemi�.\n";
						Sleep(1000);
						cout<<" Spordan: Widzia�em �e potrzebujesz pomocy.\n";
						cout<<"          Nigdy nie w�tp w pot�g� Sparty m�ody\n";
						goto koncowka;
					case 3:
						system("cls");
						cout<<"\n Wojmir: Ty parchu! Nie umiesz nawet";
						Sleep(1000);
						cout<<".";
						Sleep(1000);
						cout<<".";
						Sleep(1000);
						cout<<".";
						Sleep(1000);
						cout<<"\n\n Wojmir opad� na ziemi�.\n";
						Sleep(1000);
						cout<<" Spordan: Widzia�em �e potrzebujesz pomocy.\n";
						cout<<"          Nigdy nie w�tp w pot�g� Sparty m�ody\n";
						goto koncowka;
				}
			case 3:
				system("cls");
				stats();
				kreska();
				cout<<"|\n| Zaj�s�aw: nie, to zbyt ryzykowne!\n";
				cout<<"|           Tam zastawiona jest ca�a gwardia.\n";
				cout<<"|           Chod�my kuchni�\n";
				kreska();
				system("pause");
				goto kuchnia;
		}	
	koniec:;
}
void menu(){			//menu gry
	string detale="Wysokie";
	wuwu:
	system("cls");
	tytul();
	cout<<"\n| 1. Zacznij gre \n";
	cout<<"| 2. Ustawienia \n";
	cout<<"| 3. Informacje o grze \n";
	cout<<"| 4. Wyjscie \n";
	kreska();
	int men_chc;
	cin>>men_chc;
	switch (check(men_chc,4)){
		case 1:	
			system("cls");
			goto starting;
        case 2:
        	settings:
        	system("cls");
        	tytul();
        	kreska();
        	cout<<"\n| 1. Grafika: "<<detale<<"\n"; //to nic nie zmienia
        	cout<<"| 2. HUD: "<<HUD<<" \n";
        	cout<<"| 3. exit \n";
        	kreska();
        	int graf;
			cin>>graf;
			switch (check(graf,3)){
				case 1:
					if (detale == "Wysokie"){
						detale = "Niskie";
						goto settings;
					} else {
						detale = "Wysokie";
						goto settings;
					}
				case 2:
					if (HUD == "ON"){
						HUD = "OFF";
					}	else {
						HUD = "ON";
					}
					goto settings;
                case 3:
					goto wuwu;
			}
  	    case 3:
  	    	system("cls");
  	    	tytul();
  	    	kreska();
  	    	cout<<"\n";
  	    	cout<<"| Bielsania Adventure to gra RPG. Nazywasz sie\n";
			cout<<"| Artur i trafiasz do wioski Czechigr�d w \n";
			cout<<"| kt�rej spotykasz Stebeni�, ktora wprowadzi\n";
  	    	cout<<"| ci� do gry. Nast�pnie udasz si� do Litynii \n";
  	    	cout<<"| w celu przygotowania do walki a na ko�cu \n";
  	    	cout<<"| stoczysz walk� z Wojmirem. Wszystko le�y \n";
  	    	cout<<"| w twoich r�kach! \n";
  	    	kreska();
  	    	cout<<"\n  ";
  	    	system("pause");
  	    	goto wuwu;
    	case 4:
    		wyjdz = 1;
    		goto starting;
	}
	starting:;
}
int main() {			//main
	setlocale(LC_CTYPE, "Polish");
	disclaimer();
	menu();
	start_game:
	if (wyjdz != 1){
    start();
	} else {
		goto end;
	}
    while (ending != 0){
        kreska();
        cout<<"|\n| Gra zako�czona! \n|\n";
        switch (ending){
            case 1:
                cout<<"| Pieni�dze ending \n";
                kreska();
                ending = 0;
                goto end;
            case 2:
                cout<<"| Olanie Stebenii ending \n";
                kreska();
                ending = 0;
                goto end;
            case 3:
                cout<<"| Good ending\n";
                kreska();
                ending = 0;
                goto end;
            case 4:
                cout<<"| Unranked ending \n";
                kreska();
                ending = 0;
                goto end;
        }
    }
    chapter1();
    chapter2();
    chapter3();
    chapter4();
    system("cls");
    cout<<"\n Good ending, Bielsania jest znowu wolna.";
	Sleep(5000);
	cout<<"\n Dzi�kuj� za zagranie. Licz� �e bawili�cie\n";
	cout<<" si� dobrze.\n                    ~Janusz";
    Sleep(10000);
	end: 
    	cout<<"\n Wychodzenie z gry.\n";
        Sleep(2000);
    return 0;
}