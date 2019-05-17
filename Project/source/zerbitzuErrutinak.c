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

static int tik=0;
static int seg=0;
int x = 5;

void tekEten ()
{	
	int stop = 0;
	if (SakatutakoTekla()== START)
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
				jokoa01(0);			
				stop = 1;
			}
		}
	}

	if (SakatutakoTekla()== SELECT)
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
	static int seg=0;
	static int dec=0;
	iprintf("\x1b[18;5HPa%d DECS:  %d",jkop,zailt);
	
		tik++; 
		if (tik==1)
		{
			dec++;
			iprintf("\x1b[15;5HPasa diren segunduak=%d DECS:  %d", seg,dec);	
			if (dec == 100)
			{
				seg++;	
				dec=0; 				
			}	
			tik=0;				
		}
		switch (jkop){
			case 1:	
				if (dec % 7 == 0){
					Ezabatusonic(2,x,68);
        				Erakutsisonic(2,x+1,68);
					x++;
				}
				if (tik % 7 == 0){
					Ezabatusonic(3,x,96);
        				Erakutsisonic(3,x+1,96);
					x++;
				}
				if (tik % 7 == 0){
					Ezabatusonic(4,x,124);
        				Erakutsisonic(4,x+1,124);
					x++;
				}
			case 2:
				if (tik % 7 == 0){
					Ezabatusonic(3,x,96);
        				Erakutsisonic(3,x+1,96);
					x++;
				}
				if (tik % 7 == 0){
					Ezabatusonic(4,x,124);
        				Erakutsisonic(4,x+1,124);
					x++;
				}
			case 3:
				if (tik % 7 == 0){
					Ezabatusonic(4,x,124);
        				Erakutsisonic(4,x+1,124);
					x++;
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
