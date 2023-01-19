int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms){
    Uint32 antes = SDL_GetTicks();
    SDL_FlushEvent(SDL_MOUSEMOTION);
    if (SDL_WaitEventTimeout(evt, *ms)) {
        *ms = MAX(0, *ms - (int)(SDL_GetTicks() - antes));
        return 1;
    } return 0;
}

