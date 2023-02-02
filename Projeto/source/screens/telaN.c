void telaNorteRen(SDL_Renderer* ren, SDL_Window* win, int * screen, int * espera, character * player) {

    int i, j, w, h; 
    SDL_GetWindowSize(win, &w, &h);
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    absToRelative(&player->rect);

    #include "../objects/areia.c"
    #include "../objects/screenBorders.c"
    #include "../objects/peixe.c"

    int si = rand()%18; int sj = rand()%32; 
    gramado->sprite_cuts[si][sj] = (SDL_Rect) {16*7,16,16,16};
    SDL_Rect secret = {sj*40,si*40,16,16};

    struct colliders * objects = createNode(); 
    for (i=0; i<4; i++) addNode(objects, screenBorder[i]);

    Uint32 antes = SDL_GetTicks();
     
    while (*screen == telaNorte){
    
        SDL_RenderClear(ren);
        drawBackground(ren, gramado);
        SDL_RenderCopy(ren, player->sprite, &player->sprite_cut, &player->rect);
	if (itensEncontrados == peix) SDL_RenderCopy(ren,peixe->sprite,&peixe->sprite_cut, &peixe->rect);
        SDL_RenderPresent(ren);

        *espera = MAX(0, *espera - (int)(SDL_GetTicks() - antes));
        SDL_Event evt; int isevt = AUX_WaitEventTimeoutCount(&evt, espera);
        antes = SDL_GetTicks();
    
	    if (isevt){
             switch (evt.type){
                #include "../player_controls.c"
                case SDLK_x:     
                    if (isClose(player->rect, secret))
                        itensEncontrados = peix;
                } break;
                case SDL_WINDOWEVENT:
                    if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                        *screen = fim;
                    break;
             } 
        } else {
            *espera = 20;
            if (isClose(player->rect, screenBorder[telaSul-2])){
                *screen = telaInicial;
            }
        }

    }

}