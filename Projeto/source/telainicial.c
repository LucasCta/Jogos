void telaInicialRen(SDL_Renderer* ren, SDL_Window* win, int * screen, int * espera, character * player) {

    int i, j;

    int w, h; SDL_GetWindowSize(win, &w, &h);

    character * mistWoman = malloc(sizeof(*mistWoman));
    mistWoman->rect = (SDL_Rect) {256, 256, 64, 64};
    mistWoman->sprite = IMG_LoadTexture(ren, "images/woman_idle.png");
    mistWoman->sprite_cut = (SDL_Rect) {0, 0, 37, 46}; 
    mistWoman->state = idle;
    mistWoman->speed = 10;
    int wAnimation = 0;

    mistWoman->dialog = (char **) malloc(sizeof(char*)*2);
    mistWoman->dialog[0] = (char *) malloc(sizeof("")+1);
    mistWoman->dialog[0] = ""; 
    mistWoman->dialog[1] = (char *) malloc(sizeof("Hello")+1);
    mistWoman->dialog[1] = "Hello";
    int actualDialog = 0;

    background * gramado = malloc(sizeof(*gramado));
    gramado->tileset = IMG_LoadTexture(ren,"images/grass_tileset.png");    
    for (i=0; i<18; i++)
        for (j=0; j<32; j++)
            gramado->sprite_cuts[i][j] = (SDL_Rect) {0,rand()%3*16,16,16}; 

    Uint32 antes = SDL_GetTicks();
     
    while (*screen == telaInicial){
    
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
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
                case SDL_KEYDOWN: 
                    switch (evt.key.keysym.sym){
                         case SDLK_w:
                            if (player->sprite_cut.y == 512)
                                player->sprite_cut.x = (player->sprite_cut.x + 64) % 576;
                            player->sprite_cut.y = 512;
                            player->rect.y = MAX(player->rect.y - player->speed, 0);             
                            break;
                        case SDLK_s:
                            if (player->sprite_cut.y == 640)
                                player->sprite_cut.x = (player->sprite_cut.x + 64) % 576;
                            player->sprite_cut.y = 640;
                            player->rect.y = MIN(player->rect.y + player->speed, h - player->rect.h);
                            break;
                        case SDLK_a:
                            if (player->sprite_cut.y == 576)
                                player->sprite_cut.x = (player->sprite_cut.x + 64) % 576;
                            player->sprite_cut.y = 576;
                            player->rect.x = MAX(player->rect.x - player->speed, 0);
                            break;
                        case SDLK_d:
                            if (player->sprite_cut.y == 704)
                                player->sprite_cut.x = (player->sprite_cut.x + 64) % 576;
                            player->sprite_cut.y = 704;
                            player->rect.x = MIN(player->rect.x + player->speed, w - player->rect.w);
                            break;
                        case SDLK_LSHIFT:
                            player->speed = 10;
                            break;
                        case SDLK_RETURN:
                            if (collision(&player->rect, &mistWoman->rect))
               		            actualDialog = 1;
                            break;
                       case SDLK_ESCAPE:
                            *screen = menu;
                            break;
                    } break;
                case SDL_KEYUP:
                    if (evt.key.keysym.sym == SDLK_LSHIFT)
                        player->speed = 5;
                    break;
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
        }
        
    }
    
}
