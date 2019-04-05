#include "checkpoint.h"
#include "main.h"


Checkpoint::Checkpoint(float x, float y, float z,color_t color_ground) 
{
    this->position = glm::vec3(x, y,z);
    this->rotation=0;
    this->hp=450;
    base  = Platform(0.0f,0.0f,0.0f,8.0f,8.0f,color_ground);
    base_1  = Platform(0.0f,0.01f,0.0f,3.0f,3.0f,COLOR_GREEN);
    canon = Cylinder(0.0f,0.31f,0.0f,0.25f,0.35f,0.7f,150.0f,COLOR_BLACK,COLOR_DARK_GREY, COLOR_DARK_GREY);
    hill= Cylinder(-3.5f,1.01f,-2.5f,1.0f,2.0f,2.0f,90.0f,COLOR_ORANGE_RED,COLOR_BROWN, COLOR_BROWN);
}

void Checkpoint::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    base.draw(MVP);
    base_1.draw(MVP);
    canon.draw(MVP);
    hill.draw(MVP);
}


void Checkpoint::tick(double p_ang)
{
    canon.tick(p_ang);    
} 

bounding_box_t Checkpoint::bounding_box() 
{
    float x = this->position.x, y = this->position.y,z=this->position.z;
    bounding_box_t bd_box = {x, y, z, 8.0f,0.0f,8.0f};
    return bd_box;
}


