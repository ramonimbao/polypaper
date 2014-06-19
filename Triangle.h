#include <glm\glm.hpp>

struct Triangle {
	Triangle();
	glm::vec3 p1, p2, p3, centroid, normal, color;
	glm::vec3 computeCentroid();
	glm::vec3 computeNormal();
};