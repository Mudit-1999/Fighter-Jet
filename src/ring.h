#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z,float r, float r2, float height,color_t color,color_t color2);
    glm::vec3 position;
    float rotation,radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box() ;
private:
    VAO *object,*object1;
};

#endif // RING_H
