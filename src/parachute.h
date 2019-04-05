#include "main.h"
#include "block.h"
// #include "canon.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y,float z,float r1,float r2, float height,float rotation ,color_t color,color_t color1,color_t color2) ;
    glm::vec3 position;
    float hp,radius,height;
    float rotation,y_rotation;
    void draw(glm::mat4 VP);
    void tick(float speed);
    Block obj_block;
    bounding_box_t bounding_box(); 
private:
    VAO *object,*object1,*object2,*object3;
};

#endif // PARACHUTE_H
