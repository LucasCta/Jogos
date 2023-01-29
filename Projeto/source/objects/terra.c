background * gramado = malloc(sizeof(*gramado));
gramado->tileset = IMG_LoadTexture(ren,"images/grass_tileset.png");    
for (i=0; i<18; i++)
    for (j=0; j<32; j++)
        gramado->sprite_cuts[i][j] = (SDL_Rect) {16*6+(rand()%3*16),32,16,16}; 
