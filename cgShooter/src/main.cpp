#include "support.h"
#include "cgmath.h"		// slee's simple math library
#include "trackball.h"
#include "mesh.h"
#include "light.h"
#include "AK.h"
#include "Box.h"
//*******************************************************************
// index variables for OpenGL objects
GLuint	program = 0;					// ID holder for GPU program
GLuint	vertexPositionBuffer = 0;		// ID holder for vertex position buffer
int     windowWidth, windowHeight;

//*******************************************************************
// global variables
int			frame = 0;	// index of rendering frames
bool		bMouseLButtonDown = false;
Mesh*		pMesh_AK = nullptr;
Mesh*		pMesh_Box = nullptr;
Mesh*		pMesh_World = nullptr;
Mesh*		pMesh_CC = nullptr;
Camera		camera;
const int	NUM_OBJECTS = 9;
AK			ak;
Box			box;
Box			world;
Trackball	trackball(camera.viewMatrix, 1.0f);
GLuint	textureObject = 0;
Light		light;
Material	material;

// forward declaration of image loader function available at stb_image.c
extern "C" unsigned char*	stbi_load(const char* filename, int* x, int* y, int* comp, int req_comp);
extern "C" void				stbi_image_free(void* retval_from_stbi_load);

int width, height, comp;
//*******************************************************************
void update()
{
	// configure projection matrix
	camera.fovy = PI / 6.0f;
	//camera.aspectRatio; // udpate in reshape()
	camera.dNear = 1.0f;
	camera.dFar = 1000.0f;
	camera.projectionMatrix = mat4::perspective(camera.fovy, camera.aspectRatio, camera.dNear, camera.dFar);

	// setup uniform matrix
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_TRUE, camera.viewMatrix);
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_TRUE, camera.projectionMatrix);
	glBindTexture(GL_TEXTURE_2D, textureObject);
	glUniform1i(glGetUniformLocation(program, "TEX"), 0);	 // GL_TEXTURE0
	 
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// notify to GL that we like to use our program now
	glUseProgram(program);
	// bind vertex position buffer
	glBindBuffer(GL_ARRAY_BUFFER, pMesh_AK->vertexBuffer);

	// bind vertex position buffer
	GLuint vertexPositionLoc = glGetAttribLocation(program, "position");
	glEnableVertexAttribArray(vertexPositionLoc);
	glVertexAttribPointer(vertexPositionLoc, sizeof(vertex().pos) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(vertex), 0);

	// bind vertex normal buffer
	GLuint vertexNormalLoc = glGetAttribLocation(program, "normal");
	glEnableVertexAttribArray(vertexNormalLoc);
	glVertexAttribPointer(vertexNormalLoc, sizeof(vertex().norm) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(sizeof(vertex().pos)));

	// bind vertex texture buffer
	GLuint vertexTexlLoc = glGetAttribLocation(program, "texcoord");
	glEnableVertexAttribArray(vertexTexlLoc);
	glVertexAttribPointer(vertexTexlLoc, sizeof(vertex().tex) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(sizeof(vertex().pos) + sizeof(vertex().norm)));

	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, ak.getImage());

	//allocate and create mipmap
	for (int k = 1, w = width >> 1, h = height >> 1; k < 9; k++, w = w >> 1, h = h >> 1)
		glTexImage2D(GL_TEXTURE_2D, k, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glGenerateMipmap(GL_TEXTURE_2D);

	// configure texture parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	mat4 modelMatrix;
	//
	//modelMatrix = mat4::rotate(vec3(0, 1, 0), PI)*modelMatrix;
	modelMatrix = mat4::rotate(vec3(0, 0, 1), PI)*modelMatrix;
	modelMatrix = mat4::rotate(vec3(1, 0, 0), -PI/2)*modelMatrix;
	modelMatrix = mat4::translate(-camera.at) * modelMatrix;
	modelMatrix = mat4::scale(ak.getScale(), ak.getScale(), ak.getScale()) * modelMatrix;
	//modelMatrix = mat4::translate(camera.at) * modelMatrix; 
	modelMatrix = mat4::translate(ak.getPosition().x, ak.getPosition().y, ak.getPosition().z) * modelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_TRUE, modelMatrix);

	glDrawArrays(GL_TRIANGLES,0, pMesh_AK->vertexList.size());
	
	//glBindBuffer(GL_ARRAY_BUFFER, NULL);
	//glBindBuffer(GL_ARRAY_BUFFER, pMesh_Box->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, pMesh_Box->vertexList.size()*sizeof(vertex), &pMesh_Box->vertexList[0], GL_STATIC_DRAW);

	// bind vertex texture buffer
	vertexTexlLoc = glGetAttribLocation(program, "texcoord");
	glEnableVertexAttribArray(vertexTexlLoc);
	glVertexAttribPointer(vertexTexlLoc, sizeof(vertex().tex) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)(sizeof(vertex().pos) + sizeof(vertex().norm)));

	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, ak.getImage());

	//allocate and create mipmap
	for (int k = 1, w = width >> 1, h = height >> 1; k < 9; k++, w = w >> 1, h = h >> 1)
		glTexImage2D(GL_TEXTURE_2D, k, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glGenerateMipmap(GL_TEXTURE_2D);

	// configure texture parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	//mat4 modelMatrix;
	//
	//modelMatrix = mat4::rotate(vec3(0, 1, 0), PI)*modelMatrix;
	modelMatrix = mat4::rotate(vec3(0, 0, 1), PI)*modelMatrix;
	modelMatrix = mat4::rotate(vec3(1, 0, 0), -PI / 2)*modelMatrix;
	modelMatrix = mat4::translate(-camera.at) * modelMatrix;
	//modelMatrix = mat4::scale(10, 10, 10) * modelMatrix;
	//modelMatrix = mat4::translate(camera.at) * modelMatrix; 
	modelMatrix = mat4::translate(box.getPosition().x, box.getPosition().y, box.getPosition().z) * modelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_TRUE, modelMatrix);

	glDrawArrays(GL_TRIANGLES, 0, pMesh_Box->vertexList.size());

	
	// now swap backbuffer with front buffer, and display it
	glutSwapBuffers();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// increment FRAME index
	frame++;


}

void display()
{
	update();
	render();
}

void reshape(int width, int height)
{
	// set current viewport in pixels
	// viewport: the window area that are affected by rendering
	// (win_x, win_y, win_width, win_height)
	glViewport(0, 0, windowWidth = width, windowHeight = height);

	camera.aspectRatio = float(width) / float(height);

	// post signal to call display
	// this causes GL to call display() soon
	// but, we do not know exactly when dipslay() is called
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON){
		printf("shoooooot");
	}
}

void motion(int x, int y)
{
	camera.eye = vec3((x - windowWidth / 2) / float(windowWidth - 1), -(y - windowHeight / 2) / float(windowHeight - 1), camera.eye.z);
	camera.viewMatrix = mat4::lookAt(camera.eye, camera.at, camera.up);
}

void move(int key, int x, int y)
{
	/*if (key == GLUT_KEY_UP){
		camera.eye = vec3(camera.eye.x, camera.eye.y, camera.eye.z+1);
		camera.at = vec3(camera.at.x, camera.at.y, camera.at.z+1);
		camera.viewMatrix = mat4::lookAt(camera.eye, camera.at, camera.up);
	}
	else if (key == GLUT_KEY_DOWN){
		camera.eye = vec3(camera.eye.x, camera.eye.y, camera.eye.z-1);
		camera.at = vec3(camera.at.x, camera.at.y, camera.at.z-1);
		camera.viewMatrix = mat4::lookAt(camera.eye, camera.at, camera.up);
	}
	else if (key == GLUT_KEY_LEFT){
		camera.eye = vec3(camera.eye.x - 0.1f, camera.eye.y, camera.eye.z);
		camera.at = vec3(camera.at.x -0.1f, camera.at.y, camera.at.z);
		camera.viewMatrix = mat4::lookAt(camera.eye, camera.at, camera.up);
		ak.setPosition(vec3(ak.getPosition().x - 1.f, ak.getPosition().y, ak.getPosition().z));
	}
	else if (key == GLUT_KEY_RIGHT){
		camera.eye = vec3(camera.eye.x - 1, camera.eye.y, camera.eye.z);
		camera.at = vec3(camera.at.x -1, camera.at.y, camera.at.z);
		camera.viewMatrix = mat4::lookAt(camera.eye, camera.at, camera.up);
	}*/
}

void idle()
{
	glutPostRedisplay();	// signal to call display soon
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == GLUT_KEY_UP){
		camera.eye = vec3(camera.eye.x, camera.eye.y, camera.eye.z-1);
		camera.viewMatrix = mat4::lookAt(camera.eye, camera.at, camera.up);
		//ak.setPosition(vec3(ak.getPosition().x, ak.getPosition().y, ak.getPosition().z + 1));
	}
}

bool initShaders(const char* vertShaderPath, const char* fragShaderPath)
{
	// create a program before linking shaders
	program = glCreateProgram();
	glUseProgram(program);

	// compile shader sources
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSource = readShader(vertShaderPath); if (vertexShaderSource == NULL) return false;
	GLint vertexShaderLength = strlen(vertexShaderSource);
	glShaderSource(vertexShader, 1, &vertexShaderSource, &vertexShaderLength);
	glCompileShader(vertexShader);
	if (!checkShader(vertexShader, "vertexShader")){ printf("Unable to compile vertex shader\n"); return false; }
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderSource = readShader(fragShaderPath); if (fragmentShaderSource == NULL) return false;
	GLint fragmentShaderLength = strlen(fragmentShaderSource);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, &fragmentShaderLength);
	glCompileShader(fragmentShader);
	if (!checkShader(fragmentShader, "fragmentShader")){ printf("Unable to compile fragment shader\n"); return false; }
	// attach vertex/fragments shaders and link program
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	if (!checkProgram(program, "program")){ printf("Unable to link program\n"); return false; }

	// deallocate string
	free((void*)vertexShaderSource);
	free((void*)fragmentShaderSource);

	return true;
}

unsigned char* loadPic(char* path){
	// load an image
	unsigned char* image;
	unsigned char* image0 = stbi_load(path, &width, &height, &comp, 0);
	//flip image vertically
	image = (unsigned char*)malloc(sizeof(unsigned char)*width*height*comp);
	for (int y = 0, stride = width*comp; y < height; y++) memcpy(image + (height - 1 - y)*stride, image0 + y*stride, stride); // vertical flip
	stbi_image_free(image0); // release the original image
	return image;
}

bool userInit()
{

	pMesh_Box = loadBox();
	box = Box(100.f, vec3(0.f, 0.f, 5.f), loadPic("../bin/Images/Box.jpg"));
	//pMesh_World = loadBox();
	//world = Box(100000.0f, vec3(-700.f, -20.f, 10.f), loadPic("../bin/Images/wall_texture.jpg"));

	pMesh_AK = loadMesh("../bin/Mods/AK.obj");
	ak = AK(0.006f, vec3(0, 0,0),loadPic("../bin/Images/tex_AK.jpg"));

	GLuint buff[] = { pMesh_AK->vertexBuffer, pMesh_Box->vertexBuffer };
	//GLuint buff[] = { pMesh_World->vertexBuffer, pMesh_Box->vertexBuffer };
	
	// create a vertex buffer
	glGenBuffers(2, buff);
	glBindBuffer(GL_ARRAY_BUFFER, pMesh_AK->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, pMesh_AK->vertexList.size()*sizeof(vertex), &pMesh_AK->vertexList[0], GL_STATIC_DRAW);
	
	/*glGenBuffers(2, buff);
	glBindBuffer(GL_ARRAY_BUFFER, pMesh_AK->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, pMesh_World->vertexList.size()*sizeof(vertex), &pMesh_World->vertexList[0], GL_STATIC_DRAW);
*/

	// init camera
	camera.eye = vec3(0, 0.2f, 1);
	camera.at = vec3(0, 0, 0);
	camera.up = vec3(0, 1, 0);
	camera.viewMatrix = mat4::lookAt(camera.eye, camera.at, camera.up);

	 
	return true;
}

int main(int argc, char* argv[])
{

	// GLUT initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
	windowWidth = 1280;
	windowHeight = 720;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);
	glutCreateWindow("Solar System");


	// Register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);		// callback when the window is resized
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(move);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(motion);		// callback when the mouse is moving
	glutIdleFunc(idle);			// idle-time callback

	// init and check GLEW, version, extensions
	if (!initExtensions()){ printf("Failed to init extensions.\n"); return 0; }
	// create and compile shaders/program
	if (!initShaders("shaders/trackball.vert", "shaders/trackball.frag")){ printf("Failed to init program and shaders\n"); return 0; }
	// user initialization
	if (!userInit()){ printf("Failed to userInit()\n"); return 0; }
	// Start rendering loop
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glutMainLoop();
	return 0;
}
