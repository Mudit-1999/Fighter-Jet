#include "main.h"
#include "cylinder.h"
// #include "canon.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z);
    glm::vec3 position,scale;
    float hp;
    float x_rotation,y_rotation;
    void draw(glm::mat4 VP);
    void tick(float x,float y, float z, float x_a,float y_a, float s);

    Cylinder tail,head;
};

#endif // ARROW_H
