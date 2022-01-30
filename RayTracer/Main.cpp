#include <iostream>
#include <ctime>

#include <SDL.h>

#include <vector>

#include "Vector3D.h"
#include "Ray.h"
#include "Sphere.h"
#include "World.h"

int main(int argc, char* args[]) {
    srand(time(NULL));

	Vector3D::tests();

	Camera* camera = new Camera(50, 30, 10);
	LightSource* lightSource = new LightSource(Vector3D(0, 0, 1), Color(1, 1, 1));

	Sphere sphere0 = Sphere(Vector3D(0, 0, 10), 5, Color(1, 0, 0));
    std::vector<Sphere> spheres = { sphere0 };

	World world = World(camera, lightSource, spheres);

    for (int i = 0; i < 10000000; i++) {
        world.castRay();
    }

    int windowWidth = camera->getLensWidth() * camera->getPixelsPerUnit();
    int windowHeight = camera->getLensHeight() * camera->getPixelsPerUnit();

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Rrror initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Ray Tracer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight, 0);

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 2;
    }

    // Get a renderer for the window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderClear(renderer);

    Color* imageArray = camera->getRenderedImage();

    for (int y = 0; y < windowHeight; y++) {
        for (int x = 0; x < windowWidth; x++) {
            int arrayIndex = (y * windowWidth) + x;
            Color curPixelColor = imageArray[arrayIndex];

            SDL_SetRenderDrawColor(renderer, 
                curPixelColor.getRedAsInt(), 
                curPixelColor.getGreenAsInt(), 
                curPixelColor.getBlueAsInt(), 
                SDL_ALPHA_OPAQUE);

            SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    delete[] imageArray;

    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (true) {
        if (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }
    }

    return 0;
}