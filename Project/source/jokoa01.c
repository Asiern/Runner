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
	int zailt = 1; //1 erraza, 2 normala, 3 zaila
	int segundua = 0;	
	ErlojuaMartxanJarri();

	EGOERA = ZAI;
	

	//config	
	konfiguratuTeklatua(0x400C);
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
			

	int jokalariak () {	

		erakutsijokalariak();

		while (PANT_DAT.px == 0 && PANT_DAT.py == 0){
			touchRead(&PANT_DAT); //posizioaren irakurketa
			
		}
		
		iprintf("\x1b[23;5HAukeratu jakalari kopurua");	//Fix Height

		//1 jokalari
		if((PANT_DAT.px >= 18 && PANT_DAT.px <= 110) && (PANT_DAT.py >= 108 && PANT_DAT.py <= 129)){
			status = 1; // Zailtasun egoera
			return jkop=1;
		}

		//2 jokalari
		if((PANT_DAT.px >= 143 && PANT_DAT.px <= 235) && (PANT_DAT.py >= 108 && PANT_DAT.py <= 129)){
			status = 1; // Zailtasun egoera
			return jkop=2;
		}
			
		//3 jokalari
		if((PANT_DAT.px >= 18 && PANT_DAT.px <= 110) && (PANT_DAT.py >= 150 && PANT_DAT.py <= 190)){
			status = 1; // Zailtasun egoera
			return jkop=3;
		}
			
		//4 jokalari
		if((PANT_DAT.px >= 143 && PANT_DAT.px <= 235) && (PANT_DAT.py >= 150 && PANT_DAT.py <= 190)){
			status = 1; // Zailtasun egoera
			return jkop=4;
		}
	
	}

	int zailtasuna () {
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
			status = 2; // Jokoa egoera			
			return 1;			
		}

		//Normala
		if((PANT_DAT.px >= 47 && PANT_DAT.px <= 209) && (PANT_DAT.py >= 124 && PANT_DAT.py <= 145)){
			status = 2; // Jokoa egoera
			return 2;		
		}
			
		//Zaila
		if((PANT_DAT.px >= 47 && PANT_DAT.px <= 209) && (PANT_DAT.py >= 158 && PANT_DAT.py <= 179)){
			status = 2; // Jokoa egoera			
			return 3;
			
		}
	
	}

	void jokoa () {
		int finish = 0;
		int push = 1;
		int pushB = 1;
		int x = 5;
		
		//J1
		int j1 = 0; //finished(1) or not(0)
		int j1x = 5; //x pos of j1
		static int j1y = 40; //y pos of j1

		//J2
		int j2 = 0; //finished(1) or not(0)
		int j2x = 5; //x pos of j2
		static int j2y = 68; //y pos of j2

		//J3
		int j3 = 0; //finished(1) or not(0)
		int j3x = 5; //x pos of j3
		static int j3y = 96; //y pos of j3

		//J4
		int j4 = 0; //finished(1) or not(0)
		int j4x = 5; //x pos of j4
		static int j4y = 124; //y pos of j4

		erakutsiAtea();
		//load sprites
		Erakutsisonic(1,j1x,j1y);
		Erakutsisonic(2,j2x,j2y);
		Erakutsisonic(3,j3x,j3y);
		Erakutsisonic(4,j4x,j4y);

		while (j1 == 0 && j2 == 0 && j3 == 0 && j4 == 0) {

			if(SakatutakoTekla() == A){
                		if(TeklaDetektatu() == push){
                    			if (push == 1){
                        			EzabatuErronboHandia(1,x,40);
                        			ErakutsiErronboHandia(1,x+1,40);
                        			x = x+5;
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

			if (jkop == 1)
			{
				//mugimendu clock
			}
			else {

				if(SakatutakoTekla() == B){
	         			if(TeklaDetektatu() == pushB){
	                    			if (pushB == 1){
	                        				EzabatuErronboHandia(2,j2x,j2y);
	                        				Erakutsisonic(2,j2x+1,j2y);
	                        				j2x = j2x+5;
	                        				pushB = 0;
	                        				if (j2x >= 220)					
	                        				{
	                            					//Ezabatusonic(2,j2x,j2y);
	                            					j2 = 1;
	                            
	                        				}
	                    			}
	                    			else
	                    			{
	                        			pushB = 1;
	                    			}
	                    
	                		}
	    			}
			}

	    		if (jkop == 1 || jkop == 2)
			{
				//mugimendu clock
			}
			else {

				if(SakatutakoTekla() == GORA){
	         			if(TeklaDetektatu() == pushB){
	                    			if (pushB == 1){
	                        			Ezabatusonic(3,j3x,j3y);
	                        			Erakutsisonic(3,j3x+1,j3y);
	                        			j3x = j3x+5;
	                        			pushB = 0;
	                        			if (j3x >= 220)					
	                        			{
	                            				//Ezabatusonic(3,j3x,j3y);
	                            				j3 = 1;	                            
	                        			}
	                    			}
	                    			else
	                    			{
	                        			pushB = 1;
	                    			}
	                    
	                		}
	    			}

			}

			if (jkop == 1 || jkop == 2 || jkop == 3)
			{
				//mugimendu clock
			}
			else {

				if(SakatutakoTekla() == BEHERA){
	         			if(TeklaDetektatu() == pushB){
	                    			if (pushB == 1){
	                        			Ezabatusonic(4,j4x,j4y);
	                        			Erakutsisonic(4,j4x+1,j4y);
	                        			j4x = j4x+5;
	                        			pushB = 0;
	                        			if (j4x >= 220)					
	                        			{
	                            				//Ezabatusonic(4,j4x,80);
	                            				j4 = 1;
	                                       		}
	                    			}
	                    			else
	                    			{
	                      		  		pushB = 1;
	                    			}
	                    
	                		}
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
				jkop = jokalariak();
				break;
			case 1:
				zailt = zailtasuna();				
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
