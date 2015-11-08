/*
    Program : A shelf made using GLUT in C.
    Glut library used: freeglut3
    @uthor: Abhay Mittal
    Date of completion: April 16, 2014


    Mapping of keys:
    Arrow keys are used to rotate the shelf
    x ==> to come closer to  the object
    z ==> to move farther from the object
*/

#include<math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


int drawCuboid(GLfloat varray[],GLint indices[6][4],GLfloat fillClr[], GLfloat outlineClr[]); //Function to draw a cuboid
void rotationKeys( int key, int x, int y ); // Function to define the mapping of arrow keys for rotation
void changePerspective(unsigned char key, int x, int y); // Function to define the mapping of z and x for the perspective projection
void renderScene(); //Function for displaying the shelf
void reShape(int width, int height); //Function called when the window is created or resized

double rotation_x=0; //Initial rotation angle - along x axis
double rotation_y=0; //Initial rotation angle - along y axis
GLfloat fovy=45.0;  //Initial field of view for the perspective projection
GLfloat aspectRatio=0.0; //Initial aspect ratio

int main(int argc, char **argv) {

    glutInit(&argc,argv); //Initialize glut
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //Enable double buffer, RGBA color mode and request for depth buffer
    glutInitWindowSize(800,800); //The initial window size
    glutCreateWindow("Book Shelf");
    glEnable(GL_DEPTH_TEST);
    //Register callbacks
    glutDisplayFunc(renderScene);
    glutSpecialFunc(rotationKeys);
    glutKeyboardFunc(changePerspective);
    glutReshapeFunc(reShape);
    glutMainLoop();
    return 0;
}

int drawCuboid(GLfloat varray[],GLint indices[6][4],GLfloat fillClr[], GLfloat outlineClr[]) {
/*This function plots a cuboid along with its outline on the screen using a vertex array (varray) and a 2d array consisting of the indices of the vertices of the 6 faces. It also takes
the fill color and outline color as arguments*/
    int i;
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,varray); //set varray as the vertex array, each vertex consists of 3 coordinates and there is no separation between two consecutive coordinates
    for(i=0;i<6;i++){
        glColor4fv(fillClr);
        glEnableClientState(GL_INDEX_ARRAY);
        glIndexPointer(GL_INT,0,indices[i]);
        glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,indices[i]); //Plot using the fill color
        glColor4fv(outlineClr);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glLineWidth(2.0); //set outline width
        glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,indices[i]);//plot using the outline color
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glDisableClientState(GL_INDEX_ARRAY);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}

void rotationKeys( int key, int x, int y ) {

  if (key == GLUT_KEY_RIGHT)
    rotation_y += 5;

  else if (key == GLUT_KEY_LEFT)
    rotation_y -= 5;

  else if (key == GLUT_KEY_UP)
    rotation_x += 5;

  else if (key == GLUT_KEY_DOWN)
    rotation_x -= 5;
  glutPostRedisplay();//Mark the window to be redisplayed in the next iteration of glutMainLoop()

}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Clear the  buffer currently enabled for color writing and the depth buffer

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy,aspectRatio,0.1,200.0f); //set the perspective
    glMatrixMode(GL_MODELVIEW);


     glLoadIdentity();
    glTranslatef( 0, 0, -4 ); // Move the object away from the camera
    glRotatef( rotation_x, 1.0, 0.0, 0.0 );//Perform the rotations in x
    glRotatef( rotation_y, 0.0, 1.0, 0.0 );//and y axes, if any
    glPushMatrix();//Save the current matrix
    //The array below stores the vertices of a cuboid of each slab of the shelf
    GLfloat rack[]={-0.25,-0.35,-0.15,   0.25,-0.35,-0.15,   0.25,-0.3,-0.15,   -0.25,-0.3,-0.15,   -0.25,-0.35,0.15,   0.25,-0.35,0.15,   0.25,-0.3,0.15,   -0.25,-0.3,0.15};
    //The indices below correspond to the following faces in order - front back right left top bottom
    GLint ind[6][4]={{1,2,3,0},{1,2,6,5},{5,6,7,4},{4,7,3,0},{6,2,3,7},{1,5,4,0}};

    //set all the colors
    GLfloat rackFilc[]={0.0,0.0,1.0,1.0};
    GLfloat sideFilc[]={1.0,0.0,0.0,1.0};
    GLfloat backFilc[]={0.0,1.0,0.0,1.0};
    GLfloat legFilc[]={0.5,0.5,0.5,1.0};
    GLfloat outc[]={1.0,1.0,1.0,1.0};

    //draw all the slabs in the shelf
    drawCuboid(rack,ind,rackFilc,outc);
    glTranslatef(0.0,0.2,0.0);
    drawCuboid(rack,ind,rackFilc,outc);
    glTranslatef(0.0,0.2,0.0);
    drawCuboid(rack,ind,rackFilc,outc);
    glTranslatef(0,0.2,0.0);
    drawCuboid(rack,ind,rackFilc,outc);
    glTranslatef(0,0.2,0.0);
    drawCuboid(rack,ind,rackFilc,outc);
    glTranslatef(0,0.2,0.0);
    drawCuboid(rack,ind,rackFilc,outc);


    glPopMatrix(); //restore the initially saved matrix
    glPushMatrix();//duplicate it
    GLfloat sideFace[]={0.25,-0.35,-0.15,   0.3,-0.35,-0.15,   0.3,0.70,-0.15,   0.25,0.70,-0.15,   0.25,-0.35,0.15,   0.3,-0.35,0.15,   0.3,0.70,0.15,   0.25,0.70,0.15,};
    drawCuboid(sideFace,ind,sideFilc,outc); // draw the right face
    glTranslatef(-0.55,0.0,0.0);
    drawCuboid(sideFace,ind,sideFilc,outc); // draw the left face

    glPopMatrix(); //restore the initially saved matrix
    glColor3f(0.0,1.0,0.0);
    GLfloat backFace[]={-0.3,-0.35,0.15,   0.3,-0.35,0.15,   0.3,0.7,0.15,   -0.3,0.7,0.15,   -0.3,-0.35,0.2,   0.3,-0.35,0.2,   0.3,0.7,0.2,   -0.3,0.7,0.2};
    drawCuboid(backFace,ind,backFilc,outc);//draw the back face


    GLfloat rightLeg[]={0.15,-0.45,-0.15,   0.25,-0.45,-0.15,   0.25,-0.35,-0.15,   0.15,-0.35,-0.15,   0.15,-0.45,0.2,   0.25,-0.45,0.2,   0.25,-0.35,0.2,   0.15,-0.35,0.2};
    drawCuboid(rightLeg,ind,legFilc,outc); // draw the right leg
    glTranslatef(-0.4,0.0,0.0);
    drawCuboid(rightLeg,ind,legFilc,outc); // draw the left leg

    glFlush();
    glutSwapBuffers();

}

void reShape(int width, int height) {
    glViewport(0.0,0.0,width,height); //set the viewport
    aspectRatio=((GLfloat)width)/height; //determine the new aspect ratio
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy,aspectRatio,0.1,200.0f);//change the aspect ratio of the perspective.
    glMatrixMode(GL_MODELVIEW);
;}

void changePerspective(unsigned char key, int x, int y) {
/*This function maps x and z for changing the perspective (zoom in and zoom out)*/
    switch(key) {
        case 'z':   fovy+=3.0;
        if(fovy>180.0) //increasing beyond it will result in reversed objects as the frustum or the display volume will get inverted
            fovy=180.0;
        break;
        case 'x': fovy-=3;
        if(fovy<=0.0) //decreasing beyond it will result in reversed objects too due to the same reason
            fovy=3.0;
        break;
    }
    glutPostRedisplay(); //mark window to be redisplayed in the next iteration of glutMainLoop()
}

