#include "Triangle.h"

Triangle::Triangle() {
	p1 = glm::vec3();
	p2 = glm::vec3();
	p3 = glm::vec3();
	centroid = glm::vec3();
	normal = glm::vec3();
	color = glm::vec3();
}

glm::vec3 Triangle::computeCentroid() {
	centroid.x = p1.x + p2.x + p3.x;
	centroid.y = p1.y + p2.y + p3.y;
	centroid.z = p1.z + p2.z + p3.z;
	centroid /= 3;
	return centroid;
}

glm::vec3 Triangle::computeNormal() {
	glm::vec3 u = p2 - p1;
	glm::vec3 v = p3 - p1;
	normal = glm::normalize(glm::cross(u, v));
	return normal;
}