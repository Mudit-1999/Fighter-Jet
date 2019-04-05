#include "main.h"
#include "timer.h"
#include "plane.h"
#include "platform.h"
#include "ring.h"
#include "cylinder.h"
#include "bomb.h"
#include "checkpoint.h"
#include "parachute.h"
#include "petrol.h"
#include "arrow.h"
#include "dashboard.h"
#include "missle.h"
#include "compass.h"
#include "sevensegment.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

// global variable  
Plane rocket;
Platform ocean;
vector<Ring> smoke_ring;
vector<Cylinder> volcanoes;
vector<Bomb> bomb_player;
vector<Bomb> bomb_dushman;
vector<Checkpoint> enemy_base;
vector<Parachute> parachute_enemy;
vector<Petrol> fuel_up;
vector<Sevensegment> digit;
vector<Missle> missle_player;
Arrow guide,checkarrow;
Compass dir_nor;
color_t color_digit;
Dashboard fuel_meter, health_meter , alt_meter , speed_meter;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float stage_multiplier=15.0f;
float yaw=0,pitch=0,roll=0;   
float sea_level=-3.0f;
Timer t60(1.0 / 60);
int accx=0,accy=0, accz=0;        // rocket
double speed=1.0f;                // roatation speed
float start_time=glfwGetTime();      // bomb
float start_time_back=glfwGetTime(); // 
float start_explosion=glfwGetTime(); // 
int level=0,Final_Score=100,time_zone=0,destory_enemy=0;
float missle_act_timer;
bool topv=false,fv=true,tv=false,pv=false,hv=false; // cmaera
bool press=false,flag=false;
float dist=10.0f;
// functions 
glm::mat4 topview();
glm::mat4 planeview();
glm::mat4 followview();
glm::mat4 towerview();
glm::mat4 heliview();
void cam_rotate();
void check_collision_overall();
void backgroundcolor(color_t color);
int rnd(int upper, int lower);
void display(string s);
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    // Compute Camera matrix (view)
    if(fv)
      Matrices.view = followview();   // Rotating Camera for 3D
    else if(tv)
      Matrices.view = towerview();   // Rotating Camera for 3D
    else if(topv)
      Matrices.view = topview();   // Rotating Camera for 3D
    else if(pv)
      Matrices.view = planeview();   // Rotating Camera for 3D
    else if(hv)
      Matrices.view = heliview();   // Rotating Camera for 3D

    // Don't change unless you are sure!!
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    
    rocket.draw(VP);
    for(auto&& i : volcanoes)
      i.draw(VP);
    ocean.draw(VP);
    for(auto&& i : smoke_ring)
      i.draw(VP);
    for(auto&& i : enemy_base)
      i.draw(VP);
    for(auto&& i : bomb_player)
      i.draw(VP);
    for(auto&& i : bomb_dushman)
      i.draw(VP);
    for(auto&& i : missle_player)
      i.draw(VP);
    for(auto&& i : parachute_enemy)
      i.draw(VP);
    for(auto&& i : fuel_up)
      i.draw(VP);
    for(auto&& i : missle_player)
      i.draw(VP);
    guide.draw(VP);
    checkarrow.draw(VP);
    for(auto&& i : digit)  
      i.draw();
    fuel_meter.draw();
    health_meter.draw();
    alt_meter.draw();
    speed_meter.draw();
    dir_nor.draw();
}

void tick_input(GLFWwindow *window) 
{
    if(start_time + 7.0f < glfwGetTime())
    {

        bomb_dushman.push_back(Bomb(enemy_base[level].position.x,enemy_base[level].position.y,enemy_base[level].position.z,0.07,COLOR_DARK_GREY,true));
        int curr = bomb_dushman.size()-1;
        glm::vec3 p0=glm::vec3 (rocket.position.x- enemy_base[level].position.x,rocket.position.y- enemy_base[level].position.y,rocket.position.z- enemy_base[level].position.z);
        p0= glm::normalize(p0);
      // cout <<" intitial" << p0.x <<" " <<p0.y <<" " <<p0.z <<endl;

        bomb_dushman[curr].speedx=10*p0.x;
        bomb_dushman[curr].speedy=10*p0.y;
        bomb_dushman[curr].speedz=10*p0.z;
        start_time=glfwGetTime();
    }

    if(missle_act_timer + 5.0f < glfwGetTime())
    {
      rocket.launch=false;
    }

  if(rocket.fuel!=0 )
  {
    press=false;
    int x_pitch       = glfwGetKey(window, GLFW_KEY_UP);
    int x_pitch_neg   = glfwGetKey(window, GLFW_KEY_DOWN);
    int y_roll        = glfwGetKey(window, GLFW_KEY_P);
    int y_roll_neg    = glfwGetKey(window, GLFW_KEY_O);
    int z_rotate      = glfwGetKey(window, GLFW_KEY_LEFT);
    int z_rotate_neg  = glfwGetKey(window, GLFW_KEY_RIGHT);

    int y_up          = glfwGetKey(window, GLFW_KEY_SPACE);
    int y_down        = glfwGetKey(window, GLFW_KEY_C);
    int z_forward     = glfwGetKey(window, GLFW_KEY_W);
    int z_backward    = glfwGetKey(window, GLFW_KEY_S);


    if(z_forward)
    {
      accz=1;
      press=true;
    }
    else if(z_backward)
    {
      press=true;
      accz=-1;
    }
    else
        accz=0;
    if(y_up)  
    {
      if(flag==false)
      {
        rocket.speedy=0;
        flag=true;
      }
      else
      {
        accy=1;
      }
      press=true;
    }
    else if(y_down)
    {
      if(flag)
      {
        rocket.speedy=0;
        flag=false;
      }
      else
        accy=-1;
      press=true;
    }
    else
    {
        accy=0;       
    }

    if (x_pitch) 
    {
      press=true;
      if(rocket.rotation_pitch  <= 50.0f)
        rocket.rotation_pitch += speed;
    }
    if (x_pitch_neg) 
    {
      press=true;
      if(rocket.rotation_pitch >= -50.0f)
        rocket.rotation_pitch -= speed;
    }
    if (y_roll)
    {
      press=true;
      rocket.rotation_roll+= speed;
    } 
    if (y_roll_neg) 
    {
      press=true;
      rocket.rotation_roll -= speed;
    }
    if (z_rotate) 
    {
      press=true;
      if(rocket.rotation_yaw  - yaw<= 30.0f)
        rocket.rotation_yaw += speed;
      rocket.rotation_roll=20.0f;
    }
    else if (z_rotate_neg) 
    {
      press=true;
      if(rocket.rotation_yaw  -yaw >= -30.0f)
        rocket.rotation_yaw -= speed;
      rocket.rotation_roll=-20.0f;
    }
    else
    {
      rocket.rotation_roll=0.0f;
    }
  }
}

void tick_elements() 
{
    if(rocket.fuel!=0  )
    {
      rocket.tick(accx,accy,accz,press);
    }
    else
      rocket.tick(0.0,-1.0,0.0,0);

    for(auto&& i : bomb_player)
      i.tick(-1);
    for(auto&& i : bomb_dushman)
      i.tick(-0.005f);
    for(auto&& i : parachute_enemy)
      i.tick(1.0f);
    for(auto&& i : missle_player)
      i.tick();
    dir_nor.tick();
    if(rocket.position.z < enemy_base[level].position.z )
    {
      enemy_base[level].tick( -M_PI +  atan((rocket.position.x - enemy_base[level].position.x) / (rocket.position.z-enemy_base[level].position.z) ));
      guide.tick(rocket.position.x,rocket.position.y,rocket.position.z,  0.0f,  -M_PI +  atan((guide.position.x - enemy_base[level].position.x) / (guide.position.z-enemy_base[level].position.z )),1.0f);
    }
    else
    {
      enemy_base[level].tick(  atan((rocket.position.x - enemy_base[level].position.x) / (rocket.position.z-enemy_base[level].position.z) ));
      guide.tick(rocket.position.x,rocket.position.y,rocket.position.z, 0.0f,atan((guide.position.x - enemy_base[level].position.x) / (guide.position.z-enemy_base[level].position.z )) , 1.0f);
    }

    float temp = max(abs(rocket.position.x - enemy_base[level].position.x), abs(rocket.position.z - enemy_base[level].position.z));
    if(temp < 700)
      temp = temp/1500 * 50;  
    else
      temp = temp/1500 * 100;  

    checkarrow.tick(enemy_base[level].position.x, enemy_base[level].position.y+11.0,enemy_base[level].position.z+1.0f,glm::radians(270.0),0.0,temp);
    
    
    fuel_meter= Dashboard(-1.0f,-0.8f,0, 0.07, rocket.fuel /2000.0f, COLOR_RED);
    health_meter= Dashboard(-1.0f,-0.9f,0, 0.07, rocket.hp/ 2000.0f, COLOR_LIGHT_CORAL);
    alt_meter= Dashboard(1.0f,-0.9f,0, 0.07, (rocket.position.y -sea_level) / 200.0f, COLOR_BROWN);
    alt_meter.rotation=180.0f;
    speed_meter= Dashboard(1.0f,-0.8f,0, 0.07, (abs(rocket.speedz) ) / (2.0f*stage_multiplier), COLOR_YELLOW);
    speed_meter.rotation=180.0f;
    float time = 1/60.0f;
    // cout << rocket.speedz << " " << 2.0f*stage_multiplier <<endl;
    // cout <<fuel_meter.width << endl;  
    // cout << atan( (rocket.position.x - enemy_base[level].position.x)/(rocket.position.z-enemy_base[level].position.z ))<< endl;
    // cout << yaw<< " " << pitch << " "<< roll << endl;
    // cout << rocket.rotation_yaw<< " " << rocket.rotation_pitch << " "<< rocket.rotation_roll << endl;
    // glm::vec4 p0=glm::vec4(0.0f,0.0f,time*rocket.speedz,1.0f);
    // cout <<" intitial" << p0.x <<" " <<p0.y <<" " <<p0.z <<endl;
    // p0    = p0*glm::rotate(glm::radians(rocket.rotation_yaw  ), glm::vec3(0, 1, 0));
    // p0    = p0*glm::rotate(glm::radians(rocket.rotation_pitch) , glm::vec3(1, 0, 0));
    // // p0    = p0*glm::rotate(glm::radians(rocket.rotation_roll ), glm::vec3(0, 0, 1));
    // cout << " final" << p0.x <<" " <<p0.y <<" " <<p0.z <<endl;
    // cout  <<  rocket.speedx << " " <<rocket.speedy<<" " << rocket.speedz<<endl;
    
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) 
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models

  rocket = Plane(1.0f, sea_level +10.0f, 1.0f, COLOR_RED);
  ocean  = Platform(0.0f,sea_level,0.0f,3000.0f,3000.0f,COLOR_MID_NIGTH_BLUE);
  smoke_ring.push_back(Ring(0.0f,sea_level +10.0f,-4.0f,1.0f,1.0f,0.2f,COLOR_DEEP_PINK,COLOR_DEEP_PINK));
  volcanoes.push_back(Cylinder(1.0f,sea_level +1.0f,-20.0f,1.0f,2.0f,2.0f,90.0f,COLOR_ORANGE_RED,COLOR_YELLOWISH_ORANGE, COLOR_BROWN));
  parachute_enemy.push_back( Parachute(-1.0f,sea_level+10.0f,-3.0f,0.25f,0.10f, 0.4,90.0f,COLOR_YELLOW,COLOR_YELLOW, COLOR_YELLOW ));
  fuel_up.push_back(Petrol(2.0f,2.0f,-2.0f));

  enemy_base.push_back(Checkpoint(0.0f,sea_level +0.1f,-10.0f,COLOR_LIGHT_BROWN));
  enemy_base.push_back(Checkpoint(rnd(-1000,1000),sea_level +0.1f,rnd(-1000,1000),COLOR_LIGHT_BROWN));
  for(int i = 0; i < 100; i++)
  {

    float radius= rnd(15,25)/10.0f;
    smoke_ring.push_back(Ring(rnd(-1000,1000),rnd(sea_level+5, 40),rnd(-1000,1000),radius,radius,0.2f,COLOR_DEEP_PINK,COLOR_DEEP_PINK));
    volcanoes.push_back(Cylinder(rnd(-1000,1000),sea_level +1.0f,rnd(-1000,1000),1.0f,3.0f,2.0f*radius,90.0f,COLOR_ORANGE_RED,COLOR_YELLOWISH_ORANGE,COLOR_BROWN));
    parachute_enemy.push_back( Parachute(rnd(-1000,1000),rnd(sea_level+10, 40),rnd(-1000,1000),0.25f,0.10f, 0.4,90.0f,COLOR_YELLOW,COLOR_YELLOW, COLOR_YELLOW ));
    fuel_up.push_back(Petrol(rnd(-1000,1000),rnd(sea_level+1, 30),rnd(-1000,1000)));
  }
  enemy_base.push_back(Checkpoint(rnd(-1000,1000),sea_level +0.1f,rnd(-1000,1000),COLOR_LIGHT_BROWN));
    
  guide=Arrow(0.8f,0.8f,0.0f);
  checkarrow=Arrow(0.8f,0.8f,0.0f);
  fuel_meter= Dashboard(-1.0f,-0.8f,0, 0.07, rocket.fuel /2000.0f, COLOR_RED);
  health_meter= Dashboard(-1.0f,-0.9f,0, 0.07, rocket.hp/ 2000.0f, COLOR_LIGHT_CORAL);
  alt_meter= Dashboard(1.0f,-0.9f,0, 0.07, (rocket.position.y -sea_level) / 200.0f, COLOR_BROWN);
  alt_meter.rotation=180.0f;
  speed_meter= Dashboard(1.0f,-0.8f,0, 0.07, abs(rocket.speedz) / 2*stage_multiplier, COLOR_YELLOW);
  speed_meter.rotation=180.0f;
  dir_nor=Compass(-0.8f,0.8f, 0.0f,0.025f,0.1,0.05f);
  
  // Create and compile our GLSL program from the shaders
  programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
  // Get a handle for our "MVP" uniform
  Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
  // Matrices_ortho.MatrixID = glGetUniformLocation(programID, "MVP");

  reshapeWindow (window, width, height);
  
  // Background color of the scene
  backgroundcolor(COLOR_EARLY_SUNRISE);

  glEnable (GL_DEPTH_TEST);
  glDepthFunc (GL_LEQUAL);

  cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
  cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
  cout << "VERSION: " << glGetString(GL_VERSION) << endl;
  cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    system("aplay ../sound/smb_gameover.wav &");
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) 
    {
      // Process timers
      if (t60.processTick()) 
      {
        // 60 fps
        // OpenGL Draw commands
        if(start_time_back + 2.0f < glfwGetTime())
        {
          time_zone++;
          time_zone%=5;
          switch (time_zone) 
          {
            case 0:
              backgroundcolor(COLOR_EARLY_SUNRISE);
              color_digit=COLOR_BLACK;
              break;
            case 1:
              backgroundcolor(COLOR_SUNRISE);
              break;
            case 2:
              backgroundcolor(COLOR_MID_DAY);
              break;
            case 3:
              backgroundcolor(COLOR_SUNSET);
              break;
            case 4:
              backgroundcolor(COLOR_NIGHT);
              color_digit=COLOR_WHITE;
              break;              
            default:
              break;
          }
          start_time_back=glfwGetTime();
        }
        draw();
        // Swap Frame Buffer in double buffering

        glfwSwapBuffers(window);
        check_collision_overall();
        display(to_string(Final_Score));

        tick_elements();
        tick_input(window);
        if(rocket.position.y <= sea_level || rocket.hp < 0.0f )
        {
          quit(window);
        }

      }
      // Poll for Keyboard and mouse events
      glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) 
{
    return (abs(a.x - b.x) * 2 < (a.width + b.width))   &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) && 
           (abs(a.z - b.z) * 2 < (a.length + b.length));
}

void reset_screen() 
{
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(1.0f, 1.0f , 0.1f, 1000.0f);
}
//

void backgroundcolor(color_t color)
{
  glClearColor (color.r / 256.0, color.g / 256.0, color.b / 256.0, 0.0f); // R, G, B, A
  glClearDepth (1.0f);
}

// Camera View
glm::mat4 topview()
{
  cam_rotate();
  glm::vec3 eye ( rocket.position.x,rocket.position.y+ 20,rocket.position.z+1.0f);
  glm::vec3 target (rocket.position.x, rocket.position.y, rocket.position.z);
  glm::vec3 up (0, 0, -1);
  return glm::lookAt(eye, target, up);
}

glm::mat4 planeview()
{
  cam_rotate();
  bounding_box_t bdb= rocket.bounding_box();
  glm::vec4 p0=glm::vec4(0,0,1.0f,1.0f);
  p0    = p0*glm::rotate(glm::radians(rocket.rotation_yaw  ), glm::vec3(0, 1, 0));
  p0.y=0;
  p0    = p0*glm::rotate(glm::radians(rocket.rotation_pitch) , glm::vec3(1, 0, 0));
  glm::vec3 eye ( rocket.position.x +bdb.length*p0.x,rocket.position.y + bdb.length*p0.y , rocket.position.z - bdb.length*p0.z );
  glm::vec3 target (rocket.position.x + 10*p0.x, rocket.position.y + 10*p0.y, rocket.position.z-10*p0.z);
  glm::vec3 up (0, 1, 0);
  return glm::lookAt(eye, target, up);
}

glm::mat4 towerview()
{
    cam_rotate();
    glm::vec3 eye (-10, 15, 14);
    glm::vec3 target (rocket.position.x, rocket.position.y, rocket.position.z);
    glm::vec3 up (0, 1, 0);
    return glm::lookAt(eye, target, up);
}

glm::mat4 followview()
{
  cam_rotate();
  glm::vec4 p0=glm::vec4(0,0,1.0f,1.0f);
  p0    = p0*glm::rotate(glm::radians(yaw), glm::vec3(0, 1, 0));
  p0.y=0;
  // p0    = p0*glm::rotate(glm::radians(rocket.rotation_pitch) , glm::vec3(1, 0, 0));
  glm::vec3 eye ( -10*p0.x+ rocket.position.x, - 10*p0.y+ rocket.position.y + 2, 10*p0.z+ rocket.position.z);
  glm::vec3 target (rocket.position.x, rocket.position.y, rocket.position.z);
  glm::vec3 up (0, 1, 0); 
  return glm::lookAt(eye, target, up);
}

glm::mat4 heliview()
{
  double xpos,ypos;
  glfwGetCursorPos(window,&xpos,&ypos);
  float thetha = (360*(xpos/1000.0f) )*M_PI/180;
  float thetha1 = (360*((ypos+30)/1000.0f))*M_PI/180;
  glm::vec3 eye = rocket.position - dist*glm::vec3(cos(thetha)*sin(thetha1),cos(thetha1),sin(thetha)*sin(thetha1));
  glm::vec3 target (rocket.position.x, rocket.position.y, rocket.position.z);
  glm::vec3 up (0, 1, 0);
  return glm::lookAt(eye, target, up);
}

void cam_rotate()
{
  pitch = rocket.rotation_pitch;
  roll = rocket.rotation_roll;
  if(yaw != rocket.rotation_yaw)
  {
    if(yaw  >  rocket.rotation_yaw)
      yaw-=0.5f;
    else
      yaw+=0.5f;
  }
}

// bomb 
void drop_bomb()
{
  bomb_player.push_back(Bomb(rocket.position.x,rocket.position.y,rocket.position.z,0.07,COLOR_DARK_GREY,false));
  cout << yaw << " " << bomb_player[0].speedx <<" "<< bomb_player[0].speedy << " " << bomb_player[0].speedz <<endl;
}

// missle 
void launch_missle()
{
  if(rocket.launch==false)
  {
    system("aplay ../sound/Missile+1.wav &");
    missle_player.push_back(Missle(rocket.position.x+0.55f,rocket.position.y,rocket.position.z));
    missle_player.push_back(Missle(rocket.position.x-0.55f,rocket.position.y,rocket.position.z));
    missle_act_timer=glfwGetTime();
    rocket.launch=true;

  }
}

// Collision
void check_collision_overall()
{
  for (auto it =smoke_ring.begin(); it != smoke_ring.end(); it++) 
  {
      bounding_box_t a = (*it).bounding_box(), b=rocket.bounding_box();
      if(detect_collision(a,b))
      {
        Final_Score+=10;
        smoke_ring.erase(it);
        it--;
      }
  }

  for (auto it =volcanoes.begin(); it != volcanoes.end(); it++) 
  {
    bounding_box_t a = (*it).bounding_box(), b=rocket.bounding_box();
    if(detect_collision(a,b))
      rocket.hp -=5;
    for (auto it2 =missle_player.begin(); it2 != missle_player.end(); it2++) 
    {
      bounding_box_t c = (*it2).bounding_box();
      if(detect_collision(a,c))
      {
        missle_player.erase(it2);
        it2--;
      }
    }
    for (auto it2 =bomb_player.begin(); it2 != bomb_player.end(); it2++) 
    {
      bounding_box_t c = (*it2).bounding_box();
      if(detect_collision(a,c))
      {
        bomb_player.erase(it2);
        it2--;
      }
    }
  }

  for (auto it =bomb_dushman.begin(); it != bomb_dushman.end(); it++) 
  {
    bounding_box_t a = (*it).bounding_box(), b=rocket.bounding_box();
    if( (*it).position.y < sea_level)
    {
      bomb_dushman.erase(it);
      it--;
      continue;
    }
    if(detect_collision(a,b))
    {
      rocket.hp -= 10;
      bomb_dushman.erase(it);
      it--;
    }
  }

  for (auto it =fuel_up.begin(); it != fuel_up.end(); it++) 
  {
    bounding_box_t a = (*it).bounding_box(), b=rocket.bounding_box();
    if(detect_collision(a,b))
    {
      rocket.fuel += 100;
      if(rocket.fuel > 1000)
        rocket.fuel=1000;
      fuel_up.erase(it);
      it--;
    }
  }

  for (auto it =parachute_enemy.begin(); it != parachute_enemy.end(); it++) 
  {
    bounding_box_t a = (*it).bounding_box();
    if( (*it).position.y < sea_level)
    {
      (*it).position.y= 40.0f;
      (*it).position.x+= 1.0f;
    }
    for (auto it2 =bomb_player.begin(); it2 != bomb_player.end(); it2++) 
    {
      bounding_box_t b = (*it2).bounding_box();
      if(detect_collision(a,b))
      {
        if(start_explosion + 2.0 < glfwGetTime())
        {
          system("aplay ../sound/Explosion+2.wav & "); 
          start_explosion=glfwGetTime();
        }
        Final_Score+=10;
        bomb_player.erase(it2);
        parachute_enemy.erase(it);  // spawn again
        it2--;
        it--;
        break;
      }
    }
  }

  for (auto it =parachute_enemy.begin(); it != parachute_enemy.end(); it++) 
  {
    bounding_box_t a = (*it).bounding_box();
    if( (*it).position.y < sea_level)
    {
      (*it).position.y= 40.0f;
      (*it).position.x+= 1.0f;
    }
    for (auto it2 =missle_player.begin(); it2 != missle_player.end(); it2++) 
    {
      if( (*it2).start_time + 2.5f  < glfwGetTime())
      {
        missle_player.erase(it2);
        it2--;
      }
      bounding_box_t b = (*it2).bounding_box();
      if(detect_collision(a,b))
      {
        if(start_explosion + 2.0 < glfwGetTime())
        {
          system("aplay ../sound/Explosion+2.wav & "); 
          start_explosion=glfwGetTime();
        }
        Final_Score+=10;
        missle_player.erase(it2);
        parachute_enemy.erase(it);   /// spawn again
        it2--;
        it--;
        break;
      }
    }
  }

  for (auto it =missle_player.begin(); it != missle_player.end(); it++) 
  {
    bounding_box_t a = (*it).bounding_box();
    auto it2=enemy_base.begin();
    if(it2!=enemy_base.end())
    {
      bounding_box_t b = (*it2).bounding_box();
      if(detect_collision(a,b))
      {
        if(start_explosion + 2.0f < glfwGetTime())
        {
          system("aplay ../sound/Explosion+2.wav & "); 
          start_explosion=glfwGetTime();
        }
        (*it2).hp-=10;
        if((*it2).hp<=0)
        {
          enemy_base.erase(it2);
          system("killall -9 aplay &" );
          system("aplay ../sound/LNCRASH2.WAV & "); 
          Final_Score+=200;
          break;
        }
        missle_player.erase(it);
        it--;
      }
    }
  }
  for (auto it =bomb_player.begin(); it != bomb_player.end(); it++) 
  {
    bounding_box_t a = (*it).bounding_box();
    auto it2=enemy_base.begin();
    if(it2!=enemy_base.end())
    {
      bounding_box_t b = (*it2).bounding_box();
      if(detect_collision(a,b))
      {
        cout << start_explosion<<endl;
        if(start_explosion + 2.0 < glfwGetTime())
        {
          system("aplay ../sound/Explosion+2.wav & "); 
          start_explosion=glfwGetTime();
        }
        (*it2).hp-=5;
        if((*it2).hp<=0)
        {
          system("killall -9 aplay &" );
          system("aplay ../sound/LNCRASH2.WAV & "); 
          enemy_base.erase(it2);
          Final_Score+=200;
          destory_enemy++;
          if(destory_enemy==2)
          {
            quit(window);
            cout << "You Won"<<endl;
          }
          break;
        }
        bomb_player.erase(it);
        it--;
      }
    }
  }
}

int rnd(int a,int b)
{
  return a + rand()%(b-a +1);
}

void scroll(int xoffset, int yoffset) 
{
		if (yoffset == 1)
				dist = min(dist + 2.00f, 12.0f);
		else if (yoffset == -1)
				dist = max(dist - 2.00f, 8.0f);
}

void display(string s)
{
    digit.clear();
    for(int i = s.length()-1; i>=0 ; i--)
       digit.push_back( Sevensegment(0.9 - ((s.length()- i -1)*0.06),0.9,s[i],color_digit));
}