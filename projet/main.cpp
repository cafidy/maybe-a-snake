#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <BBOP/Graphics.h>
#include <vector>
using namespace std;

int main() {
  //Initialisation Début ############################################################################
  // Initialisation de GLFW
  if (!glfwInit()) {
      cerr << "Échec de l'initialisation de GLFW" << endl;
      return -1;
  }
  // Configuration de GLFW pour utiliser le profil OpenGL Core
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // Création d'une fenêtre GLFW
  GLFWwindow* window = glfwCreateWindow(1000, 500, "Bibibop engine", nullptr, nullptr);
  if (!window) {
      cerr << "Échec de la création de la fenêtre GLFW" << endl;
      glfwTerminate();
      return -1;
  }
  // Définition de la fenêtre comme le contexte OpenGL courant
  glfwMakeContextCurrent(window);
  // Initialisation de GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
      cerr << "Échec de l'initialisation de GLEW" << endl;
      glfwTerminate();
      return -1;
  }
  // Désactiver la synchronisation verticale (V-Sync)
  //glfwSwapInterval(0);
  //General info
  cout << "Bibibop Engine Version 0.0.1" << endl << "Author: Alexander74" << endl << "Contact: alexandre.lanternier@outlook.fr" << endl << "License: GPL-3.0" << endl; 
  //GPU info
  const GLubyte* vendor = glGetString(GL_VENDOR);
  const GLubyte* renderer = glGetString(GL_RENDERER);
  cout << "OpenGL Vendor: " << vendor << endl;
  cout << "OpenGL Renderer: " << renderer << endl;
  cout << "Window size: " << 1000 << "x" << 500 << endl;
  // Initialisation Fin ##############################################################################
  //creation du sprite
  float shapex=100;
  float shapey=100;
  float genrator(int n );
  vector<RectangleShape> testshape;
  RectangleShape shape;
  shape.setPosition(Vector2f(100.0f,100.0f));
  shape.setSize(Vector2f(100.0f,100.0f));
  shape.setColor(Vector3i(128,0,128));
  testshape.push_back(shape);

  int cpt=0;

  //creation de la sceneClass
  
  Scene defaultScene;
  RectangleShape mobe;
  mobe.setPosition(Vector2f(genrator(1),genrator(1)));
  mobe.setSize(Vector2f(100.0f,100.0f));
  mobe.setOrigin(Vector2f(100.0f,100.0f));
  mobe.setColor(Vector3i(147,71,159));
  //FPS counter
  int nbFrames = 0;
  //double frameTarget = 1.0/60.0;
  double lastTime = glfwGetTime();
  double fps;
  double currentTime;
  double delta;
  double totalFps = 0.0;
  //FPS end init #######
  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
    // FPS calc ################################################
    currentTime = glfwGetTime();
    delta = currentTime - lastTime;
    nbFrames++;
    totalFps++;
    if ( delta >= 1.0 ){ // If last cout was more than 1 sec ago
      fps = double(nbFrames) / delta;
      stringstream ss;
      ss << "BibibopEngine" << " [" << fps << " FPS]";

      glfwSetWindowTitle(window, ss.str().c_str());
      nbFrames = 0;
      lastTime = currentTime;

    }
    //FPS calc end #############################################
	  // Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
    //testspr.setPosition(testspr.getPositionX()+0.5f, testspr.getPositionY()+0.5f);
    for (int i = 0; i < cpt; i++)
    {
      testshape[i].setPosition(Vector2f(testshape[i-1].getPosition().x,testshape[i-1].getPosition().y));
    }
    if (glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS && shapex<1000-10)
    {

      
      testshape[0].setPosition(Vector2f(shapex=shapex+1,shapey=shapey) );
    }
    if (glfwGetKey(window,GLFW_KEY_LEFT)==GLFW_PRESS && shapex>10)
    {

      testshape[0].setPosition(Vector2f(shapex=shapex-1,shapey=shapey));
    }
    if (glfwGetKey(window,GLFW_KEY_UP)==GLFW_PRESS  && shapey>10)
    {

      testshape[0].setPosition(Vector2f(shapex=shapex,shapey=shapey-1));
    }
    if (glfwGetKey(window,GLFW_KEY_DOWN)==GLFW_PRESS && shapey<1000-10)
    {

      testshape[0].setPosition(Vector2f(shapex=shapex,shapey=shapey+1) );
    }
    if (testshape[0].getCollisionBox()->check(mobe.getCollisionBox()))
    {
      mobe.setPosition(Vector2f(genrator(1),genrator(1)));
      cpt++;
      shape.setPosition(Vector2f(testshape[cpt-1].getPosition().x,testshape[cpt-1].getPosition().y));
      testshape.push_back(shape);
    }
    
    
    defaultScene.Use();
    for (int i = 0; i < cpt; i++)
    {
      defaultScene.Draw(testshape[0]);
    }
    defaultScene.Draw(mobe);
    //Check d'erreur
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << error << std::endl;
    }
    // Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
    
	}
	// Delete window before ending the program
	glfwDestroyWindow(window);
  // Terminate GLFW before ending the program
  defaultScene.Delete();
  cout << "Session terminated, avg fps: " << totalFps/glfwGetTime() << endl;
	glfwTerminate();
	return 0;
}
float genrator(int n)
{
      srand(time(NULL));
      float x;
      x=rand()%1000;
      return x;
    }