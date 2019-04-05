#include "block.h"
#include "main.h"

Block::Block(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {
       -0.1f,-0.1f,-0.1f, // triangle 1 : begin
       -0.1f,-0.1f, 0.1f,
       -0.1f, 0.1f, 0.1f, // triangle 1 : end
        0.1f, 0.1f,-0.1f, // triangle 2 : begin
       -0.1f,-0.1f,-0.1f,
       -0.1f, 0.1f,-0.1f, // triangle 2 : end
        0.1f,-0.1f, 0.1f,
       -0.1f,-0.1f,-0.1f,
        0.1f,-0.1f,-0.1f,
        0.1f, 0.1f,-0.1f,
        0.1f,-0.1f,-0.1f,
       -0.1f,-0.1f,-0.1f,
       -0.1f,-0.1f,-0.1f,
       -0.1f, 0.1f, 0.1f,
       -0.1f, 0.1f,-0.1f,
        0.1f,-0.1f, 0.1f,
       -0.1f,-0.1f, 0.1f,
       -0.1f,-0.1f,-0.1f,
       -0.1f, 0.1f, 0.1f,
       -0.1f,-0.1f, 0.1f,
        0.1f,-0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f,-0.1f,-0.1f,
        0.1f, 0.1f,-0.1f,
        0.1f,-0.1f,-0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f,-0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.1f,-0.1f,
       -0.1f, 0.1f,-0.1f,
        0.1f, 0.1f, 0.1f,
       -0.1f, 0.1f,-0.1f,
       -0.1f, 0.1f, 0.1f,
        0.1f, 0.1f, 0.1f,
       -0.1f, 0.1f, 0.1f,
        0.1f,-0.1f, 0.1f
    };

    static const GLfloat g_color_buffer_data[] = 
    { 
		4*0.583f,  0.771f,  0.014f,
		4*0.609f,  0.115f,  0.436f,
		4*0.327f,  0.483f,  0.844f,
		4*0.822f,  0.569f,  0.201f,
		4*0.435f,  0.602f,  0.223f,
		4*0.310f,  0.747f,  0.185f,
		4*0.597f,  0.770f,  0.761f,
		4*0.559f,  0.436f,  0.730f,
		4*0.359f,  0.583f,  0.152f,
		4*0.483f,  0.596f,  0.789f,
		4*0.559f,  0.861f,  0.639f,
		4*0.195f,  0.548f,  0.859f,
		4*0.014f,  0.184f,  0.576f,
		4*0.771f,  0.328f,  0.970f,
		4*0.406f,  0.615f,  0.116f,
		4*0.676f,  0.977f,  0.133f,
		4*0.971f,  0.572f,  0.833f,
		4*0.140f,  0.616f,  0.489f,
		4*0.997f,  0.513f,  0.064f,
		4*0.945f,  0.719f,  0.592f,
		4*0.543f,  0.021f,  0.978f,
		4*0.279f,  0.317f,  0.505f,
		4*0.167f,  0.620f,  0.077f,
		4*0.347f,  0.857f,  0.137f,
		4*0.055f,  0.953f,  0.042f,
		4*0.714f,  0.505f,  0.345f,
		4*0.783f,  0.290f,  0.734f,
		4*0.722f,  0.645f,  0.174f,
		4*0.302f,  0.455f,  0.848f,
		4*0.225f,  0.587f,  0.040f,
		4*0.517f,  0.713f,  0.338f,
		4*0.053f,  0.959f,  0.120f,
		4*0.393f,  0.621f,  0.362f,
		4*0.673f,  0.211f,  0.457f,
		4*0.820f,  0.883f,  0.371f,
		4*0.982f,  0.099f,  0.879f
	};

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, g_color_buffer_data , GL_FILL);
}

void Block::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Block::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Block::tick() 
{
}

bounding_box_t Block::bounding_box() 
{
    float x = this->position.x, y = this->position.y,z=this->position.z;
    bounding_box_t bd_box = { x , y ,z,1.0f,1.0f,1.0f };
    return bd_box;
}
