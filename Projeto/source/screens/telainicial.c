void telaInicialRen(SDL_Renderer* ren, SDL_Window* win, int * screen, int * espera, character * player) {

    int i, j, w, h; 
    SDL_GetWindowSize(win, &w, &h);
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    absToRelative(&player->rect);

    #include "../objects/mysteriousWoman.c"
    #include "../objects/screenBorders.c"
    #include "../objects/gramado.c"

    struct colliders * objects = createNode(); 
    for (i=0; i<4; i++) addNode(objects, screenBorder[i]);
    addNode(objects, mistWoman->rect);
    
	Uint32 antes = SDL_GetTicks();
     
    while (*screen == telaInicial){
    
        SDL_RenderClear(ren);
        drawBackground(ren, gramado);
        SDL_RenderCopy(ren, mistWoman->sprite, &mistWoman->sprite_cut, &mistWoman->rect);
        stringRGBA(ren, mistWoman->rect.x+mistWoman->rect.w-5, mistWoman->rect.y, mistWoman->dialog[actualDialog], 0x00,0x00,0x00,0xFF);
        SDL_RenderCopy(ren, player->sprite, &player->sprite_cut, &player->rect);
        SDL_RenderPresent(ren);
    
        *espera = MAX(0, *espera - (int)(SDL_GetTicks() - antes));
        SDL_Event evt; int isevt = AUX_WaitEventTimeoutCount(&evt, espera);
        antes = SDL_GetTicks();
    
        if (isevt){
             switch (evt.type){
                #include "../player_controls.c"
                case SDL_WINDOWEVENT:
                    if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                        *screen = fim;
                    break;
             } 
        } else {
            *espera = 20;
            if (++wAnimation == mistWoman->speed){
                mistWoman->sprite_cut.x = (mistWoman->sprite_cut.x + 37) % 259;
                wAnimation = 0;
            } 
			if (isClose(player->rect, mistWoman->rect))
            	actualDialog = 1;
            for (i=telaOeste-2; i<telaLeste; i++)
                if (isClose(player->rect, screenBorder[i]))
                    *screen = i+2;
        }
  
    }

	free(mistWoman);
	free(gramado);
    
}
