#include "main.h"
#include "cylinder.h"
// #include "canon.h"

#ifndef MISSLE_H
#define MISSLE_H


class Missle {
public:
    Missle() {}
    Missle(float x, float y, float z);
    glm::vec3 position;
    float hp,start_time;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    double speedx,speedy,speedz;
    bounding_box_t bounding_box();
    Cylinder tail,head;
};

#endif // MISSLE_H
