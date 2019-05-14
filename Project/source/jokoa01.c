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
int status = 2; //0 jokalariak, 1 zailtasuna, 2 jokoa, 3 mark, 4 cheats, 5 pause

void jokoa01()
{	
	int tekla=0;
	int jkop = 1;
	int segundua = 0;	
	ErlojuaMartxanJarri();
	konfiguratuTeklatua(0x400C);

	EGOERA = ZAI;
	

	//config
	//konfiguratuTeklatua(int TEK_konf);
	konfiguratuTenporizadorea(65208.32,0x00C3);
	


	//Methods
	void delay (int x){ //delay = x ms
		int time = 0;

		ErlojuaMartxanJarri();
		while (x > time){
			time++;
			iprintf("\x1b[23;5HTIME: %d",time);
		}
		ErlojuaGelditu();
	}

	void temp (){
		int stop = 0;
		int tick = 0;
		int dec = 0;
		int sec = 0;
		while(stop == 0){
	
			tick = tick + 1;
	
			if (tick % 800 == 0){
				dec = dec + 1;
			}
	
			if (dec == 10){
				sec = sec + 1;
				dec = 0;
			}
	
			iprintf("\x1b[22;5H%d : %d",sec, dec);
		}
	}
			

	void jokalariak () {	
		erakutsijokalariak();
		while (PANT_DAT.px == 0 && PANT_DAT.py == 0){
			touchRead(&PANT_DAT); //posizioaren irakurketa
			
		}
		
		iprintf("\x1b[23;5HAukeratu jakalari kopurua");	//Fix Height

		//1 jokalari
		if((PANT_DAT.px >= 18 && PANT_DAT.px <= 110) && (PANT_DAT.py >= 108 && PANT_DAT.py <= 129)){
			int jkop=1;
			status = 1; // Zailtasun egoera
		}

		//2 jokalari
		if((PANT_DAT.px >= 143 && PANT_DAT.px <= 235) && (PANT_DAT.py >= 108 && PANT_DAT.py <= 129)){
			int jkop=2;
			status = 1; // Zailtasun egoera
		}
			
		//3 jokalari
		if((PANT_DAT.px >= 18 && PANT_DAT.px <= 110) && (PANT_DAT.py >= 150 && PANT_DAT.py <= 190)){
			int jkop=3;
			status = 1; // Zailtasun egoera
		}
			
		//4 jokalari
		if((PANT_DAT.px >= 143 && PANT_DAT.px <= 235) && (PANT_DAT.py >= 150 && PANT_DAT.py <= 190)){
			int jkop=4;
			status = 1; // Zailtasun egoera
		}

		//PANT_DAT.px == 0;
		//PANT_DAT.py == 0;
	
	}

	void zailtasuna () {
		delay(10000);
		erakutsizailtasuna();
		PANT_DAT.px = 0;
		PANT_DAT.py = 0;
		while (PANT_DAT.px == 0 && PANT_DAT.py == 0){
			touchRead(&PANT_DAT);
			iprintf("\x1b[12;5HAAAAAAAAAAAAAAAAAAA");	//Fix Height
		}
			
		iprintf("\x1b[23;5HAukeratu zailtasuna"); //Fix Height
			
		//Erraza
		if((PANT_DAT.px >= 47 && PANT_DAT.px <= 209) && (PANT_DAT.py >= 90 && PANT_DAT.py <= 111)){
			int zailt=1;
			status = 2; // Jokoa egoera
		}

		//Normala
		if((PANT_DAT.px >= 47 && PANT_DAT.px <= 209) && (PANT_DAT.py >= 124 && PANT_DAT.py <= 145)){
			int zailt=2;
			status = 2; // Jokoa egoera
		}
			
		//Zaila
		if((PANT_DAT.px >= 47 && PANT_DAT.px <= 209) && (PANT_DAT.py >= 158 && PANT_DAT.py <= 179)){
			int zailt=3;
			status = 2; // Jokoa egoera
		}
	
	}

	void jokoa () {
		int finish = 0;
		int push = 1;
		int x = 5;
		erakutsiAtea();
		//load sprites
		ErakutsiErronboHandia(1,5,40);
		iprintf("\x1b[12;5HRUNNER %d",jkop);
		while (finish == 0){

			if(TeklaDetektatu() == push){
				if (push == 1){
					EzabatuErronboHandia(1,x,40);
					ErakutsiErronboHandia(1,x+1,40);
					x = x+5;
					delay(100);
					push = 0;
					if (x >= 220)					
					{
						iprintf("\x1b[10;5HPOS: %d",x);
						EzabatuErronboHandia(1,x,40);
						finish = 1;
						
					}
				}
				else
				{
					push = 1;
				}
				
			}
		}
		status = 3; // Mark egoera
		
	}

	void mark () {
		/*erakutsizailtasuna();
		while (TeklaDetektatu() == 0){
			iprintf("\x1b[23;5HRUNNER"); //Fix Height
			//Implementar marcadores
			//...
		}*/
		status = 0; // Jokalari egoera
	
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
			case 5: 
				iprintf("\x1b[23;5HPAUSE");
				break;
			case 9: //tests
				temp();
				break;		
		}
	 }

	

	
}
