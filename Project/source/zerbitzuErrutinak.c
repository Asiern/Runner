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


int EGOERA;
int seg3;
static int tik=0;
static int seg=0;

void tekEten ()
{	
	int stop = 0;
	if (SakatutakoTekla()== START)
	{	
		Ezabatusonic(1,0,0);
		Ezabatusonic(2,0,0);
		Ezabatusonic(3,0,0);
		Ezabatusonic(4,0,0);
		erakutsiAteaIrekita();
		while (stop == 0){
			if(SakatutakoTekla() == A){
				erakutsiAtea();				
				stop = 1;
			}
		}			

	}
}

void tenpEten()
{	
	static int tik=0;
	static int seg=0;
	static int dec=0;
		tik++; 
		if (tik==1)
		{
			dec++;
			iprintf("\x1b[20;5HPasa diren segunduak=%d DECS:  %d", seg,dec);	
			if (dec == 100)
			{
				seg++;	
				dec=0; 				
			}	
			tik=0;				
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
