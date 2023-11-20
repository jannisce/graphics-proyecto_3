#include "cube.h"

// Constructor implementation
Cube::Cube(const glm::vec3& min, const glm::vec3& max, const Material& mat)
    : min(min), max(max), Object(mat) {}

// Ray intersection method
Intersect Cube::rayIntersect(const glm::vec3& rayOrigin, const glm::vec3& rayDirection) const {
    glm::vec3 invDir = 1.0f / rayDirection;
    glm::vec3 t0 = (min - rayOrigin) * invDir;
    glm::vec3 t1 = (max - rayOrigin) * invDir;

    glm::vec3 tmin = glm::min(t0, t1);
    glm::vec3 tmax = glm::max(t0, t1);

    float tmin_final = glm::max(tmin.x, glm::max(tmin.y, tmin.z));
    float tmax_final = glm::min(tmax.x, glm::min(tmax.y, tmax.z));

    if (tmin_final > tmax_final) {
        return Intersect{false}; // No intersection
    }

    glm::vec3 point = rayOrigin + tmin_final * rayDirection;
    glm::vec3 normal = calculateNormal(point);

    return Intersect{point, normal, tmin_final};
}

// Helper function to calculate normal based on the intersection point
glm::vec3 Cube::calculateNormal(const glm::vec3& point) const {
    glm::vec3 normal = glm::vec3(0.0f);
    const float bias = 1e-4; // Small bias to handle numerical precision issues

    if (std::fabs(point.x - min.x) < bias) normal.x = -1.0f;
    else if (std::fabs(point.x - max.x) < bias) normal.x = 1.0f;
    else if (std::fabs(point.y - min.y) < bias) normal.y = -1.0f;
    else if (std::fabs(point.y - max.y) < bias) normal.y = 1.0f;
    else if (std::fabs(point.z - min.z) < bias) normal.z = -1.0f;
    else if (std::fabs(point.z - max.z) < bias) normal.z = 1.0f;

    return normal;
}
