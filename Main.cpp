#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_rotozoom.h>

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include <functional>
#include <cmath>

#include <glm/glm.hpp>

#include "Triangle.h"
#include "Light.h"

#define NUM_LIGHTS 2
#define Z_OFFSET 100

int main(int argc, char* argv[]) {
	double params[6] = {-1,-1,-1,-1,-1,-1};

	if (argc > 1) {
		if (strcmp(argv[1],"--help") == 0 || strcmp(argv[1],"-help") == 0 || strcmp(argv[1],"-h") == 0) {
			std::cout << \
				"----------\n" << \
				"--Polypaper by Ramon Imbao\n" << \
				"-----(http://twitter.com/ramooown)\n" << \
				"----------\n" << \
				"--Inspiration from Flat Surface Shader by Matther Wagerfield\n" << \
				"-----(http://matthew.wagerfield.com/flat-surface-shader/)\n" << \
				"--and Poly Wallpaper Pack by Ryan Kelly\n" << \
				"-----(http://ryanmkelly.me/android/wallpaper/)\n" << \
				"\n" << \
				"Usage: polypaper [-h] [width] [height] [light-ambient] [light-diffuse] [mesh-ambient] [mesh-diffuse]\n" << \
				"\n" << \
				"Optional arguments:\n" << \
				"  -h, --help\t\tShows this help message.\n" << \
				"  width\t\t\tThe output width.\n" << \
				"  height\t\tThe output height.\n" << \
				"  light-ambient\t\tThe light ambient color in hexadecimal (ex. FFFFFF)\n" << \
				"  light-diffuse\t\tThe light diffuse color in hexadecimal (ex. FFFFFF)\n" << \
				"  mesh-ambient\t\tThe light ambient color in hexadecimal (ex. FFFFFF)\n" << \
				"  mesh-diffuse\t\tThe light diffuse color in hexadecimal (ex. FFFFFF)\n";

			return 0;
		}

		else {
			for (int i = 1; i < argc; i++) {
				//std::cout << parameters[i - 1] << " " << argv[i] << std::endl;
				if (i < 4)
					params[i - 1] = atoi(argv[i]);
				if (i >= 3) {
					unsigned int value;
					std::stringstream ss;
					//std::cout << argv[i] << std::endl;
					ss << std::hex << argv[i];
					ss >> value;
					params[i - 1] = value;
					//std::cout << value << std::endl;
				}
			}
		}
	}

	SDL_Init(SDL_INIT_VIDEO);
	const SDL_VideoInfo *info;
	info = SDL_GetVideoInfo();

	// Setting defaults in case no parameters are specified
	if (params[0] == -1.0)
		params[0] = info->current_w * 2; // we're gonna be downsampling this whoo
	if (params[1] == -1.0)
		params[1] = info->current_h * 2;

	std::mt19937::result_type seed = time(0);
	auto colorRand = std::bind(std::uniform_int_distribution<int>(0, 0xFFFFFF), std::mt19937(seed));
	srand(time(0));
	if (params[2] == -1.0)
		params[2] = colorRand(rand());
	if (params[3] == -1.0)
		params[3] = colorRand(rand());
	if (params[4] == -1.0)
		params[4] = 0x555555;
	if (params[5] == -1.0)
		params[5] = 0xFFFFFF;

	double width, height;
	width = params[0];
	height = params[1];

	// Let's convert params[2] and params[3] to vec3s
	glm::vec3 light_ambient = glm::vec3();
	glm::vec3 light_diffuse = glm::vec3();
	light_ambient.x = (((int)params[2] & 0xFF0000) >> 16) / 255.0f;
	light_ambient.y = (((int)params[2] & 0x00FF00) >> 8) / 255.0f;
	light_ambient.z = ((int)params[2] & 0x0000FF) / 255.0f;
	light_diffuse.x = (((int)params[3] & 0xFF0000) >> 16) / 255.0f;
	light_diffuse.y = (((int)params[3] & 0x00FF00) >> 8) / 255.0f;
	light_diffuse.z = ((int)params[3] & 0x0000FF) / 255.0f;

	glm::vec3 mesh_ambient = glm::vec3();
	glm::vec3 mesh_diffuse = glm::vec3();
	mesh_ambient.x = (((int)params[2] & 0xFF0000) >> 16) / 255.0f;
	mesh_ambient.y = (((int)params[2] & 0x00FF00) >> 8) / 255.0f;
	mesh_ambient.z = ((int)params[2] & 0x0000FF) / 255.0f;
	mesh_diffuse.x = (((int)params[3] & 0xFF0000) >> 16) / 255.0f;
	mesh_diffuse.y = (((int)params[3] & 0x00FF00) >> 8) / 255.0f;
	mesh_diffuse.z = ((int)params[3] & 0x0000FF) / 255.0f;

	// SDL setup
	SDL_Surface* screen;
	SDL_Surface* output;
	screen = SDL_SetVideoMode(1, 1, 32, SDL_SWSURFACE | SDL_NOFRAME);
	if (!screen) {
		std::cout << "ERROR CREATING SCREEN!\n";
	}

	output = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, info->vfmt->Rmask, info->vfmt->Gmask, info->vfmt->Bmask, info->vfmt->Amask);
	if (!output) {
		std::cout << "ERROR CREATING OUTPUT SURFACE!\n";
	}

	// this is where the magic happens...
	// ...supposedly

	// Vertex generation
	std::cout << "Generating vertices...\n";
	std::vector<glm::vec3> vertices;

	double vary = std::min(width/32.0f, height/16.0f);
	auto variation = std::bind(std::uniform_int_distribution<int>(-vary, vary), std::mt19937(seed));

	for (int y = 0; y <= 10; y++) {
		for (int x = 0; x <= 18; x++) {
			vertices.push_back(
				glm::vec3(
					(width / 16) * x + variation(rand()) - width/16.0f,
					(height / 8) * y + variation(rand()) - height/8.0f,
					((float)rand() / RAND_MAX) * 50 * (((float)rand() / RAND_MAX) > 0.5 ? -1 : 1)
				));
		}
	}

	// Triangle generation
	std::cout << "Generating triangles...\n";
	std::vector<Triangle> triangles;
	for (int j = 0; j <= 171; j += 19) {
		for (int i = 0; i < 18; i++) {
			// triangle 1
			Triangle t1, t2;
			t1.p1 = vertices[j + i];
			t1.p2 = vertices[j + i + 1];
			t1.p3 = vertices[j + i + 19];
			t1.computeCentroid();
			t1.computeNormal();

			// triangle 2
			t2.p1 = vertices[j + i + 1];
			t2.p2 = vertices[j + i + 19];
			t2.p3 = vertices[j + i + 20];
			t2.computeCentroid();
			t2.computeNormal();

			triangles.push_back(t1);
			triangles.push_back(t2);
		}
	}

	// Position the lights
	std::cout << "Creating and positioning lights...\n";
	std::vector<Light> lights;

	auto widthRand = std::bind(std::uniform_int_distribution<int>(0, width), std::mt19937(seed));
	auto heightRand = std::bind(std::uniform_int_distribution<int>(0, height), std::mt19937(seed));

	for (int i = 0; i < NUM_LIGHTS; i++) {
		Light l;
		l.position = glm::vec3(widthRand(rand()), heightRand(rand()), Z_OFFSET);
		//std::cout << "Light " << i + 1 << " position: " << l.position.x << "," << l.position.y << "," << l.position.z << "\n";
		lights.push_back(l);
	}

	// Compute the illuminance of the triangles
	std::cout << "Computing illuminance...\n";
	for (int i = 0; i < triangles.size(); i++) {
		Triangle t = triangles[i];
		t.color = glm::vec3(); // reset?
		for (int j = 0; j < NUM_LIGHTS; j++) {
			Light l = lights[j];
			l.ray = glm::normalize(l.position - t.centroid);
			float illuminance = glm::dot(t.normal, l.ray);

			// Calculate ambient
			t.color += mesh_ambient * light_ambient;
			// Calculate diffuse
			t.color += (mesh_diffuse * light_diffuse) * illuminance;
			
		}
		//t.color = glm::abs(t.color);
		glm::clamp(t.color, 0.0f, 1.0f);
		triangles[i] = t; // err... something to do with variable references?
		
	}

	// Draw!
	std::cout << "Rendering...\n";
	SDL_FillRect(screen, NULL, 0);

	for (int i = 0; i < triangles.size(); i++) {
		Triangle tri = triangles[i];
		Sint16 x1, x2, x3, y1, y2, y3;
		Uint8 r, g, b;
		x1 = tri.p1.x;
		x2 = tri.p2.x;
		x3 = tri.p3.x;
		y1 = tri.p1.y;
		y2 = tri.p2.y;
		y3 = tri.p3.y;
		r = tri.color.x * 255;
		g = tri.color.y * 255;
		b = tri.color.z * 255;
		filledTrigonRGBA(output, x1, y1, x2, y2, x3, y3, r, g, b, 255);
	}
	
	std::cout << "Downsampling...\n";
	SDL_Surface* finalOutput;
	finalOutput = shrinkSurface(output, 2, 2);

	std::cout << "Saving as output.bmp...\n";
	SDL_SaveBMP(finalOutput, "output.bmp");

	std::cout << "Done!\n";
	
	SDL_FreeSurface(screen);
	SDL_FreeSurface(output);
	SDL_FreeSurface(finalOutput);
	SDL_Quit();

	return 0;
}
