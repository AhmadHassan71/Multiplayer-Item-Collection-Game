#pragma once
#include "Object.hpp"
#include "render_window.hpp"


//thread data struct
struct thread_data
{
	Object *player;
	Object *item;
	RenderWindow *window;
};

float randomizer(int min, int max)
{
	srand((unsigned)time(NULL));
	float random = (float)min + (rand() % max);
	return random;
}

//collision function
void checkIntersection(void* arg)
{
	
	thread_data *data = (thread_data *)arg;
	if (data->player->getPos().intersects(data->item->getPos()))
	{
		srand(time(NULL));
		data->item->setPos(randomizer(0, 200), randomizer(0, 140));
		data->window->render(*data->item);
	}
}


//movement functions
void *moveUp(void *arg)
{
    Object *obj = (Object *)arg;

    obj->move(0, -30);

    pthread_exit((void *)obj);
}
void *moveDown(void *arg)
{
    Object *obj = (Object *)arg;

    obj->move(0, 30);

    pthread_exit((void *)obj);
}
void *moveLeft(void *arg)
{
    Object *obj = (Object *)arg;

    obj->move(-30, 0);

    pthread_exit((void *)obj);
}
void *moveRight(void *arg)
{
    Object *obj = (Object *)arg;

    obj->move(30, 0);

    pthread_exit((void *)obj);
}
