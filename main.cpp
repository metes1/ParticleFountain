#include <math.h>
#include <list>
#include <stdlib.h>
#include <time.h> 
#include "mathLib3D.h"
#include "particleSystem.h"
#include "Particle.h"
#include <list>
#include <iostream>
#include <stdlib.h>

using namespace std;

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

//global variables
bool pause = false;
bool lights = false;
bool friction = true;
bool objects = false;
float eye[] = {-170, 20, 170};
float xRotate = 0.0;
float yRotate = 0.0;
float ang = 0.0;

//material variables
//[0] is red rubber
//[1] is cyan plastic
//[2] is brass
//[3] is silver
float m_amb[4][4] = {{0.05f, 0.0f, 0.0f, 1.0f},
                     {0.0f, 0.1f, 0.06f, 1.0f},
                     {0.329412f, 0.223529f, 0.027451f, 1.0f},
                     {0.23125f, 0.23125f, 0.23125f, 1.0f}};
float m_diff[4][4] = {{0.5f, 0.4f, 0.4f, 1.0f},
                     {0.0f, 0.50980392f, 0.50980392f, 1.0f},
                     {0.780392f, 0.568627f, 0.113725f, 1.0f},
                     {0.2775f, 0.2775f, 0.2775f, 1.0f}};
float m_spec[4][4] = {{0.7f, 0.04f, 0.04f, 1.0f},
                     {0.50196078f, 0.50196078f, 0.50196078f, 1.0f},
                     {0.992157f, 0.941176f, 0.807843f, 1.0f},
                     {0.773911f, 0.773911f, 0.773911f, 1.0f}};
float shiny[4] = {10.0f, 32.0f, 27.8974f, 89.6f};

//lighting variables
float light0_pos[4] = {-130.0f, 0.0f, 130.0f, 1.0f};
float light1_pos[4] = {130.0f, 0.0f, 130.0f, 1.0f};
float amb[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float diff[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float spec[4] = {1.0f, 1.0f, 1.0f, 1.0f};

particleSystem fountain;

//color particles based on if lights are on or off
void setColor(Particle p)
{
    if (lights == true) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb[p.material]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff[p.material]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec[p.material]);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny[p.material]);
    }
    else {
        glColor3f(p.colour[0], p.colour[1], p.colour[2]);
    }
}

//draw objects in the scene
void drawObjects()
{
    //draw long rectangular prism
    glBegin(GL_QUADS);  
    glColor3f(1, 1, 1);
    //front
    glNormal3f(-0.7071, 0, 0.7071);
    glVertex3f(-33, 0, 33);
    glNormal3f(0.7071, 0, 0.7071);
    glVertex3f(33, 0, 33);
    glNormal3f(0.6914, 0.2095, 0.6914);
    glVertex3f(33, 10, 33);
    glNormal3f(-0.6914, 0.2095, 0.6914);
    glVertex3f(-33, 10, 33);
      
    //top
    glNormal3f(-0.6914, 0.2095, 0.6914);
    glVertex3f(-33,10,33);
    glNormal3f(0.6914, 0.2095, 0.6914);
    glVertex3f(33,10,33);
    glNormal3f(0.4432, 0.1343, 0.8863);
    glVertex3f(33,10,66);
    glNormal3f(-0.4432, 0.1343, 0.8863);
    glVertex3f(-33,10,66);
    
    //bottom
    glNormal3f(-0.7071, 0, 0.7071);
    glVertex3f(-33,0,33);
    glNormal3f(0.7071, 0, 0.7071);
    glVertex3f(33,0,33);
    glNormal3f(0.4472, 0.0, 0.8944);
    glVertex3f(33,0,66);
    glNormal3f(-0.4472, 0.0, 0.8944);
    glVertex3f(-33,0,66);
    
    //left side
    glNormal3f(-0.6914, 0.2095, 0.6914);
    glVertex3f(-33,10,33);
    glNormal3f(-0.7071, 0, 0.7071);
    glVertex3f(-33,0,33);
    glNormal3f(-0.4472, 0.0, 0.8944);
    glVertex3f(-33,0,66);
    glNormal3f(-0.4432, 0.1343, 0.8863);
    glVertex3f(-33,10,66);
    
    //right side
    glNormal3f(0.6914, 0.2095, 0.6914);
    glVertex3f(33,10,33);
    glNormal3f(0.7071, 0, 0.7071);
    glVertex3f(33,0,33);
    glNormal3f(0.4472, 0.0, 0.8944);
    glVertex3f(33,0,66);
    glNormal3f(0.4432, 0.1343, 0.8863);
    glVertex3f(33,10,66);
    
    //back side
    glNormal3f(-0.4432, 0.1343, 0.8863);
    glVertex3f(-33,10,66);
    glNormal3f(-0.4472, 0.0, 0.8944);
    glVertex3f(-33,0,66);
    glNormal3f(0.4472, 0.0, 0.8944);
    glVertex3f(33,0,66);
    glNormal3f(0.4432, 0.1343, 0.8863);
    glVertex3f(33,10,66);
    glEnd();

    //draw tall rectangular prism
    glBegin(GL_QUADS);  
    glColor3f(1, 1, 1);
    //front
    glNormal3f(-0.7071, 0, -0.7071);
    glVertex3f(-80, 0, -80);
    glNormal3f(-0.6, 0.0, -0.8);
    glVertex3f(-60, 0, -80);
    glNormal3f(-0.4243, 0.7071, -0.5657);
    glVertex3f(-60, 100, -80);
    glNormal3f(-0.5298, 0.6623, -0.5298);
    glVertex3f(-80, 100, -80);
      
    //top
    glNormal3f(-0.5298, 0.6623, -0.5298);
    glVertex3f(-80,100,-80);
    glNormal3f(-0.4243, 0.7071, -0.5657);
    glVertex3f(-60,100,-80);
    glNormal3f(-0.4575, 0.7625, -0.4575);
    glVertex3f(-60,100,-60);
    glNormal3f(-0.5657, 0.7071, -0.4243);
    glVertex3f(-80,100,-60);
    
    //bottom
    glNormal3f(-0.7071, 0, -0.7071);
    glVertex3f(-80,0,-80);
    glNormal3f(-0.6, 0.0, -0.8);
    glVertex3f(-60,0,-80);
    glNormal3f(-0.7071, 0, -0.7071);
    glVertex3f(-60,0,-60);
    glNormal3f(-0.8, 0.0, -0.6);
    glVertex3f(-80,0,-60);
    
    //left side
    glNormal3f(-0.5298, 0.6623, -0.5298);
    glVertex3f(-80,100,-80);
    glNormal3f(-0.7071, 0, -0.7071);
    glVertex3f(-80,0,-80);
    glNormal3f(-0.8, 0.0, -0.6);
    glVertex3f(-80,0,-60);
    glNormal3f(-0.5657, 0.7071, -0.4243);
    glVertex3f(-80,100,-60);
    
    //right side
    glNormal3f(-0.4243, 0.7071, -0.5657);
    glVertex3f(-60,100,-80);
    glNormal3f(-0.6, 0.0, -0.8);
    glVertex3f(-60,0,-80);
    glNormal3f(-0.7071, 0, -0.7071);
    glVertex3f(-60,0,-60);
    glNormal3f(-0.4575, 0.7625, -0.4575);
    glVertex3f(-60,100,-60);
    
    //back side
    glNormal3f(-0.5657, 0.7071, -0.4243);
    glVertex3f(-80,100,-60);
    glNormal3f(-0.8, 0.0, -0.6);
    glVertex3f(-80,0,-60);
    glNormal3f(-0.7071, 0, -0.7071);
    glVertex3f(-60,0,-60);
    glNormal3f(-0.4575, 0.7625, -0.4575);
    glVertex3f(-60,100,-60);
    
    glEnd();
    
}

//display function - GLUT display callback function
void display(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 500);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //sets up camera
    gluLookAt(eye[0],eye[1],eye[2],0,0,0,0,1,0);

    glPushMatrix();
        //rotates scene
        glRotatef(xRotate, 1.0f, 0.0f, 0.0f);
        glRotatef(yRotate, 0.0f, 1.0f, 0.0f);

        //sets up lightning, lights rotate with scene
        glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
        glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
        glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
        glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
        glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
        
        //draws flat quad based on if lights are on or off
        glBegin(GL_QUADS);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb[3]);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_diff[3]);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec[3]);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny[3]);
            glColor3f(0.4, 0.4, 0.4);
            glNormal3f(-0.7071, 0, 0.7071);
            glVertex3f(-100,0,100);
            glNormal3f(0.7071, 0, 0.7071);
            glVertex3f(100,0,100);
            glNormal3f(0.7071, 0, -0.7071);
            glVertex3f(100,0,-100);
            glNormal3f(-0.7071, 0, -0.7071);
            glVertex3f(-100,0,-100);
        glEnd();

        if (objects == true)
            drawObjects();

        //draw each particle
        list<Particle>::iterator it;
        for (it = fountain.particles.begin(); it != fountain.particles.end(); it++){
            glPushMatrix();
                setColor(*it); //set colour
                glTranslatef(it->position.px, it->position.py, it->position.pz);
                glRotatef(ang, it->angle.dx, it->angle.dy, it->angle.dz);
                glutSolidSphere(it->size,20,20);
            glPopMatrix();
        }
    glPopMatrix();

    //switch our buffers for a smooth animation
    glutSwapBuffers();
    glutPostRedisplay();
}

//resets system and variables
void reset()
{
    //clears list of particles
    fountain.particles.clear();

    //reset global variables
    xRotate = 0.0;
    yRotate = 0.0;
    ang = 0.0;
    pause = false;
    friction = true;
    lights = false;
    objects = false;
    eye[0] = -170;
    eye[1] = 20;
    eye[2] = 170;
    glDisable(GL_LIGHTING);
}

//actions invoked by keyboard
void keyboard(unsigned char key, int xIn, int yIn)
{
    switch (key)
    {
        //starts/stops new particles from being generated
        case 32: //space bar
            pause = !pause;
            break;

        //friction mode toggle
        case 'f':
        case 'F':
            friction = !friction;
            break;

        //toggles lights on/off
        case 'l':
        case 'L':
        {
            lights = !lights;
            if (lights == true)
                glEnable(GL_LIGHTING);
            else if (lights == false)
                glDisable(GL_LIGHTING);
            break;
        }
        //resets simulation
        case 'r':
        case 'R':
            reset();
            break;
        //adds explosive particle to the system
        case 'e':
        case 'E':
        {
            fountain.addExplosive();
            break;
        }
        case 'o':
        case 'O':
        {
            fountain.particles.clear();//so objects don't get drawn on top of particles
            objects = !objects;
            break;
        }
        //quits program
        case 27: //ESC key
        case 'q':
        case 'Q':
            exit(0);
            break;
    }
}

//rotates scene using arrow keys
void specialKey(int key, int x, int y)
{
    switch(key)
    {
        //rotates scene about x axis
        case GLUT_KEY_UP:
            xRotate++;
            break;

        case GLUT_KEY_DOWN:
            xRotate--;
            break;

        //rotates scene about y axis
        case GLUT_KEY_RIGHT:
            yRotate--;
            break;

        case GLUT_KEY_LEFT:
            yRotate++;
            break;
    }
}

//frames per second
void FPS(int val){
    //continues to add particles when system isn't paused
    if (!pause){
        fountain.add();
    }
    //resets angle to 0 when it reaches 360
    if (ang != 360.0)
        ang++;
    else
        ang = 0.0;

    //updates particles positions, simulates animation
    fountain.update(friction);
    glutTimerFunc(17, FPS, 0); // 1sec = 1000, 60fps = 1000/60 = ~17
}

void projection(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(45,1,1,500);
}

//prints instructions to console
void instruct()
{
    cout << "---------------------------------------------------------\n";
    cout << "                 Keyboard Controls         \n";
    cout << "---------------------------------------------------------\n\n";
    cout << " Left-Arrow   => Rotate scene left on y-axis\n";
    cout << " Right-Arrow  => Rotate scene right on y-axis\n";
    cout << " Up-Arrow Key => Rotate scene on x-axis\n";
    cout << " Down-Arrow   => Rotate scene on x-axis\n";
    cout << " F            => Toggle friction mode\n";
    cout << " L            => Toggle lightning\n";
    cout << " E            => Add explosive particle\n";
    cout << " O            => Add objects to the scene\n";
    cout << " R            => Reset particle system\n";
    cout << " SPACE        => Stop/Start continuous particle addition\n";
    cout << " q/ESC        => Quit program\n";
    cout << "--------------------------------------------------------\n";

}

/* main function - program entry point */
int main(int argc, char** argv)
{
    srand(time(0)); //number randomizer

    instruct(); //prints instructions
	glutInit(&argc, argv);		//starts up GLUT
    glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Particle Fountain");	//creates the window

    //enable lights
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glEnable(GL_DEPTH_TEST);

    glClearColor(0,0,0,0);
    projection();

	glutDisplayFunc(display);   //registers "display" as the display callback function
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);

    glutTimerFunc(0, FPS, 0);

	glutMainLoop();				//starts the event glutMainLoop
	return(0);
}
