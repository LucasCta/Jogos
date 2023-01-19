object * strangeHouse = malloc(sizeof(*strangeHouse));
strangeHouse->rect = (SDL_Rect) {700, 512, 62, 64};
strangeHouse->sprite = IMG_LoadTexture(ren, "images/house.png");
strangeHouse->sprite_cut = (SDL_Rect) {0, 0, 581, 611}; 