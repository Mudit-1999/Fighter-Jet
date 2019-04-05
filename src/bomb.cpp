#include "bomb.h"
#include "main.h"

Bomb:: Bomb(float x, float y,float z,float r1 ,color_t color,bool enemy ) 
{
    this->position = glm::vec3(x, y, z);
    this->radius=r1;
    this->rotation = 0;

    if(enemy==false)
    {
        this->speedz=20;
        glm::vec4 p0=glm::vec4(0.0f,0.0f,this->speedz,1.0f);
        p0    = p0*glm::rotate(glm::radians(yaw), glm::vec3(0, 1, 0));
        p0.y=0.0f;
        p0    = p0*glm::rotate(glm::radians(pitch), glm::vec3(1, 0, 0));
        this->speedx = p0.x;
        this->speedy = p0.y;
        this->speedz = -p0.z;
    }
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // speed = 0.05;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n=1000;
    GLfloat vertex_buffer_data[9*(n)];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 3; ++j)
		{
			vertex_buffer_data[9*i+j]=0.0f;
		}
		vertex_buffer_data[9*i+3]=cos((i*2*3.14)/n)*r1;
		vertex_buffer_data[9*i+4]=sin((i*2*3.14)/n)*r1;
		vertex_buffer_data[9*i+5]=0.0f;
	    
        vertex_buffer_data[9*i+6]=cos((((i+1)%n)*2*3.14)/n)*r1;
		vertex_buffer_data[9*i+7]=sin((((i+1)%n)*2*3.14)/n)*r1;
		vertex_buffer_data[9*i+8]=0.0f;

	}

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}
    
    
    
void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bomb::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bomb::tick(float accy) 
{
    this->speedy+= accy/60.0f;
    this->position += glm::vec3(this->speedx/60.0f,this->speedy/60.0f,this->speedz/60.0f);
}

bounding_box_t Bomb::bounding_box() 
{
    float x = this->position.x, y = this->position.y,z = this->position.z;
    bounding_box_t bd_box = { x , y, z,  2.0f*this->radius , 2.0f*this->radius, 0.0f};
    return bd_box;
}

