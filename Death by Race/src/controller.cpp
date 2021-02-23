#include "controller.h"

Controller::Controller()
{
    gameOver = false;
    gameRunning = false;
//    souncontroller.startTheme();
}

void Controller::renderStart(){
    glClearColor(0.0,0.0,0.0,0.0);
    if(currentScore+100 < ai.score){
        bg.overAllSpeed += 0.01;
        currentScore = ai.score;
    }

    bg.animate(sunScaleChanger);

    bg.render();

    if(gameRunning){
        ai.render();
        if(ai.hero.newBullet){
            ai.hero.newBullet = false;
        }
        if(ai.newEnemyBullet){
            ai.newEnemyBullet = false;
        }
        if(ai.enemyDead){
            ai.enemyDead = false;
        }
    }
    else{
        renderBg();
        button();
        glPushMatrix();
            glTranslatef(2.6,-3.6,0);
        glPopMatrix();


    }

    if(ai.hero.dead){
        gameOver = true;
        gameRunning = false;
//        souncontroller.heroDead(false);
        if(wait > 5){
              //  souncontroller.startTheme();
                wait = -1;
        }
        else if( wait >= 0)
            wait += 0.05;

        if(bg.overAllSpeed > 0)
        bg.overAllSpeed -= (bg.overAllSpeed/2);
    }

}

void Controller::renderBg(){
    Color color;
    color.setColor("aefou");
    glPushMatrix();
        glTranslatef(0.5,0.3,0);
        glScalef(7,5,1);
        Shapes::octagon(color);
    glPopMatrix();

    color.setColor("e67734q");
    glPushMatrix();
        glTranslatef(-3.12,-3.12,0);
        glScalef(7,7,1);
        Shapes::rect(color);
    glPopMatrix();

    color.setColor("FFFFFF");
    Text logo;
    glPushMatrix();
        glTranslatef(-1,2.3,0);
        logo.text(color, "Death By Race");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2,1.6,0);
        logo.text(color, "Click to Start the Race");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.0,-0.5,0);
        logo.text(color, "Shoot : S");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.45,-2.0,0);
        logo.text(color, "Pause : P/p");
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.0,-2.0,0);
        logo.text(color, "Resume : R/r");
    glPopMatrix();


    glPushMatrix();
        glTranslatef(-1.45,-1.0,0);
        logo.text(color, "Direction : Arrow Keys");
    glPopMatrix();

     glPushMatrix();
        glTranslatef(-1.0,-1.5,0);
        logo.text(color, "Quit : q");
    glPopMatrix();

    if(gameOver){
        glPushMatrix();
            glTranslatef(2.0,3.4,0);
            logo.score(color, ai.score);
        glPopMatrix();
    }
}

void Controller::button(){
    Color btnColor;
    btnColor.setColor("8e44ad");
    glPushMatrix();
        glTranslatef(-.5,.1,0);
        glScalef(1.5,1,1);
        Shapes::rect(btnColor);
    glPopMatrix();

    btnColor.setColor("ffffff");
    Text logo;
    glPushMatrix();
        glTranslatef(-0.05,.3,0);
        logo.text(btnColor, "Fight!");
    glPopMatrix();
}


void Controller::clicked(float x, float y){
    if(!gameRunning){

        if(x < -0.4 && x > -0.56 && y < -0.4 && y > -0.6){
            AI newAI;
            ai = newAI;
            gameRunning = true;
            gameOver = false;
            wait = 0;
            bg.overAllSpeed = 0;
        }

    }
}
