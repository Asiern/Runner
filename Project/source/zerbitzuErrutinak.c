/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"

int EGOERA;
int seg3;

void tekEten ()
{	
	int stop = 0;
	if (SakatutakoTekla()== START)
	{	
		erakutsiAteaIrekita();
		while (stop == 0){
			if(SakatutakoTekla() == A){
				stop = 1;
			}
		}			

	}
}

void tenpEten()
{
	static int tik=0;
	static int seg=0;
	

if (EGOERA!=ZAI)
{
	tik++; 
	if (tik==5)
	{
		seg++;
		iprintf("\x1b[13;5HPasa diren segunduak=%d", seg);
		tik=0;
		if (EGOERA == IREKITA)
		{
			seg3++;
			if (seg3==3)
			{
				erakutsiAtea();
				seg3=0;
				EGOERA=ITXITA;
				EzabatuErronboa(1, 5, 5);
				EzabatuErronboHandia(2, 100, 100);
			}
		}
				
	}
}
	
}

void etenZerbErrutEzarri()
{
	// HAU BETE
	irqSet(IRQ_KEYS, tenpEten);
}

