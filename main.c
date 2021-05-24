#include <stdio.h>
#include "SDL2/SDL.h"
//#include "SDL/SDL.h"

typedef struct {
    int x, y;
    short life;
    char *name;
} Man;

void processEvents(SDL_Window *window)
{
    SDL_Event event;
    int done = 0;
    while(!done)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_WINDOWEVENT_CLOSE:
                {
                    if (window) {
                        SDL_DestroyWindow(window);
                        window = NULL;
                        done = 1;
                    }
                }
                    break;
                case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            done=1;
                            break;
                    }
                }
                    break;
                case SDL_QUIT:
                    done=1;
                    break;
            }
        }

    }
}

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);

    // create application window
    window = SDL_CreateWindow("Game Window",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640,
                              480,
                              0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    processEvents(window);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}
