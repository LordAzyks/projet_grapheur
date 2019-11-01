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
float g_minX = -10.0;
float g_minX_control = 0;
float g_maxX = 10.0;
float g_maxX_control = 0;

float g_minY = -10.0;
float g_maxY = 10.0;
float g_pas = .1;

void curve()
{
    // printf("DISPLAY %d\n",value++);
    int nbVal = (g_maxX - g_minX) / g_pas;
    g_tab = calculValeur(g_minX, g_maxX, g_pas, g_func);
    /*  if(strcmp(g_func,g_func_control)){
        strcpy(g_func_control,g_func);
    }else if(g_minX != g_minX_control) {
        g_minX_control = g_minX;
        g_tab = calculValeur(g_minX, g_maxX, g_pas, g_func);
    } else if(g_maxX != g_maxX_control) {
        g_maxX_control = g_maxX;
        g_tab = calculValeur(g_minX, g_maxX, g_pas, g_func);
    } */

    float ecartX = (g_maxX - g_minX) / 2;
    float ecartY = (g_maxY - g_minY) / 2;

    glColor3f(0.0, 0.9, 0.2);
    glLineWidth(2.0);
    int i = 0;
    while (i < nbVal)
    {
        glBegin(GL_LINES);
        {
            float x1 = g_tab[i][0]<0 ? g_tab[i][0]/fabs(g_minX) : g_tab[i][0]/g_maxX;
            float y1 = g_tab[i][1]<0 ? g_tab[i][1]/fabs(g_minY) : g_tab[i][1]/g_maxY;
            float x2 = g_tab[i+1][0]<0 ? g_tab[i+1][0]/fabs(g_minX) : g_tab[i+1][0]/g_maxX;
            float y2 = g_tab[i+1][1]<0 ? g_tab[i+1][1]/fabs(g_minY) : g_tab[i+1][1]/g_maxY;
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        }
        glEnd();
        i++;
    }
}

void display(void)
{
    glClearColor(0.25,0.25,0.25,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    {
        glColor3f(.2,.2,.2);
        glRectf(0.0,0.0,1.0,1.0);
        glRectf(-1.0,-1.0,0.0,0.0);
        curve();
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
    TwDefine(" Menu size='200 450' color='216 0 216' "); // change default tweak bar size and color

    TwAddVarRW(bar, "function", TW_TYPE_CSSTRING(sizeof(char)*100), g_func, " label='function' help='A mathematical function to draw' ");
    TwAddVarRW(bar, "minX", TW_TYPE_FLOAT, &g_minX, " label='Min X' help='Borne inferieur X' ");
    TwAddVarRW(bar, "maxX", TW_TYPE_FLOAT, &g_maxX, " label='Max X' help='Borne superieur X' ");
    TwAddVarRW(bar, "minY", TW_TYPE_FLOAT, &g_minY, " label='Min Y' help='Borne inferieur Y' ");
    TwAddVarRW(bar, "maxY", TW_TYPE_FLOAT, &g_maxY, " label='Max Y' help='Borne siperieur Y' ");
    TwAddVarRW(bar, "pas", TW_TYPE_FLOAT, &g_pas, " label='pas' help='Pas d'incrémentation de X et Y' ");
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
    gluLookAt(0,0,2, 0,0,1, 0,1,0);
    glTranslatef(0.5f, 0.0f, -1);

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
    glutInitWindowSize(750, 500);
    // glutInitWindowPosition(500, 100);
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
