#include <GL/glut.h>

static int window_width, window_height;

static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);

int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    
   
    glMatrixMode(GL_PROJECTION);
    gluPerspective(70, 800.0/600.0, 0.1, 250);

    glutMainLoop();
    
    return 0;
}


static void on_keyboard(unsigned char key, int x, int y){
    
    switch(key) {
        case 27:
            exit(0);
            break;
    }
}

static void on_reshape(int width, int height)
{
    window_width = width;
    window_height = height;
}

static void on_display(void){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 3, -3, 
              0, 0, 0,
              0, 1, 0);
    
    //iscrtavanje platforme
    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
        glVertex3f(-2, 0, -2);
        glVertex3f(2, 0, -2);
        glVertex3f(2, 0, 2);
        glVertex3f(-2, 0, 2);
    glEnd();
    
    
    glutSwapBuffers();
}