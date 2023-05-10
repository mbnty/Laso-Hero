#include "enemy.h"

enemy::enemy()
{
    enemyPosition.x = 0.0;
    enemyPosition.y = -0.25;
    enemyPosition.z = -2;

    enemySize.x = 1.0;
    enemySize.y = 0.5;

    enemyColor.x = 1.0;
    enemyColor.y = 1.0;
    enemyColor.z = 1.0;

    enemyRotation.x = enemyRotation.y = enemyRotation.z = 0;
    movement = IDLE;

    enemySpeed.x = 0.03;
    enemySpeed.y = 0.0;

    isHit = false;
    isDead = false;
    isIdle = false;
    isAttack = false;
    isSpawn = true;
    isJump = false;
    enHP = 2;

    enemyOffsetY = -0.4;
    groundValue = -0.25;

    currTime = clock();
    attackTimer = clock();

    indexTexture = 1;

    enDir = 'L';

    velocity = 30;
    theta = 30 * PI/180.0;
    t = 1;
    jumpSpeed = 0;
    airSpeed = 0.01;
}

enemy::~enemy()
{
    //dtor
}

void enemy::drawEnemy()
{
    tLoad->binder(texInd[indexTexture]);

    glPushMatrix();
    glColor3f(enemyColor.x,enemyColor.y,enemyColor.z);
    glTranslated(enemyPosition.x, enemyPosition.y, enemyPosition.z);
    glRotatef(enemyRotation.x,1,0,0);
    glRotatef(enemyRotation.y,0,1,0);
    glRotatef(enemyRotation.z,0,0,1);

    glScalef(1,enemySize.y, 1);

    glBegin(GL_POLYGON);

    glTexCoord2f(xMin, yMin);
    glVertex3f(1.0,1.0,0.0);

    glTexCoord2f(xMax, yMin);
    glVertex3f(-1.0,1.0,0.0);

    glTexCoord2f(xMax, yMax);
    glVertex3f(-1.0,-1.0,0.0);

    glTexCoord2f(xMin, yMax);
    glVertex3f(1.0,-1.0,0.0);

    glEnd();

    glPopMatrix();
}

void enemy::placeEnemy(pos3 placement)
{
    enemyPosition.x = placement.x;
    enemyPosition.y = placement.y;
    enemyPosition.z = placement.z;

    initialPosition.x = placement.x;
    initialPosition.y = placement.y;
    initialPosition.z = placement.z;
}

void enemy::initEnemy(GLuint tex, int verticalFrames, int horizontalFrames)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    vFrames = verticalFrames;
    hFrames = horizontalFrames;

    xMax = 1.0/(float)verticalFrames;
    xMin = 0.0;
    yMax = 1.0/(float)horizontalFrames;
    yMin = 0.0;

    this->tex = tex;
}

void enemy::resetEnemy()
{
    enemyPosition.x = 0.0;
    enemyPosition.y = -0.25;
    enemyPosition.z = -2;

    enemySize.x = 1.0;
    enemySize.y = 0.5;
    movement = IDLE;

    enemySpeed.x = 0.03;
    enemySpeed.y = 0.0;

    isHit = false;
    isDead = false;
    isIdle = false;
    isAttack = false;
    isSpawn = true;
    isJump = false;
    enHP = 2;

    groundValue = -0.25;

    currTime = clock();
    attackTimer = clock();

    indexTexture = 1;

    enDir = 'L';

    velocity = 30;
    theta = 30 * PI/180.0;
    t = 1;
    jumpSpeed = 0;
    airSpeed = 0.01;
}

void enemy::enemySkin(char* fileName)
{
    tLoad->loadTexture(fileName,tex);
}

void enemy::enemySkinMulti(char* fileName, GLuint& Tex)
{
    tLoad->arrayTexLoader(fileName, Tex);
}

void enemy::setAsSpear()
{
    enemySkinMulti("images/Skeleton_Spearman/Walk.png", texInd[0]);
    enemySkinMulti("images/Skeleton_Spearman/Idle.png", texInd[1]);
    enemySkinMulti("images/Skeleton_Spearman/Attack_1.png", texInd[2]);
    enemySkinMulti("images/Skeleton_Spearman/Attack_2.png", texInd[3]);
    enemySkinMulti("images/Skeleton_Spearman/Hurt.png", texInd[4]);
    enemySkinMulti("images/Skeleton_Spearman/Dead.png", texInd[5]);
    enemySkinMulti("images/Skeleton_Spearman/Fall.png", texInd[6]);
    enemySkinMulti("images/Skeleton_Spearman/Protect.png", texInd[7]);
    enemySkinMulti("images/Skeleton_Spearman/Run.png", texInd[8]);
    enemySkinMulti("images/Skeleton_Spearman/Run+attack.png", texInd[9]);

    for(int i = 0; i < 10; i++){ //Horizontal Frames only 1 cause separate images
        hFramesInd[i] = 1;
    }

    vFramesInd[0] = 7; //Walk
    vFramesInd[1] = 7; //Idle
    vFramesInd[2] = 4; //Attack 1
    vFramesInd[3] = 4; //Attack 2
    vFramesInd[4] = 3; //Hurt
    vFramesInd[5] = 5; //Dead
    vFramesInd[6] = 6; //Fall
    vFramesInd[7] = 2; //Protect
    vFramesInd[8] = 6; //Run
    vFramesInd[9] = 5; //Run+Attack
}

bool enemy::enemyPlatformCollision(platform* plat)
{

    bool collisionX = plat->pos.x + (0.25 * plat->scaleSize.x) >= enemyPosition.x &&
         enemyPosition.x >= plat->pos.x - (0.25 * plat->scaleSize.x);

    // collision y-axis
    bool collisionY = enemyPosition.y >= plat->pos.y - (0.25 * plat->scaleSize.y) &&
        plat->pos.y + (0.25 * plat->scaleSize.y) >= enemyPosition.y - 0.5;

    return collisionX && collisionY;
}

bool enemy::enemyPlayerCollisionAttack(player* ply)
{
    bool collisionX = ply->pPos.x + 0.25 >= enemyPosition.x - 0.4 &&
        enemyPosition.x + 0.5 >= ply->pPos.x - 0.25;
    bool collisionY = ply->pPos.y + 0.4 >= enemyPosition.y - 0.5 &&
        enemyPosition.y >= ply->pPos.y - 0.4;

    return collisionX && collisionY;
}

bool enemy::enemyMoveCollisionLinear(player* ply)
{
    if((fabs(ply->pPos.y-(enemyPosition.y+enemyOffsetY))) < 0.05) return true;
    else return false;
}

bool enemy::checkPlayerHit(player* ply, sounds* snds, particles* sand)
{
    if(movement == ATTACK && enemyPlayerCollisionAttack(ply) && clock() - ply->damage > 2000){
        ply->actions(ply->HURT, snds, sand);
        ply->pColor.y = 0; ply->pColor.z = 0;
        ply->health--;
        ply->damage = clock();
        snds->playSound("sounds/hurt.mp3");
    }
}

void enemy::enemyAIManager(player* ply, sounds* snds, particles* sand)
{
    if(movement == DIE || movement == ATTACK || movement == HURT || movement == JUMP){//Draws death animation
            if(xMin >= 0.75 || xMax >= 0.75){
                checkPlayerHit(ply, snds, sand);
            }
            drawEnemy();
            actions();
    }
    else if(enemyPlayerCollisionAttack(ply)){
        if(clock() - attackTimer > 3000){
            movement = ATTACK;
            attackTimer = clock();
        }else if (enDir = 'L'){
            movement = WALKL;
        }else{
            movement = WALKR;
        }
    }
    else if(enemyPosition.x < 0.90 && enemyPosition.x > -1.50){ //Distance check
        if(enemyPosition.x > ply->pPos.x && !isDead){
            if(!enemyMoveCollisionLinear(ply)){// if enemy sees player: move toward player
                movement = IDLE;
            }else{
                movement = WALKL;
            }
        }
        else if(enemyPosition.x < ply->pPos.x && !isDead){
            if(!enemyMoveCollisionLinear(ply)){
                movement = IDLE;
            }else{
                movement = WALKR;
            }
        }
    }
}


void enemy::actions()
{
    switch(movement){
    case IDLE: //stops the enemy from moving
        indexTexture = 1;
        if(isIdle == false){
            if(enDir == 'L'){
                xMax = 1.0/(float)vFramesInd[indexTexture];
                xMin = 0.0;
                yMax = 1.0/(float)hFramesInd[indexTexture];
                yMin = 0.0;
            }else{
                xMin = 1.0/(float)vFramesInd[indexTexture];
                xMax = 0.0;
                yMax = 1.0/(float)hFramesInd[indexTexture];
                yMin = 0.0;
            }
            isIdle = true;
        }
        if(clock() - currTime > 60){
            xMax += 1.0/(float)vFramesInd[indexTexture];
            xMin += 1.0/(float)vFramesInd[indexTexture];
            currTime = clock();
        }
        enemyPosition.x += 0;
        enemyPosition.y += 0;
        enemyPosition.z += 0;
        break;
    case WALKR:
        indexTexture = 0;
        isIdle = false;
        if(enDir != 'R'){
            enDir = 'R';
            xMin = 1.0/(float)vFramesInd[indexTexture];
            xMax = 0.0;
            yMax = 1.0/(float)hFramesInd[indexTexture];
            yMin = 0.0;
        }

        if(clock() - currTime > 60){
            xMax += 1.0/(float)vFramesInd[indexTexture];
            xMin += 1.0/(float)vFramesInd[indexTexture];
            enemyPosition.x += enemySpeed.x;
            currTime = clock();
        }
        break;
    case WALKL:
        indexTexture = 0;
        isIdle = false;
        if(enDir != 'L'){
            enDir = 'L';
            xMax = 1.0/(float)vFramesInd[indexTexture];
            xMin = 0.0;
            yMax = 1.0/(float)hFramesInd[indexTexture];
            yMin = 0.0;
        }
        if(clock() - currTime > 60){
            xMax += 1.0/(float)vFramesInd[indexTexture];
            xMin += 1.0/(float)vFramesInd[indexTexture];
            enemyPosition.x -= enemySpeed.x;
            currTime = clock();
        }
        break;
    case JUMP:
        indexTexture = 6;
        isIdle = false;
        if(isJump == false){
            if(enDir == 'L'){
                xMax = 1.0/(float)vFramesInd[indexTexture];
                xMin = 0.0;
                yMax = 1.0/(float)hFramesInd[indexTexture];
                yMin = 0.0;
            }else{
                xMin = 1.0/(float)vFramesInd[indexTexture];
                xMax = 0.0;
                yMax = 1.0/(float)hFramesInd[indexTexture];
                yMin = 0.0;
            }
            isJump = true;
        }
        if(clock() - currTime >= 30){
            jumpSpeed = (velocity * t * sin(theta) - 0.5 * GRVITY * t * t) / 700.0;
            enemyPosition.y += jumpSpeed;
            if(enDir == 'L'){
                enemyPosition.x -= airSpeed;
            }else{
                enemyPosition.x += airSpeed;
            }
            if(clock() - jumpTimer > 60 && (xMax >= 1.0 || xMin >= 1.0)){
                if(enDir == 'L'){
                    xMax = 6.0/(float)vFramesInd[indexTexture];
                    xMin = 5.0/(float)vFramesInd[indexTexture];

                }else{
                    xMax = 5.0/(float)vFramesInd[indexTexture];
                    xMin = 6.0/(float)vFramesInd[indexTexture];
                }
                jumpTimer = clock();
            }else if (clock() - jumpTimer > 60 && (xMax < 1.0 || xMin < 1.0)){
                xMax += 1.0/(float)vFramesInd[indexTexture];
                xMin += 1.0/(float)vFramesInd[indexTexture];
                jumpTimer = clock();

            }
            if(enemyPosition.y >= groundValue){
                t += 0.02;
                movement = JUMP;
            }else{
                t = 1;
                enemyPosition.y = groundValue;
                movement = IDLE;
            }
        }
        break;
    case ATTACK:
        indexTexture = 2;
        isIdle = false;
        if(isAttack == false){
            if(enDir == 'L'){
                xMax = 1.0/(float)vFramesInd[indexTexture];
                xMin = 0.0;
                yMax = 1.0/(float)hFramesInd[indexTexture];
                yMin = 0.0;
            }else{
                xMin = 1.0/(float)vFramesInd[indexTexture];
                xMax = 0.0;
                yMax = 1.0/(float)hFramesInd[indexTexture];
                yMin = 0.0;
            }
            isAttack = true;
        }
        if(clock() - currTime > 180){
            xMax += 1.0/(float)vFramesInd[indexTexture];
            xMin += 1.0/(float)vFramesInd[indexTexture];
            currTime = clock();
            if(xMax >= 1.0 || xMin >= 1.0){
                isAttack = false;
                movement = IDLE;
            }
        }
        break;
    case HURT:
        indexTexture = 4;
        isIdle = false;
        if(isHit == false){
            if(enDir == 'L'){
            xMax = 1.0/(float)vFramesInd[indexTexture];
            xMin = 0.0;
            yMax = 1.0/(float)hFramesInd[indexTexture];
            yMin = 0.0;
            currTime = clock();
            }
            if(enDir == 'R'){
            xMin = 1.0/(float)vFramesInd[indexTexture];
            xMax = 0.0;
            yMax = 1.0/(float)hFramesInd[indexTexture];
            yMin = 0.0;
            currTime = clock();
            }
            isHit = true;
        }
        if(clock() - currTime >= 360){
            xMax += 1.0/(float)vFramesInd[indexTexture];
            xMin += 1.0/(float)vFramesInd[indexTexture];
            currTime = clock();
            if(xMax >= 1.0 || xMin >= 1.0){
                movement = IDLE;
                isHit = false;
            }

        }
        break;
    case DIE:
        indexTexture = 5;
        isIdle = false;
        if(isDead == false){
            isDead = true;
            DeathTimer = clock();
        }
        if(enDir == 'L'){
            xMax = 1.0/(float)vFramesInd[indexTexture];
            xMin = 0.0;
            yMax = 1.0/(float)hFramesInd[indexTexture];
            yMin = 0.0;
            enDir = 'A';
            currTime = clock();
        }
        if(enDir == 'R'){
            xMin = 1.0/(float)vFramesInd[indexTexture];
            xMax = 0.0;
            yMax = 1.0/(float)hFramesInd[indexTexture];
            yMin = 0.0;
            enDir = 'D';
            currTime = clock();
        }
        if(clock() - currTime >= 60){
            xMax += 1.0/(float)vFramesInd[indexTexture];
            xMin += 1.0/(float)vFramesInd[indexTexture];
            currTime = clock();
            if(xMax >= 1.0){ // Final Frame
                if(enDir == 'A'){ //"Freezes" frame
                    xMax = 1.0;
                    xMin = xMax - 1.0/vFramesInd[indexTexture];
                }
                if(enDir == 'D'){
                    xMin = 1.0;
                    xMax = xMin - 1.0/vFramesInd[indexTexture];
                }
            }
        }
        if(clock() - DeathTimer >= 2500 && isDead == true){
            enemyPosition.y = -10;
        }
        break;
    }
}
