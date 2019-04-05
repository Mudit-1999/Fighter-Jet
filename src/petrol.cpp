#include "petrol.h"
#include "main.h"

Petrol::Petrol(float x, float y,float z)
{
    this->position = glm::vec3(x,y,z);
    this->rotation=0;
    static const GLfloat vertex_buffer_data [] = 
    {
        0.0f              ,   0.0f               , 0.0f, 
        0.5f*1.0f         ,   0.0f               , 0.0f, 
        0.5f*cos(M_PI/3)  ,   0.5f* sin(M_PI/3)  , 0.0f, 
        0.5f*cos(2*M_PI/3),   0.5f* sin(2*M_PI/3), 0.0f, 
        0.5f*cos(3*M_PI/3),   0.5f* sin(3*M_PI/3), 0.0f, 
        0.5f*cos(4*M_PI/3),   0.5f* sin(4*M_PI/3), 0.0f, 
        0.5f*cos(5*M_PI/3),   0.5f* sin(5*M_PI/3), 0.0f, 
        0.5f*1.0f         ,                  0.0f, 0.0f, 
    };

    static const GLfloat colour_buffer_data [] = 
    {
             1.0f , 0.5* 1.0f ,     1.0f,
        0.5*0.95f , 0.5*0.95f , 0.4*0.95f,
        0.5*0.97f , 0.5*0.97f , 0.4*0.95f,
        0.5*0.97f , 0.5*0.95f , 0.4*0.97f,
        0.5*0.95f , 0.5*0.97f , 0.4*0.97f,
        0.5*0.97f , 0.5* 1.0f , 0.4*0.97f,
        0.5 *1.0f , 0.5*0.97f , 0.4*0.97f,
        0.5*0.97f , 0.5* 1.0f , 0.4*0.97f
    };
    this->object = create3DObject(GL_TRIANGLE_FAN, 8, vertex_buffer_data, colour_buffer_data, GL_FILL);
}

void Petrol::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

// void Petrol::tick()
// {
// }   


bounding_box_t Petrol::bounding_box() 
{
    float x = this->position.x, y = this->position.y,z=this->position.z;
    bounding_box_t bd_box = { x , y ,z,1.0f,1.0f,0.0f };
    return bd_box;
}
