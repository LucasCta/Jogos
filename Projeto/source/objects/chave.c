object * chave = malloc(sizeof(*chave));
chave->rect = (SDL_Rect) {1200, 40, 64, 32};
chave->sprite = IMG_LoadTexture(ren, "images/chave.png");
chave->sprite_cut = (SDL_Rect) {0, 0, 1024, 512};
