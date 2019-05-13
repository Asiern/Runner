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
int status = 0; //0 jokalariak, 1 zailtasuna, 2 jokoa, 3 mark, 4 cheats, 5 pause

void jokoa01()
{	
	int tekla=0;
	int jkop = 1;

	EGOERA = ZAI;

	//EGOERA=JOKALARIAK; //Egoera orain jokalari kopuruaren aukeraketa da.

	touchPosition pos_pantaila; //aldagaiaren definizioa
	touchRead(&pos_pantaila); //posizioaren irakurketa

	//config
	//konfiguratuTeklatua(int TEK_konf);
	//konfiguratuTenporizadorea(Latch,TENP_konf);



	//Methods

	void jokalariak () {
		erakutsijokalariak();
		while (TeklaDetektatu() == 0){
			iprintf("\x1b[23;5HAukeratu jakalari kopurua");	//Fix Height
			//Implementar tactil con 4 if(){}
			//...
		}
		status = 1; // Zailtasun egoera
	
	}

	void zailtasuna () {
		erakutsizailtasuna();
		while (TeklaDetektatu() == 0){
			iprintf("\x1b[23;5HAukeratu zailtasuna"); //Fix Height
			//Implementar tactil con 3 if(){}
			//...
		}
		status = 2; // Zailtasun egoera
	
	}

	void jokoa () {
		int finish = 0;
		int x = 5;
		erakutsiAtea();
		//load sprites
		ErakutsiErronboHandia(1,5,40);
		while (finish == 0){
			if(TeklaDetektatu == 1){
				EzabatuErronboHandia(1,x,40);
				ErakutsiErronboHandia(1,x+10,40);
				x = x+10;
			}
		}
		status = 3; // Zailtasun egoera
	
	}

	void mark () {
		erakutsizailtasuna();
		while (TeklaDetektatu() == 0){
			iprintf("\x1b[23;5HRUNNER"); //Fix Height
			//Implementar marcadores
			//...
		}
		status = 0; // Zailtasun egoera
	
	}


	while(1){
		//Egoeren aldaketa
		switch (status){

			case 0:				
				jokalariak();
				break;
			case 1:
				zailtasuna();				
				break;
			case 2:
				jokoa();
				break;
			case 3:
				mark();
				break;
			case 4:
				iprintf("\x1b[23;5HAldagai proba. Balioa= 4");
				break;			
		}
	 }

	

	
}
