void telaInicialRen(SDL_Renderer* ren, SDL_Window* win, int * screen, int * espera, character * player) {

    int i, j, w, h; 
    SDL_GetWindowSize(win, &w, &h);
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    absToRelative(&player->rect);
  
    #include "../objects/house.c"
    #include "../objects/mysteriousWoman.c"
    #include "../objects/screenBorders.c"
    #include "../objects/gramado.c"
    #include "../objects/peixe.c"

    struct colliders * objects = createNode(); 
    for (i=0; i<4; i++) addNode(objects, screenBorder[i]);
    addNode(objects, strangeHouse->rect);
    addNode(objects, mystWoman->rect);
    int dialogCounter = 0;

    Uint32 antes = SDL_GetTicks();
     
    while (*screen == telaInicial){
    
        SDL_RenderClear(ren);
        drawBackground(ren, gramado);
        SDL_RenderCopy(ren, player->sprite, &player->sprite_cut, &player->rect);
        SDL_RenderCopy(ren, strangeHouse->sprite, &strangeHouse->sprite_cut, &strangeHouse->rect);
        SDL_RenderCopy(ren, mystWoman->sprite, &mystWoman->sprite_cut, &mystWoman->rect);
	    if (itensEncontrados == peix) SDL_RenderCopy(ren, peixe->sprite,&peixe->sprite_cut, &peixe->rect);
            stringRGBA(ren, mystWoman->rect.x+mystWoman->rect.w-5, mystWoman->rect.y, mystWoman->dialog[actualDialog], 0x00,0x00,0x00,0xFF);

            SDL_RenderPresent(ren);
        
            *espera = MAX(0, *espera - (int)(SDL_GetTicks() - antes));
            SDL_Event evt; int isevt = AUX_WaitEventTimeoutCount(&evt, espera);
            antes = SDL_GetTicks();
    
            if (isevt){
                 switch (evt.type){
                    #include "../player_controls.c"
		            } break;
                    case SDL_WINDOWEVENT:
                        if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                            *screen = fim;
                        break;
                 } 
            } else {
                *espera = 20;
                if (++wAnimation == mystWoman->speed){
                    mystWoman->sprite_cut.x = (mystWoman->sprite_cut.x + 37) % 259;
                    wAnimation = 0;
                } 
	            if (isClose(player->rect, mystWoman->rect)) {
                    switch (itensEncontrados){
		                case nada:
                            if (actualDialog == 0) actualDialog = 1;
		                    if (actualDialog > 0 && actualDialog < 4) {
                                dialogCounter += 1; 
                                dialogCounter %= 200;
                                if(dialogCounter == 199)
                                    actualDialog += 1; 
                            } break;
                        case peix:
                            if (actualDialog == 0) actualDialog = 5;
                            if (actualDialog >=  5 && actualDialog < 7) { 
                                dialogCounter += 1; 
                                dialogCounter %= 200;
                                if(dialogCounter == 199)
                                    actualDialog += 1; 
                            } break;
                     }
                }
                for (i=telaOeste-2; i<telaLeste; i++)
                    if (isClose(player->rect, screenBorder[i]))
                        *screen = i+2;
           }
  
    }
    
}
