void menuRen (SDL_Renderer* ren, int * screen) {

    int i;
    SDL_Point mouse;

    SDL_Color orange = {0xF6,0x6A,0x03,0xFF}; 
    SDL_Color black = {0x00,0x00,0x00,0xFF};
    SDL_Color grey = {125,125,125,125};

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("fonts/zk.ttf", 100);
    
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);

    screenText * menuText = malloc(sizeof(*menuText) * 3);
    
    menuText[0].text = malloc(sizeof("Detalhes"));
    menuText[0].text = "Detalhes";
    menuText[0].font = font;
    menuText[0].color = orange;
    menuText[0].rect = (SDL_Rect) {340,100,600,200};
    
    menuText[1].text = malloc(sizeof("Jogar"));
    menuText[1].text = "Jogar";
    menuText[1].font = font;
    menuText[1].color = grey;
    menuText[1].rect = (SDL_Rect) {540,300,250,200};    
    
    menuText[2].text = malloc(sizeof("Sair"));
    menuText[2].text = "Sair";
    menuText[2].font = font;
    menuText[2].color = grey;
    menuText[2].rect = (SDL_Rect) {540,500,250,200};
    
    while (*screen == menu){
    
        SDL_RenderClear(ren);   
        for (i = 0; i < 3; i++){
            struct SDL_Surface * tempSur = TTF_RenderText_Solid(menuText[i].font,menuText[i].text,menuText[i].color);
            struct SDL_Texture * tempTex = SDL_CreateTextureFromSurface(ren,tempSur);
            SDL_RenderCopy(ren,tempTex,NULL,&(menuText[i].rect));
            SDL_FreeSurface(tempSur); SDL_DestroyTexture(tempTex);
        } SDL_RenderPresent(ren);

	    SDL_Event evt;
        if (SDL_WaitEvent(&evt)){
            switch (evt.type) {
                case SDL_WINDOWEVENT:
                    if (SDL_WINDOWEVENT_CLOSE == evt.window.event)
                        *screen = fim;
                    break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouse.x, &mouse.y);
                    menuText[1].color = grey; menuText[2].color = grey;
                    if (SDL_EnclosePoints(&mouse, 1, &menuText[1].rect, NULL))
                        menuText[1].color = black;
                    else if (SDL_EnclosePoints(&mouse, 1, &menuText[2].rect, NULL))
                        menuText[2].color = black;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouse.x, &mouse.y);
                    if (SDL_EnclosePoints(&mouse, 1, &menuText[1].rect, NULL))
                        *screen = telaInicial;
                    else if (SDL_EnclosePoints(&mouse, 1, &menuText[2].rect, NULL))
                        *screen = fim;
                    break;
            }
        }
        
    }
    
    TTF_CloseFont(font);
    free(menuText);
    
}
