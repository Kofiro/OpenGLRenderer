#ifndef VECTOR_H
#define VECTOR_H

#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

// minimal implementation of a vector struct
struct Vector3 {

    float x;
    float y;
    float z;

    Vector3() : x(0), y(0), z(0) {};    // constructors
    Vector3(float x, float y, float z): x(x), y(y), z(z) {};

    // functions
    Vector3& normalize();
    Vector3 operator-(const Vector3& rhs) const;    // subtraction
    Vector3 cross(const Vector3& rhs) const;    // cross product
};

Vector3& Vector3::normalize() {
    float invLength = 1 / glm::sqrt(x*x + y*y + z*z);
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& rhs) const {
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector3 Vector3::cross(const Vector3& rhs) const {
    return Vector3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
}

void lookAtToAxes(const Vector3& position, const Vector3& target, Vector3& left, Vector3& up, Vector3& forward) {
    // compute forward vector
    forward = target - position;    // direction FROM position TO target
    forward.normalize();    // normalize after

    // compute temporal up vector based on forward vector
    // becareful for when look up/down at 90 degrees
    // for e.g, forward vector is on the Y axis
    if(glm::abs(forward.x) < 0.0001 && glm::abs(forward.z) < 0.0001) {
        // forward vector is pointing +Y axis
        if(forward.y > 0)
            up = Vector3(0, 0, -1);
        else
            up = Vector3(0, 0, 1);

    }
    else{
        up = Vector3(0, 1, 0);
    }

    // compute left vector
    left = up.cross(forward);
    left.normalize();

    // recalculate up vector
    up = forward.cross(left);
}

void lookAtToAxes(const Vector3& pos, const Vector3& target, const Vector3& updir, Vector3& left, Vector3& up, Vector3& forward) {
    forward = target - pos;
    forward.normalize();

    // compuet left vector
    left = updir.cross(forward);
    left.normalize();

    up = forward.cross(left); 
}

#endif