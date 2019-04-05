#include "main.h"
#include "cylinder.h"

#ifndef WMISSLE_H
#define WMISSLE_H


class Wmissle {
public:
    Wmissle() {}
    Wmissle(float x, float y, float z);
    glm::vec3 position;
    float hp;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    Cylinder tail,head;
};

#endif // WMISSLE_H
