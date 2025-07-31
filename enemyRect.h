#ifndef ENEMYRECT_H
#define ENEMYRECT_H

typedef struct {
    float x;
    float y;
    float width;
    float height;
    float speed;
    int lane;
    int active;
} EnemyRect;

void initEnemyRect(EnemyRect* enemy, float x, float y, float width, float height, float speed, int lane);
int checkCollision(EnemyRect* enemy, float playerX, float playerY, float playerWidth, float playerHeight);
void updateEnemyRect(EnemyRect* enemy, float deltaTime);
void resetEnemyRect(EnemyRect* enemy);

#endif