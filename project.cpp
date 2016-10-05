#include<GL/glut.h>
#include<GL/glu.h>
#include<stdio.h>
#include<GL/gl.h>
#include<time.h>
#include<iostream>
#include<unistd.h>

void table(double tableWid, double tableThick, double legthick, double legLen);
void tableLeg(double thick, double len);
void display();
void light();

GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0}; 
GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0};
GLfloat redSpecularMaterial[] = {1.0, 0.0, 0.0};
GLfloat blueEmissiveMaterial[] = {0.0, 0.0, 1.0}; 
GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0};
GLfloat redAmbientMaterial[] = {1.0, 0.0, 0.0};
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; 
GLfloat redSpecularLight[] = {1.0, 0.0, 0.0};
GLfloat redAmbientLight[] = {1.0, 0.0, 0.0}; 
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; 
GLfloat blankMaterial[] = {0.0, 0.0, 0.0}; 
GLfloat mShininess[] = {128}; 

float lig_pos[]={-0.5,1.8,-0.5};
float lig_pos1[]={0.3,0.3,0.3};

bool diffuse = false;
bool emissive = false;
bool specular = false;
bool ambient = false;

void init (void) {
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    //glEnable (GL_LIGHT0);
}

void light (void) {
    glLightfv(GL_LIGHT0, GL_DIFFUSE,redDiffuseMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,redDiffuseMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,mShininess);
    glLightfv(GL_LIGHT0,GL_POSITION,lig_pos1);
    
    glLightfv(GL_LIGHT1, GL_SPECULAR, whiteSpecularLight);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,whiteSpecularMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
    glLightfv(GL_LIGHT1,GL_POSITION,lig_pos);
    
    glLightfv(GL_LIGHT2, GL_AMBIENT, redAmbientLight);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, redAmbientMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
    glLightfv(GL_LIGHT2,GL_POSITION,lig_pos1);
}

void axis (double length)
{
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0,0,length);
	glEnd();
	glPopMatrix();
}

void tableLeg(double thick, double len)
{
	glPushMatrix();
	glTranslated(0, len/2, 0);
	glScaled(thick, len, thick);	
	glutSolidCube(1.0);
	glPopMatrix();
}

void table(double tableWid, double tableThick, double legthick, double legLen)
{
	glPushMatrix();
	glTranslated(0,legLen, 0);
	glScaled(tableWid, tableThick, tableWid);
	glutSolidCube(1.0);
	glPopMatrix();
	double dist =0.95 *tableWid/2.0 - legthick / 2.0;
	glPushMatrix();
	glTranslated(dist,0,dist);
	tableLeg(legthick, legLen);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-dist,0,-dist);
	//tableLeg(legthick, legLen);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-dist,0,dist);
	tableLeg(legthick, legLen);
	glPopMatrix();
	glPushMatrix();
	glTranslated(dist,0,-dist);
	tableLeg(legthick, legLen);
	glPopMatrix();
}

void display()
{
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double winHt=10.0;
	glOrtho(-2.0 * 64/48.0, 2.0 * 64/48.0, -2.0, 2.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	light();
	gluLookAt(2.0,1.0,2.0,1.0,-0.4,-0.4,0.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3d(1.0,0.0,0.0);
	//axis(40);
	
	//glColor3d(1.0,0.0,0.0);
	
	glPushMatrix();
	glRotated(90,0, 1.0, 0);
	//axis(40);
	glRotated(-90, 1, 0, 0);
	//axis(40);
	glPopMatrix();
	
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glTranslated(1.0,0.0,0.0);
	GLfloat wall1[]={0.76,0.97,1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wall1);
	//glColor3d(0.76,0.97,1.0);
	table(6,0.02, 0.02, 0.7);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(1.74,-2.4,0.0);
	GLfloat wall2[]={1.0,0.87,0.67};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wall2);
	//glColor3d(1.0,0.87,0.67);
	table(6,0.02, 0.02, 0.7);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(1.74,-1.5,0.0);
	GLfloat table1[]={0.54,0.27,0.07};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, table1);
	//glColor3d(0.54,0.27,0.07);
	table(2.5, 0.02, 0.02, 0.7);
	glPopMatrix();
	
	glPushMatrix();
    	glTranslated(-2.11,-2.9,-5.0);
    	GLfloat line[]={0.0,0.0,0.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, line);
    	//glColor3d(0.0,0.0,0.0);
    	tableLeg(0.02,2.0);
    	glPopMatrix();
    	
    	glPushMatrix();
    	glRotated(-90, 1, 0, 0);
    	glTranslated(-1.55,-1.2,-2.2);
    	GLfloat line1[]={1.0,0.67,0.39};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, line1);
    	//glColor3d(1.0,0.67,0.39);
    	tableLeg(0.1,5.0);
    	glPopMatrix();
    	
    	glPushMatrix();
    	glRotated(90,0,0,1);
    	glTranslated(0.0,-4.95,-0.07);
    	GLfloat line2[]={1.0,0.67,0.39};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, line2);
    	//glColor3d(1.0,0.67,0.39);
    	tableLeg(0.1,5.0);
    	glPopMatrix();
    	
    	glPushMatrix();
	glTranslated(1.0,-1.5,-2.0);
	GLfloat teapot[]={0.84,0.75,0.84};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, teapot);
	//glColor3d(0.84,0.75,0.84);
	glutSolidTeapot(0.4);
	glPopMatrix();
	
	glPushMatrix();
    	glTranslated(-1.0,-2.5,-3.0);
    	GLfloat stand[]={0.75,0.75,0.75};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, stand);
    	//glColor3d(0.75,0.75,0.75);
    	tableLeg(0.074,1.5);
    	glPopMatrix();
    	
	glPushMatrix();        
        glRotatef(-90,1,0,0);
        glTranslated(-0.5,1.8,-0.5);
        GLfloat cone[]={0.96,0.96,0.86};
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cone);
    	//glColor3d(0.96,0.96,0.86);
    	glutSolidCone(0.4,0.6,10,8);
    	glPopMatrix();
    	
    	glPushMatrix();
	glTranslated(0.2,-1.5,0.0);
	GLfloat table3[]={0.54,0.27,0.07};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, table3);
	//glColor3d(0.54,0.27,0.07);
	table(1, 0.02, 0.02, 0.7);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(1.1,-2.8,0.0);
	GLfloat table4[]={0.54,0.27,0.07};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, table4);
	//glColor3d(0.54,0.27,0.07);
	table(1, 0.02, 0.02, 0.7);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(3.5,-1.7,0.0);
	GLfloat table5[]={0.54,0.27,0.07};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, table5);
	//glColor3d(0.54,0.27,0.07);
	table(1, 0.02, 0.02, 0.7);
	glPopMatrix();
    	
	glPushMatrix();
	glTranslated(-1.0,-2.3,0.0);
	GLfloat ball[]={1.0,0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ball);
	//glColor3d(1.0,0.8,0.0);
	glutSolidSphere(0.5,15,10);
	glPopMatrix();
	
	glFlush();
}	

void keyboard (unsigned char key, int x, int y) {
    if (key=='s') 
    {
        if (specular==false)
        {
            specular = true;
            glEnable(GL_LIGHT1);
        }
        else if (specular==true)
        {
            specular = false;
            glDisable(GL_LIGHT1);
            
        }
    }
    
    if (key=='d') 
    {
        if (diffuse==false)
        {
            diffuse = true;
            glEnable(GL_LIGHT0);
        }
        else if (diffuse==true)
        {
            diffuse = false;
            glDisable(GL_LIGHT0);
        }
    }
    
    if (key=='t') 
    {
        if (ambient==false)
        {
            ambient = true;
            glEnable(GL_LIGHT2);
        }
        else if (ambient==true)
        {
            ambient = false;
            glDisable(GL_LIGHT2);
        }
    }
    
    if (key=='e') 
    {
        if (emissive==false)
        {
            emissive = true;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,blueEmissiveMaterial);
        }
        else if (emissive==true)
        {
            emissive = false;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,greenEmissiveMaterial);
        }
    }
}

int main(int argc, char **argv)
{	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("3D viewing");
	init();
	glutDisplayFunc(display);
	glutIdleFunc (display);
	glutKeyboardFunc(keyboard);
	glClearColor(0.1f,0.1f,0.1f,0.0f);
	glViewport(0,0,640,480);
	glutMainLoop();
	return 0;
}
