//	Some code

//#include<windows.h>
#include<stdlib.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include<iostream>
#include<cmath>
//#include<windows.h>
#include<stdlib.h>

using namespace std;

struct gridblock
{
    bool occ;
    GLfloat col_arr[3];
    GLfloat trans[3];
}grid[6][15];

bool win=false,lose=false;

GLint blockI1,blockI2,blockJ1,blockJ2;

void reshape(int,int);
void init(void);
void display(void);
void camera(void);
void specialKeys(int,int,int);
void initgrid();

int width,height,cubeLen=2,blockPosition=1;

GLfloat tranX=0.0,tranY=cubeLen,tranZ=0.0,scaleX=1,scaleY=2,scaleZ=1;

GLfloat greenDiffuseMaterial[] = {0.0, 1.0, 0.0}; //set the material to red
GLfloat blueDiffuseMaterial[] = {0.0, 0.0, 1.0}; //set the material to blue
GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0}; //set the material to red
GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0}; //set the material to white
//GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0}; //set the material to green
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; //set the light specular to white
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; //set the light ambient to black
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; //set the diffuse light to white
//GLfloat blankMaterial[] = {0.0, 0.0, 0.0}; //set the diffuse light to white
GLfloat mShininess[] = {128}; //set the shininess of the material
GLfloat LightPosition[] = {0.25, 0.25, 0.25, 0.0}; //set the LightPosition to the specified values

int main (int argc,char **argv) {
	glutInit (&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(1364,689);
	glutInitWindowPosition(0,0);
	glutCreateWindow("BlockX");
	init();
	initgrid();
	glutDisplayFunc(display);
	glutIdleFunc(display);
//	glutKeyboardFunc(keyboard);
//	glutMouseFunc(mouse);
//	glutPassiveMotionFunc(passive);
	glutSpecialFunc(specialKeys);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void display(void) {
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	camera();

	glRotatef(30,1,0,0);
	glRotatef(30,0,1,0);

    for(int i=0;i<6;i++)
    {
        for(int j=0;j<15;j++)
        {
            if(grid[i][j].occ)
            {
                glPushMatrix();
                glColor3f(grid[i][j].col_arr[0],grid[i][j].col_arr[1],grid[i][j].col_arr[2]);
                glTranslatef(grid[i][j].trans[0],grid[i][j].trans[1],grid[i][j].trans[2]);
//                glScalef(1.0,1,1.0);
                glutSolidCube(2.0);
                glPopMatrix();
            }
        }
    }


//	glTranslatef(0,4,0);
//	glScalef(1,2,1);
//	glutSolidCube(cubeLen);


	glTranslatef(tranX,tranY+cubeLen/2.0,tranZ);
	glScalef(scaleX,scaleY,scaleZ);
	glutSolidCube(cubeLen);

	glutSwapBuffers();

	if(lose)
		tranY-=0.1;
	if(win)
		tranY+=0.1;
}

void camera(void) {
	glRotatef(0.0,1.0,0.0,0.0);
	glRotatef(0.0,0.0,1.0,0.0);
//	glRotatef(1.0,0.0,0.0,.0);
	glTranslated(0,0,-40);
}

void init(void) {
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
	glLightfv (GL_LIGHT0, GL_POSITION, LightPosition); //change the light accordingly
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
}

void reshape(int w, int h) {
	width=w; height=h;
	glViewport(0,0,(GLsizei)w,(GLsizei)h); 			//set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); 				//set the matrix to projection
	glLoadIdentity();
	gluPerspective(60,(GLfloat)w/(GLfloat)h,1.0,100.0); 	//set the perspective (angle of sight, width, height, , depth)
	glMatrixMode(GL_MODELVIEW); 				//set the matrix back to model
}

void initgrid()
{
    grid[0][0].occ=false;//1st row
    grid[0][0].trans={-25.0,0.0,-20.0};
    //grid[0][0].col_arr={1.0,1.0,0.0};
    grid[0][1].occ=false;
    grid[0][1].trans={-23.0,0.0,-20.0};
    //grid[0][0].col_arr={1.0,1.0,0.0};
    grid[0][2].occ=false;
    grid[0][2].trans={-21.0,0.0,-20.0};
    //grid[0][0].col_arr={1.0,1.0,0.0};
    grid[0][3].occ=false;
    grid[0][3].trans={-19.0,0.0,-20.0};
    //grid[0][3].col_arr={1.0,1.0,0.0};
    grid[0][4].occ=false;
    grid[0][4].trans={-17.0,0.0,-20.0};
    //grid[0][0].col_arr={1.0,1.0,0.0};
    grid[0][5].occ=false;
    grid[0][5].trans={-15.0,0.0,-20.0};
    //grid[0][5].col_arr={1.0,1.0,0.0};


    grid[0][6].occ=true;
    grid[0][6].trans={-13.0,0.0,-20.0};
    grid[0][6].col_arr={1.0,1.0,0.0};
    grid[0][7].occ=true;
    grid[0][7].trans={-11.0,0.0,-20.0};
    grid[0][7].col_arr={0.0,0.0,1.0};
    grid[0][8].occ=true;
    grid[0][8].trans={-9.0,0.0,-20.0};
    grid[0][8].col_arr={1.0,1.0,0.0};
    grid[0][9].occ=true;
    grid[0][9].trans={-7.0,0.0,-20.0};
    grid[0][9].col_arr={0.0,0.0,1.0};
    grid[0][10].occ=true;
    grid[0][10].trans={-5.0,0.0,-20.0};
    grid[0][10].col_arr={1.0,1.0,0.0};
    grid[0][11].occ=true;
    grid[0][11].trans={-3.0,0.0,-20.0};
    grid[0][11].col_arr={0.0,0.0,1.0};
    grid[0][12].occ=true;
    grid[0][12].trans={-1.0,0.0,-20.0};
    grid[0][12].col_arr={1.0,1.0,0.0};

    grid[0][13].occ=false;
    grid[0][13].trans={1.0,0.0,-20.0};
    grid[0][14].occ=false;
    grid[0][14].trans={3.0,0.0,-20.0};

    grid[1][0].occ=true;//2nd row
    grid[1][0].trans={-25.0,0.0,-18.0};
    grid[1][0].col_arr={0.0,0.0,1.0};
    grid[1][1].occ=true;
    grid[1][1].trans={-23.0,0.0,-18.0};
    grid[1][1].col_arr={1.0,1.0,0.0};
    grid[1][2].occ=true;
    grid[1][2].trans={-21.0,0.0,-18.0};
    grid[1][2].col_arr={0.0,0.0,1.0};
    grid[1][3].occ=true;
    grid[1][3].trans={-19.0,0.0,-18.0};
    grid[1][3].col_arr={1.0,1.0,0.0};


    grid[1][4].occ=false;
    grid[1][4].trans={-17.0,0.0,-18.0};
    grid[1][5].occ=false;
    grid[1][5].trans={-15.0,0.0,-18.0};


    grid[1][6].occ=true;
    grid[1][6].trans={-13.0,0.0,-18.0};
    grid[1][6].col_arr={0.0,0.0,1.0};
    grid[1][7].occ=true;
    grid[1][7].trans={-11.0,0.0,-18.0};
    grid[1][7].col_arr={1.0,1.0,0.0};
    grid[1][8].occ=true;
    grid[1][8].trans={-9.0,0.0,-18.0};
    grid[1][8].col_arr={0.0,0.0,1.0};

    grid[1][9].occ=false;
    grid[1][9].trans={-7.0,0.0,-18.0};
    grid[1][10].occ=false;
    grid[1][10].trans={-5.0,0.0,-18.0};

     grid[1][11].occ=true;
    grid[1][11].trans={-3.0,0.0,-18.0};
    grid[1][11].col_arr={1.0,1.0,0.0};
    grid[1][12].occ=true;
    grid[1][12].trans={-1.0,0.0,-18.0};
    grid[1][12].col_arr={0.0,0.0,1.0};



    grid[1][13].occ=false;
    grid[1][13].trans={1.0,0.0,-18.0};
    grid[1][14].occ=false;
    grid[1][14].trans={3.0,0.0,-18.0};

     grid[2][0].occ=true;//3rd row
    grid[2][0].trans={-25.0,0.0,-16.0};
    grid[2][0].col_arr={1.0,1.0,0.0};
    grid[2][1].occ=true;
    grid[2][1].trans={-23.0,0.0,-16.0};
    grid[2][1].col_arr={0.0,0.0,1.0};
     grid[2][2].occ=true;
    grid[2][2].trans={-21.0,0.0,-16.0};
    grid[2][2].col_arr={1.0,1.0,0.0};
    grid[2][3].occ=true;
    grid[2][3].trans={-19.0,0.0,-16.0};
    grid[2][3].col_arr={0.0,0.0,1.0};
     grid[2][4].occ=true;
    grid[2][4].trans={-17.0,0.0,-16.0};
    grid[2][4].col_arr={1.0,1.0,0.0};
    grid[2][5].occ=true;
    grid[2][5].trans={-15.0,0.0,-16.0};
    grid[2][5].col_arr={0.0,0.0,1.0};
     grid[2][6].occ=true;
    grid[2][6].trans={-13.0,0.0,-16.0};
    grid[2][6].col_arr={1.0,1.0,0.0};
    grid[2][7].occ=true;
    grid[2][7].trans={-11.0,0.0,-16.0};
    grid[2][7].col_arr={0.0,0.0,1.0};
    grid[2][8].occ=true;
    grid[2][8].trans={-9.0,0.0,-16.0};
    grid[2][8].col_arr={1.0,1.0,0.0};


     grid[2][9].occ=false;
    grid[2][9].trans={-7.0,0.0,-16.0};
     grid[2][10].occ=false;
    grid[2][10].trans={-5.0,0.0,-16.0};



    grid[2][11].occ=true;
    grid[2][11].trans={-3.0,0.0,-16.0};
    grid[2][11].col_arr={0.0,0.0,1.0};
     grid[2][12].occ=true;
    grid[2][12].trans={-1.0,0.0,-16.0};
    grid[2][12].col_arr={1.0,1.0,0.0};
    grid[2][13].occ=true;
    grid[2][13].trans={1.0,0.0,-16.0};
    grid[2][13].col_arr={0.0,0.0,1.0};
    grid[2][14].occ=true;
    grid[2][14].trans={3.0,0.0,-16.0};
    grid[2][14].col_arr={1.0,1.0,0.0};



     grid[3][0].occ=true;//4th row
    grid[3][0].trans={-25.0,0.0,-14.0};
    grid[3][0].col_arr={0.0,0.0,1.0};
     grid[3][1].occ=true;
    grid[3][1].trans={-23.0,0.0,-14.0};
    grid[3][1].col_arr={1.0,1.0,0.0};
    grid[3][2].occ=true;
    grid[3][2].trans={-21.0,0.0,-14.0};
    grid[3][2].col_arr={0.0,0.0,1.0};
    grid[3][3].occ=true;
    grid[3][3].trans={-19.0,0.0,-14.0};
    grid[3][3].col_arr={1.0,1.0,0.0};

    grid[3][4].occ=false;
    grid[3][4].trans={-17.0,0.0,-14.0};
    grid[3][5].occ=false;
    grid[3][5].trans={-15.0,0.0,-14.0};
    grid[3][6].occ=false;
    grid[3][6].trans={-13.0,0.0,-14.0};
    grid[3][7].occ=false;
    grid[3][7].trans={-11.0,0.0,-14.0};
    grid[3][8].occ=false;
    grid[3][8].trans={-9.0,0.0,-14.0};
    grid[3][9].occ=false;
    grid[3][8].trans={-7.0,0.0,-14.0};
    grid[3][10].occ=false;
    grid[3][10].trans={-5.0,0.0,-14.0};

     grid[3][11].occ=true;
    grid[3][11].trans={-3.0,0.0,-14.0};
    grid[3][11].col_arr={1.0,1.0,0.0};
    grid[3][12].occ=true;
    grid[3][12].trans={-1.0,0.0,-14.0};
    grid[3][12].col_arr={0.0,0.0,1.0};
    grid[3][13].occ=false;
    grid[3][13].trans={1.0,0.0,-14.0};
    grid[3][14].occ=true;
    grid[3][14].trans={3.0,0.0,-14.0};
    grid[3][14].col_arr={0.0,0.0,1.0};



    grid[4][0].occ=true;//5th row
    grid[4][0].trans={-25.0,0.0,-12.0};
    grid[4][0].col_arr={1.0,1.0,0.0};
     grid[4][1].occ=true;
    grid[4][1].trans={-23.0,0.0,-12.0};
    grid[4][1].col_arr={0.0,0.0,1.0};
    grid[4][2].occ=true;
    grid[4][2].trans={-21.0,0.0,-12.0};
    grid[4][2].col_arr={1.0,1.0,0.0};
    grid[4][3].occ=true;
    grid[4][3].trans={-19.0,0.0,-12.0};
    grid[4][3].col_arr={0.0,0.0,1.0};

    grid[4][4].occ=false;
    grid[4][4].trans={-17.0,0.0,-12.0};
    grid[4][5].occ=false;
    grid[4][5].trans={-15.0,0.0,-12.0};
    grid[4][6].occ=false;
    grid[4][6].trans={-13.0,0.0,-12.0};
    grid[4][7].occ=false;
    grid[4][7].trans={-11.0,0.0,-12.0};
    grid[4][8].occ=false;
    grid[4][8].trans={-9.0,0.0,-12.0};
    grid[4][9].occ=false;
    grid[4][8].trans={-7.0,0.0,-12.0};
    grid[4][10].occ=false;
    grid[4][10].trans={-5.0,0.0,-12.0};

    grid[4][11].occ=true;
    grid[4][11].trans={-3.0,0.0,-12.0};
    grid[4][11].col_arr={0.0,0.0,1.0};
    grid[4][12].occ=true;
    grid[4][12].trans={-1.0,0.0,-12.0};
    grid[4][12].col_arr={1.0,1.0,0.0};
    grid[4][13].occ=true;
    grid[4][13].trans={1.0,0.0,-12.0};
    grid[4][13].col_arr={0.0,0.0,1.0};
    grid[4][14].occ=true;
    grid[4][14].trans={3.0,0.0,-12.0};
    grid[4][14].col_arr={1.0,1.0,0.0};









     grid[5][0].occ=false;//5th row
    grid[5][0].trans={-25.0,0.0,-10.0};
    //grid[0][0].col_arr={1.0,1.0,0.0};
    grid[5][1].occ=false;
    grid[5][1].trans={-23.0,0.0,-10.0};
    //grid[0][0].col_arr={1.0,1.0,0.0};
    grid[5][2].occ=false;
    grid[5][2].trans={-21.0,0.0,-10.0};
    //grid[0][0].col_arr={1.0,1.0,0.0};
    grid[5][3].occ=false;
    grid[5][3].trans={-19.0,0.0,-10.0};
    grid[5][4].occ=false;
    grid[5][4].trans={-17.0,0.0,-10.0};
    grid[5][5].occ=false;
    grid[5][5].trans={-15.0,0.0,-10.0};
    grid[5][6].occ=false;
    grid[5][6].trans={-13.0,0.0,-10.0};
    grid[5][7].occ=false;
    grid[5][7].trans={-11.0,0.0,-10.0};
    grid[5][8].occ=false;
    grid[5][8].trans={-9.0,0.0,-10.0};
    grid[5][9].occ=false;
    grid[5][8].trans={-7.0,0.0,-10.0};
    grid[5][10].occ=false;
    grid[5][10].trans={-5.0,0.0,-10.0};
    grid[5][11].occ=false;
    grid[5][11].trans={-3.0,0.0,-10.0};

    grid[5][12].occ=true;
    grid[5][12].trans={-1.0,0.0,-10.0};
    grid[5][12].col_arr={0.0,0.0,1.0};
    grid[5][13].occ=true;
    grid[5][13].trans={1.0,0.0,-10.0};
    grid[5][13].col_arr={1.0,1.0,0.0};
    grid[5][14].occ=true;
    grid[5][14].trans={3.0,0.0,-10.0};
    grid[5][14].col_arr={0.0,0.0,1.0};



    blockI1=0;
    blockJ1=8;
    blockI2=-1;
    blockJ2=-1;

	tranX=grid[blockI1][blockJ1].trans[0];
	tranY=grid[blockI1][blockJ1].trans[1]+2;
	tranZ=grid[blockI1][blockJ1].trans[2];


















}

void specialKeys(int key,int a,int b) {
	switch(key) {
		case GLUT_KEY_RIGHT : 	if(blockPosition==1) {
						blockI1=blockI1;
						blockJ1=blockJ1+1;
						blockI2=blockI1;
						blockJ2=blockJ1+1;
						scaleY=1;
						scaleX=2;
						scaleZ=1;
//						tranX+=(cubeLen+cubeLen/2);
						tranY=cubeLen/2;
						blockPosition=2;
						tranX=(grid[blockI1][blockJ1].trans[0]+grid[blockI2][blockJ2].trans[0])/2;
						if(!((blockI1==3 && blockJ1==13) || (blockI2==3 && blockJ2==13)))
						if(!grid[blockI1][blockJ1].occ || !grid[blockI2][blockJ2].occ)
							lose=true;
					}
					else if(blockPosition==2) {
						blockI1=blockI1;
						blockJ1=blockJ1+2;
						blockI2=-1;
						blockJ2=-1;
						scaleY=2;
						scaleX=1;
						scaleZ=1;
//						tranX+=(cubeLen+cubeLen/2);
						tranY=cubeLen;
						blockPosition=1;
						tranX=grid[blockI1][blockJ1].trans[0];
						if(blockI1==3 && blockJ1==13)
							win=true;
						else if(!grid[blockI1][blockJ1].occ)
							lose=true;
					}
					else if(blockPosition==3) {
						blockI1=blockI1;
						blockJ1=blockJ1+1;
						blockI2=blockI1;
						blockJ2=blockJ2+1;
						scaleY=1;
						scaleX=1;
						scaleZ=2;
//						tranX+=cubeLen;
						tranY=cubeLen/2;
						blockPosition=3;
						tranX=(grid[blockI1][blockJ1].trans[0]+grid[blockI2][blockJ2].trans[0])/2;
						if(!((blockI1==3 && blockJ1==13) || (blockI2==3 && blockJ2==13)))
						if(!grid[blockI1][blockJ1].occ || !grid[blockI2][blockJ2].occ)
							lose=true;
					}
					break;
		case GLUT_KEY_LEFT : 	if(blockPosition==1) {
						blockI1=blockI1;
						blockJ1=blockJ1-2;
						blockI2=blockI1;
						blockJ2=blockJ1+1;
						scaleY=1;
						scaleX=2;
						scaleZ=1;
//						tranX-=(cubeLen+cubeLen/2);
						tranY=cubeLen/2;
						blockPosition=2;
						tranX=(grid[blockI1][blockJ1].trans[0]+grid[blockI2][blockJ2].trans[0])/2;
						if(!((blockI1==3 && blockJ1==13) || (blockI2==3 && blockJ2==13)))
						if(!grid[blockI1][blockJ1].occ || !grid[blockI2][blockJ2].occ)
							lose=true;
					}
					else if(blockPosition==2) {
						blockI1=blockI1;
						blockJ1=blockJ1-1;
						blockI2=-1;
						blockJ2=-1;
						scaleY=2;
						scaleX=1;
						scaleZ=1;
//						tranX-=(cubeLen+cubeLen/2);
						tranY=cubeLen;
						blockPosition=1;
						tranX=grid[blockI1][blockJ1].trans[0];
						if(blockI1==3 && blockJ1==13)
							win=true;
						else if(!grid[blockI1][blockJ1].occ)
							lose=true;
					}
					else if(blockPosition==3) {
						blockI1=blockI1;
						blockJ1=blockJ1-1;
						blockI2=blockI2;
						blockJ2=blockJ2-1;
						scaleY=1;
						scaleX=1;
						scaleZ=2;
//						tranX-=cubeLen;
						tranY=cubeLen/2;
						blockPosition=3;
						tranX=(grid[blockI1][blockJ1].trans[0]+grid[blockI2][blockJ2].trans[0])/2;
						if(!((blockI1==3 && blockJ1==13) || (blockI2==3 && blockJ2==13)))
						if(!grid[blockI1][blockJ1].occ || !grid[blockI2][blockJ2].occ)
							lose=true;
					}
					break;
		case GLUT_KEY_UP : 	if(blockPosition==1) {
						blockI1=blockI1-1;
						blockJ1=blockJ1;
						blockI2=blockI1-1;
						blockJ2=blockJ1;
						scaleY=1;
						scaleX=1;
						scaleZ=2;
//						tranZ-=(cubeLen+cubeLen/2);
						tranY=cubeLen/2;
						blockPosition=3;
						tranZ=(grid[blockI1][blockJ1].trans[2]+grid[blockI2][blockJ2].trans[2])/2;
						if(!((blockI1==3 && blockJ1==13) || (blockI2==3 && blockJ2==13)))
						if(!grid[blockI1][blockJ1].occ || !grid[blockI2][blockJ2].occ)
							lose=true;
					}
					else if(blockPosition==3) {
						blockI1=blockI1-2;
						blockJ1=blockJ1;
						blockI2=-1;
						blockJ2=-1;
						scaleY=2;
						scaleX=1;
						scaleZ=1;
//						tranZ-=(cubeLen+cubeLen/2);
						tranY=cubeLen;
						blockPosition=1;
						tranZ=grid[blockI1][blockJ1].trans[2];
						if(blockI1==3 && blockJ1==13)
							win=true;
						else if(!grid[blockI1][blockJ1].occ)
							lose=true;
					}
					else if(blockPosition==2) {
						blockI1=blockI1-1;
						blockJ1=blockJ1;
						blockI2=blockI2-1;
						blockJ2=blockJ2;
						scaleY=1;
						scaleX=2;
						scaleZ=1;
//						tranZ-=cubeLen;
						tranY=cubeLen/2;
						blockPosition=2;
						tranZ=(grid[blockI1][blockJ1].trans[2]+grid[blockI2][blockJ2].trans[2])/2;
						if(!((blockI1==3 && blockJ1==13) || (blockI2==3 && blockJ2==13)))
						if(!grid[blockI1][blockJ1].occ || !grid[blockI2][blockJ2].occ)
							lose=true;
					}
					break;
		case GLUT_KEY_DOWN : 	if(blockPosition==1) {
						blockI1=blockI1+2;
						blockJ1=blockJ1;
						blockI2=blockI1-1;
						blockJ2=blockJ1;
						scaleY=1;
						scaleX=1;
						scaleZ=2;
//						tranZ+=(cubeLen+cubeLen/2);
						tranY=cubeLen/2;
						blockPosition=3;
						tranZ=(grid[blockI1][blockJ1].trans[2]+grid[blockI2][blockJ2].trans[2])/2;
						if(!((blockI1==3 && blockJ1==13) || (blockI2==3 && blockJ2==13)))
						if(!grid[blockI1][blockJ1].occ || !grid[blockI2][blockJ2].occ)
							lose=true;
					}
					else if(blockPosition==3) {
						blockI1=blockI1+1;
						blockJ1=blockJ1;
						blockI2=-1;
						blockJ2=-1;
						scaleY=2;
						scaleX=1;
						scaleZ=1;
//						tranZ+=(cubeLen+cubeLen/2);
						tranY=cubeLen;
						blockPosition=1;
						tranZ=grid[blockI1][blockJ1].trans[2];
						if(blockI1==3 && blockJ1==13)
							win=true;
						else if(!grid[blockI1][blockJ1].occ)
							lose=true;
					}
					else if(blockPosition==2) {
						blockI1=blockI1+1;
						blockJ1=blockJ1;
						blockI2=blockI2+1;
						blockJ2=blockJ2;
						scaleY=1;
						scaleX=2;
						scaleZ=1;
//						tranZ+=cubeLen;
						tranY=cubeLen/2;
						blockPosition=2;
						tranZ=(grid[blockI1][blockJ1].trans[2]+grid[blockI2][blockJ2].trans[2])/2;
						if(!((blockI1==3 && blockJ1==13) || (blockI2==3 && blockJ2==13)))
						if(!grid[blockI1][blockJ1].occ || !grid[blockI2][blockJ2].occ)
							lose=true;
					}
					break;
	}
}

