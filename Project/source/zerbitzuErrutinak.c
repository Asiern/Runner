/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "jokoa01.h"
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"
int zailt;
int jkop;
int timereset;

static int tik=0;
static int seg=0;
int x = 5;
int x1 = 5;
int x2 = 5;
int x3 = 5;
int x4 = 5;

void tekEten ()
{	
	int stop = 0;
	if (SakatutakoTekla()== START) //MENUA
	{	
		Ezabatusonic(1,0,0);
		Ezabatusonic(2,0,0);
		Ezabatusonic(3,0,0);
		Ezabatusonic(4,0,0);
		erakutsipause();
		while (stop == 0){
			if(SakatutakoTekla() == A){
				erakutsijokoa();				
				stop = 1;
			}	
			if(SakatutakoTekla() == B){
				timereset = 0;
				jokoa01(0);			
				stop = 1;
			}
		}
	}

	if (SakatutakoTekla()== SELECT) //PAUSA
	{
		while (stop == 0){
			if(SakatutakoTekla() == A){
				stop = 1;
			}
		}
	}
}

void tenpEten()
{	
	//static int tik=0;
	/* Void honetan erlojuaren bitartez beste jokalariak kontrolatzen dira*/
	static int seg=0;
	static int dec=0;
	static int kont=0; // mugitzeko kontagailua
	static int speed1 = 10; //Zailtasun errazaren abiadura
	static int speed2 = 20; //Zailtasun normalaren abiadura
	static int speed3 = 30; //Zailtasun zailaren abiadura
	
	if (timereset == 0){ //Timer-a hasieratu
		Ezabatusonic(1,0,0);
		Ezabatusonic(2,0,0);
		Ezabatusonic(3,0,0);
		Ezabatusonic(4,0,0);
		x = 5;
		x1 = 5;
		x2 = 5;
		x3 = 5;
		x4 = 5;
		seg = 0;
		dec = 0;
	}
	else{
		tik++; 
		if (tik==1)
		{
			dec++;
			if (dec == 100)
			{
				seg++;	
				dec=0; 	
				kont = 1;			
			}	
			tik=0;				
		}
		switch (jkop){
			case 1:	//Jokalari baten kasuan 
				if (kont == 1){
					if (x2 > 240){
						
						Ezabatusonic(2,0,0);
					}
					else{
						Ezabatusonic(2,x2,68);
						Erakutsisonic(2,x2+1,68);
						if (zailt == 1){
							x2 = x2+speed1;}
						else if (zailt == 2){
							x2 = x2+speed2;}
						else {
							x2 = x2+speed3;	
						}
					}
				}
				if (kont == 1){
					if (x3 > 240){
						Ezabatusonic(3,0,0);
					}
					else{
						Ezabatusonic(3,x3,96);
						Erakutsisonic(3,x3+1,96);
						if (zailt == 1){
							x3 = x3 + speed1;}
						else if (zailt == 2){
							x3 = x3+speed2;}
						else {
							x3 = x3+speed3;	
						}
					}
				}
				if (kont == 1){
					if (x4 > 240){
						
						Ezabatusonic(4,0,0);
					}
					else{
						Ezabatusonic(4,x4,124);
						Erakutsisonic(4,x4+1,124);
						if (zailt == 1){
							x4 = x4+speed1;}
						else if (zailt == 2){
							x4 = x4+speed2;}
						else {
							x4 = x4+speed3;	
						}
					}
				}
				kont = 0;
			case 2: //2 Jokalarien kasuan 
				if (kont == 1){
					if (x3 > 240){
						
						Ezabatusonic(3,0,0);
					}
					else{
						Ezabatusonic(3,x3,96);
        					Erakutsisonic(3,x3+1,96);
						if (zailt == 1){
							x3 = x3 + speed1;}
						else if (zailt == 2){
							x3 = x3+speed2;}
						else {
							x3 = x3+speed3;	
						}
					}
				}
				if (kont == 1){
					if (x4 > 240){
						
						Ezabatusonic(4,0,0);
					}
					else{
						Ezabatusonic(4,x4,124);
						Erakutsisonic(4,x4+1,124);
						if (zailt == 1){
							x4 = x4+speed1;}
						else if (zailt == 2){
							x4 = x4+speed2;}
						else {
							x4 = x4+speed3;	
						}
					}
				}
				
				kont = 0;
			case 3: //3 Jokalarien kasuan 
				if (kont == 1){
					if (x4 > 240){
						
						Ezabatusonic(4,0,0);
					}
					else{
						kont = 0;
						Ezabatusonic(4,x4,124);
						Erakutsisonic(4,x4+1,124);
						if (zailt == 1){
							x4 = x4+speed1;}
						else if (zailt == 2){
							x4 = x4+speed2;}
						else {
							x4 = x4+speed3;	
						}
					}
				}
		}
	}
		
}

void tenpZerbErrutEzarri()
{
	irqSet(IRQ_TIMER0, tenpEten);
}

void etenZerbErrutEzarri()
{
    irqSet(IRQ_KEYS, tekEten);

}
