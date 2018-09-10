#include<windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

bool pasue = false;
//Game Speed
int FPS = 30;
//Game Track
int start=0;
int gv=0;
int level = 0;

//Track Score
int score = 0;
int saveScore;
int save;

//Form move track
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

//For Card Left / RIGHT
int lrIndex = 0 ;

//Car Coming
int car1 = 0;
int lrIndex1=0;
int car2 = +35;
int lrIndex2=0;
int car3 = +70;
int lrIndex3=0;

//For Display TEXT
const int font1=(int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2=(int)GLUT_BITMAP_HELVETICA_18 ;
const int font3=(int)GLUT_BITMAP_8_BY_13;

char s[30];
void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void tree(int x, int y){
    int newx=x;
    int newy=y;
    //Tree Left
            //Bottom
        glColor3f(0.871, 0.722, 0.529);
        glBegin(GL_TRIANGLES);
        glVertex2f(newx+11,newy+55);
        glVertex2f(newx+12,newy+45);
        glVertex2f(newx+10,newy+45);
        glEnd();
            //Up
      glColor3f(0.133, 0.545, 0.133);
        glBegin(GL_TRIANGLES);
        glVertex2f(newx+11,newy+58);
        glVertex2f(newx+15,newy+52);
        glVertex2f(newx+7,newy+52);
        glEnd();
}


void startGame(){
    //Road
    glColor3f(0.412, 0.412, 0.412);
    glBegin(GL_POLYGON);
    glVertex2f(20,0);
    glVertex2f(20,100);
    glVertex2f(80,100);
    glVertex2f(80,0);
    glEnd();

    //Road Left Border
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(19,0);
    glVertex2f(19,100);
    glVertex2f(22,100);
    glVertex2f(22,0);
    glEnd();

    //Road Right Border
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(78,0);
    glVertex2f(78,100);
    glVertex2f(81,100);
    glVertex2f(81,0);
    glEnd();

    //Road Middle Border
      //TOP
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48,roadDivTop+80);
    glVertex2f(48,roadDivTop+100);
    glVertex2f(52,roadDivTop+100);
    glVertex2f(52,roadDivTop+80);
    glEnd();
    roadDivTop--;
    if(roadDivTop<-100){
        roadDivTop =20;
        score++;
    }
        //Middle
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48,roadDivMdl+40);
    glVertex2f(48,roadDivMdl+60);
    glVertex2f(52,roadDivMdl+60);
    glVertex2f(52,roadDivMdl+40);
    glEnd();

    roadDivMdl--;

    if(roadDivMdl<-60){
        roadDivMdl =60;
        score++;
    }
        //Bottom
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48,roadDivBtm);
    glVertex2f(48,roadDivBtm+20);
    glVertex2f(52,roadDivBtm+20);
    glVertex2f(52,roadDivBtm);
    glEnd();
    roadDivBtm--;
    if(roadDivBtm<-20){
        roadDivBtm=100;
        score++;
    }
    //Score Board
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(78,97);
    glVertex2f(100,97);
    glVertex2f(100,90);
    glVertex2f(78,90);
    glEnd();

    //Print Score
    char buffer [50];
    sprintf (buffer, "SCORE: %d", score);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(78.5,95,(void *)font3,buffer);
    //Speed Print
    char buffer1 [50];
    sprintf (buffer1, "SPEED: %dKm/h", FPS);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(78.5,93,(void *)font3,buffer1);
    //level Print
    if(score % 10 == 0){
        int last = score /10;
        if(last!=level){
            level = score /10;
            FPS=FPS+2;

        }
    }
    char level_buffer [50];
    sprintf (level_buffer, "LEVEL: %d", level);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(78.5,91,(void *)font3,level_buffer);

    //Increase Speed With level

    //Truck
        //Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex+23,6);
    glVertex2f(lrIndex+23,8);
    glVertex2f(lrIndex+33,8);
    glVertex2f(lrIndex+33,6);
    glEnd();
        //Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex+23,2);
    glVertex2f(lrIndex+23,4);
    glVertex2f(lrIndex+33,4);
    glVertex2f(lrIndex+33,2);
    glEnd();
        //Truck Body
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex+24,1);
    glVertex2f(lrIndex+32,1);
    glVertex2f(lrIndex+32,6.75);
    glVertex2f(lrIndex+24,6.75);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex+24,7.25);
    glVertex2f(lrIndex+24,9);
    glVertex2f(lrIndex+25,10);
    glVertex2f(lrIndex+31,10);
    glVertex2f(lrIndex+32,9);
    glVertex2f(lrIndex+32,7.25);
    glEnd();

    //Opposite car 1
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1+24,car1+96);
    glVertex2f(lrIndex1+24,car1+94);
    glVertex2f(lrIndex1+32,car1+94);
    glVertex2f(lrIndex1+32,car1+96);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1+24,car1+100);
    glVertex2f(lrIndex1+24,car1+98);
    glVertex2f(lrIndex1+32,car1+98);
    glVertex2f(lrIndex1+32,car1+100);
    glEnd();
    glColor3f(1.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1+25,car1+100);
    glVertex2f(lrIndex1+25,car1+93);
    glVertex2f(lrIndex1+27,car1+91);
    glVertex2f(lrIndex1+29,car1+91);
    glVertex2f(lrIndex1+31,car1+93);
    glVertex2f(lrIndex1+31,car1+100);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1+27.75,car1+99);
    glVertex2f(lrIndex1+27.75,car1+94);
    glVertex2f(lrIndex1+28.25,car1+94);
    glVertex2f(lrIndex1+28.25,car1+99);
    glEnd();
    car1--;
    if(car1<-100){
        car1=0;
        lrIndex1=lrIndex;
    }
    //KIll check car1
    if((abs(lrIndex-lrIndex1)<8) && (car1+100<10)){
            start = 0;
            gv=1;

    }

    //Opposite car 2
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2+24,car2+96);
    glVertex2f(lrIndex2+24,car2+94);
    glVertex2f(lrIndex2+32,car2+94);
    glVertex2f(lrIndex2+32,car2+96);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2+24,car2+100);
    glVertex2f(lrIndex2+24,car2+98);
    glVertex2f(lrIndex2+32,car2+98);
    glVertex2f(lrIndex2+32,car2+100);
    glEnd();
    glColor3f(0.294, 0.000, 0.510);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2+25,car2+100);
    glVertex2f(lrIndex2+25,car2+93);
    glVertex2f(lrIndex2+27,car2+91);
    glVertex2f(lrIndex2+29,car2+91);
    glVertex2f(lrIndex2+31,car2+93);
    glVertex2f(lrIndex2+31,car2+100);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2+27,car2+99);
    glVertex2f(lrIndex2+27,car2+94);
    glVertex2f(lrIndex2+27.5,car2+94);
    glVertex2f(lrIndex2+27.5,car2+99);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2+28.5,car2+99);
    glVertex2f(lrIndex2+28.5,car2+94);
    glVertex2f(lrIndex2+29,car2+94);
    glVertex2f(lrIndex2+29,car2+99);
    glEnd();
    car2--;
    if(car2<-100){
        car2=0;
        lrIndex2=lrIndex;
    }
    //KIll check car2
    if((abs(lrIndex-lrIndex2)<8) && (car2+100<10)){
            start = 0;
            gv=1;
    }

    //Opposite car 3
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3+24,car3+96);
    glVertex2f(lrIndex3+24,car3+94);
    glVertex2f(lrIndex3+32,car3+94);
    glVertex2f(lrIndex3+32,car3+96);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3+24,car3+100);
    glVertex2f(lrIndex3+24,car3+98);
    glVertex2f(lrIndex3+32,car3+98);
    glVertex2f(lrIndex3+32,car3+100);
    glEnd();
    glColor3f(1.000, 0.271, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3+25,car3+100);
    glVertex2f(lrIndex3+25,car3+93);
    glVertex2f(lrIndex3+27,car3+91);
    glVertex2f(lrIndex3+29,car3+91);
    glVertex2f(lrIndex3+31,car3+93);
    glVertex2f(lrIndex3+31,car3+100);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3+26.5,car3+99);
    glVertex2f(lrIndex3+26.5,car3+94);
    glVertex2f(lrIndex3+27,car3+94);
    glVertex2f(lrIndex3+27,car3+99);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3+28,car3+99);
    glVertex2f(lrIndex3+28,car3+94);
    glVertex2f(lrIndex3+28.5,car3+94);
    glVertex2f(lrIndex3+28.5,car3+99);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3+29.5,car3+99);
    glVertex2f(lrIndex3+29.5,car3+94);
    glVertex2f(lrIndex3+30,car3+94);
    glVertex2f(lrIndex3+30,car3+99);
    glEnd();
    car3--;
    if(car3<-100){
        car3=0;
        lrIndex3=lrIndex;
    }
    //KIll check car3
    if((abs(lrIndex-lrIndex3)<8) && (car3+100<10)){
            start = 0;
            gv=1;
    }
    //tree(-2,roadDivMdl+30);
    //tree(-2,roadDivMdl-30);
    tree(-4,roadDivMdl+20);
    tree(4,roadDivMdl-20);
    //tree(4,roadDivTop+40);
    //tree(84,roadDivMdl);
    //tree(82,roadDivTop+25);
    //tree(80,roadDivTop+40);
}

void fristDesign(){

        //1st page Background
        glColor3f(0.000, 0.392, 0.000);
        glBegin(GL_POLYGON);
        glVertex2f(0,55);
        glVertex2f(100,55);
        glColor3f(0.604, 0.804, 0.196);
        glVertex2f(100,0);
        glVertex2f(0,0);
        glEnd();

        //1st page Road Design
        glColor3f(00, 0, 0);
        glBegin(GL_TRIANGLES);
        glVertex2f(51,55);
        glVertex2f(90,0);
        glVertex2f(10,0);
        glEnd();

        //Road Middle
        glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLES);
        glVertex2f(51,55);
        glVertex2f(53,0);
        glVertex2f(48,0);
        glEnd();

         //Road Sky
        glColor3f(0.000, 0.749, 1.000);
        glBegin(GL_POLYGON);
        glVertex2f(100,100);
        glVertex2f(0,100);
        glColor3f(0.686, 0.933, 0.933);
        glVertex2f(0,55);
        glVertex2f(100,55);
        glEnd();
        /* Bird 1
        glColor3f(0.000, 0.000, 0.000);
        glBegin(GL_POLYGON);
        glVertex2f(25,80);
        glVertex2f(30,83);
        glVertex2f(10,90);
        glVertex2f(5,88);
        glEnd();
        glColor3f(0.000, 0.000, 0.000);
        glBegin(GL_TRIANGLES);
        glVertex2f(21,86);
        glVertex2f(25,88);
        glVertex2f(18,87);
        glEnd();
        */
        //Hill 1
        glColor3f(0.235, 0.702, 0.443);
        glBegin(GL_TRIANGLES);
        glVertex2f(20,65);
        glVertex2f(27,55);
        glVertex2f(0,55);
        glEnd();

        //Hill 2
        glColor3f(0.000, 0.502, 0.000);
        glBegin(GL_TRIANGLES);
        glVertex2f(35,67);
        glVertex2f(50,55);
        glVertex2f(10,55);
        glEnd();

        //Hill 3
        glColor3f(0.235, 0.702, 0.443);
        glBegin(GL_TRIANGLES);
        glVertex2f(87,65);
        glVertex2f(100,55);
        glVertex2f(60,55);
        glEnd();

         //Hill 4
        glColor3f(0.000, 0.502, 0.000);
        glBegin(GL_TRIANGLES);
        glVertex2f(70,70);
        glVertex2f(90,55);
        glVertex2f(50,55);
        glEnd();

        //Tree Left
            //Bottom
        glColor3f(0.871, 0.722, 0.529);
        glBegin(GL_TRIANGLES);
        glVertex2f(11,55);
        glVertex2f(12,45);
        glVertex2f(10,45);
        glEnd();
            //Up
      glColor3f(0.133, 0.545, 0.133);
        glBegin(GL_TRIANGLES);
        glVertex2f(11,58);
        glVertex2f(15,52);
        glVertex2f(7,52);
        glEnd();

        tree(5,-15);
        tree(9,5);
        tree(85,9);
        tree(75,-5);

        //Menu Place Holder
        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(25,65);
        glVertex2f(80,65);
        glVertex2f(80,45);
        glVertex2f(25,45);
        glEnd();

        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(25,65);
        glVertex2f(80,65);
        glVertex2f(80,64);
        glVertex2f(25,64);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(79,65);
        glVertex2f(80,65);
        glVertex2f(80,45);
        glVertex2f(79,45);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(25,46);
        glVertex2f(80,46);
        glVertex2f(80,45);
        glVertex2f(25,45);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(25,65);
        glVertex2f(24,65);
        glVertex2f(24,45);
        glVertex2f(25,45);
        glEnd();

        //Text Information in Frist Page
        if(gv==1){
            glColor3f(0,0,0);
            glBegin(GL_POLYGON);
            glVertex2f(31,76);
            glVertex2f(71,76);
            glVertex2f(71,66.5);
            glVertex2f(31,66.5);
            glEnd();
            glColor3f(1,1,1);
            glBegin(GL_POLYGON);
            glVertex2f(32,75);
            glVertex2f(70,75);
            glVertex2f(70,67.5);
            glVertex2f(32,67.5);
            glEnd();
            glColor3f(1.000, 0.000, 0.000);
            renderBitmapString(36,72,(void *)font1,"GAME OVER");
            glColor3f(1.000, 0.000, 0.000);
            char buffer2 [50];
            sprintf (buffer2, "Your Score is : %d", score);
            renderBitmapString(33,68,(void *)font1,buffer2);

        }

        glColor3f(1.000, 1.000, 0.000);
        renderBitmapString(30,80,(void *)font1,"2D Truck Racing Game ");

        glColor3f(0.000, 1.000, 0.000);
        renderBitmapString(35,60,(void *)font2,"Press S to START");
        renderBitmapString(35,57,(void *)font2,"Press ESC to Exit");

        glColor3f(1.000, 1.000, 1.000);
        renderBitmapString(27,54,(void *)font3,"Press Up Key to increase Speed");
        renderBitmapString(27,52,(void *)font3,"Press Down Key to decrease Speed");
        renderBitmapString(27,50,(void *)font3,"Press Right Key to turn Right");
        renderBitmapString(27,48,(void *)font3,"Press Left key to turn Left");
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    if(start==1){
        glClearColor(0.000, 0.392, 0.000,1);
        startGame();
    }
    else{
        sndPlaySound(NULL, SND_ASYNC);
        fristDesign();
    }
    glFlush();
    glutSwapBuffers();
}

void spe_key(int key, int x, int y){
        switch (key) {
        case GLUT_KEY_DOWN:
            if(FPS>(50+(level*2)))
            FPS=FPS-2;
            break;
        case GLUT_KEY_UP:
            FPS=FPS+2;
            break;

        case GLUT_KEY_LEFT:
            if(lrIndex>=0){
                lrIndex = lrIndex - (FPS/10);
                if(lrIndex<0){
                    lrIndex=-1;
                }
            }
            break;

        case GLUT_KEY_RIGHT:
            if(lrIndex<=44){
                lrIndex = lrIndex + (FPS/10);
                if(lrIndex>44){
                    lrIndex = 45;
                }
            }
            break;

        default:
                break;
        }
}

void processKeys(unsigned char key, int x, int y) {

      switch (key)
            {
                case 's':
            if(start==0){
                start = 1;
                gv = 0;
                FPS = 50;
                roadDivTopMost = 0;
                roadDivTop = 0;
                roadDivMdl = 0;
                roadDivBtm = 0;
                lrIndex = 0 ;
                car1 = 0;
                lrIndex1=0;
                car2 = +35;
                lrIndex2=0;
                car3 = +70;
                lrIndex3=0;
                score=0;
                level=0;
                sndPlaySound("Sound.wav",SND_ASYNC | SND_LOOP);//Play background music

            }
             break;
                //case ' ' :
                    //if()
             case 27:
                 exit(0);

             break;
             default:
                break;
        }
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer,0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,650);
    glutInitWindowPosition(200,20);
    glutCreateWindow("Truck Game");

    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(processKeys );

    glOrtho(0,100,0,100,-1,1);
    glClearColor(0.184, 0.310, 0.310,1);

    glutTimerFunc(1000,timer,0);
    glutMainLoop();

    return 0;
}
