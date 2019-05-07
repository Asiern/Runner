

function score(){
    //Vertical Locate text
	iprintf("\x1b[23;5HAldagai proba. Balioa=%d", p1timer);
    iprintf("\x1b[23;5HAldagai proba. Balioa=%d", p2timer);
    iprintf("\x1b[23;5HAldagai proba. Balioa=%d", p3timer);
    iprintf("\x1b[23;5HAldagai proba. Balioa=%d", p4timer);
}

function game(){

	bool bukatu=False;
	bool bukatu1=False;
	bool bukatu2=False;
	int meta = 240;
    int min;
    int max;



	while (!bukatu){
		//Player1
		if (detektatu1){
			imgpx1 = imgpx1 + 1;
		}
		if (imgpx1 = meta){
			bukatu1 = True;
		}

		//Player2
		if (detektatu2){
			imgpx2 = imgpx2 + 1;
		}
		if (imgpx2 = meta){
			bukatu2 = True;
		}

		//Player3
		if (detektatu3){
			imgpx3 = imgpx3 + 1;
		}
		if (imgpx3 = meta){
			bukatu3 = True;
		}

		//Player4
		if (detektatu4){
			imgpx4 = imgpx4 + 1;
		}
		if (imgpx4 = meta){
			bukatu4 = True;
		}

		if (bukatu1 & bukatu2 & bukatu3 & bukatu4){
			bukatu = True;
		}

	}
	x=score();
}

function IA(){
	x=random(min..max) //Variables segun dificultad
	if(time%x=0){}
		imgpx=imgpx + 1;

	if (imgpx = meta){
			bukatu = True;
		}

	/////////////PENDIENTE DE REVISIÓN////////////////
}



function playerelection(){
	
	fondo = playerelection.png;
	if(detektatu = rango[player1]){
		player=1;
		difficulty(player);
	}

	if(detektatu = rango[player2]){
		player=2;
		difficulty(player);
		
	}
	
	if(detektatu = rango[player3]){
		player=3;
		difficulty(player);

	}

	if(detektatu = rango[player4]){
		player=4;
		difficulty(player);

	}
}

function difficulty(player){
	fondo=difficulty.png;
	if(detektatu = rango[difficulty1]){
		min = 20;
		max = 30;
		if(player = 1){
			game1(min,max);
		}

		if(player = 2){
			game2(min,max);
		}

		if(player = 3){
			game3(min,max);
		}

		if(player = 4){
			game4(min,max);
		}
	}

	if(detektatu = rango[difficulty2]){
		min = 10;
		max = 20;
		if(player = 1){
			game1(min,max);
		}

		if(player = 2){
			game2(min,max);
		}

		if(player = 3){
			game3(min,max);
		}

		if(player = 4){
			game4(min,max); 
		}
	}

	
	if(detektatu = rango[difficulty3]){
		min = 5;
		max = 10;
		if(player = 1){
			game1(min,max);
		}

		if(player = 2){
			game2(min,max);
		}

		if(player = 3){
			game3(min,max);
		}

		if(player = 4){
			game4(min,max);
		}
	}
}