#include <GL/glut.h>
#include <unistd.h>

#include "graphic.h"
#include "../part3_evelua/evalua.h"

static int window;
static int menu_id;
static int submenu_id;
static int value = 0;

void menu(int num)
{
    if (num == 0)
    {
        glutDestroyWindow(window);
        exit(0);
    }
    else
    {
        value = num;
    }
    glutPostRedisplay();
}

void curve(float borneMin, float borneMax, float pas, char *func)
{
    int nbVal = (borneMax - borneMin) / pas;
    float **tab = calculValeur(borneMin, borneMax, pas, func);

    glColor3d(0.0, 0.9, 0.2);
    glLineWidth(2.0);
    int i = 0;
    while (i < nbVal)
    {
        glBegin(GL_LINES);
        glVertex2f(tab[i][0], tab[i][1]);
        glVertex2f(tab[i + 1][0], tab[i + 1][1]);
        glEnd();
        i++;
    }
}

void createMenu(void)
{
    submenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Curve", 2);
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 1);
    glutAddSubMenu("Draw", submenu_id);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display(void)
{
    glClearColor(0.25, 0.25, 0.25, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    if (value == 1)
    {
        return; //glutPostRedisplay();
    }
    else if (value == 2)
    {
        glPushMatrix();

        curve(-5.0, 5.0, 0.1, "sin(x-25)");
        glPopMatrix();
    }
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    window = glutCreateWindow("Curve");
    createMenu();
    glClearColor(0.2, 0.2, 0.2, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return EXIT_SUCCESS;
}
