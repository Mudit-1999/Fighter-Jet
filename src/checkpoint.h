#include "main.h"
#include "cylinder.h"
#include "platform.h"
// #include "canon.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H


class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float z,color_t color_ground);
    glm::vec3 position;
    float hp;
    float rotation;
    void draw(glm::mat4 VP);
    void tick(double p_ang);
    bounding_box_t bounding_box(); 

    Platform base,base_1;
    Cylinder canon,hill;
};

#endif // CHECKPOINT_H
