#include "Sphere.h"
#include "IntersectionInfo.h"

Vector3D Sphere::getPosition() {
    return position;
}

Color Sphere::getColor() {
    return color;
}

bool Sphere::rayIntersects(Ray ray, IntersectionInfo& intersectionInfo) {
    
    double t0, t1;

    Vector3D L = position - ray.getPosition();
    double tca = L.dotProduct(ray.getDirection());
    double d2 = L.dotProduct(L) - tca * tca;

    if (d2 > (radius * radius)) {
        return false;
    }

    double thc = sqrt((radius * radius) - d2);
    t0 = tca - thc;
    t1 = tca + thc;

    if (t0 > t1) {
        std::swap(t0, t1);
    }

    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) {
            // Both were negative, return false
            return false;
        }
    }

    intersectionInfo.t = t0;
    intersectionInfo.sphere = this;
    intersectionInfo.position = ray.getPosition() + ray.getDirection().scale(t0);

    return true;
}


