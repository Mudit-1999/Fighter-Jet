#include "main.h"

#ifndef CYLINDER_H
#define CYLINDER_H


class Cylinder {
public:
    Cylinder() {}
    Cylinder(float x, float y, float z, float r1,float r2, float height,float rotation, color_t color,color_t color1,color_t color2);
    glm::vec3 position;
    float rotation,y_rotation,height, radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick(double p_ang);
    bounding_box_t bounding_box(); 
private:
    VAO *object,*object1,*object2,*object3;
};

#endif // CYLINDER_H
