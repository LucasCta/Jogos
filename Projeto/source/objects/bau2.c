object * bau2 = malloc(sizeof(*bau2));
bau2->rect = (SDL_Rect) {870, 450, 64, 64};
bau2->sprite = IMG_LoadTexture(ren, "images/chest2.png");
bau2->sprite_cut = (SDL_Rect) {0, 0, 254, 254}; 
