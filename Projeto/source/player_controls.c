case SDL_KEYUP:
    if (evt.key.keysym.sym == SDLK_LSHIFT)
	player->speed = 5;
    break;

case SDL_KEYDOWN: 

    switch (evt.key.keysym.sym){

	    case SDLK_w:
	        if (player->sprite_cut.y == 512)
	            player->sprite_cut.x = (player->sprite_cut.x + 64) % 576;
	        player->sprite_cut.y = 512;
	        if (!checkCollisions(player->rect, objects, -player->speed, 0))
		    player->rect.y -= player->speed;             
	        break;

	    case SDLK_s:
	        if (player->sprite_cut.y == 640)
	            player->sprite_cut.x = (player->sprite_cut.x + 64) % 576;
	        player->sprite_cut.y = 640;
	        if (!checkCollisions(player->rect, objects, player->speed, 0))
	            player->rect.y += player->speed;
	        break;

	    case SDLK_a:
	        if (player->sprite_cut.y == 576)
	            player->sprite_cut.x = (player->sprite_cut.x + 64) % 576;
	        player->sprite_cut.y = 576;    
	        if (!checkCollisions(player->rect, objects, -player->speed, 1))
		    player->rect.x -= player->speed;
	        break;

	    case SDLK_d:
	        if (player->sprite_cut.y == 704)
	            player->sprite_cut.x = (player->sprite_cut.x + 64) % 576;
	        player->sprite_cut.y = 704;
	        if (!checkCollisions(player->rect, objects, player->speed, 1))
	            player->rect.x += player->speed;
	        break;

	    case SDLK_LSHIFT:
	        player->speed = 7;
	        break;

	    case SDLK_ESCAPE:
	        *screen = menu;
	        break;

    



