#include "3D-Renderer.hpp"

Renderer3D::Renderer3D(SDL_Window* _window, SDL_Renderer* _renderer, std::vector<Point3d>& _points, std::vector<edge>& _edges) {
	SDL_GetWindowSize(_window, &winSizeX, &winSizeY);
	renderer = _renderer;
	points = _points;
	edges = _edges;
}

void Renderer3D::render() {
	auto time1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration(0); // These are for frame-independent timing

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); 
	SDL_RenderClear(renderer); // Setting the window to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // Then to black

	rotation += 1 * deltatime; // rotate the cube a lil

	for (auto& edge : edges) {
		Point3d rotatedStartP = rotateX(rotateY(points[edge.start])); // P for point
		Point3d rotatedEndP = rotateX(rotateY(points[edge.end]));
		Point2d start = projection(rotatedStartP);
		Point2d end = projection(rotatedEndP);
		SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
	}
	SDL_RenderPresent(renderer);

	auto time2 = std::chrono::high_resolution_clock::now();
	duration = time2 - time1;
	deltatime = duration.count();
	time1 = time2;
}

Point3d Renderer3D::rotateX(Point3d point) {
	Point3d returnP;
	returnP.x = point.x;
	returnP.y = cos(rotation) * point.y - sin(rotation) * point.z;
	returnP.z = sin(rotation) * point.y + cos(rotation) * point.z;
	return returnP; // horrible name, but i can't be bothered to change it
}

Point3d Renderer3D::rotateY(Point3d point) {
	Point3d returnP;
	returnP.x = cos(rotation) * point.x - sin(rotation) * point.z;
	returnP.y = point.y;
	returnP.z = sin(rotation) * point.x + cos(rotation) * point.z;
	return returnP;
}

Point2d Renderer3D::projection(Point3d point) {
	return Point2d{ winSizeX / 2 + (fov * point.x) / (fov + point.z) * 100, winSizeY / 2 + (fov * point.y) / (fov + point.z) * 100 };
}