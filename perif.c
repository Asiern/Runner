/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"


int tekla; //sakatutako tekla gordetzeko aldagaia



int TeklaDetektatu() 
{
	//TRUE itzultzen du teklaren bat sakatu dela detektatzen badu
	if ((~TEKLAK_DAT & 0x03ff)!=0) return 1;
	else return 0;

}

int SakatutakoTekla() 
{
	int Tek = ~TEKLAK_DAT & 0x03ff;

	switch(Tek)
	{
		case 0x0001: return A;
		case 0x0002: return B;
		case 0x0004: return SELECT;
		case 0x0008: return START;
		case 0x0010: return ESKUBI;
		case 0x0020: return EZKER;
		case 0x0040: return GORA;
		case 0x0080: return BEHERA;
		case 0x0100: return R;
		case 0x0200: return L;
	}	
	//Sakatutako teklaren balioa itzultzen du: A=0;B=1;Select=2;Start=3;Esk=4;Ezk=5;
	//Gora=6;Behera=7;R=8;L=9;
}
void konfiguratuTeklatua(int TEK_konf)
{
	//0x400C
	TEKLAK_KNT = TEK_konf;
	
}

void konfiguratuTenporizadorea(int Latch, int TENP_konf)
{
	//Tenporizadorearen konfigurazioa bere S/I erregistroak aldatuz
	DENB0_DAT = Latch;
	DENB0_KNT = TENP_konf;
	// Erregistroen aldaketa

}


void TekEtenBaimendu()
{
	//Teklatuaren etenak baimendu
	//Lan hau burutzeko lehenengo eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME = 0;
	IE = IE | 0x00001000;
	
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IME = 1;
	
}




void TekEtenGalarazi()
{

	//Teklatuaren etenak galarazi
	//Lan hau burutzeko lehenengo eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	IE = IE & 0xFFFFEFFF;
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IME=1;
}  

void DenbEtenBaimendu()
{

//Denboragailu baten etenak baimendu (Timer0)
//Horretarako lehenengo eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	IE = IE | 0x00000008;
	//irqSet(IRQ_TIMER0, TeklaZE);
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IME=1;
}

void DenbEtenGalarazi()
{

//Denboragailu baten etenak galarazi (Timer0)
//Horretarako lehenengo eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	IE = IE & 0xFFFFFFF7;
	
	// HEMEN IDATZI BEHAR DUZUE ZUEN KODEA
	IME=1;

}

void ErlojuaMartxanJarri()
{
	DENB0_KNT = DENB0_KNT | 0x0080;
}

void ErlojuaGelditu()
{
	DENB0_KNT = DENB0_KNT & 0xFF7F;
}

	
	

