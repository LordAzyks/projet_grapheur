#include <GL/glut.h>
#include <unistd.h>

#include <AntTweakBar.h>

#include "graphic.h"
#include "../part3_evelua/evalua.h"

static int window;
static int menu_id;
static int submenu_id;
static int value = 0;

char g_func[50] = "sin(x+2)";
char g_func_control[50] = "";
float g_Zoom = 1.0f;
float** g_tab;

void curve(float borneMin, float borneMax, float pas)
{
    // printf("DISPLAY %d\n",value++);
    int nbVal = (borneMax - borneMin) / pas;
    if(strcmp(g_func,g_func_control)){
        g_tab = calculValeur(borneMin, borneMax, pas, g_func);
        strcpy(g_func_control,g_func);
    }

    glColor3d(0.0, 0.9, 0.2);
    glLineWidth(2.0);
    int i = 0;
    while (i < nbVal)
    {
        glBegin(GL_LINES);
        glVertex2f(g_tab[i][0], g_tab[i][1]);
        glVertex2f(g_tab[i + 1][0], g_tab[i + 1][1]);
        glEnd();
        i++;
    }
}

void display(void)
{
    glClearColor(0.2f,0.2f,0.2f,1.0f);

    glPushMatrix();
    {
        curve(-5.0, 5.0, 0.1);
    }
    glPopMatrix();

    // Draw tweak bars
    TwDraw();

    // Present frame buffer
    glutSwapBuffers();

    // Recall Display at next frame
    glutPostRedisplay();

}

void setGLUTeventCB(){
    // - Directly redirect GLUT mouse button events to AntTweakBar
    glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
    // - Directly redirect GLUT mouse motion events to AntTweakBar
    glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
    // - Directly redirect GLUT mouse "passive" motion events to AntTweakBar (same as MouseMotion)
    glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
    // - Directly redirect GLUT key events to AntTweakBar
    glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
    // - Directly redirect GLUT special key events to AntTweakBar
    glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);
    // - Send 'glutGetModifers' function pointer to AntTweakBar;
    //   required because the GLUT key event functions do not report key modifiers states.
    TwGLUTModifiersFunc(glutGetModifiers);
}

void createMenuBar(TwBar *bar){
    // Create a tweak bar
    bar = TwNewBar("Menu");
    TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLUT and OpenGL.' "); // Message added to the help bar.
    TwDefine(" Menu size='200 400' color='216 0 216' "); // change default tweak bar size and color

    TwAddVarRW(bar, "function", TW_TYPE_CSSTRING(sizeof(char)*100), g_func, " label='function' help='A mathematical function to draw' ");
}

// Callback function called by GLUT when window size changes
void reshape(int width, int height)
{
    // Set OpenGL viewport and camera
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, (double)width/height, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);
    glTranslatef(0, 0.6f, -1);

    // Send the new window size to AntTweakBar
    TwWindowSize(width, height);
}

// Function called at exit
void terminate(void)
{
    TwTerminate();
}


int main(int argc, char **argv)
{
    TwBar *bar; // Pointer to the tweak bar
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(500, 100);
    glutCreateWindow("Curve");
    glutCreateMenu(NULL);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    atexit(terminate);

    // Initialize AntTweakBar
    TwInit(TW_OPENGL, NULL);

    setGLUTeventCB();

    createMenuBar(bar);

    glutMainLoop();
    return EXIT_SUCCESS;
}
