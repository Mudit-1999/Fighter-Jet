#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z,float r1 ,color_t color,bool enemy);
    glm::vec3 position;
    float rotation,radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(float accy);
    double speedx,speedy,speedz;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BOMB_H
