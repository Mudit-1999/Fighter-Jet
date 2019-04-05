#include "main.h"
#include "cylinder.h"
#include "ring.h"
#include "wmissle.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation_yaw,rotation_pitch, rotation_roll ;
    void draw(glm::mat4 VP);
    void draw_missle(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(double accx,double accy, double accz ,int press);
    double speedx,speedy,speedz;
    double hp,fuel;
    bool launch;
    Cylinder body[5];
    Ring exhaust;
    bounding_box_t bounding_box();
    Wmissle missile[2];
private:
    VAO *object;
};

#endif // PLANE_H
