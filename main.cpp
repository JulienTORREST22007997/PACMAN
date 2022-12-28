#define FPS_LIMIT 60

#include <iostream>
#include <thread>
#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"
#include "mingl/audio/audioengine.h"
#include "mingl/gui/sprite.h"
#include "mingl/gui/sprite.h"

using namespace std;
// 0 -> Droite
// 1 -> Gauche
// 2 -> Bas
// 3 -> Haut
unsigned int rotationActuelle = 1;

unsigned int posCircleX = 50;
unsigned int posCircleY = 270;

unsigned int centreX = 50;
unsigned int centreY = 50;

float factorX1 = 0;
float factorY1 = 0.5;

float factorX2= 0;
float factorY2 =1.5;

unsigned int x1 = posCircleX + centreX * factorX1;
unsigned int y1 = posCircleY + centreY * factorY1;

unsigned int x2 = posCircleX + centreX * factorX2;
unsigned int y2 = posCircleY + centreY * factorY2;

nsGraphics::Vec2D rectPos;

void dessiner(MinGL &window, unsigned int x1,unsigned int y1, unsigned int x2, unsigned int y2)
{
    //    window << nsShape::Circle(nsGraphics::Vec2D(100, 320), 50, nsGraphics::KYellow);
    window << nsShape::Circle(nsGraphics::Vec2D(rectPos.getX()+100, rectPos.getY()+320), 50, nsGraphics::KYellow);

    unsigned int posCircleX = 50;
    unsigned int posCircleY = 270;
    //    window << nsShape::Circle(nsGraphics::Vec2D(posCircleX, posCircleY), 5, nsGraphics::KRed); // milieu constante

    unsigned int centreX = 50;
    unsigned int centreY = 50;


    window << nsShape::Triangle(nsGraphics::Vec2D(rectPos.getX()+x1, rectPos.getY()+y1), nsGraphics::Vec2D(rectPos.getX()+100, rectPos.getY()+320), nsGraphics::Vec2D(rectPos.getX()+x2, rectPos.getY()+y2), nsGraphics::KBlack);

    //    window << nsShape::Circle(nsGraphics::Vec2D(100, 320), 5, nsGraphics::KCyan); // milieu constante
    //    window << nsShape::Circle(nsGraphics::Vec2D(x1, y1), 5, nsGraphics::KCyan); // 75, 370
    //    window << nsShape::Circle(nsGraphics::Vec2D(x2, y2), 5, nsGraphics::KCyan); // 125, 370
    // N'hésitez pas a lire la doc pour plus de .détails
}

void rotateMouth(unsigned int & x1,unsigned int & y1, unsigned int & x2, unsigned int & y2, bool & ascend)
{
    if(!ascend) { // si il ferme la bouche
        if(rotationActuelle == 0 || rotationActuelle == 1) {
            if(y1 - 270 > 50 ) // on vérifie qu'elle est pas totalement fermée
            {
                ascend = true; // si elle est fermée on ouvre la bouche
            }
        } else {
            if(x1 - 50 > 50 ) // on vérifie qu'elle est pas totalement fermée
            {
                ascend = true; // si elle est fermée on ouvre la bouche
            }
        }

    } else { // si il ouvre la bouche
        if(rotationActuelle == 0 || rotationActuelle == 1) {
            if(y1 - 270 < 25) // on vérifie qu'elle est pas totalement ouverte
            {
                ascend = false; // on ferme la bouche si elle est totalement ouverte
            }
        } else {
            if(x1 - 50 < 10) // on vérifie qu'elle est pas totalement ouverte
            {
                ascend = false; // on ferme la bouche si elle est totalement ouverte
            }
        }
    }
    cout << y1 - 270 << " " <<ascend<< endl;

    int test = 7;

    if(!ascend) { // si il ferme la bouche
        if(rotationActuelle == 0 || rotationActuelle == 1) {
            y1 = y1 + test;
            y2 = y2 - test;
        } else {
            x1 = x1 +test;
            x2 = x2 - test;
        }
    } else {
        if(rotationActuelle == 0 || rotationActuelle == 1) {
            y1 = y1 -test;
            y2 = y2 + test;
        } else {
            x1 = x1-test;
            x2 = x2 +test;
        }
    }

    //    if(y2 - 270 < 270+50)
    //    {
    //        --y2;
    //    } else ++y2;

}

void setMouthRotation(unsigned int & x1,unsigned int & y1, unsigned int & x2, unsigned int & y2) {
    // 0 -> Droite
    // 1 -> Gauche
    // 2 -> Bas
    // 3 -> Haut
    float factorX1;
    float factorY1;

    float factorX2;
    float factorY2;
    if(rotationActuelle == 0) {
        factorX1 = 2;
        factorY1 = 0.5;

        factorX2= 2;
        factorY2 = 1.5;
    } else if(rotationActuelle == 1) {
        factorX1 = 0;
        factorY1 = 0.5;

        factorX2= 0;
        factorY2 = 1.5;
    } else if(rotationActuelle == 2) {
        factorX1 = 0.5;
        factorY1 = 2;

        factorX2= 1.5;
        factorY2 = 2;
    } else if(rotationActuelle == 3) {
        factorX1 = 0.5;
        factorY1 = 0;

        factorX2= 1.5;
        factorY2 = 0;

    }

    unsigned int posCircleX = 50;
    unsigned int posCircleY = 270;
    unsigned int centreX = 50;
    unsigned int centreY = 50;
    x1 = posCircleX + centreX * factorX1;
    y1 = posCircleY + centreY * factorY1;

    x2 = posCircleX + centreX * factorX2;
    y2 = posCircleY + centreY * factorY2;
}

void alwaysWalk() {
    switch(rotationActuelle) {
    case 0 :
        rectPos.setX(rectPos.getX() + 5);

        break;
    case 1:
        rectPos.setX(rectPos.getX() - 5);

        break;
    case 2:
        rectPos.setY(rectPos.getY() + 5);

        break;
    case 3:
        rectPos.setY(rectPos.getY() - 5);

        break;

    default:
        break;
    }
}

void clavier(MinGL &window){
    // On vérifie si ZQSD est pressé, et met a jour la position
    if (window.isPressed({'z', false})) {
        rotationActuelle = 3;
        setMouthRotation(x1, y1, x2, y2);

    }if (window.isPressed({'s', false})) {
        rotationActuelle = 2;
        setMouthRotation(x1, y1, x2, y2);

    }if (window.isPressed({'q', false})){
        rotationActuelle = 1;
        setMouthRotation(x1, y1, x2, y2);

    }if (window.isPressed({'d', false})) {
        rotationActuelle = 0;
        setMouthRotation(x1, y1, x2, y2);

    }

}


int main()
{
    // Initialise le système
    MinGL window("01 - Shapes", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();


    // Initialise le sous-système audio
    nsAudio::AudioEngine audioEngine;

    // On définit la musique du sous-système, et on la joue
    audioEngine.setMusic("music.wav");
    audioEngine.startMusicFromBeginning();



    // On fait tourner la boucle tant que la fenêtre est ouverte
    // Orientation du PAC-MAN

    bool ascend = false;


    nsGui::Sprite doggo("doggo.si2", nsGraphics::Vec2D(195, 195));


    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();


    // On fait tourner la boucle tant que la fenêtre est ouverte

    while (window.isOpen())
    {

        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();
        // On affiche l'image
        window << doggo;

        // On dessine les formes géométriques
        //setMouthRotation(x1, y1, x2, y2);
        alwaysWalk();
        rotateMouth(x1, y1, x2, y2, ascend);
        dessiner(window, x1, y1, x2, y2);
        clavier(window);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }

    return 0;
}

