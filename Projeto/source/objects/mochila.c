object * mochila = malloc(sizeof(*mochila));
mochila->rect = (SDL_Rect) {1150, 0, 128, 128};
mochila->sprite = IMG_LoadTexture(ren, "images/backpack.png");
mochila->sprite_cut = (SDL_Rect) {440, 0, 348, 284}; 