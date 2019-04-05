#include "ring.h"
#include "main.h"


Ring::Ring(float x, float y, float z,float r1,float r2,float height, color_t color, color_t color2)
 {
    this->position = glm::vec3(x,y,z);
    this->rotation=0;
    this->radius=radius;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n=4000;
    GLfloat vertex_buffer_triangular_strip[9*n] ;
    GLfloat vertex_buffer_triangular_strip1[9*n] ;

    for (int i = 0; i < n; i++) 
    {
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

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_triangular_strip, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_triangular_strip1, color2, GL_FILL);
}


void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}


void Ring::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Ring::bounding_box() 
{
    float x = this->position.x, y = this->position.y,z = this->position.z;
    bounding_box_t bd_box = { x , y, z, 1.5f*this->radius ,  1.5f*this->radius, 0.2f};
    return bd_box;
}
// void Ring::tick()
// {
    
// }   

