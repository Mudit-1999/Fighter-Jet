#include "main.h"

#ifndef PETROL_H
#define PETROL_H


class Petrol {
public:
    Petrol() {}
    Petrol(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // PETROL_H
