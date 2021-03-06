#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin 
{
public:
    Coin() {}
    Coin(float x, float y, float height,color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif // COIN_H
