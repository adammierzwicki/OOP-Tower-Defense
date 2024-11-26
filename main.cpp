#include <iostream>
#include <vector>
// #include "gun.cpp"
// #include "enemy.cpp"
#include "tower.cpp"

int main() {
    Tower* tower = new Tower();
    tower->placeTower(1, 2);

    Enemy* enemy1 = new Peasant();
    Enemy* enemy2 = new Warrior();
    Enemy* enemy3 = new HeavyKnight();

    enemy1->setStartPosition({3, 4});
    enemy2->setStartPosition({10, 10});
    enemy3->setStartPosition({6, 8});

    std::vector<Enemy*> enemies = {enemy1, enemy2, enemy3};

    Enemy* closestEnemy = tower->getClosestEnemy(enemies);
    tower->shoot(closestEnemy);    

    Tower* upgradedTower = tower->upgrade();
    delete tower;
    upgradedTower->shoot(closestEnemy);
    closestEnemy = tower->getClosestEnemy(enemies);
    upgradedTower->shoot(closestEnemy);

    // Tower* finalTower = upgradedTower->upgrade();
    // delete upgradedTower;
    // finalTower->shoot();

    // Tower* maxTower = finalTower->upgrade();
    // delete maxTower;
    delete upgradedTower;

    return 0;
}