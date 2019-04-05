#include "arrow.h"
#include "main.h"


Arrow::Arrow(float x, float y, float z)
{
    this->position = glm::vec3(x, y,z);
    this->y_rotation=0;
    this->x_rotation=0;
    this->scale = glm::vec3(1,1,1);
    tail = Cylinder(0.0f,0.0f,+0.5f,0.2f,0.2f,1.0f,0.0f,COLOR_RED,COLOR_RED,COLOR_RED);
    head = Cylinder(0.0f,0.0f,-0.5f,0.0f,0.3f,1.0f,0.0f,COLOR_RED,COLOR_RED,COLOR_RED);
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) this->y_rotation , glm::vec3(0, 1, 0));
    glm::mat4 rotate1    = glm::rotate((float) this->x_rotation, glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    glm::mat4 scale = glm::scale(this->scale);
    Matrices.model *= (translate * rotate * rotate1 *scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    tail.draw(MVP);
    head.draw(MVP);
}


void Arrow::tick(float x,float y, float z,float x_a,float y_a,float s)
{
    this->position = glm::vec3(x, y+4.0f,z-1.0f);
    this->y_rotation=y_a;
    this->x_rotation=x_a;
    this->scale=glm::vec3(s, s,s)   ;
}   

