#include "main.h"
#include "coin.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z, float width,float height, float r1);
    glm::vec3 position;
    float rotation;
    void draw();
    void tick();
    Coin contianer;
private:
    VAO *object,*object1,*object2;
};

#endif // COMPASS_H
