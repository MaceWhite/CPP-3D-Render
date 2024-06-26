#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include <chrono>
#include <vector>

struct Point2d{
	float x, y;
};
struct Point3d {
	float x, y, z;
};
struct edge {
	int start, end;
};

class Renderer3D {
public:
	Renderer3D(SDL_Window* window, SDL_Renderer* renderer, std::vector<Point3d>& points, std::vector<edge>& edges);
	void render();
private:
	Point3d rotateX(Point3d point);
	Point3d rotateY(Point3d point);
	Point2d projection(Point3d point);

	float rotation = 0.0f;
	float fov = 10.0;
	float deltatime = 0.0f;

	int winSizeX;
	int winSizeY;
	SDL_Renderer* renderer;

	std::vector<Point3d> points;
	std::vector<edge> edges;
};