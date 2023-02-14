object * bau = malloc(sizeof(*bau));
bau->rect = (SDL_Rect) {620, 450, 64, 64};
bau->sprite = IMG_LoadTexture(ren, "images/chest.png");
bau->sprite_cut = (SDL_Rect) {0, 0, 254, 254}; 
