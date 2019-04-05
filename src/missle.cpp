#include "missle.h"
#include "main.h"


Missle::Missle(float x, float y, float z)
{
    this->position = glm::vec3(x, y,z);
    this->rotation=0;
    tail = Cylinder(0.0f,0.0f,+0.2f,0.1f,0.1f,0.4f,0.0f,COLOR_RED,COLOR_RED,COLOR_RED);
    head = Cylinder(0.0f,0.0f,-0.2f,0.0f,0.1f,0.4f,0.0f,COLOR_YELLOW,COLOR_YELLOW,COLOR_YELLOW);
    this->speedz=20;
    glm::vec4 p0=glm::vec4(0.0f,0.0f,this->speedz,1.0f);
    p0    = p0*glm::rotate(glm::radians(yaw), glm::vec3(0, 1, 0));
    p0.y=0.0f;
    p0    = p0*glm::rotate(glm::radians(pitch), glm::vec3(1, 0, 0));
    this->speedx = p0.x;
    this->speedy = p0.y;
    this->speedz = -p0.z;
    this->start_time= glfwGetTime();
}

void Missle::draw(glm::mat4 VP) 
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (yaw * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate1   = glm::rotate((float) (pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate*rotate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    tail.draw(MVP);
    head.draw(MVP);
}


void Missle::tick()
{
    this->position += glm::vec3(this->speedx/60.0f,this->speedy/60.0f,this->speedz/60.0f);
}

bounding_box_t Missle::bounding_box() 
{
    float x = this->position.x, y = this->position.y,z=this->position.z;
    bounding_box_t bd_box = {x, y, z,0.2f,0.2f,2*0.4f };
    return bd_box;
}


