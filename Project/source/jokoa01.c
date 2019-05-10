/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		//nds-rako garatuta dagoen liburutegia
#include <stdio.h>		//c-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		//c-ko liburutegi estandarra memoria erreserbak eta zenbaki konbertsioak egiteko
#include <unistd.h>		//Sistema eragileen arteko konpatibilitatea ziurtatzeko liburutegia

//Geuk garatutako fitxategiak
	
#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "fondoak.h"

int denb;

void jokoa01()
{	
	//aldagai baten definizioa
	int i=9;
	int tekla=0;

	EGOERA=ZAI;

	iprintf("\x1b[23;5HAldagai proba. Balioa=%d", i);

	EGOERA=JOKALARIAK; //Egoera orain jokalari kopuruaren aukeraketa da.

	touchPosition pos_pantaila; //aldagaiaren definizioa
	touchRead(&pos_pantaila); //posizioaren irakurketa

	//config
	konfiguratuTeklatua(int TEK_konf);
	konfiguratuTenporizadorea(Latch,TENP_konf);


	while(1){
		//Egoeren aldaketa
		switch (EGOERA){

			case JOKALRIAK:
				jokalariak();
				//jokaliaen pantaila
				break;
			case ZAILTASUNA:
				zailtasuna();
				//zailtasunaren pantaila erakutsi
				break;
			case JOKOA:
				jokoa();
				//jokoa hasten da
				break;
			case CHEATS:
				cheats();
				//cheats
				break;
			case MARK:
				mark();
				//mark
				break;			
		}
	}

	//Methods

	void jokalariak (){
		//JOKALARIAK

		erakutsiAteaIrekita(); //fondoa aldatu

		while (EGOERA = JOKALARIAK){
			while(pos_pantaila.px==0 && pos_pantalla.py==0) {
				touchRead(&pos_pantalla); //pantaila ukimenaren zai
			}

			//1 jokalari
			if((pos_pantaila.px >= 30 && pos_pantaila.px <= 226) && (pos_pantaila.py >= 30 && pos_pantaila.py <= 70)){
				EGOERA = ZAILTASUNA;
				int jkop=1;

			//2 jokalari
			if((pos_pantaila.px >= 30 && pos_pantaila.px <= 226) && (pos_pantaila.py >= 90 && pos_pantaila.py <= 130)){
				EGOERA = ZAILTASUNA;
				int jkop=2;
			
			//3 jokalari
			if((pos_pantaila.px >= 30 && pos_pantaila.px <= 226) && (pos_pantaila.py >= 150 && pos_pantaila.py <= 190)){
				EGOERA = ZAILTASUNA;
				int jkop=3;
			
			//4 jokalari
			if((pos_pantaila.px >= 30 && pos_pantaila.px <= 226) && (pos_pantaila.py >= 150 && pos_pantaila.py <= 190)){
				EGOERA = ZAILTASUNA;
				int jkop=4;
		}
	}


	void zailtasuna (){
		//ZAILTASUNA	

		erakutsiZailtasunfondoa(); //fondoa erakutsi		

		while (EGOERA = JOKALARIAK){
			while(pos_pantaila.px==0 && pos_pantalla.py==0) {
				touchRead(&pos_pantalla); //ukimen pantailaren zai
			}

			//Erraza
			if((pos_pantaila.px >= 30 && pos_pantaila.px <= 226) && (pos_pantaila.py >= 30 && pos_pantaila.py <= 70)){
				EGOERA = JOKOA;
				int zailt=1;

			//Normala
			if((pos_pantaila.px >= 30 && pos_pantaila.px <= 226) && (pos_pantaila.py >= 90 && pos_pantaila.py <= 130)){
				EGOERA = JOKOA;
				int zailt=2;
			
			//Zaila
			if((pos_pantaila.px >= 30 && pos_pantaila.px <= 226) && (pos_pantaila.py >= 150 && pos_pantaila.py <= 190)){
				EGOERA = JOKOA;
				int zailt=3;

		}
	}	


	void jokoa (){
		//JOKOA

		erakutsiJokofondoa(); //fondoa erakutsi
		int j1 = 1; //A tekla  --  1 balioa jokalartiak kontrolatzen du 0 balia IA-k
		int j2 = 1; //B tekla  --  1 balioa jokalartiak kontrolatzen du 0 balia IA-k
		int j3 = 0; //L tekla  --  1 balioa jokalartiak kontrolatzen du 0 balia IA-k
		int j4 = 0; //R tekla  --  1 balioa jokalartiak kontrolatzen du 0 balia IA-k

		int posj1 = 10; //spritearen x posizioa (y posizioa ez da aldatzen)
		int posj2 = 10; //spritearen x posizioa (y posizioa ez da aldatzen)
		int posj3 = 10; //spritearen x posizioa (y posizioa ez da aldatzen)
		int posj4 = 10; //spritearen x posizioa (y posizioa ez da aldatzen)
		int helmuga = 200; // helmugaren x posizioa
		int time; //denboragailua

		bool bukatua = false; //lau jokalariak helmugara iristean true bihurtuko da

		while (!bukatua) {
			//inkesta egin
			if (TeklaDetektatu()){
				switch (SakatutakoTekla()){
					case A:
						mugitu(1,posj1,y); //teklen mugimendua j1
					case B:
						mugitu(2,posj1,y); //teklen mugimendua j2
					case L:
						mugitu(3,posj1,y); //teklen mugimendua j3
					case R:
						mugitu(4,posj1,y); //teklen mugimendua j4
				}
			}

			if (j2 = 0){
				mugitu(2,posj2,y); //IA-ko mugimendua
			}
			if (j3 = 0){
				mugitu(3,posj2,y); //IA-ko mugimendua
			}
			if (j4 = 0){
				mugitu(4,posj2,y); //IA-ko mugimendua
			}

			//Helmuga
			if (posj1 = helmuga || posj2 = helmuga || posj3 = helmuga || posj4 = helmuga)
			{
				//norbaitek bukatu du
				switch (helmuga){
					case posj1:
						iprintf("\x1b[23;5HJ1 ===> %ds ", time); //Helmugara iristen denean pantailaratu denbora
						//lock movement
					case posj2:
						iprintf("\x1b[23;5HJ2 ===> %ds ", time); //Helmugara iristen denean pantailaratu denbora
						//lock movement
					case posj3:
						iprintf("\x1b[23;5HJ3 ===> %ds ", time); //Helmugara iristen denean pantailaratu denbora
						//lock movement
					case posj4:
						iprintf("\x1b[23;5HJ4 ===> %ds ", time); //Helmugara iristen denean pantailaratu denbora
						//lock movement
				}
			}
		}

		EGOERA = MARK; //hurrengo egoerara joan
	}

	void mugitu(int jokalari, int posx){
		//spreiteak mugitzeko
		static int posyj1 = 10;
		static int posyj2 = 20;
		static int posyj3 = 30;
		static int posyj4 = 40;
		int posy;

		switch (jokalari){
			case 1:
				posy = posyj1; //aukeratu spritearen y posizioa
				break;

			case 2:
				posy = posyj2; //aukeratu spritearen y posizioa
				break;

			case 3:
				posy = posyj3; //aukeratu spritearen y posizioa
				break;

			case 4:
				posy = posyj4; //aukeratu spritearen y posizioa
				break;
		}

		//ezabatu spritea
		EzabatuPepe(jokalari,posx,posy);

		//Erakutsi spritea 
		ErakutsiPepe(jokalari,posx+1,posy);

	}

	void cheats (){
		ErakutsiCheats(); //fondoa erakutsi
		//...
	}

	void mark (){
		ErakutsiMark(); //fondoa erakutsi
		//...
	}
}
