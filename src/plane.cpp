#include "plane.h"
#include "main.h"

Plane::Plane(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation_pitch = 0;
    this->rotation_yaw = 0;
    this->rotation_roll = 0;
    this->hp=1000;
    this->fuel=900;
    this->launch= false;
    body[0]=Cylinder(0.0f,0.0f,-2.1f,0.0f,0.2f,0.3f,0.0f,COLOR_RED,COLOR_RED,COLOR_RED);
    body[1]=Cylinder(0.0f,0.0f,-1.45f,0.2f,0.5f,1.0f,0.0f,COLOR_BLACK,COLOR_RED,COLOR_WHITE);
    body[2]=Cylinder(0.0f,0.0f,+0.05f,0.5f,0.5f,0.75f,0.0f,COLOR_BLACK,COLOR_GOLD,COLOR_GOLD);
    body[3]=Cylinder(0.0f,0.0f,+0.05f,0.5f,0.5f,2.0f,0.0f,COLOR_BLACK,COLOR_GREY,COLOR_GREY);
    body[4]=Cylinder(0.0f,0.0f,+1.4f,0.35f,0.5f,0.7f,180.0f,COLOR_YELLOWISH_ORANGE,COLOR_WHITE,COLOR_GREY);
    exhaust=    Ring(0.0f,0.0f,2.00f,0.35f,0.5f,0.5f,COLOR_YELLOWISH_ORANGE,COLOR_BLACK);
    missile[0]=Wmissle(0.55f,0.0f,0.0f);
    missile[1]=Wmissle(-0.55f,0.0f,0.0f);
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation_yaw * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rotate1    = glm::rotate((float) (this->rotation_pitch * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 rotate2    = glm::rotate((float) (this->rotation_roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate*rotate1*rotate2);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);
    exhaust.draw(MVP);
    for(int i = 4; i >=0 ; i--)
    {
        body[i].draw(MVP);
    }
    if(this->launch==false) 
    {
        missile[0].draw(MVP);
        missile[1].draw(MVP);
    }

}


void Plane::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Plane::tick(double accx,double accy, double accz ,int press) 
{   
    double  time = 1.0/60;
    // if(this->speedx >= 1*stage_multiplier  && accx>0)
    //     this->speedx=1*stage_multiplier;
    // else if( this->speedx <= -1*stage_multiplier && accx < 0)
    //     this->speedx=-1*stage_multiplier;
    // else
    //     this->speedx+= accx*time;

    if(this->speedy >= 1*stage_multiplier  && accy>0)
        this->speedy=1*stage_multiplier;
    else if (accy<0 && this->speedy < -1*stage_multiplier )
    {
        this->speedy=-1*stage_multiplier;
        this->speedy+= accy*time;
    }
    else
        this->speedy+= accy*time;

    if(this->speedz >= 1*stage_multiplier  && accz>0)
        this->speedz=1*stage_multiplier;
    else if (accz<0 && this->speedz < -1*stage_multiplier )
    {
        this->speedz=-1*stage_multiplier;
        this->speedz+= accz*time;
    }
    else
        this->speedz+= accz*time;

    glm::vec4 p0=glm::vec4(0.0f,0.0f,time*this->speedz,1.0f);
    // glm::vec4 p0=glm::vec4(0.0f,0.0f,-100,1.0f);
    p0    = p0*glm::rotate(glm::radians(this->rotation_yaw), glm::vec3(0, 1, 0));
    p0.y=this->speedy*time;
    if(p0.z  <  0)
    {
        p0    = p0*glm::rotate(glm::radians(this->rotation_pitch) , glm::vec3(1, 0, 0));
        p0.y*=-1;
    }
    else
    {
        p0    = p0*glm::rotate(glm::radians(this->rotation_pitch) , glm::vec3(1, 0, 0));
    }
    
    // p0.z*=-1;
    // p0    = p0*glm::rotate(glm::radians(this->rotation_roll ), glm::vec3(0, 0, 1));
    this->position.x+= p0.x;
    this->position.y+= p0.y;
    this->position.z-= p0.z;
    if(press)
        this->fuel-=0.1f;
    if(this->fuel < 0)
        this->fuel=0;
    // if(this->position.y<=-2.24)
    // {
    //     this->position.y=-2.24;
    //     this->speedy=0;
    // }
    // if(this->position.x < -( 3.8/screen_zoom) )
    // {
    //     this->position.x=-3.8/screen_zoom;
    //     this->speedx=0;
    // }
    // if(this->position.y > (3.8/screen_zoom) )
    // {
    //     this->position.y=3.8/screen_zoom;
    //     this->speedy=0;
    // }
}


bounding_box_t Plane::bounding_box() 
{
    float x = this->position.x, y = this->position.y,z=this->position.z;
    bounding_box_t bd_box = { x , y ,z,1.0f,1.0f,4.5f };
    return bd_box;
}
