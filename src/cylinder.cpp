#include "cylinder.h"
#include "main.h"
using namespace std;
Cylinder:: Cylinder(float x, float y,float z,float r1,float r2, float height,float rotation ,color_t color,color_t color1,color_t color2) 
{
    this->position = glm::vec3(x, y, z);
    this->rotation = rotation;
    this->y_rotation=0;
    this->radius = r2;
    this->height=height;

    int n=100;
    GLfloat vertex_buffer_circle[9*n] ;
    GLfloat vertex_buffer_triangular_strip[9*n] ;
    GLfloat vertex_buffer_circle1[9*n] ;
    GLfloat vertex_buffer_triangular_strip1[9*n] ;

    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_circle[i*9]   = 0.0;
        vertex_buffer_circle[i*9+1] = 0.0;
        vertex_buffer_circle[i*9+2] = -height/2.0;  
        vertex_buffer_circle[i*9+3] = cos((i*M_PI)/10)*r1;
        vertex_buffer_circle[i*9+4] = sin((i*M_PI)/10)*r1;
        vertex_buffer_circle[i*9+5] = -height/2.0;  
        vertex_buffer_circle[i*9+6] = cos(((i+1)*M_PI)/10)*r1;
        vertex_buffer_circle[i*9+7] = sin(((i+1)*M_PI)/10)*r1;
        vertex_buffer_circle[i*9+8] = -height/2.0;  

        vertex_buffer_circle1[i*9]   = 0.0;
        vertex_buffer_circle1[i*9+1] = 0.0;
        vertex_buffer_circle1[i*9+2] = height/2.0f; 
        vertex_buffer_circle1[i*9+3] = cos(M_PI/n+(i*M_PI)/10)*r2;
        vertex_buffer_circle1[i*9+4] = sin(M_PI/n+(i*M_PI)/10)*r2;
        vertex_buffer_circle1[i*9+5] = height/2.0f; 
        vertex_buffer_circle1[i*9+6] = cos(M_PI/n+((i+1)*M_PI)/10)*r2;
        vertex_buffer_circle1[i*9+7] = sin(M_PI/n+((i+1)*M_PI)/10)*r2;
        vertex_buffer_circle1[i*9+8] = height/2.0f; 
        
        
        vertex_buffer_triangular_strip[i*9]   = cos((i*M_PI)/10)*r1;
        vertex_buffer_triangular_strip[i*9+1] = sin((i*M_PI)/10)*r1;
        vertex_buffer_triangular_strip[i*9+2] = -height/2.0;    
        vertex_buffer_triangular_strip[i*9+3] = cos(((i+1)*M_PI)/10)*r1;
        vertex_buffer_triangular_strip[i*9+4] = sin(((i+1)*M_PI)/10)*r1;
        vertex_buffer_triangular_strip[i*9+5] = -height/2.0;    
        vertex_buffer_triangular_strip[i*9+6] = cos(M_PI/n+(i*M_PI)/10)*r2;
        vertex_buffer_triangular_strip[i*9+7] = sin(M_PI/n+(i*M_PI)/10)*r2;
        vertex_buffer_triangular_strip[i*9+8] = height/2;
        

        vertex_buffer_triangular_strip1[i*9]   = cos(M_PI/n+(i*M_PI)/10)*r2;
        vertex_buffer_triangular_strip1[i*9+1] = sin(M_PI/n+(i*M_PI)/10)*r2;
        vertex_buffer_triangular_strip1[i*9+2] = height/2.0f;   
        vertex_buffer_triangular_strip1[i*9+3] = cos(M_PI/n+((i+1)*M_PI)/10)*r2;
        vertex_buffer_triangular_strip1[i*9+4] = sin(M_PI/n+((i+1)*M_PI)/10)*r2;
        vertex_buffer_triangular_strip1[i*9+5] = height/2.0f;   
        vertex_buffer_triangular_strip1[i*9+6] = cos(((i+1)*M_PI)/10)*r1;
        vertex_buffer_triangular_strip1[i*9+7] = sin(((i+1)*M_PI)/10)*r1;
        vertex_buffer_triangular_strip1[i*9+8] = -height/2.0;
    }

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_circle, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_circle1, color2, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_triangular_strip, color1, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_triangular_strip1, color2, GL_FILL);
}

void Cylinder::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 yrotate    = glm::rotate((float) (this->y_rotation), glm::vec3(0, 1, 0));
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));

    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate *yrotate *  rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Cylinder::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cylinder::tick(double p_ang) 
{
    this->y_rotation=p_ang;
}

bounding_box_t Cylinder::bounding_box() 
{
    float x = this->position.x, y = this->position.y,z=this->position.z;
    bounding_box_t bd_box = {x, y, z, 2.0f*this->radius,1.5f*this->height,2*this->radius };
    return bd_box;
}
