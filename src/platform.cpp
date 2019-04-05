#include "platform.h"
#include "main.h"

using namespace std;

Platform::Platform(float x, float y,float z, float length, float width, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->length=length;
    this->width=width;
    GLfloat vertex_buffer_data[] = 
    {
         width/2, 0.0f, length/2,
         width/2, 0.0f,-length/2,
        -width/2, 0.0f,-length/2,
         width/2, 0.0f, length/2,
        -width/2, 0.0f,-length/2,
        -width/2, 0.0f, length/2,
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Platform::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    // cout <<" hi" <<endl;
}

void Platform::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Platform::tick(double speed) {
    // this->rotation += speed;
    this->position += glm::vec3(speed,0,0);
}


bounding_box_t Platform::bounding_box() 
{
    float x = this->position.x, y = this->position.y,z=this->position.z;
    bounding_box_t bd_box = { x , y ,z,this->length,this->width,0.0f};
    return bd_box;
}
