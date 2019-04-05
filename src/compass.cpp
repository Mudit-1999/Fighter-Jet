#include "compass.h"
#include "main.h"


Compass::Compass(float x, float y, float z,  float width,float height, float r1)
{
    this->position = glm::vec3(x, y,z);
    this->rotation=0;

    int n=100;
    GLfloat vertex_buffer_circle[9*n] ;
    
    contianer = Coin(0.0f,0.0f,2*r1,COLOR_BLACK);
    static const GLfloat vertex_buffer_north[] = {
       -width,0.0f,-0.0f, // triangle 1 : begin
        width,0.0f, 0.0f,
       -0.0f,height, 0.0f, // triangle 1 : end
    };
    static const GLfloat vertex_buffer_south[] = {
       -width,0.0f,-0.0f, // triangle 1 : begin
        width,0.0f, 0.0f,
       -0.0f,-height, 0.0f, // triangle 1 : end
    };
    
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_circle[i*9]   = 0.0f;
        vertex_buffer_circle[i*9+1] = 0.0f;
        vertex_buffer_circle[i*9+2] = 0.0f;  
        vertex_buffer_circle[i*9+3] = cos((i*M_PI)/10)*r1;
        vertex_buffer_circle[i*9+4] = sin((i*M_PI)/10)*r1;
        vertex_buffer_circle[i*9+5] = 0.0f;  
        vertex_buffer_circle[i*9+6] = cos(((i+1)*M_PI)/10)*r1;
        vertex_buffer_circle[i*9+7] = sin(((i+1)*M_PI)/10)*r1;
        vertex_buffer_circle[i*9+8] = 0.0f;  
    }
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_circle,COLOR_GOLD, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_north, COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_south, COLOR_WHITE, GL_FILL);
}

void Compass::draw() 
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    contianer.draw(MVP);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}


void Compass::tick()
{
    this->rotation=-yaw;
}   

