#include <GL/glut.h>
#include <AntTweakBar.h>
#include <unistd.h>

#include "graphic.h"
#include "../part3_evelua/evalua.h"

static int window;
static int menu_id;
static int submenu_id;
static int value = 0;

char g_func[100] = "x*sin(abs(x))";
char g_func_control[100] = "";

float g_Zoom = 1.0f;
float** g_tab;
float g_minX = -300.0;
float g_minX_control = 0;
float g_maxX = 300.0;
float g_maxX_control = 0;

float g_minY = -300.0;
float g_maxY = 300.0;
float g_pas = 3.0;
float g_pas_control = 0;

float g_curveColor[3] = {0.0, 0.7, 0.35};

int g_printError = 1;

void curve()
{   
    int check = strcmp(g_func,g_func_control) || g_maxX != g_maxX_control || g_minX != g_minX_control || g_pas != g_pas_control;
    if( check ) {
        g_tab = calculValeur(g_minX, g_maxX, g_pas, g_func);
        strcpy(g_func_control,g_func);
        g_maxX_control = g_maxX;
        g_minX_control = g_minX;
        g_pas_control = g_pas;
    }

    if ( g_tab[0][0] != MAXFLOAT ){
        g_printError = 1;

        glScalef(2/(fabs(g_minX)+fabs(g_maxX)),2/(fabs(g_minY)+fabs(g_maxY)),1);
        glTranslatef(-(g_minX+g_maxX)/2,-(g_minY+g_maxY)/2,0);

        glColor3f(.3,.3,.3);
        {
            glRectf(g_minX,g_minY,g_maxX,g_maxY);
        }

        glColor3f(.2,.2,.2);
        {
            glRectf(0.0,0.0,g_maxX,g_maxY);
            glRectf(g_minX,g_minY,0.0,0.0);
        }

        glColor3fv(g_curveColor);
        glLineWidth(2.0);
        
        int i = 0;
        int nbVal = (g_maxX - g_minX) / g_pas;
        while (i < nbVal)
        {
            glBegin(GL_LINES);
            {
                float x1 = g_tab[i][0];
                float y1 = g_tab[i][1];
                float x2 = g_tab[i+1][0];
                float y2 = g_tab[i+1][1];
                
                glVertex2f(x1, y1);
                glVertex2f(x2, y2);
            }
            glEnd();
            i++;
        }
    } else if ( g_printError ){
        printf("Erreur : Aucune valeur à afficher\n");
        g_printError = 0;
    }
}

void TW_CALL zoomIn(){
    g_minX = g_minX>=-2e-2 ? -1e-2 : g_minX/2; 
    g_maxX = g_maxX<=2e-2 ? 1e-2 : g_maxX/2;
    g_minY = g_minY>=-2e-2 ? -1e-2 : g_minY/2;
    g_maxY = g_maxY<=2e-2 ? 1e-2 : g_maxY/2;
    g_pas = g_maxX/100;
}

void TW_CALL zoomOut(){
    g_minX = g_minX<=-1e4/2 ? -1e4 : g_minX*2; 
    g_maxX = g_maxX>1e4/2 ? 1e4 : g_maxX*2;
    g_minY = g_minY<=-1e4/2 ? -1e4 : g_minY*2;
    g_maxY = g_maxY>1e4/2 ? 1e4 : g_maxY*2;
    g_pas = g_maxX/100;
}

void display(void)
{
    glClearColor(.25,.25,.25,1);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    {
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
    TwDefine(" GLOBAL help='Ce programme permet l affichage de fonction mathematique sous forme de graphes.\nRealisation :\n    1 - Analyse Lexicale :\n        Pierre-Antoine PAUWELS\n        Valentin PINTE\n    2 - Analyse Syntaxique :\n        Samuel OUTTIER\n        Nathan POPCZYK\n    3 - Evaluation :\n        Quentin BRANQUART\n        Lucas HADJERES\n    4 - Interface Graphique\n        Remi GUILLEMIN\n        Victor LIMOU\n\nHarmoINFO@IMT Lille-Douai' "); // Message added to the help bar.
    TwDefine(" Menu size='200 450' color='96 112 128' "); // change default tweak bar size and color

    TwAddVarRW(bar, "function", TW_TYPE_CSSTRING(sizeof(char)*100), g_func, " label='Fonction' help='Une fonction mathematique a dessiner' ");
    TwAddSeparator(bar,NULL,NULL);
    
    TwAddVarRW(bar, "minX", TW_TYPE_FLOAT, &g_minX, " label='Min X' min=-10000 max=10000 group='Bornes X' help='Borne inferieur X' ");
    TwAddVarRW(bar, "maxX", TW_TYPE_FLOAT, &g_maxX, " label='Max X' min=-10000 max=10000 group='Bornes X' help='Borne superieur X' ");
    
    TwAddVarRW(bar, "minY", TW_TYPE_FLOAT, &g_minY, " label='Min Y' min=-10000 max=10000 group='Bornes Y' help='Borne inferieur Y' ");
    TwAddVarRW(bar, "maxY", TW_TYPE_FLOAT, &g_maxY, " label='Max Y' min=-10000 max=10000 group='Bornes Y' help='Borne siperieur Y' ");
    TwAddSeparator(bar,NULL,NULL);

    TwAddButton(bar,"zoomIn",zoomIn,NULL,"label='Zoom +' key=UP");
    TwAddButton(bar,"zoomOut",zoomOut,NULL,"label='Zoom -' key=DOWN");
    TwAddSeparator(bar,NULL,NULL);
    
    TwAddVarRW(bar, "pas", TW_TYPE_FLOAT, &g_pas, " label='Pas' min=0.0001 max=100.0 step=0.01 precision=4 help='Incrementation de X et Y' ");
    TwAddSeparator(bar,NULL,NULL);

    TwAddVarRW(bar, "curveColor", TW_TYPE_COLOR3F, &g_curveColor, " label='Curve' group='Colors' open colormode=rgb ");
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
