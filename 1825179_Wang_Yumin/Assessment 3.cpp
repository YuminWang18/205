#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include<iostream>
#include "stdlib.h"
#include <math.h>

GLfloat w = 1000;
GLfloat h = 1000;
GLfloat ln = 0.25;
double rotate_x = 0.0;
double rotate_y = 0.0;
double rotate_z = 0.0;


# define sunshine 1, 0.82, 0.65
#define BMP_Header_Length 54  // The offset of image data in memory block




double rect[8][3];             // Define the 8 vertices of a cuboid
double trape[8][3];            // Define a cuboid with a trapezoid bottom

// Define the texture object number
static GLuint texture_1;
static GLuint texture_2;
static GLuint texture_3;
static GLuint texture_4;
static GLuint texture_5;
static GLuint texture_6;
static GLuint texture_7;
static GLuint texture_8;
static GLuint texture_9;
static GLuint texture_10;
static GLuint texture_11;
static GLuint texture_12;
static GLuint texture_13;
static GLuint texture_14;
static GLuint texture_15;
static GLuint texture_16;
static GLuint texture_17;


static GLfloat angle = 0.0f;   // rotation angle 
// Material parameters
GLfloat matiral_specular[4] = { 0.00, 0.00, 0.00, 1.00 };  
GLfloat matiral_emission[4] = { 0.00, 0.00, 0.00, 1.00 };  
const GLfloat matiral_shininess = 11.00;



GLfloat sca[3] = { 1, 1, 1};
GLfloat tra[3] = { -300, 0, -300 };

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_position[] = { 1.0,1.0,0,0 };  // Light source location
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };


GLfloat AngleX;
GLfloat AngleY;


GLfloat bx = 0;  // The moving coordinates of the balloon in the swimming pool
GLfloat by = 0;
GLfloat bz = 0;


// Set the color and material parameters
void setMetiral(GLfloat matiral_diffuse_ambient[4])
{
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matiral_diffuse_ambient); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matiral_specular);  
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matiral_emission);  
	glMaterialf(GL_FRONT_AND_BACK, matiral_shininess, 0);   //Specular index
}

 

void trapezoid(double x, double y, double z, double x1, double y1, double z1) {  // trapezoid
	trape[0][0] = x;
	trape[0][1] = y;
	trape[0][2] = z;    

	trape[1][0] = x;
	trape[1][1] = y;
	trape[1][2] = z + z1;    

	trape[4][0] = x;
	trape[4][1] = y + y1;
	trape[4][2] = z;    

	trape[5][0] = x;
	trape[5][1] = y + y1;
	trape[5][2] = z + z1 / 2;      
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			trape[3][i] = trape[0][i] + x1;
			trape[2][i] = trape[1][i] + x1;
			trape[6][i] = trape[4][i] + x1;
			trape[7][i] = trape[5][i] + x1;
		}
		else {
			trape[3][i] = trape[0][i];
			trape[2][i] = trape[1][i];
			trape[6][i] = trape[4][i];
			trape[7][i] = trape[5][i];
		}
	}
}

void cuboid(double x, double y, double z, double x1, double y1, double z1) { //cuboid
	rect[0][0] = x;
	rect[0][1] = y;
	rect[0][2] = z;       

	rect[1][0] = x;
	rect[1][1] = y;
	rect[1][2] = z + z1;    
	rect[2][0] = x + x1;
	rect[2][1] = y;
	rect[2][2] = z + z1;    

	rect[3][0] = x + x1;
	rect[3][1] = y;
	rect[3][2] = z;        
	for (int i = 0; i < 4; i++) {  // for() loop to complete the remaining four points
		for (int j = 0; j < 3; j++) {
			if (j == 1)
				rect[i + 4][j] = rect[i][j] + y1;
			else
				rect[i + 4][j] = rect[i][j];
		}
	}
}

void build() {
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(rect[0][0], rect[0][1], rect[0][2]);
	glVertex3f(rect[1][0], rect[1][1], rect[1][2]);
	glVertex3f(rect[2][0], rect[2][1], rect[2][2]);
	glVertex3f(rect[3][0], rect[3][1], rect[3][2]);
	glEnd();   //     bottom

	glBegin(GL_POLYGON);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(rect[1][0], rect[1][1], rect[1][2]);
	glVertex3f(rect[0][0], rect[0][1], rect[0][2]);
	glVertex3f(rect[4][0], rect[4][1], rect[4][2]);
	glVertex3f(rect[5][0], rect[5][1], rect[5][2]);
	glEnd();   //   left

	glBegin(GL_POLYGON);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(rect[7][0], rect[7][1], rect[7][2]);
	glVertex3f(rect[6][0], rect[6][1], rect[6][2]);
	glVertex3f(rect[2][0], rect[2][1], rect[2][2]);
	glVertex3f(rect[3][0], rect[3][1], rect[3][2]);
	glEnd();     //   right

	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(rect[5][0], rect[5][1], rect[5][2]);
	glVertex3f(rect[6][0], rect[6][1], rect[6][2]);
	glVertex3f(rect[2][0], rect[2][1], rect[2][2]);
	glVertex3f(rect[1][0], rect[1][1], rect[1][2]);
	glEnd();     //    front

	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(rect[0][0], rect[0][1], rect[0][2]);
	glVertex3f(rect[3][0], rect[3][1], rect[3][2]);
	glVertex3f(rect[7][0], rect[7][1], rect[7][2]);
	glVertex3f(rect[4][0], rect[4][1], rect[4][2]);
	glEnd();     //   bak

	glBegin(GL_POLYGON);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(rect[4][0], rect[4][1], rect[4][2]);
	glVertex3f(rect[7][0], rect[7][1], rect[7][2]);
	glVertex3f(rect[6][0], rect[6][1], rect[6][2]);
	glVertex3f(rect[5][0], rect[5][1], rect[5][2]);
	glEnd();       //   top
}

void build2() {
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(trape[0][0], trape[0][1], trape[0][2]);
	glVertex3f(trape[1][0], trape[1][1], trape[1][2]);
	glVertex3f(trape[2][0], trape[2][1], trape[2][2]);
	glVertex3f(trape[3][0], trape[3][1], trape[3][2]);
	glEnd();   //   bottom

	glBegin(GL_POLYGON);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(trape[1][0], trape[1][1], trape[1][2]);
	glVertex3f(trape[0][0], trape[0][1], trape[0][2]);
	glVertex3f(trape[4][0], trape[4][1], trape[4][2]);
	glVertex3f(trape[5][0], trape[5][1], trape[5][2]);
	glEnd();       //  left

	glBegin(GL_POLYGON);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(trape[7][0], trape[7][1], trape[7][2]);
	glVertex3f(trape[6][0], trape[6][1], trape[6][2]);
	glVertex3f(trape[3][0], trape[3][1], trape[3][2]);
	glVertex3f(trape[2][0], trape[2][1], trape[2][2]);
	glEnd();   //    right

	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(trape[5][0], trape[5][1], trape[5][2]);
	glVertex3f(trape[6][0], trape[6][1], trape[6][2]);
	glVertex3f(trape[2][0], trape[2][1], trape[2][2]);
	glVertex3f(trape[1][0], trape[1][1], trape[1][2]);
	glEnd();   //     front

	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(trape[0][0], trape[0][1], trape[0][2]);
	glVertex3f(trape[3][0], trape[3][1], trape[3][2]);
	glVertex3f(trape[7][0], trape[7][1], trape[7][2]);
	glVertex3f(trape[4][0], trape[4][1], trape[4][2]);
	glEnd();   //     back

	glBegin(GL_POLYGON);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(trape[4][0], trape[4][1], trape[4][2]);
	glVertex3f(trape[7][0], trape[7][1], trape[7][2]);
	glVertex3f(trape[6][0], trape[6][1], trape[6][2]);
	glVertex3f(trape[5][0], trape[5][1], trape[5][2]);
	glEnd();   //   top
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();          //add matrix
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);



	glScalef(sca[0], sca[1], sca[2]);
	glTranslatef(tra[0], tra[1], tra[2]);



	//draw ground floor
	glBegin(GL_POLYGON);
	cuboid(-200, 0, -200, 1500, 10, 900);
	glColor3f(0.32,0.545,0.32);
	build();

	//draw formation
	glBegin(GL_POLYGON);
	cuboid(-200, -5, -200, 1500, 1,1100);
	glColor3f(128.0/255.0, 64.0/255.0, 64.0/255.0);
	build();

	// set texture 
	// Set materials
	GLfloat matiral_diffused[4] = { 0.20, 0.32, 0.80, 1.00 };
	setMetiral(matiral_diffused);

	glEnable(GL_TEXTURE_2D);    //grass
	glBindTexture(GL_TEXTURE_2D, texture_3);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-200, 11, -200);
	glTexCoord2f(0.0f, 5.0f); glVertex3f(-200, 11, 630);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(900, 11, 630);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(900, 11, -200);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);    //cement floor
	glBindTexture(GL_TEXTURE_2D, texture_2);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(900, 11, -200);
	glTexCoord2f(0.0f, 5.0f); glVertex3f(900, 11, 630);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(1300, 11, 630);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(1300, 11, -200);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);   //river
	glBindTexture(GL_TEXTURE_2D, texture_17);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-200, 11, 700);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-200, 11, 900);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1300, 11, 900);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1300, 11, 700);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//handrail
	cuboid(-200, 11, 700, 1500, 25, 2);
	glColor3f(1, 1, 1);
	build();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_16);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-200, 10, 703); 
	glTexCoord2f(5.0f, 0.0f); glVertex3f(1300, 10, 703); 
	glTexCoord2f(5.0f, 1.0f); glVertex3f(1300, 36, 703); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-200, 36, 703); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_16);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-200, 10, 699);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(1300, 10, 699); 
	glTexCoord2f(5.0f, 1.0f); glVertex3f(1300, 36, 699); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-200, 36, 699);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// courtyard walls
	glBegin(GL_POLYGON);
	cuboid(-100, 10, -100, 30, 100, 600);
	glColor3f(1,1,1);
	build();       
	cuboid(-80, 10, -100, 880, 100, 20);
	glColor3f(1,1,1);
	build();       
	cuboid(780, 10, -100, 20, 100, 600);
	glColor3f(1,1,1);
	build();       
	cuboid(-100, 10, 500, 110, 100, 20);
	glColor3f(1,1,1);
	build();       
	cuboid(270, 10, 500, 530, 100, 20);
	glColor3f(1,1,1);
	build();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_14);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100, 0, 521);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(10,0, 521); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10, 110, 521); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100, 110, 521); 
	glEnd();
	glDisable(GL_TEXTURE_2D); 

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_14);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(270, 0, 521); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(800, 0, 521); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(800,110, 521); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(270, 110, 521); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_14);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-80, 0, -79); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(800, 0, -79); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(800, 110, -79); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-80, 110, -79); 
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_14);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-101, 0, 522); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-101, 110, 522);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-101, 110, -100); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-101, 0, -100); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_14);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-69, 0, -80);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-69, 110, -80); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-69, 110, 500); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-69, 0, 500); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_14);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(769, 0, 500); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(769, 110, 500); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(769, 110, -80); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(769, 0, -80); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_14);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(801, 0, -100); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(801, 110, -100); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(801, 110, 522); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(801, 0, 522); 
	glEnd();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_14);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(800, 0, -101); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-100, 0, -101); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-100, 110, -101); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(800, 110, -101); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_14);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(800, 0, 499); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(270, 0, 499); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(270, 110, 499); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(800, 110, 499); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_14);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(10, 0, 499); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-100, 0, 499); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-100, 110, 499); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10, 110, 499); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//shopping mall
	cuboid(1000, 10,-100, 200, 200, 400);
	glColor3f(1,1,1);
	build();

	glEnable(GL_TEXTURE_2D);    //right
	glBindTexture(GL_TEXTURE_2D, texture_1);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1201, 10, -100); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1201, 210, -100); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1201, 210, 300); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1201, 10, 300); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	
	glEnable(GL_TEXTURE_2D);   //left 
	glBindTexture(GL_TEXTURE_2D, texture_1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(999, 10, -100); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(999, 10, 300); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(999, 210, 300); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(999, 210, -100); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);  //front
	glBindTexture(GL_TEXTURE_2D, texture_10);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1000, 10, 301); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1200, 10, 301);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1200, 210, 301); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1000, 210, 301); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);//back
	glBindTexture(GL_TEXTURE_2D, texture_12);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1000, 10, -101); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1000, 210, -101); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1200, 210, -101); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1200, 10, -101); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);  //top
	glBindTexture(GL_TEXTURE_2D, texture_13);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1000, 211, -100);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1000, 211, 300);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1200, 211, 300);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1200, 211, -100);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	//lamp pole
	glColor3f(0.10,0.10,0.10);
	for (int i = -60; i < 540; i += 200)
	{	
		cuboid(-90, 100, i, 6, 100, 6);
		build();  
		       
	}
	for (int i = -60; i < 540; i += 200)
	{
		cuboid(785, 100, i, 6, 100, 6);
		build();          
	}
	for (int i = -60; i < 780; i += 200)
	{
		cuboid(i, 100, -95, 6, 100, 6);
		build();          
	}
	for (int i = -60; i < 10; i += 45)
	{
		cuboid(i, 100, 510, 6, 100, 6);
		build();          
	}
	for (int i = 280; i < 800; i += 200)
	{
		cuboid(i, 100, 510, 6, 100, 6);
		build();         
	}

	//sunroom 
	glColor3f(1,1,1);
	cuboid(520, 10, 0, 10, 100, 220);
	build();
	cuboid(660, 10, 0, 10, 100, 220);
	build();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_15);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(519, 0, 220); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(519, 110, 220); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(519, 110, 0); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(519, 0, 0); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_15);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(671, 0, 0); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(671, 110, 0); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(671, 110, 220); 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(671, 0, 220); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(1, 0.97, 0.86);
	cuboid(600, 10, 100, 6, 30, 6);
	build();
	glColor3f(1, 0.97, 0.86);
	cuboid(640, 10, 100, 6, 30, 6);
	build();
	glColor3f(1, 0.97, 0.86);
	cuboid(640, 10, 125, 6, 30, 6);
	build();
	glColor3f(1, 0.97, 0.86);
	cuboid(600, 10, 125, 6, 30, 6);
	build();
	glColor3f(1, 0.97, 0.86);
	cuboid(590, 41, 90, 60, 10, 60);
	build();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_9);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(650, 51, 90);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(650, 51, 150);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(590, 51, 150);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(590, 51, 90);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(141.0/255.0, 193.0/255.0, 241.0/255.0);
	trapezoid(600, 10, 70, 40, 25, 20);
	build2();

	glColor3f(141.0/255.0, 193.0/255.0, 241.0/255.0);
	trapezoid(600, 10, 170, 40, 25, -20);
	build2();
	

	glColor4f(0.117, 0.180,0.227,0.15);
	cuboid(520, 110, 0, 150, 10, 220);
	build();


	//road to river
	for (int i = 0; i < 8; i++) {
		glBegin(GL_POLYGON);
		cuboid(i * 200 - 180, 10, 630, 30, 5, 70);
		glColor3f(0.545, 0.555, 0.398);
		build();
	}

	//swimming pool
	

	glColor3f(1,1,1);
	cuboid(490, 10, 275, 8, 12, 150);
	build();     //left
	glColor3f(1,1,1);
	cuboid(632, 10, 275, 8, 12, 150);
	build();     //right
	glColor3f(1,1,1);
	cuboid(498, 10, 275, 134, 12, 8);
	build();     //top
	glColor3f(1,1,1);
	cuboid(498, 10, 417, 134, 12, 8);
	build();     //bottom

	glEnable(GL_TEXTURE_2D);   
	glBindTexture(GL_TEXTURE_2D, texture_5);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(490, 16, 275);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(490, 16, 420);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(640, 16, 420);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(640, 16, 275);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	//mahjong table
	glColor3f(0.545, 0.278, 0.15);
	cuboid(200, 10, 100, 6, 30, 6);
	build();
	glColor3f(0.545, 0.278, 0.15);
	cuboid(220, 10, 100, 6, 30, 6);
	build();
	glColor3f(0.545, 0.278, 0.15);
	cuboid(220, 10, 125, 6, 30, 6);
	build();
	glColor3f(0.545, 0.278, 0.15);
	cuboid(200, 10, 125, 6, 30, 6);
	build();
	glColor3f(0, 1, 0);
	cuboid(190, 41, 90, 60, 10, 60);
	build();
	glEnable(GL_TEXTURE_2D);  
	glBindTexture(GL_TEXTURE_2D, texture_6);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(250, 51, 90);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(250, 51, 150);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(190, 51, 150);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(190, 51, 90);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//sofa
	glColor3f(1, 0.87, 0.78);
	cuboid(400, 10, 0, 6, 20, 6);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(420, 10, 0, 6, 20, 6);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(420, 10, 40, 6, 20, 6);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(400, 10, 40, 6, 20, 6);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(390, 31, -10, 40, 5, 60);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(430, 31, -10, 5, 25, 60);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(390, 31, -10, 45, 50, 5);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(390, 31, -10, 5, 25, 60);
	build();
	glColor3f(1, 1, 0);
	cuboid(410, 36, 10, 15, 5,15);
	build();

	glColor3f(1, 0.87, 0.78);
	cuboid(300, 10, 0, 6, 20, 6);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(320, 10, 0, 6, 20, 6);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(320, 10, 40, 6, 20, 6);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(300, 10, 40, 6, 20, 6);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(290, 31, -10, 40, 5, 60);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(330, 31, -10, 5, 25, 60);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(290, 31, -10, 45, 50, 5);
	build();
	glColor3f(1, 0.87, 0.78);
	cuboid(290, 31, -10, 5, 25, 60);
	build();
	glColor3f(1, 1, 0);
	cuboid(310, 36, 10, 15, 5, 15);
	build();



	
	//room wall
	glColor3f(1,1,1);
	cuboid(10, 10, -50, 12, 150, 297);
	build();     //left
	glColor3f(1,1,1);
	cuboid(438, 10, -50, 12, 150, 297);
	build();     //right
	glColor3f(1,1,1);
	cuboid(20, 10, -50, 425, 150, 12);
	build();     //top

	glColor3f(1,1,1);
	cuboid(22, 10, 235, 416, 35, 12);
	build();     //bottom1
	glColor3f(1,1,1);
	cuboid(22, 45, 235, 90, 65, 12);
	build();     //bottom2
	glColor3f(1,1,1);
	cuboid(200, 45, 235, 238, 65, 12);
	build();     //bottom3
	glColor3f(1,1,1);
	cuboid(22, 110, 235, 416, 50, 12);
	build();     //bottom4 

	//TV
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_8);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(420, 150, 234); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(420, 60, 234); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(300, 60, 234);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(300, 150, 234); 
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	

	//floor
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_4);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(22, 15, -50);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(22, 15, 235);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(438, 15, 235);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(438, 15, -50);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//bed
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_7);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(150, 16, 185);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(150, 16, 0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(50, 16, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(50, 16, 185);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//gate
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_11);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(10, 10, 510); 
	glTexCoord2f(1.0f, 0.0f); glVertex3f(115, 10, 611); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(115, 110, 611); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10, 110, 510); 
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_11);
	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(5, 10,490); 
	glTexCoord2f(1.0f, 1.0f); glVertex3f(5, 110, 490); 
	glTexCoord2f(0.0f, 1.0f); glVertex3f(122, 110, 606);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(122, 10, 606); 
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//window
	glColor4f(0,0,1, 0.25);
	cuboid(112, 45, 235, 88, 65, 12);
	build();

	//roof
	glColor4f(1,1,1,ln);
	cuboid(12, 160, -50, 435, 15, 350);
	build();
	
	//door
	glColor3f(244.0/255.0 ,164.0/255.0 , 96.0/255.0);
	cuboid(230, 10, 250, 50, 100, 5);
	build();              
	glColor3f(139.0/255.0 ,69.0/255.0,19.0/255.0);
	cuboid(235, 60, 255, 5, 5, 5);
	build();              
	//yard path
	for (int i = 0; i < 6; i++)
	{
		glColor3f(210.0/255.0, 105.0/255.0,  30.0/255.0);
		cuboid(235 - i , 10, 250 + i * 40, 50, 2, 20);
		build();
	}
	//sun
	glColor3f(1,0.647,0);
	glTranslatef(700, 500, 100);
	glutSolidSphere(55.0, 20, 20);
	glTranslatef(-700, -500, -100);

	//cloud 1
	glColor3f(1,1,1);
	glTranslatef(60, 300-by, 200);
	glutSolidSphere(30.0, 20, 20);  

	glTranslatef(60, 0, 0);
	glutSolidSphere(30.0, 20, 20);  

	glTranslatef(-30, 20, -0);
	glutSolidSphere(40.0, 20, 20);  

	
	glTranslatef(-90, -320+by, -200);

	//cloud 2
	glColor3f(1, 1, 1);
	glTranslatef(360+2*bx, 420, 10);
	glutSolidSphere(30.0, 20, 20);  

	glTranslatef(60, 0, 0);
	glutSolidSphere(30.0, 20, 20);  

	glTranslatef(-30, 20, -0);
	glutSolidSphere(40.0, 20, 20);  




	glTranslatef(-390-2*bx,-440,-10);

	//tree
	glColor3f(210.0/255.0, 105.0/255.0,  30.0/255.0);
	cuboid(60, 10, 390, 15, 100, 15);
	build();

	//leaves
	glColor3f(0.0,100.0/255.0,0.0);
	glTranslatef(60, 100, 400);
	glutSolidSphere(40.0, 20, 20);  

	glTranslatef(20, 0, 0);
	glutSolidSphere(40.0, 20, 20); 

	glTranslatef(-10, 0, -10);
	glutSolidSphere(40.0, 20, 20); 

	glTranslatef(0, 0, 20);
	glutSolidSphere(40.0, 20, 20); 

	glTranslatef(0, 10, -10);
	glutSolidSphere(40.0, 20, 20);  
	glTranslatef(-70, -80, -400);



	glColor3f(210.0/255.0, 105.0/255.0,  30.0/255.0);
	cuboid(360, -20, 390, 15, 100, 15);
	build();
	glColor3f(0.0,100.0/255.0,0.0);
	glTranslatef(360,100, 400);
	glutSolidSphere(40.0, 20, 20); 

	glTranslatef(20, 0, 0);
	glutSolidSphere(40.0, 20, 20);  

	glTranslatef(-10, 0, -10);
	glutSolidSphere(40.0, 20, 20); 

	glTranslatef(0, 0, 20);
	glutSolidSphere(40.0, 20, 20); 

	glTranslatef(0, 10, -10);
	glutSolidSphere(40.0, 20, 20);  
	glTranslatef(-70, -80, -400);

	glColor3f(210.0/255.0, 105.0/255.0,  30.0/255.0);
	cuboid(640, -60, 450, 15, 120, 15);
	build();
	glColor3f(0.0,100.0/255.0,0.0);
	glTranslatef(630, 100, 460);
	glutSolidSphere(45.0, 20, 20); 

	glTranslatef(40, 0, 0);
	glutSolidSphere(45.0, 20, 20);  

	glTranslatef(-20, 0, -20);
	glutSolidSphere(45.0, 20, 20);  
	glTranslatef(0, 0, 40);
	glutSolidSphere(45.0, 20, 20);  
	
	glTranslatef(0, 20, -20);
	glutSolidSphere(45.0, 20, 20);  
	glTranslatef(-650,-120, -460);


	glColor3f(210.0/255.0, 105.0/255.0,  30.0/255.0);
	cuboid(920, -60, 450, 15, 120, 15);
	build();
	glColor3f(0.0,100.0/255.0,0.0);
	glTranslatef(910, 100, 460);
	glutSolidSphere(45.0, 20, 20);  

	glTranslatef(40, 0, 0);
	glutSolidSphere(45.0, 20, 20);  

	glTranslatef(-20, 0, -20);
	glutSolidSphere(45.0, 20, 20);  
	glTranslatef(0, 0, 40);
	glutSolidSphere(45.0, 20, 20);  

	glTranslatef(0, 20, -20);
	glutSolidSphere(45.0, 20, 20);  
	glTranslatef(-930, -120, -460);
	
	//light bulb 
	glColor4f(1,0.96,0.56,0.8);
	glTranslatef(-385, 145, 145);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(0, 0, 200);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(0, 0, -400);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(30, 0, -40);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(200, 0, 0);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(200, 0, 0);
	glutSolidSphere(12.5, 20, 20); 
	glTranslatef(200, 0, 0);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(200, 0, 0);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(40, 0, 40);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(0, 0, 200);
	glutSolidSphere(12.5, 20, 20); 
	glTranslatef(0, 0, 200);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(-100, 0, 170);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(-200, 0, 0);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(-200, 0, 0);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(-295, 0, 0);
	glutSolidSphere(12.5, 20, 20);
	glTranslatef(-45, 0, 0);
	glutSolidSphere(12.5, 20, 20);

	glTranslatef(355, -145, -515);
	
	
	glRotatef(-45, 0, 1, 0);
	glTranslatef(80, -20, 80);
	cuboid(70, -30, 475, 150, 100, 7.5);
	glColor3f(1,1,1);
	build();

	//balloon
	glColor4f(255.0/255.0, 128.0/255.0, 0.0/255.0, 0.8);
	glTranslatef(350 - bx, -20 - by, 0 - bz);
	glutSolidSphere(15, 20, 20);
	glTranslatef(-500, -25, -250);
	glEnd();

	
	

	glFlush();  // refresh
	glutSwapBuffers();
}



void init(void)
{


	GLfloat sun_direction[] = { 700.0, 400.0, 100.0, 1.0 };
	GLfloat sun_intensity[] = { sunshine, 1.0 };
	GLfloat ambient_intensity[] = { 0.5, 0.5, 0.5, 1.0 };

	glEnable(GL_LIGHTING);              // Set up ambient light.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);
	

	glEnable(GL_LIGHT0);                // Set up sunlight.
	glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);

	glEnable(GL_COLOR_MATERIAL);        // Configure glColor().
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	glLineWidth(5);
	glClearColor(0.78, 0.98, 0.96, 0.0);      //background

	glEnable(GL_BLEND);  // open the mixture
	glDisable(GL_DEPTH_TEST);  // close the depth test
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
	glEnable(GL_DEPTH_TEST); // open the depth test
	glDepthFunc(GL_LEQUAL);

	glMatrixMode(GL_PROJECTION);     
	glOrtho(-w, 1.8*w, -h, 1.5*h, -1.8*w, 1.2*w); // specify clipping volume
}

//time function
int flag = 1;
void timerFunction(int value)
{
	if (flag == 1) {
		bx = bx + 6;
		by = by + 4;
		flag++;
	}
	else if (flag == 2) {
		bx = bx - 6;
		by = by - 4;
		flag--;
	}
	
	glutPostRedisplay();
	glutTimerFunc(1000, timerFunction, 1);
}





//keyboard interaction
void inputKey(unsigned char key, int x, int y) {   
	switch (key)
	{ 

	
	//balloon move
	case '1':
		bx -= 1;
		break;
	case '2':
		bx += 1;
		break;
	case '3':
		bz += 1;
		break;
	case '4':
		bz -= 1;
		break;
	//roof  transparency 
	case '5':
		ln += 0.05;
		break;
	case '6':
		ln -= 0.05;
		break;

	//rotate
	case 'd':
		rotate_y -= 1;
		break;
	case 'a':
		rotate_y += 1;
		break;
	case 's':
		rotate_x -= 1;
		break;
	case 'w':
		rotate_x += 1;
		break;

	//zoom out/ in
	case 'q':
		for (int i = 0; i < 3; i++)
			sca[i] = sca[i] + 0.1;
		break;
	
	case 'e':
		for (int i = 0; i < 3; i++)
			sca[i] = sca[i] - 0.1;
		break;

	//translate
	case '7':
		for (int i = 0; i < 3; i++)
			tra[i] = tra[i] + 5;
		    break;
	case '8':
		for (int i = 0; i < 3; i++)
			tra[i] = tra[i] - 5;
		    break;
	//exit
	case 'p':
		exit(0);
		break;

	}
	glutPostRedisplay();
}

//  determine if an integer is an integer power of 2
int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}


GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;
	FILE* pFile;
	errno_t err;

	// open file/ return
	if ((err = fopen_s(&pFile, file_name, "rb")) != 0)
	{
		printf("failure\n");            
		exit(0);                               
	}

	// Reads the width and height of an image in a file
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// Calculates the number of bytes of pixels per row and calculates the total number of pixel bytes based on this data
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// Allocate memory based on the total number of pixel bytes
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// 
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 500;
			const GLint new_height = 500; 
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// Calculates the number of bytes required per line and the total number of bytes
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

	
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// zoom in/ out
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// Release the original pixel data, point pixels to the new pixel data, and reset width and height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// Assign a new texture number
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// Bind a new texture
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //Restore the previous texture binding
	return texture_ID;
}

int main(int argc, char** argv)   
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(w-200, h-500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assessment 3");
	init();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);    // enable the texture
	texture_2 = load_texture("1.bmp");  // Loading textures
	texture_1 = load_texture("2.bmp");
	texture_3 = load_texture("3.bmp");
	texture_4 = load_texture("4.bmp");
	texture_5 = load_texture("5.bmp");
	texture_6 = load_texture("6.bmp");
	texture_7 = load_texture("7.bmp");
	texture_8 = load_texture("8.bmp");
	texture_9 = load_texture("9.bmp");
	texture_10 = load_texture("10.bmp");
	texture_11 = load_texture("11.bmp");
	texture_12 = load_texture("12.bmp");
	texture_13 = load_texture("13.bmp");
	texture_14 = load_texture("14.bmp");
	texture_15 = load_texture("15.bmp");
	texture_16 = load_texture("16.bmp");
	texture_17 = load_texture("17.bmp");

	glutDisplayFunc(display);
	glutKeyboardFunc(inputKey);  //keyboard
	glutTimerFunc(1000, timerFunction, 1);    //timer
	glutMainLoop();
	
}