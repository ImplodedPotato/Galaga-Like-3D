#include "Player.h"

Player::Player(Model mod) : 
    direction({0.0f, 0.0f, 0.0f}), 
    pos({0.0f, 0.0f, 0.0f}), 
    model(mod), 
    bBox(GetBoundingBox(model, pos)), 
    score(0),
    isDead(false) {}

void Player::update(float dt) {
    direction.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    direction.z = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

    if (direction.x == 0.0f && direction.z == 0.0f) {
        direction.x = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
        direction.z = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);
    }

    direction = Vector3Normalize(direction);

    pos.x += direction.x * PLAYER_SPEED * dt;
    pos.z += direction.z * PLAYER_SPEED * dt;

    if (pos.x > 10.0f) {
        pos.x = 10.0f;
    }
    if (pos.x < -5.0f) {
        pos.x = -5.0f;
    }
    if (pos.z > 5.0f) {
        pos.z = 5.0f;
    }
    if (pos.z < -5.0f) {
        pos.z = -5.0f;
    }

    bBox = GetBoundingBox(model, pos);
}

void Player::shoot(std::vector<Laser> &lasers, Model laserMod, Sound laserSound) {
    lasers.push_back(Laser(pos, laserMod));
    PlaySound(laserSound);
}