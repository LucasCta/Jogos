void drawBackground(SDL_Renderer* ren, background * bg){
    int i, j; 
    bg->tile = (SDL_Rect) {0, 0, 40, 40};
    for (i=0; i<18; i++) {
        for (j=0; j<32; j++) {
            SDL_RenderCopy(ren, bg->tileset, &bg->sprite_cuts[i][j], &bg->tile);
            bg->tile.x = (bg->tile.x + 40) % 1280;    
        } bg->tile.y += 40;
    }
}
