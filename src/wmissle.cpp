#include "wmissle.h"
#include "main.h"


Wmissle::Wmissle(float x, float y, float z)
{
    this->position = glm::vec3(x, y,z);
    this->rotation=0;
    tail = Cylinder(0.0f,0.0f,+0.2f,0.1f,0.1f,0.4f,0.0f,COLOR_RED,COLOR_RED,COLOR_RED);
    head = Cylinder(0.0f,0.0f,-0.2f,0.0f,0.1f,0.4f,0.0f,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW);
}

void Wmissle::draw(glm::mat4 VP) 
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    tail.draw(MVP);
    head.draw(MVP);
}



