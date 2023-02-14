object * semente = malloc(sizeof(*semente));
semente->rect = (SDL_Rect) {1200, 0, 65, 40};
semente->sprite = IMG_LoadTexture(ren, "images/seed.png");
semente->sprite_cut = (SDL_Rect) {0, 0, 520, 320};
