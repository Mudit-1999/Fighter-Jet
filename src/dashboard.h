#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H

class Dashboard 
{
public:
    Dashboard() {}
    Dashboard(float x, float y, float z,float height,float width, color_t color);
    glm::vec3 position;
    float rotation,height,width;
    void draw();
    void tick();
private:
    VAO *object;
};

#endif // DASHBOARD_H
