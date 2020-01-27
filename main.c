#include <GL/glut.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define TIMER_ID 0
#define TIMER_ID2 0
#define TIMER_INTERVAL 20
#define TIMER_INTERVAL2 10  

static int animation_ongoing;
static int keyboard_active;
static float x_current=0, y_current=0, z_current=0; //koordinate kuglice
int current_hole = 5; //promenljiva koja pamti koja je trenutna rupa da ne bi dolazilo do ponavljanja
static float ball_speed = 0.04;


/*globalne promenljive za palicu*/
static float step = 5;
static float translate_step = 0;
static float z_bat=-3.3; //pocetni polozaj
static float wanted_z_bat; //zeljeni polozaj
static float rot_angle = 0; //ugao rotacije
static float wanted_angle; // zeljeni ugao


static bool y_down = false, y_stop = false; //flagovi za kretanje kuglice
static int score = 1, level = 0;
static int highScore = 0;


static void on_keyboard(unsigned char key, int x, int y);
static void on_mouse(int button, int state, int x, int y);
static void on_timer(int value);
static void on_timer2(int value);
static void on_display(void);

static void drawText(double x, double y, char *s);
static void drawUI(void);
static void drawCircles(void);
static void drawBat(void);

int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    
    glutMouseFunc(on_mouse);
    glutKeyboardFunc(on_keyboard);
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


static void on_mouse(int button, int state, int x, int y){
    switch(button) {
        case GLUT_LEFT_BUTTON:
            if (!animation_ongoing){
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                animation_ongoing = 1;
            }
            break;
        case GLUT_RIGHT_BUTTON:
            animation_ongoing = 0;
            if (score - level - 1 > highScore)
                highScore = score - level - 1;
            score = 1;
            level = 0;
            ball_speed = 0.04;
            break;
    }
}

static void on_keyboard(unsigned char key, int x, int y){
    /*pritiskom odgovaracucjeg broja 
     palica se pokrece do te rupe i udara iznad nje,
     a ako je kuglica izasla iz te rupe u tom trenutku
     povecava se broj poena*/
    switch(key) {
        case '1':
            if (!keyboard_active){
                wanted_angle =90;
                step = 3;
                glutTimerFunc(TIMER_INTERVAL2, on_timer2, TIMER_ID2);
                keyboard_active = 1;
                if (current_hole == 1){
                    score++;
                }
            }
            break;
        case '2':
            if (!keyboard_active){
                wanted_angle = 60;
                step = 2;
                glutTimerFunc(TIMER_INTERVAL2, on_timer2, TIMER_ID2);
                keyboard_active = 1;
                if (current_hole == 2)
                    score++;
            }
            break;
        case '3':
            if (!keyboard_active){
                wanted_angle = 30;
                step = 1;
                glutTimerFunc(TIMER_INTERVAL2, on_timer2, TIMER_ID2);
                keyboard_active = 1;
                if (current_hole == 3)
                    score++;
            }
            break;
        case '4':
            if (!keyboard_active){
                wanted_angle = 90;
                step = 3;
                wanted_z_bat = -2.1;
                translate_step = 0.04;
                glutTimerFunc(TIMER_INTERVAL2, on_timer2, TIMER_ID2);
                keyboard_active = 1;
                if (current_hole == 4)
                    score++;
            }
            break;
        case '5':
            if (!keyboard_active){
                wanted_angle = 60;
                step = 2;
                wanted_z_bat = -2.1;
                translate_step = 0.04;
                glutTimerFunc(TIMER_INTERVAL2, on_timer2, TIMER_ID2);
                keyboard_active = 1;
                if (current_hole == 5)
                    score++;
            }
            
            break;
        case '6':
            if (!keyboard_active){
                wanted_angle = 30;
                step = 1;
                wanted_z_bat = -2.1;
                translate_step = 0.04;
                glutTimerFunc(TIMER_INTERVAL2, on_timer2, TIMER_ID2);
                keyboard_active = 1;
                if (current_hole == 6)
                    score++;
            }
            break;
        case '7':
            if (!keyboard_active){
                wanted_angle = 90;
                step = 3;
                wanted_z_bat = -0.6;
                translate_step = 0.09;
                glutTimerFunc(TIMER_INTERVAL2, on_timer2, TIMER_ID2);
                keyboard_active = 1;
                if (current_hole == 7)
                    score++;
            }
            break;
        case '8':
            if (!keyboard_active){
                wanted_angle = 60;
                step = 2;
                wanted_z_bat = -0.6;
                translate_step = 0.09;
                glutTimerFunc(TIMER_INTERVAL2, on_timer2, TIMER_ID2);
                keyboard_active = 1;
                if (current_hole == 8)
                    score++;
            }
            break;
        case '9':
            if (!keyboard_active){
                wanted_angle = 30;
                step = 1;
                wanted_z_bat = -0.6;
                translate_step = 0.09;
                glutTimerFunc(TIMER_INTERVAL2, on_timer2, TIMER_ID2);
                keyboard_active = 1;
                if (current_hole == 9)
                    score++;
            }
            break;
        case 27:
            exit(0);
            break;
    }
}

/*vraca random broj 1-9 da bi se odredilo iz koje
rupe izlazi objekat i postavlja globlane
koordinate iznad te rupe*/
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

//animacija palice
static void on_timer2(int value){
    if (value != TIMER_ID2)
        return;
    
    /*kada postignemo zeljeni ugao 
     pocinjemo da je vracamo unazad*/
    if (rot_angle == wanted_angle){
        step *= -1;
        translate_step *= -1;
    }
    
    rot_angle += step;
    z_bat += translate_step;
    
    /*zaustavljamo animaciju i 
     resetujemo relevantne globalne promenljive*/
    if (rot_angle <= 0){
        keyboard_active = 0;
        step *= -1;
        translate_step = 0;
    }
    
    
    glutPostRedisplay();
    
    if (keyboard_active)
        glutTimerFunc(TIMER_INTERVAL2, on_timer2, TIMER_ID2);
    
}

//animacija iskakanja kuglice
static void on_timer(int value){
    
    if (value != TIMER_ID)
        return;
    
    /*kada se kuglica popne na odredjenu visinu
      treba da stane i malo se zadrzi tu*/
    if (y_current >= 1 && animation_ongoing){
        y_stop = true;
    }
    
    if (y_current >= 1.001 && animation_ongoing){
        y_down = true;
    }
    
    /*kada se vrati u pocetni polozaj 
     resetujemo relevantne globalne promenljive
     i random biramo sledecu rupu*/
    if (y_current <0 && animation_ongoing){
        y_current = 0;
        y_down = false;
        y_stop = false;
        randomHole(current_hole);
    }
    
    /*povecavamo brzinu kuglice 
     sa porastom broja poena ali samo
     do odredjene brzine*/
    if (score % 10 == 0 && ball_speed < 0.06){
        ball_speed += 0.005;
        score++;
        level++;
    }
    
    if (y_down) {
        y_current -= ball_speed;
    } 
    else if (y_stop) {
        /*zadrzavanje kuglice u vazduhu je realizovano
         tako sto se ona zapravo pomalo pomera na gore*/
        y_current += 0.0001;
    }
    else {
        y_current += ball_speed;
    }
    
    glutPostRedisplay();
    
    
    if (animation_ongoing)
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
}

static void drawText(double x, double y, char *s){
    glRasterPos2d(x, y);
    
    for (char* c=s; *c != '\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}

//ispisivanje teksta 
static void drawUI(void){
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800.0, 600.0, 0, 0, 250);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor3f(1, 1, .8);

    char currentScore[20], currenthighScore[20], currentLevel[8];
    sprintf(currenthighScore, "High score: %i", highScore);
    sprintf(currentLevel, "Level: %i", level);
    sprintf(currentScore, "Score: %i", score - level - 1);
    drawText(10, 590, currentScore);
    drawText(10, 570, currentLevel);
    drawText(10, 550, currenthighScore);
    
    glEnable(GL_LIGHTING);     
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, 800.0/600.0, 0.1, 250);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 5, -3.5, 
              0, 0, 0,
              0, 1, 0);
    
    glPopMatrix();
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
    
        //ovo je za animaciju
        glTranslatef(-1, 0, z_bat);
        glRotatef(rot_angle, 0, 1, 0);
        
        glRotatef(-40, 0, 1, 0);

        gluCylinder(qobj, 0.1, 0.25, 4, 150, 150);
        glTranslatef(0, 0, 4);
        
        gluDisk(qobj, 0, 0.25, 30, 30);
            
        gluDeleteQuadric(qobj);
    glPopMatrix();
    
}

static void on_display(void){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawUI();
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 5, -3.5, 
              0, 0, 0,
              0, 1, 0);
    
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
    
    //kuglica
    glPushMatrix();
    	GLfloat ambient4[] = {0.45,0.3,0.1,0};
        GLfloat diffuse4[] = {0.4,0.2,0.2,0};
        GLfloat specular4[] = {0.3,0.3,0.3,0};
        GLfloat shininess4 = 80;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient4);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular4);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess4);
        glTranslatef(x_current, y_current, z_current);
        glutSolidSphere(0.30, 30, 30);
    glPopMatrix();
       
    //iscrtavanje palice
    glPushMatrix();
        GLfloat ambient1[] = {0.45,0.3,0.1,0};
        GLfloat diffuse1[] = {0.4,0.2,0.2,0};
        GLfloat specular1[] = {0.25,0.3,0.3,0};
        GLfloat shininess1 = 80;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular1);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess1);
        
        
        drawBat();
    glPopMatrix(); 
    
    glutSwapBuffers();
}
