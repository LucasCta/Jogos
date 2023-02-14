object * peixe = malloc(sizeof(*peixe));
peixe->rect = (SDL_Rect) {1200, 0, 64, 64};
peixe->sprite = IMG_LoadTexture(ren, "images/fish.png");
peixe->sprite_cut = (SDL_Rect) {0, 0, 700, 700};
