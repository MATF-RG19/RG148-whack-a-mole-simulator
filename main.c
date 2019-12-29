#include <GL/glut.h>
#include <time.h>
#include <stdio.h>

#define TIMER_ID 0
#define TIMER_INTERVAL 20

static int window_width, window_height;

static int animation_ongoing;
static float x_current=0, y_current=0, z_current=0;
int current_hole = 5; //promenljiva koja pamti koja je trenutna rupa da ne bi dolazilo do ponavljanja

static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int value);
static void on_reshape(int width, int height);
static void on_display(void);


static void drawCircles(void);
static void drawBat(void);

int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    
    animation_ongoing = 0;
    
   
    glMatrixMode(GL_PROJECTION);
    gluPerspective(70, 800.0/600.0, 0.1, 250);
    
    glClearColor(0.4, 0.4, 0.4, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    float light_position[] = {-1, 1, 1, 0};
    float light_ambient[] = {.4f, .4f, .4f, 1};
    float light_diffuse[] = {.7f, .7f, .7f, 1};
    float light_specular[] = {.7f, .7f, .7f, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    

    glutMainLoop();
    
    return 0;
}


static void on_keyboard(unsigned char key, int x, int y){
    
    switch(key) {
        case 'g':
        case 'G':
            if (!animation_ongoing){
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                animation_ongoing = 1;
            }
            break;
        case 's':
        case 'S':
            animation_ongoing = 0;
            break;
        case 27:
            exit(0);
            break;
    }
}

//vraca random broj 1-9 da bi se odredilo iz koje rupe izlazi objekat
//i postavlja globlane koordinate iznad te rupe
int randomHole(int curr_hole){
    
    srand(time(NULL));
    
    int upper = 9;
    int lower = 1;
    
    int random_num =  (rand() % (upper - lower + 1) + lower);
    while (random_num == current_hole){
        random_num = (rand() % (upper - lower + 1) + lower);
    }
    current_hole = random_num;
    
    switch (random_num){
        case 1:
            x_current = 1.4;
            z_current = -1.4;
            break;
        case 2:
            x_current = 0;
            z_current = -1.4;
            break;
        case 3:
            x_current = -1.4;
            z_current = -1.4;
            break;
        case 4:
            x_current = 1.4;
            z_current = 0;
            break;
        case 5:
            x_current = 0;
            z_current = 0;
            break;
        case 6:
            x_current = -1.4;
            z_current = 0;
            break;
        case 7:
            x_current = 1.4;
            z_current = 1.4;
            break;
        case 8:
            x_current = 0;
            z_current = 1.4;
            break;
        case 9:
            x_current = -1.4;
            z_current = 1.4;
            break;
    }
    
    return random_num;
    
}

static void on_timer(int value){
    
    if (value != TIMER_ID)
        return;
    
    if (y_current >= 1 && animation_ongoing){
        y_current = 0;
        randomHole(current_hole);
    }
    
    y_current += 0.04;
    
    
    glutPostRedisplay();
    
    if (animation_ongoing)
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
}

void draw_axis(float len) {
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(len,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,len,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,len);
    glEnd();
}

static void on_reshape(int width, int height)
{
    window_width = width;
    window_height = height;
}


static void drawCircles(void){
    
    //odsecanje
    GLdouble plane0[] = {0, -1, 0, 0};
    glEnable(GL_CLIP_PLANE0);
    glClipPlane(GL_CLIP_PLANE0, plane0);
    
    
    float r = 0.5;
    float spacing = 1.6/4.0;
    
    GLUquadricObj *qobj = gluNewQuadric();
        
    glPushMatrix();
        //iscrtavanje rupa 3-1
        glTranslatef(-2.3 + r + spacing, 0, -2.3 + r + spacing);
        glColor3f(1, 0, 0);
        gluSphere(qobj, r, 30, 30);
        
        glTranslatef(2*r + spacing, 0, 0);
        gluSphere(qobj, r, 30, 30);
        
        glTranslatef(2*r + spacing, 0, 0);
        gluSphere(qobj, r, 30, 30);
        
        
        //iscrtavanje rupa 4-6
        glTranslatef(0, 0, 2*r + spacing);
        gluSphere(qobj, r, 30, 30);
        
        glTranslatef(-(2*r + spacing), 0, 0);
        gluSphere(qobj, r, 30, 30);
        
        glTranslatef(-(2*r + spacing), 0, 0);
        gluSphere(qobj, r, 30, 30);
        
        //iscrtavanje rupa 9-7
        glTranslatef(0, 0, 2*r + spacing);
        gluSphere(qobj, r, 30, 30);
        
        glTranslatef(2*r + spacing, 0, 0);
        gluSphere(qobj, r, 30, 30);
        
        glTranslatef(2*r + spacing, 0, 0);
        gluSphere(qobj, r, 30, 30);
        
        gluDeleteQuadric(qobj);
    glPopMatrix();
    
    glDisable(GL_CLIP_PLANE0);

}

void drawBat(void){
    
    glPushMatrix();
    
        GLUquadricObj *qobj = gluNewQuadric();
    
        glTranslatef(-1, 0, -3.3);
        glRotatef(-40, 0, 1, 0);

        gluCylinder(qobj, 0.1, 0.25, 4, 150, 150);
        glTranslatef(0, 0, 4);
        gluDisk(qobj, 0, 0.25, 30, 30);
            
        gluDeleteQuadric(qobj);
    glPopMatrix();
    
}

static void on_display(void){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 5, -3.5, 
              0, 0, 0,
              0, 1, 0);
    
   // draw_axis(5);
    
    //iscrtavanje platforme
    glPushMatrix();
        GLfloat ambient3[] = {1,0.78,0.35,0};
        GLfloat diffuse3[] = {0.3,0.3,0,0,0};
        GLfloat specular3[] = {0.6,0.6,0.6,0};
        GLfloat shininess3 = 80;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse3);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular3);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess3);
        glBegin(GL_QUADS);
            glVertex3f(-2.3, 0, -2.3);
            glVertex3f(2.3, 0, -2.3);
            glVertex3f(2.3, 0, 2.3);
            glVertex3f(-2.3, 0, 2.3);
        glEnd();
    glPopMatrix();
    
    //iscrtavanje krugova
    glPushMatrix();
        GLfloat ambient2[] = {1,0.62,0.11,0};
        GLfloat diffuse2[] = {0.2,0.2,0,0,0};
        GLfloat specular2[] = {0.3,0.3,0.3,0};
        GLfloat shininess2 = 40;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular2);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess2);
        
        drawCircles();
    glPopMatrix();
    
       
    //iscrtavanje palice
    glPushMatrix();
        GLfloat ambient1[] = {0.45,0.3,0.1,0};
        GLfloat diffuse1[] = {0.4,0.2,0.2,0};
        GLfloat specular1[] = {0.3,0.3,0.3,0};
        GLfloat shininess1 = 80;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular1);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess1);
        
        drawBat();
    glPopMatrix(); 

    //kuglica
    glPushMatrix();
        glTranslatef(x_current, y_current, z_current);
        glutSolidSphere(0.15, 30, 30);
    glPopMatrix();
    
    glutSwapBuffers();
}