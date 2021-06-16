#include <allegro.h>
//animação player
struct obj {int x, y, wx, wy, w, h;};
struct obj chefe = {200, 205, 2, 1, 115, 104};
struct obj p = {0, 100, 0, 51, 48, 48};
struct obj tile = {0, 0, 0, 0, 35, 35};
struct obj tiro = {-10, -10, 15, 0, 15, 8};
struct obj chefe_tiro = {100, 100, 0, 0, 30, 30};

//funções
void sair();
int colidir(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh);
int jogador();

//Variáveis Globais
int enemy_x[35];
int enemy_y[35];
int enemy_wx[35];
int enemy_wy[35];
int enemy_w[35];
int enemy_h[35];
int mov_auto[40];
int controle[10];
int menu_dir[4] = {0, 0, 0, 0};
int tile_y[5] = {120, 120, 350, 120, 420};

int i = 0;
int fase = 0;
int pontos = 0;
int vidas = 0;
int nTile_boss = 0, dir_boss = 0;
int vidas_boss = 0;
int atirar_boss = 0;
//plataformas que se movem

//int bloco_y = 420;
int atirar = 0;
int timer = 0;

int guia = 4;
int botMenu_troca = 0;
int mov_menuX = -900;
int mov_menuSobre = -1300;
int nTile = 0; 
int dir = 0;

//guia sair e função que habilita o x da janela
int fechar = 0, sai = 0;

int vly = 0;
int pLimit = 0;
int pulando = 0;
int grv = 3;
int caindo = 1;
int vup = 10;

//medidas da tela
int width  = 920, height = 450;

void tempo(){timer++;}

BITMAP *buffer, *backgroundMenu, *titulo, *guias, *botMenu, *sobreFundo, *textoSobre ,
 *player, *bala, *comoJogar, *vida, *tileFase1, *tileFase2, *tileFase3, *bg, *bg01, *bg02, 
 *bg03, *final, *tiroboss, *inimigo, *boss, *perdeu, *botaoPerdeu, *ponteiro;
 
SAMPLE *musicafase1, *musicafase2, *musicafase3, *musicafinal, *musicaMenu, *tirotocou, *morteboss,
*danoboss, *select, *pulo, *musicaTiro, *musicaMorte, *musicaAndar, *musicaCaiu, *musicaCoroninha, *danoCoroninha;
 
int main() {
	//variaveis dos inimigos
	for(i = 0; i < 35; i++){
	enemy_x[i] = 300;
	enemy_y[i] = 270;
	enemy_wx[i] = 0;
	enemy_wy[i] = 0;
	enemy_w[i] = 40;
	enemy_h[i] = 40;}
	
	for(i = 0; i < 40; i++){mov_auto[i] = 100;}
	for(i = 0; i < 10; i++){controle[i] = 0;}
	
    //Iniciação
	allegro_init();
    install_keyboard();
    install_mouse();
	set_color_depth(32);
	set_window_title("Pandemic Projet");
	set_close_button_callback(sair);
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);  
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);
	
	//Variáveis Locais
	buffer = create_bitmap(width, height);
	backgroundMenu = load_bitmap("midias/menu/background-menu.bmp",NULL);
	titulo = load_bitmap("midias/menu/titulo.bmp",NULL);
	guias = load_bitmap("midias/menu/tile-menu.bmp",NULL);
	botMenu = load_bitmap("midias/tile-go-menu.bmp",NULL);
	sobreFundo = load_bitmap("midias/sobre/fundo-praca.bmp",NULL);
	textoSobre = load_bitmap("midias/sobre/sobre-texto.bmp",NULL);
	comoJogar = load_bitmap("midias/manual.bmp",NULL);
	
	//jogo
	vida = load_bitmap("midias/jogo/vida.bmp",NULL);
	//blocos
	tileFase1 = load_bitmap("midias/jogo/tile.bmp",NULL);
	tileFase2 = load_bitmap("midias/jogo/tile2.bmp",NULL);
	tileFase3 = load_bitmap("midias/jogo/tile3.bmp",NULL);
	
	//backgrounds
	bg = load_bitmap("midias/jogo/BG.bmp",NULL);
	bg01 = load_bitmap("midias/jogo/BG-1.bmp",NULL);
	bg02 = load_bitmap("midias/jogo/BG-2.bmp",NULL);
	bg03 = load_bitmap("midias/jogo/BG-3.bmp",NULL);
	final = load_bitmap("midias/jogo/final.bmp",NULL);
	
	tiroboss = load_bitmap("midias/jogo/tiro_boss.bmp",NULL);
	inimigo = load_bitmap("midias/jogo/tile-coroninha.bmp",NULL);
	boss = load_bitmap("midias/jogo/boss.bmp",NULL);
	player = load_bitmap("midias/jogo/tile-medico.bmp",NULL);
	bala = load_bitmap("midias/jogo/tiro.bmp",NULL);
	//voce perdeu
	perdeu = load_bitmap("midias/jogo/voce perdeu/voce perdeu.bmp",NULL);
	botaoPerdeu = load_bitmap("midias/jogo/voce perdeu/botao.bmp",NULL);
	ponteiro = load_bitmap("midias/ponteiro-do-mouse.bmp",NULL);
	//músicas
	musicafase1 = load_sample("midias/jogo/musicas/gravity falls.wav");
	musicafase2 = load_sample("midias/jogo/musicas/skyrim 8 bits.wav");
	musicafase3 = load_sample("midias/jogo/musicas/star wars.wav");
	musicafinal = load_sample("midias/jogo/musicas/evangelion.wav");
	
	musicaMenu = load_sample("midias/jogo/musicas/lo-fi 8 bits.wav");
	tirotocou = load_sample("midias/jogo/musicas/tiro_tocou.wav");
	
	morteboss = load_sample("midias/jogo/musicas/morte_boss.wav");
	danoboss = load_sample("midias/jogo/musicas/dano_boss.wav");
	select = load_sample("midias/jogo/musicas/select.wav");
	pulo = load_sample("midias/jogo/musicas/pulo.wav");
	musicaTiro = load_sample("midias/jogo/musicas/tiro.wav");
	musicaMorte = load_sample("midias/jogo/musicas/morte.wav");
	musicaAndar = load_sample("midias/jogo/musicas/andar.wav");
	musicaCaiu = load_sample("midias/jogo/musicas/caiu.wav");
	musicaCoroninha = load_sample("midias/jogo/musicas/mortecoroninha.wav");
	danoCoroninha = load_sample("midias/jogo/musicas/danocoroninha.wav");
	
	//timers
	install_int_ex(tempo,MSEC_TO_TIMER(55));
	float delay;
	
	while (!(sai || key[KEY_ESC] || fechar == 1)){	
		  delay = timer;
		  
switch(guia){
			 case 0:
			 	  if(guia == 0 && controle[0] == 0){play_sample(musicaMenu, 100, 128, 1000, 0);controle[0]+=1;guia = 4;}
			 	  
			 	  //background menu	
        mov_menuX++;
        if(mov_menuX == -10)mov_menuX = -900; 
		draw_sprite(buffer, backgroundMenu, mov_menuX,0);
		
		draw_sprite(buffer, titulo, 183, 15);
		rest(10);
		
		textout_ex(buffer, font, "VERSAO 1.0 BETA", 10, 10, makecol(255,255,255), -1);
		
		//jogar
		if(colidir(mouse_x, mouse_y, 306, 110, 10, 10, 288, 62)){
							
							menu_dir[0] = 62;
						    if(mouse_b == 1 || key[KEY_ENTER]){guia = 1;play_sample(select, 100, 128, 1000, 0);}}
        else{menu_dir[0] = 0;}
		masked_blit(guias, buffer,   0, menu_dir[0], 306, 110, 288, 62);
		
		
		
		//como jogar
		if(colidir(mouse_x, mouse_y, 306, 190, 10, 10, 288, 62)){
							menu_dir[1] = 62; 
							if(mouse_b == 1 || key[KEY_ENTER]){guia = 2;play_sample(select, 100, 128, 1000, 0);}}
        else{menu_dir[1] = 0;}
		masked_blit(guias, buffer, 288, menu_dir[1], 306, 190, 288, 62);
		
		//sobre
		if(colidir(mouse_x, mouse_y, 306, 270, 10, 10, 288, 62)){
							menu_dir[2] = 62; 
							if(mouse_b == 1 || key[KEY_ENTER]){guia = 3;play_sample(select, 100, 128, 1000, 0);}}
        else{menu_dir[2] = 0;}
		masked_blit(guias, buffer, 576, menu_dir[2], 306, 270, 288, 62);
		
        //sair
		if(colidir(mouse_x, mouse_y, 306, 350, 10, 10, 288, 62)){
							menu_dir[3] = 62;
							fechar = mouse_b;}
        else{menu_dir[3] = 0;}
		masked_blit(guias, buffer, 864, menu_dir[3], 306, 350, 288, 62);
		 
		break;
            case 1:
				 controle[0] = 0;
				 stop_sample(musicaMenu);
				  switch(fase){
				  			   case 0:
							   		if(fase == 0 && controle[1] == 0){play_sample(musicafase1, 40, 128, 1000, 1);controle[1]+=1;}
							   		
				 //fundo do jogo
				 draw_sprite(buffer, bg01, 0, 0);
				
				 //função que invoca o player
                 jogador();
                 
                 	//chão e colisão com o chão=====================================================
                 	//chão esquerdo 
		for(i = 0;i < 6; i++){
              masked_blit(tileFase1, buffer, tile.wx+35, tile.wy, 35*i, tile.y+420, tile.w, tile.h);
            if(colidir(p.x, p.y, 34*i, 410, p.w, p.h, 35, 35)){p.y = 420 - p.h; caindo = 0;}
              }
              masked_blit(tileFase1, buffer, tile.wx+2*35, tile.wy, 210, tile.y+420, tile.w, tile.h);
              
              //agua
       for(i = 0;i < 16; i++){
              masked_blit(tileFase1, buffer, tile.wx+16*35, tile.wy, 244+35*i, tile.y+420, tile.w, tile.h);
              }
              
              //chão direita
       for(i = 0;i < 5; i++){
              masked_blit(tileFase1, buffer, tile.wx+1*35, tile.wy, 839+35*i, tile.y+385, tile.w, tile.h);
            if(colidir(p.x, p.y, 820+35*i, tile.y+385, p.w, p.h, 40, 35)){p.y = 386 - p.h; caindo = 0;}
              }
              masked_blit(tileFase1, buffer, tile.wx, tile.wy, 629+35*i, tile.y+385, tile.w, tile.h);
              
              masked_blit(tileFase1, buffer, tile.wx+35*3, tile.wy, 629+35*i, tile.y+420, tile.w, tile.h);
              masked_blit(tileFase1, buffer, tile.wx+35*4, tile.wy, 664+35*i, tile.y+420, tile.w, tile.h);
              masked_blit(tileFase1, buffer, tile.wx+35*4, tile.wy, 699+35*i, tile.y+420, tile.w, tile.h);
              masked_blit(tileFase1, buffer, tile.wx+35*4, tile.wy, 734+35*i, tile.y+420, tile.w, tile.h);
              
              //parte das plataformas
        masked_blit(tileFase1, buffer, tile.wx + 12*35, tile.wy, 275+35, tile.y+318, tile.w*3, tile.h);
          if(colidir(p.x, p.y, 275+49, 317, p.w, p.h, 80, 5)){p.y = 320 - p.h; caindo = 0;}
        
        masked_blit(tileFase1, buffer, tile.wx + 12*35, tile.wy, 300+35, tile.y+130, tile.w*3, tile.h);
         if(colidir(p.x, p.y, 350, 130, p.w, p.h, 80, 5)){p.y = 131 - p.h; caindo = 0;}
        
        masked_blit(tileFase1, buffer, tile.wx + 12*35, tile.wy, 55+35, tile.y+226, tile.w*3, tile.h);
         if(colidir(p.x, p.y, 105, 225, p.w, p.h, 80, 5)){p.y = 226 - p.h; caindo = 0;}
         
        masked_blit(tileFase1, buffer, tile.wx + 12*35, tile.wy, 570+35, tile.y+176, tile.w*3, tile.h);
         if(colidir(p.x, p.y, 580+35, 176, p.w, p.h, 80, 5)){p.y = 177 - p.h; caindo = 0;}
              
              //======================================================================================
             //inimigo 1
             if(enemy_x[1] < 400 && mov_auto[1] == 100){enemy_x[1]+=3;enemy_wy[1] = 40;}
             else if(enemy_x[1] > 300 && mov_auto[1] ==101){enemy_x[1]-=3;enemy_wy[1] = 0;}
             else if(mov_auto[1] == 100)mov_auto[1]++;
             else if(mov_auto[1] == 101 && enemy_x[1] == 300)mov_auto[1]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[1], enemy_y[1]-5, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[1] += 80;
							   pontos +=10;
                               if(enemy_wx[1] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[1] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[1], enemy_y[1]-5, p.x, p.y, enemy_w[1]-10, enemy_h[1], p.w-15, p.h-15)){
			  						 play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[1], enemy_wy[1], enemy_x[1], enemy_y[1]-5, enemy_w[1], enemy_h[1]);  
			
			//inimigo  2
	         if(enemy_x[2] < 400 && mov_auto[2] == 100){enemy_x[2]+=3;enemy_wy[2] = 40;}
             else if(enemy_x[2] > 300 && mov_auto[2] ==101){enemy_x[2]-=3;enemy_wy[2] = 0;}
             else if(mov_auto[2] == 100)mov_auto[2]++;
             else if(mov_auto[2] == 101 && enemy_x[2] == 300)mov_auto[2]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[2]-225, enemy_y[2]-100, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[2] += 80;
							   pontos +=10;
                               if(enemy_wx[2] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[2] = 1000;}}
			 
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[2]-225, enemy_y[2]-100, p.x, p.y, enemy_w[2]-10, enemy_h[2], p.w-15, p.h-15)){
			  							 play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			 if(enemy_wx[2] == 160){enemy_y[2] = 1000;}
			
			masked_blit(inimigo, buffer, enemy_wx[2], enemy_wy[2], enemy_x[2]-225, enemy_y[2]-100, enemy_w[2], enemy_h[2]);  
			
			//inimigo 3
			 if(enemy_x[3] < 400 && mov_auto[3] == 100){enemy_x[3]+=3;enemy_wy[3] = 40;}
             else if(enemy_x[3] > 300 && mov_auto[3] ==101){enemy_x[3]-=3;enemy_wy[3] = 0;}
             else if(mov_auto[3] == 100)mov_auto[3]++;
             else if(mov_auto[3] == 101 && enemy_x[3] == 300)mov_auto[3]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[3]+20, enemy_y[3]-195, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[3] += 80;
							   pontos +=10;
                               if(enemy_wx[3] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[3] = 1000;}}
			 
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[3]+20, enemy_y[3]-195, p.x, p.y, enemy_w[3]-10, enemy_h[3], p.w-15, p.h-15)){
			  							play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			 if(enemy_wx[3] == 160){enemy_y[3] = 1000;}
			
			masked_blit(inimigo, buffer, enemy_wx[3], enemy_wy[3], enemy_x[3]+20, enemy_y[3]-195, enemy_w[3], enemy_h[3]);  
			
			//inimigo 4
			if(enemy_x[4] < 400 && mov_auto[4] == 100){enemy_x[4]+=3;enemy_wy[4] = 40;}
             else if(enemy_x[4] > 300 && mov_auto[4] ==101){enemy_x[4]-=3;enemy_wy[4] = 0;}
             else if(mov_auto[4] == 100)mov_auto[4]++;
             else if(mov_auto[4] == 101 && enemy_x[4] == 300)mov_auto[4]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[4]+285, enemy_y[4]-145, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[4] += 80;
							   pontos +=10;
                               if(enemy_wx[4] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[4] = 1000;}}
			 
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[4]+285, enemy_y[4]-145, p.x, p.y, enemy_w[4]-10, enemy_h[4], p.w-15, p.h-15)){
			  							 play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			 if(enemy_wx[4] == 160){enemy_y[4] = 1000;}
			
			masked_blit(inimigo, buffer, enemy_wx[4], enemy_wy[4], enemy_x[4]+285, enemy_y[4]-145, enemy_w[4], enemy_h[4]);  
			
			//inimigo 5
			if(enemy_x[5] < 400 && mov_auto[5] == 100){enemy_x[5]+=3;enemy_wy[5] = 40;}
             else if(enemy_x[5] > 300 && mov_auto[5] ==101){enemy_x[5]-=3;enemy_wy[5] = 0;}
             else if(mov_auto[5] == 100)mov_auto[5]++;
             else if(mov_auto[5] == 101 && enemy_x[5] == 300)mov_auto[5]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[5]+485, enemy_y[5]+60, tiro.w, tiro.h, 30, 17)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[5] += 80;
							   pontos +=10;
                               if(enemy_wx[5] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[5] = 1000;}}
			 
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[5]+485, enemy_y[5]+60, p.x, p.y, enemy_w[5]-10, enemy_h[5], p.w-15, p.h-15)){
			  							 play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			 if(enemy_wx[5] == 160){enemy_y[5] = 1000;}
			
			masked_blit(inimigo, buffer, enemy_wx[5], enemy_wy[5], enemy_x[5]+485, enemy_y[5]+60, enemy_w[5], enemy_h[5]); 
        	
        	          break;
        	     case 1:
				 	  //fundo do jogo
				 draw_sprite(buffer, bg01, 0, 0);
				 
				 //função que invoca o player
                 jogador();
				 	  
				 	  //chão e colisão com o chão=====================================================
				 	  for(i = 0; i < 27; i++){
					  		masked_blit(tileFase1, buffer, tile.wx + 17*35, tile.wy, 35*i, tile.y+415, tile.w, tile.h);
					  		masked_blit(tileFase1, buffer, tile.wx + 16*35, tile.wy, 35*i, tile.y+380, tile.w, tile.h);
							  }

	            	masked_blit(tileFase1, buffer, tile.wx + 12*35, tile.wy, 5, tile.y+320, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 15, 320, p.w, p.h, 80, 5)){p.y = 321 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase1, buffer, tile.wx + 12*35, tile.wy, 160, tile.y+260, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 170, 260, p.w, p.h, 75, 5)){p.y = 261 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase1, buffer, tile.wx + 12*35, tile.wy, 300, tile.y+180, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 315, 180, p.w, p.h, 75, 5)){p.y = 181 - p.h; caindo = 0;} 
                    
                    masked_blit(tileFase1, buffer, tile.wx + 12*35, tile.wy, 115, tile.y+120, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 125, 120, p.w, p.h, 75, 5)){p.y = 121 - p.h; caindo = 0;}
                    //====================algoritmo que faz a plataforma subir e descer
              //subir e descer da plataforma e mov do enemy
              if(tile_y[0] < 350 && mov_auto[0] == 100){tile_y[0]+=3; enemy_y[7] +=3;
			           if(colidir(p.x, p.y, 530, tile_y[0], p.w, p.h, 80, 5)){p.y = tile_y[0]+4 - p.h; caindo = 0;}}
             else if(tile_y[0] > 120 && mov_auto[0] ==101){tile_y[0]-=3; enemy_y[7] -=3;
			           if(colidir(p.x, p.y, 530, tile_y[0], p.w, p.h, 80, 5)){p.y = tile_y[0]-2 - p.h; caindo = 0;}
			 }
             else if(mov_auto[0] == 100)mov_auto[0]++;
             else if(mov_auto[0] == 101 && tile_y[0] == 120)mov_auto[0]--;
             
              if(enemy_x[7] < 400 && mov_auto[7] == 100){enemy_x[7]+=3;enemy_wy[7] = 40;}
             else if(enemy_x[7] > 300 && mov_auto[7] ==101){enemy_x[7]-=3;enemy_wy[7] = 0;}
             else if(mov_auto[7] == 100)mov_auto[7]++;
             else if(mov_auto[7] == 101 && enemy_x[7] == 300)mov_auto[7]--;
                    
                    masked_blit(tileFase1, buffer, tile.wx + 12*35, tile.wy, 520, tile_y[0], tile.w*3, tile.h);
            
            if(colidir(tiro.x, tiro.y, enemy_x[7]+210, enemy_y[7]-200, tiro.w, tiro.h, 30, 25)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[7] += 80;
							   pontos +=10;
                               if(enemy_wx[7] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[7] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[7]+210, enemy_y[7]-200, p.x, p.y, enemy_w[7]-10, enemy_h[7], p.w-15, p.h-15)){
			  							 play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[7], enemy_wy[7], enemy_x[7]+205, enemy_y[7]-200, enemy_w[7], enemy_h[7]); 
                    //====================
                    
					masked_blit(tileFase1, buffer, tile.wx + 0*35, tile.wy, 815, tile.y+355, tile.w*3, tile.h);
					masked_blit(tileFase1, buffer, tile.wx + 3*35, tile.wy, 815, tile.y+390, tile.w*3, tile.h);
					masked_blit(tileFase1, buffer, tile.wx + 3*35, tile.wy, 815, tile.y+425, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 830, 355, p.w, p.h, 80, 5)){p.y = 356 - p.h; caindo = 0;}
              
        	//inimigos e seus respectivos scripts
             //inimigo 1
             if(enemy_x[6] < 400 && mov_auto[8] == 100){enemy_x[6]+=3;enemy_wy[6] = 40;}
             else if(enemy_x[6] > 300 && mov_auto[8] ==101){enemy_x[6]-=3;enemy_wy[6] = 0;}
             else if(mov_auto[8] == 100)mov_auto[8]++;
             else if(mov_auto[8] == 101 && enemy_x[6] == 300)mov_auto[8]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[6]-160, enemy_y[6]-60, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[6] += 80;
							   pontos +=10;
                               if(enemy_wx[6] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[6] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[6]-160, enemy_y[6]-60, p.x, p.y, enemy_w[6]-10, enemy_h[6], p.w-15, p.h-15)){
			  							 play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[6], enemy_wy[6], enemy_x[6]-160, enemy_y[6]-60, enemy_w[6], enemy_h[6]);   
			
			//inimigo 2
             if(enemy_x[9] < 400 && mov_auto[9] == 100){enemy_x[9]+=3;enemy_wy[9] = 40;}
             else if(enemy_x[9] > 300 && mov_auto[9] ==101){enemy_x[9]-=3;enemy_wy[9] = 0;}
             else if(mov_auto[9] == 100)mov_auto[9]++;
             else if(mov_auto[9] == 101 && enemy_x[9] == 300)mov_auto[9]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[9]-200, enemy_y[9]-200, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[9] += 80;
							   pontos +=10;
                               if(enemy_wx[9] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[9] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[9]-200, enemy_y[9]-200, p.x, p.y, enemy_w[9]-10, enemy_h[9], p.w-15, p.h-15)){
			  							 play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[9], enemy_wy[9], enemy_x[9]-200, enemy_y[9]-200, enemy_w[9], enemy_h[9]);
			
			//inimigo 3
             if(enemy_x[10] < 400 && mov_auto[10] == 100){enemy_x[10]+=3;enemy_wy[10] = 40;}
             else if(enemy_x[10] > 300 && mov_auto[10] ==101){enemy_x[10]-=3;enemy_wy[10] = 0;}
             else if(mov_auto[10] == 100)mov_auto[10]++;
             else if(mov_auto[10] == 101 && enemy_x[10] == 300)mov_auto[10]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[10]-25, enemy_y[10]-140, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[10] += 80;
							   pontos +=10;
                               if(enemy_wx[10] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[10] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[10]-25, enemy_y[10]-140, p.x, p.y, enemy_w[10]-10, enemy_h[10], p.w-15, p.h-15)){
			  							 play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[10], enemy_wy[10], enemy_x[10]-25, enemy_y[10]-140, enemy_w[10], enemy_h[10]);
			
			
			//inimigo 5
             if(enemy_x[8] < 400 && mov_auto[11] == 100){enemy_x[8]+=3;enemy_wy[8] = 40;}
             else if(enemy_x[8] > 300 && mov_auto[11] ==101){enemy_x[8]-=3;enemy_wy[8] = 0;}
             else if(mov_auto[11] == 100)mov_auto[11]++;
             else if(mov_auto[11] == 101 && enemy_x[8] == 300)mov_auto[11]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[8]+490, enemy_y[8]+30, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[8] += 80;
							   pontos +=10;
                               if(enemy_wx[8] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[8] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[8]+490, enemy_y[8]+30, p.x, p.y, enemy_w[8]-10, enemy_h[8], p.w-15, p.h-15)){
			  							 play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[8], enemy_wy[8], enemy_x[8]+490, enemy_y[8]+30, enemy_w[8], enemy_h[8]);  
        	
				 	  break;
	             case 2: 
				 	  controle[1] = 0;
				 stop_sample(musicafase1);
				 if(fase == 2 && controle[2] == 0){play_sample(musicafase2, 100, 128, 1000, 1);controle[2]+=1;}
				 	  //background
				 	  draw_sprite(buffer, bg02, 0, 0);
				 	  jogador();
				 	  
			 	  	masked_blit(tileFase2, buffer, tile.wx + 6*35+1, tile.wy, 5, tile.y+350, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 15, 350, p.w, p.h, 80, 5)){p.y = 351 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase2, buffer, tile.wx + 6*35+1, tile.wy, 180, tile.y+240, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 200, 240, p.w, p.h, 70, 5)){p.y = 241 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase2, buffer, tile.wx + 6*35+1, tile.wy, 20, tile.y+135, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 40, 135, p.w, p.h, 75, 5)){p.y = 136 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase2, buffer, tile.wx + 0*35+1, tile.wy, 815, tile.y+415, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 820, 415, p.w, p.h, 75, 5)){p.y = 416 - p.h; caindo = 0;}
                    
                    //================================================================
                    if(tile_y[3] < 350 && mov_auto[13] == 100){tile_y[3]+=3;enemy_y[11]+=3;
			           if(colidir(p.x, p.y, 570, tile_y[3], p.w, p.h, 72, 5)){p.y = tile_y[3]+4 - p.h; caindo = 0;}}
        			   
              else if(tile_y[3] > 120 && mov_auto[13] ==101){tile_y[3]-=3;enemy_y[11]-=3;
			           if(colidir(p.x, p.y, 570, tile_y[3], p.w, p.h, 72, 5)){p.y = tile_y[3]-2 - p.h; caindo = 0;}}
        			   
             else if(mov_auto[13] == 100)mov_auto[13]++;
             else if(mov_auto[13] == 101 && tile_y[3] == 120)mov_auto[13]--;
             
              if(enemy_x[11] < 400 && mov_auto[12] == 100){enemy_x[11]+=3;enemy_wy[11] = 40;}
             else if(enemy_x[11] > 300 && mov_auto[12] ==101){enemy_x[11]-=3;enemy_wy[11] = 0;}
             else if(mov_auto[12] == 100)mov_auto[12]++;
             else if(mov_auto[12] == 101 && enemy_x[11] == 300)mov_auto[12]--;
                    
                    masked_blit(tileFase2, buffer, tile.wx + 6*35.3, tile.wy, 560, tile_y[3], tile.w*3, tile.h);
            
            if(colidir(tiro.x, tiro.y, enemy_x[11]+245, enemy_y[11]-200, tiro.w, tiro.h, 30, 25)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[11] += 80;
							   pontos +=10;
                               if(enemy_wx[11] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[11] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[11]+245, enemy_y[11]-200, p.x, p.y, enemy_w[11]-10, enemy_h[11], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;}
             
			masked_blit(inimigo, buffer, enemy_wx[11], enemy_wy[11], enemy_x[11]+245, enemy_y[11]-200, enemy_w[11], enemy_h[11]); 
			       //================================================================
			      if(enemy_x[12] < 400 && mov_auto[14] == 100){enemy_x[12]+=3;enemy_wy[12] = 40;}
             else if(enemy_x[12] > 300 && mov_auto[14] ==101){enemy_x[12]-=3;enemy_wy[12] = 0;}
             else if(mov_auto[14] == 100)mov_auto[14]++;
             else if(mov_auto[14] == 101 && enemy_x[12] == 300)mov_auto[14]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[12]+490, enemy_y[12]+95, tiro.w, tiro.h, 30, 20)){
							   atirar = 0;
							   enemy_wx[12] += 80;
							   pontos +=10;
                               if(enemy_wx[12] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[12] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[12]+490, enemy_y[12]+95, p.x, p.y, enemy_w[12]-10, enemy_h[12], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[12], enemy_wy[12], enemy_x[12]+490, enemy_y[12]+95, enemy_w[12], enemy_h[12]); 
			      //================================================================
			      if(enemy_x[13] < 400 && mov_auto[15] == 100){enemy_x[13]+=3;enemy_wy[13] = 40;}
             else if(enemy_x[13] > 300 && mov_auto[15] ==101){enemy_x[13]-=3;enemy_wy[13] = 0;}
             else if(mov_auto[15] == 100)mov_auto[15]++;
             else if(mov_auto[15] == 101 && enemy_x[13] == 300)mov_auto[15]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[13]-130, enemy_y[13]-85, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[13] += 80;
							   pontos +=10;
                               if(enemy_wx[13] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[13] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[13]-130, enemy_y[13]-85, p.x, p.y, enemy_w[13]-10, enemy_h[13], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[13], enemy_wy[13], enemy_x[13]-130, enemy_y[13]-85, enemy_w[13], enemy_h[13]); 
			      //================================================================
			      if(enemy_x[14] < 400 && mov_auto[16] == 100){enemy_x[14]+=3;enemy_wy[14] = 40;}
             else if(enemy_x[14] > 300 && mov_auto[16] ==101){enemy_x[14]-=3;enemy_wy[14] = 0;}
             else if(mov_auto[16] == 100)mov_auto[16]++;
             else if(mov_auto[16] == 101 && enemy_x[14] == 300)mov_auto[16]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[14]-305, enemy_y[14]-190, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[14] += 80;
							   pontos +=10;
                               if(enemy_wx[14] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[14] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[14]-305, enemy_y[14]-190, p.x, p.y, enemy_w[14]-10, enemy_h[14], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[14], enemy_wy[14], enemy_x[14]-305, enemy_y[14]-190, enemy_w[14], enemy_h[14]); 
			      //================================================================
			      
					   
	  if(tile_y[2] < 350 && mov_auto[17] == 101){tile_y[2]+=3;
			           if(colidir(p.x, p.y, 370, tile_y[2], p.w, p.h, 70, 5)){p.y = tile_y[2]+6 - p.h; caindo = 0;}}
        			   
   else if(tile_y[2] > 120 && mov_auto[17] == 100){tile_y[2]-=3;
			           if(colidir(p.x, p.y, 370, tile_y[2], p.w, p.h, 70, 5)){p.y = tile_y[2]-2 - p.h; caindo = 0;}}
              else if(mov_auto[17] == 101 && tile_y[2] == 350){mov_auto[17]-=1;}
              else if(mov_auto[17] == 100){mov_auto[17]+=1;}
              
                    
                    masked_blit(tileFase2, buffer, tile.wx + 6*35.3, tile.wy, 350, tile_y[2], tile.w*3, tile.h);
              if(enemy_x[15] < 900){      
            if(enemy_x[15] < 400 && mov_auto[18] == 100){enemy_x[15]+=3;enemy_wy[15] = 40;}
             else if(enemy_x[15] > 300 && mov_auto[18] ==101){enemy_x[15]-=3;enemy_wy[15] = 0;}
             else if(mov_auto[18] == 100)mov_auto[18]++;
             else if(mov_auto[18] == 101 && enemy_x[15] == 300)mov_auto[18]--;}
             
            if(colidir(tiro.x, tiro.y, enemy_x[15]+35, tile_y[2]-50, tiro.w, tiro.h, 30, 25)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[15] += 80;
							   pontos +=10;
                               if(enemy_wx[15] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_x[15] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[15]+35, tile_y[2]-50, p.x, p.y, enemy_w[15]-10, enemy_h[15], p.w-15, p.h-15)){
				                    play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;}
             
			masked_blit(inimigo, buffer, enemy_wx[15], enemy_wy[15], enemy_x[15]+35, tile_y[2]-50, enemy_w[15], enemy_h[15]); 
					   
				 	  break;
	             case 3: 
				 	  draw_sprite(buffer, bg02, 0, 0);
				 	  jogador();
				 	  
				 	//plataforma 1  
			 	    masked_blit(tileFase2, buffer, tile.wx + 6*35+1, tile.wy, 5, tile.y+320, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 15, 320, p.w, p.h, 80, 5)){p.y = 321 - p.h; caindo = 0;}
                    
                    //plataforma automatica 1
                     if(tile_y[4] < 350 && mov_auto[19] == 100){tile_y[4]+=3;
			           if(colidir(p.x, p.y, 170, tile_y[4], p.w, p.h, 72, 5)){p.y = tile_y[4]+4 - p.h; caindo = 0;}}
        			   
              else if(tile_y[4] > 120 && mov_auto[19] ==101){tile_y[4]-=3;
			           if(colidir(p.x, p.y, 170, tile_y[4], p.w, p.h, 72, 5)){p.y = tile_y[4]-2 - p.h; caindo = 0;}}
        			   
             else if(mov_auto[19] == 100)mov_auto[19]++;
             else if(mov_auto[19] == 101 && tile_y[4] == 120)mov_auto[19]--;
             
             if(enemy_x[17] < 1000){
              if(enemy_x[17] < 400 && mov_auto[20] == 100){enemy_x[17]+=3;enemy_wy[17] = 40;}
             else if(enemy_x[17] > 300 && mov_auto[20] ==101){enemy_x[17]-=3;enemy_wy[17] = 0;}
             else if(mov_auto[20] == 100)mov_auto[20]++;
             else if(mov_auto[20] == 101 && enemy_x[17] == 300)mov_auto[20]--;}
                    
                    masked_blit(tileFase2, buffer, tile.wx + 6*35.3, tile.wy, 160, tile_y[4], tile.w*3, tile.h);
            
            if(colidir(tiro.x, tiro.y, enemy_x[17]-160, tile_y[4]-50, tiro.w, tiro.h, 30, 25)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[17] += 80;
							   pontos +=10;
                               if(enemy_wx[17] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_x[17] = 2000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[17]-160, tile_y[4]-50, p.x, p.y, enemy_w[17]-10, enemy_h[17], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;}
             
			masked_blit(inimigo, buffer, enemy_wx[17], enemy_wy[17], enemy_x[17]-160, tile_y[4]-50, enemy_w[17], enemy_h[17]); 
                    
                    
                    //plataforma 2
			 	    masked_blit(tileFase2, buffer, tile.wx + 6*35+1, tile.wy, 330, tile.y+360, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 340, 360, p.w, p.h, 80, 5)){p.y = 361 - p.h; caindo = 0;}
                    
                     if(enemy_x[16] < 400 && mov_auto[26] == 100){enemy_x[16]+=3;enemy_wy[16] = 40;}
             else if(enemy_x[16] > 300 && mov_auto[26] ==101){enemy_x[16]-=3;enemy_wy[16] = 0;}
             else if(mov_auto[26] == 100)mov_auto[26]++;
             else if(mov_auto[26] == 101 && enemy_x[16] == 300)mov_auto[26]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[16]+7, enemy_y[16]+38, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[16] += 80;
							   pontos +=10;
                               if(enemy_wx[16] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[16] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[16]+7, enemy_y[16]+38, p.x, p.y, enemy_w[16]-10, enemy_h[16], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[16], enemy_wy[16], enemy_x[16]+7, enemy_y[16]+38, enemy_w[16], enemy_h[16]); 
			      //================================================================
			      
			      //plataforma 3
			 	    masked_blit(tileFase2, buffer, tile.wx + 6*35+1, tile.wy, 480, tile.y+250, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 495, 250, p.w, p.h, 80, 5)){p.y = 251 - p.h; caindo = 0;}
                    
                     if(enemy_x[18] < 400 && mov_auto[27] == 100){enemy_x[18]+=4;enemy_wy[18] = 40;}
             else if(enemy_x[18] > 300 && mov_auto[27] ==101){enemy_x[18]-=4;enemy_wy[18] = 0;}
             else if(mov_auto[27] == 100)mov_auto[27]++;
             else if(mov_auto[27] == 101 && enemy_x[18] == 300)mov_auto[27]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[18]+160, enemy_y[18]-70, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[18] += 80;
							   pontos +=10;
                               if(enemy_wx[18] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[18] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[18]+160, enemy_y[18]-70, p.x, p.y, enemy_w[18]-10, enemy_h[18], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[18], enemy_wy[18], enemy_x[18]+160, enemy_y[18]-70, enemy_w[18], enemy_h[18]); 
			      //================================================================
			      
			      
			       //plataforma 4
			 	    masked_blit(tileFase2, buffer, tile.wx + 6*35+1, tile.wy, 650, tile.y+150, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 660, 150, p.w, p.h, 80, 5)){p.y = 151 - p.h; caindo = 0;}
                    
                     if(enemy_x[19] < 400 && mov_auto[28] == 100){enemy_x[19]+=4;enemy_wy[19] = 40;}
             else if(enemy_x[19] > 300 && mov_auto[28] ==101){enemy_x[19]-=4;enemy_wy[19] = 0;}
             else if(mov_auto[28] == 100)mov_auto[28]++;
             else if(mov_auto[28] == 101 && enemy_x[19] == 300)mov_auto[28]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[19]+350, enemy_y[19]-170, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[19] += 80;
							   pontos +=10;
                               if(enemy_wx[19] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[19] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[19]+350, enemy_y[19]-170, p.x, p.y, enemy_w[19]-10, enemy_h[19], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[19], enemy_wy[19], enemy_x[19]+350, enemy_y[19]-170, enemy_w[19], enemy_h[19]); 
			      //================================================================
			      
			      //plataforma 4
			 	    masked_blit(tileFase2, buffer, tile.wx + 6*35+1, tile.wy, 820, tile.y+200, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 830, 200, p.w, p.h, 80, 5)){p.y = 201 - p.h; caindo = 0;}
                    
                    
                     if(enemy_x[20] < 400 && mov_auto[29] == 100){enemy_x[20]+=5;enemy_wy[20] = 40;}
             else if(enemy_x[20] > 300 && mov_auto[29] ==101){enemy_x[20]-=5;enemy_wy[20] = 0;}
             else if(mov_auto[29] == 100)mov_auto[29]++;
             else if(mov_auto[29] == 101 && enemy_x[20] == 300)mov_auto[29]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[20]+485, enemy_y[20]-120, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[20] += 80;
							   pontos +=10;
                               if(enemy_wx[20] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[20] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[20]+485, enemy_y[20]-120, p.x, p.y, enemy_w[20]-10, enemy_h[20], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[20], enemy_wy[20], enemy_x[20]+485, enemy_y[20]-120, enemy_w[20], enemy_h[20]); 
				 	  
				 	  break;
	             case 4: 
	             controle[2] = 0;
				 stop_sample(musicafase2);
				 if(fase == 4 && controle[3] == 0){play_sample(musicafase3, 100, 128, 1000, 1);controle[3]+=1;}
				 
				      draw_sprite(buffer, bg03, 0, 0);
				      jogador();
				      //plataformas
                    masked_blit(tileFase3, buffer, tile.wx + 0*35, tile.wy, 0, tile.y+400, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 10, 400, p.w, p.h, 80, 10)){p.y = 401 - p.h; caindo = 0;}
                    
                     masked_blit(tileFase3, buffer, tile.wx + 0*35, tile.wy, 150, tile.y+300, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 160, 300, p.w, p.h, 80, 10)){p.y = 301 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase3, buffer, tile.wx + 0*35, tile.wy, 300, tile.y+200, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 320, 200, p.w, p.h, 75, 10)){p.y = 201 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase3, buffer, tile.wx + 0*35, tile.wy, 450, tile.y+100, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 465, 100, p.w, p.h, 75, 10)){p.y = 101 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase3, buffer, tile.wx + 0*35, tile.wy, 610, tile.y+170, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 625, 170, p.w, p.h, 75, 10)){p.y = 171 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase3, buffer, tile.wx + 0*35, tile.wy, 820, tile.y+250, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 836, 250, p.w, p.h, 75, 10)){p.y = 251 - p.h; caindo = 0;}
                    
				 //inimigo 1
				  if(enemy_x[21] < 400 && mov_auto[21] == 100){enemy_x[21]+=4;enemy_wy[21] = 40;}
             else if(enemy_x[21] > 300 && mov_auto[21] ==101){enemy_x[21]-=4;enemy_wy[21] = 0;}
             else if(mov_auto[21] == 100)mov_auto[21]++;
             else if(mov_auto[21] == 101 && enemy_x[21] == 300)mov_auto[21]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[21]-160, enemy_y[21]-20, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[21] += 80;
							   pontos +=10;
                               if(enemy_wx[21] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[21] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[21]-160, enemy_y[21]-20, p.x, p.y, enemy_w[21]-10, enemy_h[21], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
			 						p.y = 280;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[21], enemy_wy[21], enemy_x[21]-160, enemy_y[21]-20, enemy_w[21], enemy_h[21]); 
			
			//inimigo 2
			if(enemy_x[22] < 400 && mov_auto[22] == 100){enemy_x[22]+=5;enemy_wy[22] = 40;}
             else if(enemy_x[22] > 300 && mov_auto[22] ==101){enemy_x[22]-=5;enemy_wy[22] = 0;}
             else if(mov_auto[22] == 100)mov_auto[22]++;
             else if(mov_auto[22] == 101 && enemy_x[22] == 300)mov_auto[22]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[22]-20, enemy_y[22]-120, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[22] += 80;
							   pontos +=10;
                               if(enemy_wx[22] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[22] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[22]-20, enemy_y[22]-120, p.x, p.y, enemy_w[21]-10, enemy_h[22], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[22], enemy_wy[22], enemy_x[22]-20, enemy_y[22]-120, enemy_w[22], enemy_h[22]); 
			
			//inimigo 3
			if(enemy_x[23] < 400 && mov_auto[23] == 100){enemy_x[23]+=6;enemy_wy[23] = 40;}
             else if(enemy_x[23] > 300 && mov_auto[23] ==101){enemy_x[23]-=6;enemy_wy[23] = 0;}
             else if(mov_auto[23] == 100)mov_auto[23]++;
             else if(mov_auto[23] == 101 && enemy_x[23] == 300)mov_auto[23]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[23]+130, enemy_y[23]-220, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[23] += 80;
							   pontos +=10;
                               if(enemy_wx[23] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[23] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[23]+130, enemy_y[23]-220, p.x, p.y, enemy_w[23]-10, enemy_h[23], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[23], enemy_wy[23], enemy_x[23]+130, enemy_y[23]-220, enemy_w[23], enemy_h[23]); 
				 
				 	//inimigo 4
			if(enemy_x[24] < 400 && mov_auto[24] == 100){enemy_x[24]+=7;enemy_wy[24] = 40;}
             else if(enemy_x[24] > 300 && mov_auto[24] ==101){enemy_x[24]-=7;enemy_wy[24] = 0;}
             else if(mov_auto[24] == 100)mov_auto[24]++;
             else if(mov_auto[24] == 101 && enemy_x[24] == 300)mov_auto[24]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[24]+290, enemy_y[24]-150, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[24] += 80;
							   pontos +=10;
                               if(enemy_wx[24] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[24] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[24]+290, enemy_y[24]-150, p.x, p.y, enemy_w[24]-10, enemy_h[24], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[24], enemy_wy[24], enemy_x[24]+290, enemy_y[24]-150, enemy_w[24], enemy_h[24]); 
			
			//inimigo 5
			if(enemy_x[25] < 400 && mov_auto[25] == 100){enemy_x[25]+=7;enemy_wy[25] = 40;}
             else if(enemy_x[25] > 300 && mov_auto[25] ==101){enemy_x[25]-=7;enemy_wy[25] = 0;}
             else if(mov_auto[25] == 100)mov_auto[25]++;
             else if(mov_auto[25] == 101 && enemy_x[25] == 300)mov_auto[25]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[25]+500, enemy_y[25]-75, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[25] += 80;
							   pontos +=10;
                               if(enemy_wx[25] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[25] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[25]+500, enemy_y[25]-75, p.x, p.y, enemy_w[25]-10, enemy_h[25], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[25], enemy_wy[25], enemy_x[25]+500, enemy_y[25]-75, enemy_w[25], enemy_h[25]); 
				 
				 
				 	  break;
                 case 5: 
				 	  draw_sprite(buffer, bg03, 0, 0);
				 	  jogador();
				 	  
				 	  //plataformas
	 	            masked_blit(tileFase3, buffer, tile.wx + 0*35, tile.wy, 0, tile.y+400, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 10, 400, p.w, p.h, 80, 10)){p.y = 401 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase3, buffer, tile.wx + 0*35, tile.wy, 200, tile.y+300, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 210, 300, p.w, p.h, 80, 10)){p.y = 301 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase3, buffer, tile.wx + 0*35, tile.wy, 380, tile.y+200, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 390, 200, p.w, p.h, 80, 10)){p.y = 201 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase3, buffer, tile.wx + 0*35, tile.wy, 570, tile.y+150, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 580, 150, p.w, p.h, 80, 10)){p.y = 151 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase3, buffer, tile.wx + 0*35, tile.wy, 200, tile.y+100, tile.w*3, tile.h);
                    if(colidir(p.x, p.y, 210, 100, p.w, p.h, 80, 10)){p.y = 101 - p.h; caindo = 0;}
                    
                    masked_blit(tileFase3, buffer, tile.wx + 3*35, tile.wy, 680, tile.y+270, tile.w*2, tile.h);
                    for(i = 0; i < 6; i++){masked_blit(tileFase3, buffer, tile.wx + 4*35, tile.wy, 750+35*i, tile.y+270, tile.w*1, tile.h);}
                    if(colidir(p.x, p.y, 690, 270, p.w, p.h, 220, 10)){p.y = 271 - p.h; caindo = 0;}
                    masked_blit(tileFase3, buffer, tile.wx + 6*35, tile.wy, 680, tile.y+305, tile.w*2, tile.h);
                    for(i = 0; i < 6; i++){masked_blit(tileFase3, buffer, tile.wx + 7*35, tile.wy, 750+35*i, tile.y+305, tile.w*1, tile.h);}
                    masked_blit(tileFase3, buffer, tile.wx + 6*35, tile.wy, 680, tile.y+340, tile.w*2, tile.h);
                    for(i = 0; i < 6; i++){masked_blit(tileFase3, buffer, tile.wx + 7*35, tile.wy, 750+35*i, tile.y+340, tile.w*1, tile.h);}
                    masked_blit(tileFase3, buffer, tile.wx + 6*35, tile.wy, 680, tile.y+375, tile.w*2, tile.h);
                    for(i = 0; i < 6; i++){masked_blit(tileFase3, buffer, tile.wx + 7*35, tile.wy, 750+35*i, tile.y+375, tile.w*1, tile.h);}
                    masked_blit(tileFase3, buffer, tile.wx + 6*35, tile.wy, 680, tile.y+410, tile.w*2, tile.h);
                    for(i = 0; i < 6; i++){masked_blit(tileFase3, buffer, tile.wx + 7*35, tile.wy, 750+35*i, tile.y+410, tile.w*1, tile.h);}
                    masked_blit(tileFase3, buffer, tile.wx + 6*35, tile.wy, 680, tile.y+445, tile.w*2, tile.h);
                    for(i = 0; i < 6; i++){masked_blit(tileFase3, buffer, tile.wx + 7*35, tile.wy, 750+35*i, tile.y+445, tile.w*1, tile.h);}
                    
                    //inimigos
                    
                    	//inimigo 1
			if(enemy_x[26] < 400 && mov_auto[30] == 100){enemy_x[26]+=7;enemy_wy[26] = 40;}
             else if(enemy_x[26] > 300 && mov_auto[30] ==101){enemy_x[26]-=7;enemy_wy[26] = 0;}
             else if(mov_auto[30] == 100)mov_auto[30]++;
             else if(mov_auto[30] == 101 && enemy_x[26] == 300)mov_auto[30]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[26]-120, enemy_y[26]-20, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[26] += 80;
							   pontos +=10;
                               if(enemy_wx[26] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[26] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[26]-120, enemy_y[26]-20, p.x, p.y, enemy_w[26]-10, enemy_h[26], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[26], enemy_wy[26], enemy_x[26]-120, enemy_y[26]-20, enemy_w[26], enemy_h[26]); 
			
			//inimigo 2
			if(enemy_x[27] < 400 && mov_auto[31] == 100){enemy_x[27]+=7;enemy_wy[27] = 40;}
             else if(enemy_x[27] > 300 && mov_auto[31] ==101){enemy_x[27]-=7;enemy_wy[27] = 0;}
             else if(mov_auto[31] == 100)mov_auto[31]++;
             else if(mov_auto[31] == 101 && enemy_x[27] == 300)mov_auto[31]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[27]+70, enemy_y[27]-120, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[27] += 80;
							   pontos +=10;
                               if(enemy_wx[27] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[27] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[27]+70, enemy_y[27]-120, p.x, p.y, enemy_w[27]-10, enemy_h[27], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[27], enemy_wy[27], enemy_x[27]+70, enemy_y[27]-120, enemy_w[27], enemy_h[27]); 
			
			//inimigo 3
			if(enemy_x[28] < 400 && mov_auto[32] == 100){enemy_x[28]+=7;enemy_wy[28] = 40;}
             else if(enemy_x[28] > 300 && mov_auto[32] ==101){enemy_x[28]-=7;enemy_wy[28] = 0;}
             else if(mov_auto[32] == 100)mov_auto[32]++;
             else if(mov_auto[32] == 101 && enemy_x[28] == 300)mov_auto[32]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[28]-120, enemy_y[28]-220, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[28] += 80;
							   pontos +=10;
                               if(enemy_wx[28] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[28] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[28]-120, enemy_y[28]-220, p.x, p.y, enemy_w[28]-10, enemy_h[28], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[28], enemy_wy[28], enemy_x[28]-120, enemy_y[28]-220, enemy_w[28], enemy_h[28]); 
			
			//inimigo 4
			if(enemy_x[29] < 400 && mov_auto[33] == 100){enemy_x[29]+=7;enemy_wy[29] = 40;}
             else if(enemy_x[29] > 300 && mov_auto[33] ==101){enemy_x[29]-=7;enemy_wy[29] = 0;}
             else if(mov_auto[33] == 100)mov_auto[33]++;
             else if(mov_auto[33] == 101 && enemy_x[29] == 300)mov_auto[33]--;
             
            if(colidir(tiro.x, tiro.y, enemy_x[29]+250, enemy_y[29]-170, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[29] += 80;
							   pontos +=10;
                               if(enemy_wx[29] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_y[29] = 1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[29]+250, enemy_y[29]-170, p.x, p.y, enemy_w[29]-10, enemy_h[29], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[29], enemy_wy[29], enemy_x[29]+250, enemy_y[29]-170, enemy_w[29], enemy_h[29]);
			
			//inimigo 5
			if(enemy_x[30] != -1000){
			if(enemy_x[30] < 550 && mov_auto[34] == 100){enemy_x[30]+=12;enemy_wy[30] = 40;}
             else if(enemy_x[30] > 300 && mov_auto[34] ==101){enemy_x[30]-=12;enemy_wy[30] = 0;}
             else if(mov_auto[34] == 100)mov_auto[34]++;
             else if(mov_auto[34] == 101 && enemy_x[30] == 300)mov_auto[34]--;}
             
             if(enemy_y[30] < 290 && mov_auto[35] == 100){enemy_y[30]+=8;}
             else if(enemy_y[30] > 270 && mov_auto[35] ==101){enemy_y[30]-=8;}
             else if(mov_auto[35] == 100)mov_auto[35]++;
             else if(mov_auto[35] == 101 && enemy_y[30] == 270)mov_auto[35]--;
             
             
            if(colidir(tiro.x, tiro.y, enemy_x[30]+350, enemy_y[30]-65, tiro.w, tiro.h, 30, 20)){
							   play_sample(danoCoroninha, 200, 128, 1000, 0);
							   atirar = 0;
							   enemy_wx[30] += 80;
							   pontos +=10;
                               if(enemy_wx[30] >= 160){play_sample(musicaCoroninha, 100, 128, 1000, 0); enemy_x[30]=-1000;}}
                               
			 //mata o player ao tocar enemy
			  if(colidir(enemy_x[30]+350, enemy_y[30]-65, p.x, p.y, enemy_w[30]-10, enemy_h[30], p.w-15, p.h-15)){
			  							  play_sample(musicaMorte, 200, 128, 1000, 0);
			 						vidas-=1;
			 						caindo = 1;
			 						p.x = 0;
									 }
             
			masked_blit(inimigo, buffer, enemy_wx[30], enemy_wy[30], enemy_x[30]+350, enemy_y[30]-65, enemy_w[30], enemy_h[30]);
				 	  
				 	  break;
	            case 6:
					 //papel de parede
					 draw_sprite(buffer, bg, 0,0);
		 			
					 //faz o chão e a colisão dele com o player
					 for(i = 0; i < 27; i++){
					 	   masked_blit(tileFase3, buffer, tile.wx + 4*35, tile.wy, 35*i, tile.y+415, tile.w, tile.h);}
							if(colidir(p.x, p.y, 0, 415, p.w, p.h, 945, 35)){p.y = 416 - p.h; caindo = 0;}
							
					//faz a tranca de fase e a condição para desfaze-la
					if(vidas_boss != 0){
								  	//colisão do boss com o tiro do player
						if(colidir(chefe.x, chefe.y, tiro.x, tiro.y, chefe.w, chefe.h, tiro.w, tiro.h)){
						     atirar_boss = 1;
							 atirar = 0;
							 vidas_boss -=1;
							 play_sample(danoboss, 200, 128, 1000, 0);
							 if(dir_boss == 0){dir_boss = -2;}
							 else if(dir_boss == -1){dir_boss = -3;}
							 }	
							 	
			       masked_blit(tileFase3, buffer, tile.wx + 3*35, tile.wy, 885, tile.y+320, tile.w, tile.h);
			       masked_blit(tileFase3, buffer, tile.wx + 6*35, tile.wy, 885, tile.y+355, tile.w, tile.h);	
		           masked_blit(tileFase3, buffer, tile.wx + 6*35, tile.wy, 885, tile.y+390, tile.w, tile.h);
		           if(p.x > 845){p.x -= 12;}}
		           
						//chefão 	  
		 	masked_blit(boss, buffer, chefe.wx+nTile_boss*116, chefe.wy-dir_boss*107, chefe.x, chefe.y, chefe.w-5, chefe.h);
						//colisão do player com o boss
						if(colidir(p.x, p.y, chefe.x, chefe.y, p.w, p.h, chefe.w, chefe.h)){
										play_sample(danoCoroninha, 200, 128, 1000, 0);
										vidas--;
										p.x = 0;
										}
										
					    if(vidas_boss == 0){
									 if(controle[6] == 0){ play_sample(morteboss, 200, 128, 1000, 0);controle[6]++;}
									  chefe.y = 2000;}
						
						
              //sistema de tiro do boss	
              //ele atira quando a posição estiver igual a posição descrita em !atirar_boss
       	if(chefe_tiro.x == chefe.x-10 && chefe_tiro.y == chefe.y+70){atirar_boss = 1;}
       	
        if(atirar_boss){chefe_tiro.x -=25;}	
        if(chefe_tiro.x > 900 || chefe_tiro.x < 0){atirar_boss = 0;}		 
        if(!atirar_boss){chefe_tiro.x = chefe.x-10; chefe_tiro.y = chefe.y+70;}	
		 masked_blit(tiroboss, buffer, chefe_tiro.wx, chefe_tiro.wy, chefe_tiro.x, chefe_tiro.y, chefe_tiro.w, chefe_tiro.h); 
		 
		 //limita a animação do tiro do inimigo
		 if(chefe_tiro.wx > 120){chefe_tiro.wx = 0;}
					
			//ele se movimenta até que as vidas sejam zero			
		   	 if(vidas != 0){			
			 if(chefe.x < 765 && mov_auto[36] == 100){chefe.x +=8;nTile_boss += 1; dir_boss = 0; chefe_tiro.wx +=30;}
             else if(chefe.x > 200 && mov_auto[36] ==101){chefe.x -=8;nTile_boss += 1; dir_boss = -1; chefe_tiro.wx +=30;}
             else if(mov_auto[36] == 100)mov_auto[36]++;
             else if(mov_auto[36] == 101 && chefe.x == 200)mov_auto[36]--;}	
             
             //colisão tiro do boss com o player
			 if(colidir(chefe_tiro.x, chefe_tiro.y, p.x, p.y, chefe_tiro.w, chefe_tiro.h, p.w, p.h)){
                  play_sample(tirotocou, 200, 128, 1000, 0);
				  atirar_boss = 0;
			 	  vidas--;
			 	  p.x = 0;}	 
			 	  
						//limita a animação do boss dentro do tile
						if(nTile_boss < 0){nTile_boss = 3;}
						else if(nTile_boss > 2){nTile_boss = 0;}
 		
		
 		
 		//mostra as vidas do chefão e também invoca o jogador
		 textprintf_ex(buffer, font, 340, 440, makecol(255, 255, 255), -1, "VIDAS DO CHEFAO FINAL: %i",vidas_boss);
		 jogador();
				 	  break;
		 	  case 7:
			  	   controle[3] = 0;
                   stop_sample(musicafase3);
                      
					if(controle[5] == 0 && fase == 7){play_sample(musicafinal, 120, 128, 1000, 1);controle[5]+=1;}
					
					 draw_sprite(buffer, final, 0, 0);
					  if(colidir(mouse_x, mouse_y, 825, 400, 10, 10, 85, 38)){
				 					 botMenu_troca = 100;
			                         if(mouse_b == 1 || key[KEY_ENTER]){
									 			play_sample(select, 100, 128, 1000, 0);
									 			guia = 4; 
										        mouse_b = 0;}}
                 else{botMenu_troca = 0;}
                 masked_blit(botMenu, buffer, botMenu_troca, 0, 825, 400, 100, 55);
                 
			  	   
			  	   break;}
			
                 rest(50);
                 
                 break;
	        case 2:
				 draw_sprite(buffer, sobreFundo, 0, 0);
			     if(colidir(mouse_x, mouse_y, 820, -5, 10, 10, 85, 38)){
				 					 botMenu_troca = 100;
						             if(mouse_b == 1 || key[KEY_ENTER]){
									 			play_sample(select, 100, 128, 1000, 0);guia = 4;
									 			guia = 0; 
										        mouse_b = 0;
												rest(30);}}
                 else{botMenu_troca = 0;}
                 masked_blit(botMenu, buffer, botMenu_troca, 0, 820, -5, 100, 55);
                 draw_sprite(buffer, comoJogar, 160, 120);
                 draw_sprite(buffer, titulo, 183, 15);
                 textout_ex(buffer, font, "VERSAO 1.0 BETA", 10, 10, makecol(255,255,255), -1);
                 
	    break;
	        case 3:
		         draw_sprite(buffer, sobreFundo, 0, 0);
				 if(colidir(mouse_x, mouse_y, 820, -5, 10, 10, 85, 38)){
				 					 botMenu_troca = 100;
			                         if(mouse_b == 1 || key[KEY_ENTER]){
									 			play_sample(select, 100, 128, 1000, 0);guia = 4;
									 			guia = 4; 
										        mouse_b = 0;}}
                 else{botMenu_troca = 0;}
                 masked_blit(botMenu, buffer, botMenu_troca, 0, 820, -5, 100, 55);
                 
                 draw_sprite(buffer, titulo, 183, 15);
                 draw_sprite(buffer, textoSobre, 125, 80);
                 textout_ex(buffer, font, "VERSAO 1.0 BETA", 10, 10, makecol(255,255,255), -1);
	    break;
	       case 4:
   		
 		         stop_sample(musicafase1);
				 stop_sample(musicafase2);
				 stop_sample(musicafase3);
				 stop_sample(musicafinal);
tile_y[0] = 120; tile_y[1] = 120; tile_y[2] = 350; tile_y[3] = 120; tile_y[4] = 420;
chefe.x   = 200; 
chefe.y   = 305;			 
vidas_boss = 10;
p.x = 0;
p.y = 280;
guia = 0;
fase = 0;
pontos = 0;
vidas = 3;
i = 0;
mov_menuX = -900;
mov_menuSobre = -1300;
fechar = 0, sai    = 0;
botMenu_troca = 0;
grv = 3;
caindo = 1;
vup = 10;
for(i = 0; i < 35; i++){
	enemy_x[i] = 300;
	enemy_y[i] = 270;
	enemy_wx[i] = 0;
	enemy_wy[i] = 0;
	enemy_w[i] = 40;
	enemy_h[i] = 40;}
for(i = 1; i < 10; i++){controle[i] = 0;}

		   		break;
		   		case 5:
					 draw_sprite(buffer, perdeu, 0, 0);
					 
					  masked_blit(botaoPerdeu, buffer, botMenu_troca, 0, 315, 250, 290, 61);
					  if(colidir(mouse_x, mouse_y, 315, 250, 10, 10, 290, 61)){
				 					 botMenu_troca = 290;
			                         if(mouse_b == 1 || key[KEY_ENTER]){
									 			play_sample(select, 100, 128, 1000, 0);guia = 4;
									 			guia = 4; 
										        mouse_b = 0;}}
                 else{botMenu_troca = 0;}
                
					 
					 break; }
		draw_sprite(buffer, ponteiro, mouse_x, mouse_y);
		//show_mouse(buffer);	
		draw_sprite(screen, buffer, 0, 0);
		clear(buffer);		
	}
	
	//Finalização
	//blocos
	destroy_bitmap(tileFase1);
	destroy_bitmap(tileFase2);
	destroy_bitmap(tileFase3);
	//backgrounds
	destroy_bitmap(tiroboss);
	destroy_bitmap(sobreFundo);
	destroy_bitmap(backgroundMenu);
	destroy_bitmap(bg);
	destroy_bitmap(bg01);
	destroy_bitmap(bg02);
	destroy_bitmap(bg03);
	destroy_bitmap(final);
	destroy_bitmap(vida);
	destroy_bitmap(buffer);
	destroy_bitmap(titulo);
	destroy_bitmap(guias);
	destroy_bitmap(botMenu);
	destroy_bitmap(textoSobre);
	destroy_bitmap(comoJogar);
	destroy_bitmap(player);
	destroy_bitmap(inimigo);
	destroy_bitmap(boss);
	destroy_bitmap(bala);
	destroy_bitmap(perdeu);
	destroy_bitmap(botaoPerdeu);
	destroy_bitmap(ponteiro);
	
	destroy_sample(musicafase1);
	destroy_sample(musicafase2);
	destroy_sample(musicafase3);
	destroy_sample(musicaMenu);
	destroy_sample(select);
    destroy_sample(pulo);
    destroy_sample(musicaTiro);
    destroy_sample(musicaMorte);
	destroy_sample(musicaAndar);
	destroy_sample(musicaCaiu);
    destroy_sample(musicaCoroninha);
    destroy_sample(danoCoroninha);
    destroy_sample(morteboss);
    destroy_sample(danoboss);
	destroy_sample(tirotocou);
	destroy_sample(musicafinal);
	
	return 0;
}

int colidir(int Ax, int Ay, int Bx, int By, int Aw, int Ah, int Bw, int Bh){
if(Ax + Aw > Bx && Ax < Bx + Bw && Ay + Ah > By && Ay < By + Bh)return 1;
return 0;}

END_OF_MAIN();
void sair(){sai= 1;}
END_OF_FUNCTION(sair);
int jogador(){
	//movimentação
	 if(key[KEY_LEFT] || key[KEY_A]){p.x -= 12; dir = 0; nTile--; if(!pulando && !caindo){play_sample(musicaAndar, 150, 128, 1000, 0);}}
     else if(key[KEY_RIGHT] || key[KEY_D]){p.x += 12;dir = 1; nTile++; if(!pulando && !caindo){play_sample(musicaAndar, 150, 128, 1000, 0);}}
	    else{nTile = 3;}
	    
	    //sistema de pulo
        if(key[KEY_UP]&& !pulando && !vly){
                       if(fase != 6)play_sample(pulo, 120, 128, 1000, 0);
                       pLimit = p.y;
                       pulando = 1;}
        if(key[KEY_W]&& !pulando && !vly){
					   if(fase != 6)play_sample(pulo, 120, 128, 1000, 0);
                       pLimit = p.y;
                       pulando = 1;}
                       
        if(pulando && p.y > pLimit - 45){
                   nTile = 4;
                   p.y += vly;
                   vly = -vup;
                   caindo = 1;}
        //gravidade              
        else if(caindo){
	           nTile = 4;
               pulando = 0;
		       vly += grv;
		       p.y += vly;}
		       
	    else{pulando = 0;vly = 0;}
		caindo = 1;
		
		if(nTile < 0){nTile = 2;}
		else if(nTile > 3){nTile = 0;}
		
                 if(p.x < -13){p.x +=12;}
                 //limita até onde o player pode ir
                 if(p.y > 500){
				 		play_sample(musicaCaiu, 255, 128, 1000, 0);
				 		p.x = 0;
				 		p.y = 200;
				 		vidas--;
						 }
				//mecanica de tiro
        if(key[KEY_ENTER] && atirar == 0 && tiro.x == p.x+15 && tiro.y == p.y+5) {atirar = 1; play_sample(musicaTiro, 200, 128, 1000, 0);}
        if(atirar){tiro.x +=20;tiro.wx = 0;}
		           
        if(tiro.x > 900 || tiro.x < 0){atirar = 0;}
        if(!atirar){tiro.x = p.x+15; tiro.y = p.y+5;}
        
        	masked_blit(bala, buffer, tiro.wx, tiro.wy, tiro.x, tiro.y, tiro.w, tiro.h);		 
						 	 
                masked_blit(player, buffer, p.wx + nTile*48, p.wy-dir*51, p.x, p.y, p.w, p.h);
                
                if(vidas == 0 )guia = 5;                     //se vidas for igual a 0 voce perdeu!
                if(pontos == 100){pontos = 0; vidas++;}      //troca pontos por vidas
                if(p.x > 910){fase +=1; p.x = 0; p.y = 150;} //responsável por trocar de fase
     			
	        if(vidas == 1){
						 masked_blit(vida, buffer, 0, 0, 17, 6, 15, 15);
						 for(i = 2; i < 10; i++){masked_blit(vida, buffer, 15, 0, 17*i, 6, 15, 15);}
						 }
            if(vidas == 2){
						 for(i = 1; i < 3; i++){masked_blit(vida, buffer, 0, 0, 17*i, 6, 15, 15);}
						 for(i = 3; i < 10; i++){masked_blit(vida, buffer, 15, 0, 17*i, 6, 15, 15);}
						 }
	        if(vidas == 3){
			   			 for(i = 1; i < 4; i++){masked_blit(vida, buffer, 0, 0, 17*i, 6, 15, 15);}
						 for(i = 4; i < 10; i++){masked_blit(vida, buffer, 15, 0, 17*i, 6, 15, 15);}
						 }
            if(vidas == 4){
			   			 for(i = 1; i < 5; i++){masked_blit(vida, buffer, 0, 0, 17*i, 6, 15, 15);}
						 for(i = 5; i < 10; i++){masked_blit(vida, buffer, 15, 0, 17*i, 6, 15, 15);}
						 }
		    if(vidas == 5){
			   			 for(i = 1; i < 6; i++){masked_blit(vida, buffer, 0, 0, 17*i, 6, 15, 15);}
						 for(i = 6; i < 10; i++){masked_blit(vida, buffer, 15, 0, 17*i, 6, 15, 15);}
						 }
    	    if(vidas == 6){
			   			 for(i = 1; i < 7; i++){masked_blit(vida, buffer, 0, 0, 17*i, 6, 15, 15);}
						 for(i = 7; i < 10; i++){masked_blit(vida, buffer, 15, 0, 17*i, 6, 15, 15);}
						 }
		    if(vidas == 7){
			   			 for(i = 1; i < 8; i++){masked_blit(vida, buffer, 0, 0, 17*i, 6, 15, 15);}
						 for(i = 8; i < 10; i++){masked_blit(vida, buffer, 15, 0, 17*i, 6, 15, 15);}
						 }
            if(vidas == 8){
			   			 for(i = 1; i < 9; i++){masked_blit(vida, buffer, 0, 0, 17*i, 6, 15, 15);}
						 for(i = 9; i < 10; i++){masked_blit(vida, buffer, 15, 0, 17*i, 6, 15, 15);}
						 }
	        if(vidas == 9){
			   			 for(i = 1; i < 10; i++){masked_blit(vida, buffer, 0, 0, 17*i, 6, 15, 15);}}
 
        	textprintf_ex(buffer, font, 180, 8, makecol(55,55,55), -1, "PONTOS: %i",pontos);
        	
        	if(colidir(mouse_x, mouse_y, 820, -5, 10, 10, 90, 55)){
									botMenu_troca = 100;
									   if(mouse_b == 1){play_sample(select, 100, 128, 1000, 0);guia = 4;}}
                else{botMenu_troca = 0;}
                 masked_blit(botMenu, buffer, botMenu_troca, 0, 820, -5, 90, 55);
                
	}
