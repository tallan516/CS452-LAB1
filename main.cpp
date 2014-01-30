
//run command g++ error.cpp -lglut -lGL -lGLEW -g

#include "initShaders.h"
#include "vec.h"
using namespace std;

int image = 0; //image shown
GLuint vaoID, vboID;// the buffers that are going to be linked too
//vertices
GLfloat triVertexarray[]= {0.5f,0.5f,0.0f,
				-0.5f,0.5f,0.0f,
				0.0f,-0.5f,0.0f}; // vertices that are drawn x,y,z ...
GLfloat squareVertexarray[]= {0.75f,0.75f,0.0f,
					0.75f,-0.75f,0.0f,
					-0.75f,-0.75f,0.0f,
					-0.75f,0.75f,0.0f}; // vertices that are drawn x,y,z ...
GLfloat octVertexarray[] =   {0.5f,0.2f,0.0f,
					0.2f,0.5f,0.0f,
					0.2f,0.5f,0.0f,
					-0.2f,0.5f,0.0f,
					-0.2f,0.5f,0.0f,
					-0.5f,0.2f,0.0f,
					-0.5f,0.2f,0.0f,
					-0.5f,-0.2f,0.0f,
					-0.5f,-0.2f,0.0f,
					-0.2f,-0.5f,0.0f,
					-0.2f,-0.5f,0.0f,
					0.2f,-0.5f,0.0f,
					0.2f,-0.5f,0.0f,
					0.5f,-0.2f,0.0f,
					0.5f,-0.2f,0.0f,
					0.5f,0.2f,0.0f}; //vertices that are drawn x,y,z ...
//indices
GLubyte triIndices[3]={0,1,2};
GLubyte squareIndices[4]={0,1,2,3};
GLubyte octIndices[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

void initTriangle()
{
  glClear(GL_COLOR_BUFFER_BIT);//clear screen
  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array
  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(triVertexarray), triVertexarray, GL_STATIC_DRAW);//allocates the memory of the vertices
  ShaderInfo shaders[]=
  { //create the shader specified by my initshaders input
    { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
    { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
    { GL_NONE , NULL} 
  };
  initShaders(shaders);//creates shaders	
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, triIndices);//draws object based on indices of the polygon
  glDisableVertexAttribArray(0);
  glFlush();//make sure the processes finish
}
void initSquare()
{
  glClear(GL_COLOR_BUFFER_BIT);//clear screen
  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array
  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertexarray), squareVertexarray, GL_STATIC_DRAW);//allocates the memory of the vertices
  ShaderInfo shaders[]=
  { //create the shader specified by my initshaders input
    { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
    { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
    { GL_NONE , NULL} 
  };
  initShaders(shaders);//creates shaders	
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw
  glDrawElements(GL_POLYGON,4, GL_UNSIGNED_BYTE, squareIndices);//draws object based on indices of the polygon
  glDisableVertexAttribArray(0);
  glFlush();//make sure the processes finish
}
void initOct()
{
  glClear(GL_COLOR_BUFFER_BIT);//clear screen
  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array
  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(octVertexarray), octVertexarray, GL_STATIC_DRAW);//allocates the memory of the vertices
  ShaderInfo shaders[]=
  { //create the shader specified by my initshaders input
    { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
    { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
    { GL_NONE , NULL} 
  };
  initShaders(shaders);//creates shaders	
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw
  glDrawElements(GL_LINES,16, GL_UNSIGNED_BYTE, octIndices);//draws lines to simulate an octagon
  glDisableVertexAttribArray(0);
  glFlush();//make sure the processes finish
}

//Draw Functions

void draw()
{
  switch(image)
  {
    case 0:
      glutDisplayFunc(initOct);
      glutPostRedisplay(); //sets flags for opengl to redraw the display
      break;
    case 1:
      glutDisplayFunc(initSquare);
    	glutPostRedisplay();
      break;
    case 2:
    	glutDisplayFunc(initTriangle);
      glutPostRedisplay();
    	break;
  }
}

//right click closes screen, left click moves to next drawing
void mousepress(int button, int state, int x, int y)
{
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
  {
    exit(0);
  }
  else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  {
    image++;
    if(image > 2)
    {
    	image = 0;
    }
    draw();
  }
}

void idle(void)
{
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  //Freeglut window and context management	
  glutInit(&argc, argv);
  glutCreateWindow("Octagon, Square, and Triangle"); //creates the window
  
  //initializes glew
  glewExperimental=GL_TRUE;
  if(glewInit())
  {
    fprintf(stderr, "Unable to initalize GLEW");
    exit(EXIT_FAILURE);
  }
  
  
  //glutInitContextVersion(4, 3); //specifies the version of opengl
  //glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE); //specifies what profile your using

  glutDisplayFunc(draw);//displays callback draws the shapes
  glutMouseFunc(mousepress);//control callback specifies the mouse controls
  glutMainLoop();//sets opengl state in a neverending loop
  return 0;
}
	
