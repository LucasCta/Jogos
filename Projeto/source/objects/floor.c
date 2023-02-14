object * floor = malloc(sizeof(*floor));
floor->rect = (SDL_Rect) {0,0,1280,720};
floor->sprite = IMG_LoadTexture(ren, "images/floor.png");
floor->sprite_cut = (SDL_Rect) {0, 0, 1000, 500}; 