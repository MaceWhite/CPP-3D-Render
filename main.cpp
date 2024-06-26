#include "3D-Renderer.hpp"
#include <vector>
#include <SDL2/SDL.h>

std::vector<Point3d> points{ Point3d{-1.0f, -1.0f, -1.0f}, Point3d{-1.0f, -1.0f, 1.0f}, Point3d {1.0f, -1.0f, -1.0f}, Point3d {-1.0f, 1.0f, -1.0f}, Point3d {-1.0f, 1.0f, 1.0f}, Point3d {1.0f, -1.0f, 1.0f}, Point3d {1.0f, 1.0f, -1.0f}, Point3d{1.0f, 1.0f, 1.0f} };

std::vector<edge> edges{ edge{0,1},edge{0,2},edge{0,3}, edge {2,5}, edge{3,6}, edge {3,4},edge{4,7}, edge{6,7},edge{7,5}, edge{5,1}, edge{4,1}, edge{2,6} };

int main(int argc, char** argv) {
	SDL_Window* window;
	SDL_Renderer* renderer;
	window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool running = true;

	Renderer3D renderer3d(window, renderer, points, edges);

	while (running) {
		if (SDL_QuitRequested()) { running = false; break; }
		renderer3d.render();
	}
	return 0;
}