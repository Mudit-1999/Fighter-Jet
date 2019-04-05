#include "dashboard.h"
#include "main.h"

using namespace std;

Dashboard::Dashboard(float x, float y,float z, float height, float width, color_t color) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->height=height;
    this->width=width;
    GLfloat vertex_buffer_data[] = 
    {
            0.0f,      0.0f , 0.0f,
            0.0f,     height, 0.0f,
           width,       0.0f, 0.0f,
            0.0f,     height, 0.0f,
           width,       0.0f, 0.0f,
           width,     height, 0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Dashboard::draw() 
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Dashboard::tick() {
    // this->rotation += speed;
    // this->position += glm::vec3(speed,0,0);
}


