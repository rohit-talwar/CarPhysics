// additions 1. movement
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#include <GL/freeglut.h>
#include <sys/time.h>
using namespace std;
// the macros
#define pi 3.141592653
#define dtime 0.01
#define e 0.1
// the global variables
double t2;
//time_val t1;
float slider_cam,slider;
int siren_d = 1;
float x,z, theta;
float pre_x,pre_z,pre_theta;
float v, angle;  // car variables
int flag[20];
float hel_r,hel_theta,hel_phi;  // theta is in the x-y plane and phi is in the x-z plane
void initialize(void)
{
	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120,1,0.5,1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}
void track(){
	int i;
	glColor3f(0.623,0.713,0.803);
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(40, 0, -40);
	glVertex3f(40, 0, 40);
	glVertex3f(80, 0, 40);
	glVertex3f(80, 0, -40);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-40, 0, -40);
	glVertex3f(-40, 0, 40);
	glVertex3f(-80, 0, 40);
	glVertex3f(-80, 0, -40);
	glEnd();

	glPushMatrix();
	glRotatef(90,1,0,0);
	glTranslatef(0,40,0);
	gluPartialDisk(gluNewQuadric(),40,80,100,100,-90,180);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,1,0,0);
	glTranslatef(0,40,0);
	gluPartialDisk(gluNewQuadric(),40,80,100,100,-90,180);
	glPopMatrix();

	glColor3f(0,0.803,0.4);
	//ground
	glBegin(GL_QUADS);
	glVertex3f(200,-1,200);
	glVertex3f(200,-1,-200);
	glVertex3f(-200,-1,-200);
	glVertex3f(-200,-1,200);
	glEnd();

	glColor3f(0,0.9607,1);
	//roof
	glBegin(GL_QUADS);
	glVertex3f(200,200,200);
	glVertex3f(200,200,-200);
	glVertex3f(-200,200,-200);
	glVertex3f(-200,200,200);
	glEnd();

	//front wall
	glBegin(GL_QUADS);
	glVertex3f(200,200,-200);
	glVertex3f(200,-200,-200);
	glVertex3f(-200,-200,-200);
	glVertex3f(-200,200,-200);
	glEnd();
	
	//back wall
	glBegin(GL_QUADS);
	glVertex3f(200,200,200);
	glVertex3f(200,-200,200);
	glVertex3f(-200,-200,200);
	glVertex3f(-200,200,200);
	glEnd();
	
	//left wall
	glBegin(GL_QUADS);
	glVertex3f(-200,200,200);
	glVertex3f(-200,-200,200);
	glVertex3f(-200,-200,-200);
	glVertex3f(-200,200,-200);
	glEnd();
	
	//right wall
	glBegin(GL_QUADS);
	glVertex3f(200,200,200);
	glVertex3f(200,-200,200);
	glVertex3f(200,-200,-200);
	glVertex3f(200,200,-200);
	glEnd();
	glPopMatrix();
/*	glBegin(GL_LINE);
	glVertex3f(40, 0, -40);
	glVertex3f(40, 0, 40);
	glVertex3f(80, 0, -40);
	glVertex3f(80, 0, 40);
	glVertex3f(-40, 0, -40);

	glVertex3f(-40, 0, 40);
	glVertex3f(-80, 0, -40);
	glVertex3f(-80, 0, 40);
	for(i=180;i<360;i++)
		glVertex3f(40*cos(i*(pi/180)),0,-40+40*sin(i*(pi/180)));
	for(i=180;i<360;i++)
		glVertex3f(80*cos(i*(pi/180)),0,-40+80*sin(i*(pi/180)));
	for(i=0;i<180;i++)
		glVertex3f(40*cos(i*(pi/180)),0,40+40*sin(i*(pi/180)));
	for(i=0;i<180;i++)
		glVertex3f(80*cos(i*(pi/180)),0,40+80*sin(i*(pi/180)));
	glEnd();
	*/
}

void car(){
	//glPushMatrix();
	glColor3f(1,0.647,0);
	glBegin(GL_QUADS);
	glVertex3f( -5, 5, 10);
	glVertex3f( -5, 5,-10);
	glVertex3f( -5, 10, -10);
	glVertex3f( -5, 10, 10);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f( 5, 5,  10);
	glVertex3f( 5, 5, -10);
	glVertex3f( 5, 10,-10);
	glVertex3f( 5, 10, 10);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(  5, 5, 10);
	glVertex3f( -5, 5, 10);
	glVertex3f( -5, 5,-10);
	glVertex3f(  5, 5,-10);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(  5, 10, 10);
	glVertex3f( -5, 10, 10);
	glVertex3f( -5, 10, -10);
	glVertex3f(  5, 10, -10);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(  5, 10, -10);
	glVertex3f( -5, 10, -10);
	glVertex3f( -5, 5, -10);
	glVertex3f(  5, 5, -10);
	glEnd();
	glColor3f(1,0,0); // steering wheel
	glPushMatrix();
	glTranslatef(0,7,10);
	glRotatef(angle,0,0,1);
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<360;i++)
	{
		glVertex3f(2*cos(i*(pi/180)),2*sin(i*(pi/180)),0);
	}
	glEnd();
	glBegin(GL_LINE);
	//	glVertex3f(2*cos(90*(3.14/180)),2*sin(90*(3.14/180)),0);
	//	glVertex3f(2*cos(270*(3.14/180)),2*sin(270*(3.14/180)),0);
	glVertex3f(2*cos(180*(3.14/180)),2*sin(180*(3.14/180)),0);
	glVertex3f(2*cos(0*(3.14/180)),2*sin(0*(3.14/180)),0);
	glVertex3f(2*cos(45*(3.14/180)),2*sin(45*(3.14/180)),0);
	glVertex3f(2*cos(225*(3.14/180)),2*sin(225*(3.14/180)),0);
	glVertex3f(2*cos(135*(3.14/180)),2*sin(135*(3.14/180)),0);
	glVertex3f(2*cos(315*(3.14/180)),2*sin(315*(3.14/180)),0);
	glEnd();

	glPopMatrix();
	// siren code 
	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(slider,12,0); // center of the polygon or rail made above
	glBegin(GL_POLYGON);
	glVertex3f(2,-1.9,2);
	glVertex3f(-2,-1.9,2);
	glVertex3f(-2,-1.9,-2);
	glVertex3f(2,-1.9,-2);
	
	glEnd();
	glRotatef(slider_cam,0,1,0);
	glBegin(GL_POLYGON);
	for(int i=0;i<360;i++)
	{
		glVertex2f(2*cos(i*(pi/180)),2*sin(i*(pi/180)));
	}
	glEnd();
	glPopMatrix();
	// wheels left front
	glColor3f(0,1,0);
	
	glPushMatrix();
	glTranslatef(-5,2.5,7.5); 
	glRotatef(angle,0,-1,0);
	glBegin(GL_POLYGON);
	for(int i=0;i<360;i++)
	{
		glVertex3f(0,2.5*cos(i*(pi/180)),2.5*sin(i*(pi/180)));
	}
	glEnd();
	glPopMatrix();

	glBegin(GL_POLYGON);
	for(int i=0;i<360;i++)
	{
		glVertex3f(-5,2.5+2.5*cos(i*(pi/180)),-7.5+2.5*sin(i*(pi/180)));
	}
	glEnd();
	
	glPushMatrix();
	glTranslatef(5,2.5,7.5); 
	glRotatef(angle,0,-1,0);
	glBegin(GL_POLYGON);
	for(int i=0;i<360;i++)
	{
		glVertex3f(0,2.5*cos(i*(pi/180)),2.5*sin(i*(pi/180)));
	}
	glEnd();
	glPopMatrix();
	
	glBegin(GL_POLYGON);
	for(int i=0;i<360;i++)
	{
		glVertex3f(5,2.5+2.5*cos(i*(pi/180)),-7.5+2.5*sin(i*(pi/180)));
	}
	glEnd();
}
void keyboard (unsigned char key, int x, int y) {
	int i;
	if( key==27 )
		exit(0);
	if ( key == 'w'){
		v = v + 1;
	}
	if ( key == 's'){
		v = v - 1;
	}
	if ( key == 'h'){
		v = 0;
	}
	if ( key == 'd'){
		angle = angle + 5;
		if(angle >= 45 )
			angle = 45;
	}
	if ( key == 'a'){
		angle = angle - 5;
		if(angle < -45 )
			angle = -45;
	}
	if ( key == '1'){
		for(i=0;i<20;i++)
			flag[i]=0;
		flag[1] = 1;
	}
	if ( key == '2'){
		for(i=0;i<20;i++)
			flag[i]=0;
		flag[2] = 1;
	}
	if ( key == '3'){
		for(i=0;i<20;i++)
			flag[i]=0;
		flag[3] = 1;
	}
	if ( key == '4'){
		for(i=0;i<20;i++)
			flag[i]=0;
		flag[4] = 1;
	}
	if ( key == '5'){
		for(i=0;i<20;i++)
			flag[i]=0;
		flag[5] = 1;
	}
	if ( key == '6'){
		for(i=0;i<20;i++)
			flag[i]=0;
		flag[6] = 1;
	}
	if ( key == '7'){
		for(i=0;i<20;i++)
			flag[i]=0;
		flag[7] = 1;
	}
	if ( key == '8'){
		for(i=0;i<20;i++)
			flag[i]=0;
		flag[8] = 1;
	}
	if ( key == '9'){
		for(i=0;i<20;i++)
			flag[i]=0;
		flag[9] = 1;
	}
}
void keyup(unsigned char key, int x, int y) {
}
int pressed;
void mouse(int button, int state, int x, int y){
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
		pressed = 1;
	if(button==3){
		hel_r += 2;
	}
	if(button==4 && hel_r > 2){
		hel_r -= 2;
	}
}
int xfin = 0, xini = 0, yfin = 0, yini = 0;
void mousemotion(int x,int y){
	xfin = x;
	yfin = y;
	if(pressed == 1){
		if (xfin>xini)
			hel_phi++;
		if (xfin<xini)
			hel_phi--;
		if (yfin<yini){
			if((hel_theta+1)<=90 && (hel_theta+1)>0)
				hel_theta++;
		}
		if (yfin>yini ){
			if((hel_theta-1)<=90 && (hel_theta-1)>0)
			hel_theta--;
		}
	}
	xini = xfin;
	yini = yfin;
}




void draw(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
//	gluLookAt(0,50,0,0,0,0,0,0,-1);
	if(flag[1] == 1)
		gluLookAt(x-7*sin(theta*(pi/180)),7.5,z+7*cos(theta*(pi/180)),x-50*sin(theta*(pi/180)),0,z+50*cos(theta*(pi/180)),0,1,0);   // driver view
	if(flag[2] == 1)
		gluLookAt(x,13,z,x-50*sin(theta*(pi/180)),0,z+50*cos(theta*(pi/180)),0,1,0);   // top view
	if(flag[3] == 1)
		gluLookAt(x+slider*cos(theta*(pi/180)),12,z+slider*sin(theta*(pi/180)),x-50*sin(theta*(pi/180)),0,z+50*cos(theta*(pi/180)),0,1,0);   // sliding box
	if(flag[4] == 1)
		gluLookAt(x+slider*cos(theta*(pi/180)),12,z+slider*sin(theta*(pi/180)),x+sin(slider_cam*(pi/180)),12,z+cos(slider_cam*(pi/180)),0,1,0);  // search light
	if(flag[5] == 1)
		gluLookAt(x+5*cos(theta*(pi/180))-5.5*sin(theta*(pi/180)),2.5,z+5*sin(theta*(pi/180))+5.5*cos(theta*(pi/180)),x+5*cos(theta*(pi/180))-20*sin(theta*(pi/180)),2.5,z+5*sin(theta*(pi/180))+20*cos(theta*(pi/180)),0,1,0);   // wheel view u see the wheel here only
	if(flag[6] == 1)
		gluLookAt(x+5*cos(theta*(pi/180))-7.5*sin(theta*(pi/180)),2.5,z+5*sin(theta*(pi/180))+7.5*cos(theta*(pi/180)),x+5*cos((theta+angle)*(pi/180))-20*sin((theta+angle)*(pi/180)),2.5,z+5*sin((theta+angle)*(pi/180))+20*cos((theta+angle)*(pi/180)),0,1,0);   // wheel view u see what wheel sees
	if(flag[7] == 1)
		gluLookAt(x+5*cos(theta*(pi/180))-5.5*sin(theta*(pi/180)),2.5,z+5*sin(theta*(pi/180))+5.5*cos(theta*(pi/180)),x+5*cos((theta+angle)*(pi/180))-20*sin((theta+angle)*(pi/180)),2.5,z+5*sin((theta+angle)*(pi/180))+20*cos((theta+angle)*(pi/180)),0,1,0);   // wheel view u see in which direction wheel sees
	if(flag[8] == 1)
		gluLookAt(x+20*sin(theta*(pi/180)),25,z-20*cos(theta*(pi/180)),x-10*sin((theta)*(pi/180)),15,z+10*cos((theta)*(pi/180)),0,1,0);  // gamer view
	if(flag[9] == 1)
		gluLookAt(hel_r*sin(hel_theta*pi/180)*cos(hel_phi*pi/180),hel_r*cos(hel_theta*pi/180),hel_r*sin(hel_theta*pi/180)*sin(hel_phi*pi/180),0,0,0,0,1,0);  // helicopter view
	
	track();
	glPushMatrix();
	glTranslatef(x,0,z);
	glRotatef(theta,0,-1,0);
	car();
	glPopMatrix();
/*	glColor3f(1,1,1);
	char sc[100];
	sprintf(sc,"Velocity %f",v);
	glRasterPos3d(200 ,10 ,0);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)sc );
*/	
	glutSwapBuffers();
}
int in_out(float x,float z){
	if(z > -40 && z < 40){
		if(x > -80 && x < -40){
			return 1;
		}
		if(x < 80 && x > 40 ){
			return 1;
		}
	}else{
		if(((x*x+(z-40)*(z-40)) > 1600) && (((x*x)+(z-40)*(z-40)) < 6400)) {
			return 1;
		}
		if(((x*x+(z+40)*(z+40)) > 1600) && (((x*x)+(z+40)*(z+40)) < 6400) ) {
			return 1;
		}
	}
	return -1;
}


void calculations(void){
	pre_x = x;
	pre_z = z;
	pre_theta = theta;
/*	int a;
	a = in_out((x+5*cos(theta*pi/180)-10*sin(theta*pi/180)),(z+5*sin(theta*pi/180)+10*cos(theta*pi/180)));
	a += in_out((x+5*cos(theta*pi/180)+10*sin(theta*pi/180)),(z+5*sin(theta*pi/180)-10*cos(theta*pi/180)));
	a += in_out((x-5*cos(theta*pi/180)+10*sin(theta*pi/180)),(z-5*sin(theta*pi/180)-10*cos(theta*pi/180)));
	a += in_out((x-5*cos(theta*pi/180)-10*sin(theta*pi/180)),(z-5*sin(theta*pi/180)+10*cos(theta*pi/180)));
	if(a != 4){
		v = -v;
	}
*/
	printf("hel theta %f\n",hel_theta);
	if(slider > 5 || slider < -5)
		siren_d *= -1;
	slider = slider + siren_d*0.1;
	slider_cam += 0.5 ;
	// ffriction of the steering and wheels
	printf("angle %f\n",angle);
	printf("theta %f\n",theta);
	printf("velocity %f\n",v);
	//	printf("angle %f\n",angle);
	if(angle >= -45 && angle < 0){
		angle +=0.5 ;
		//if(angle > -0.2)
		//	angle = 0;
	}
	if(angle <= 45 && angle > 0){
		angle -= 0.5;
		//if(angle < 0.2)
		//	angle = 0;
	}
	if(v > 0 && v!=0){  
		v -= 0.02;
		if(v < 0.2)
			v = 0;
	}
	if(v < 0 && v!=0){
		v += 0.02;
		if(v > -0.2)
			v = 0;
	}
		float i,k; // change in x and z angles
		if(v>=0){
			x -= v*sin(theta*(pi/180))*dtime;
			z += v*cos(theta*(pi/180))*dtime;
			i = v*sin(theta*(pi/180)) + v*dtime*sin((theta+angle)*(pi/180));  // positive in the -x axis
			k = v*cos(theta*(pi/180)) + v*dtime*cos((theta+angle)*(pi/180));  // positive in the +z axis
			if(k>0){
				theta = atan(i/k) * 180/pi;
			}
			if(k<0){
				theta = (pi-atan(-i/k)) * 180/pi;
			}
			if(k==0){
				if(i>0)
					theta = 90;
				if(i<0)
					theta = -90;
				//		if(i==0)
				//			theta = 0;
			}
		}else{ 	
			float v_neg, theta_neg;// negative velocity
			v_neg = -v;
			//	theta_neg = theta+180;
			x += v_neg*sin(theta*(pi/180))*dtime;
			z -= v_neg*cos(theta*(pi/180))*dtime;
			i = v_neg*sin(theta*(pi/180)) - v_neg*dtime*sin((theta+angle)*(pi/180));  
			k = v_neg*cos(theta*(pi/180)) - v_neg*dtime*cos((theta+angle)*(pi/180));  
			if(k>0){
				theta = atan(i/k) * 180/pi;

			}
			if(k<0){
				theta = (pi-atan(-i/k)) * 180/pi;
			}
			if(k==0){
				if(i>0)
					theta = 90;
				if(i<0)
					theta = -90;
			}
		}
	int a;
	a = in_out((x+5*cos(theta*pi/180)-10*sin(theta*pi/180)),(z+5*sin(theta*pi/180)+10*cos(theta*pi/180)));
	a += in_out((x+5*cos(theta*pi/180)+10*sin(theta*pi/180)),(z+5*sin(theta*pi/180)-10*cos(theta*pi/180)));
	a += in_out((x-5*cos(theta*pi/180)+10*sin(theta*pi/180)),(z-5*sin(theta*pi/180)-10*cos(theta*pi/180)));
	a += in_out((x-5*cos(theta*pi/180)-10*sin(theta*pi/180)),(z-5*sin(theta*pi/180)+10*cos(theta*pi/180)));
	if(a!=4){
		x = pre_x;
		z= pre_z;
		theta = pre_theta;
		v = -e*v;
	}

	draw();
}
int main(int argc,char **argv)
{
	v = 1;
	angle = 0;
	x = 50;
	z = 0;
	theta = 0;
	hel_r = 100;
	hel_theta = 1;
	hel_phi = 0;

	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(1,1);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
	glutCreateWindow("F1 Racing");
	glutDisplayFunc(draw);
	glutIdleFunc(calculations);
	glutKeyboardFunc(keyboard);
	glutMouseFunc( mouse );
	glutMotionFunc( mousemotion );
	//glutKeyboardUpFunc(keyup);
	initialize();
	glutMainLoop();
	return 0;
}
