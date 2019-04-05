#include "main.h"

#ifndef PLATFORM_H
#define PLATFORM_H

class Platform 
{
public:
    Platform() {}
    Platform(float x, float y, float z,float length,float width, color_t color);
    glm::vec3 position;
    float rotation,length,width;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick(double speed);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // PLATFORM_H
