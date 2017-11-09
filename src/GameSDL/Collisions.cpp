#include "Collisions.h"

bool Collision(SDL_Rect* origen, SDL_Rect* target)
{

	return !(target->x > (origen->x + origen->w) ||
		(target->x + target->w) < origen->x ||
		target->y > (origen->y + origen->h) ||
		(target->y + target->h) < origen->y);
	
}
