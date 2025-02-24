#pragma once
#include "raylib.h"
#include "Laser.h"
#include "Settings.h"
#include "fun.h"
#include <vector>

class Player {
    private:
        Vector3 direction;

    public:
        Vector3 pos;
        Model model;
        BoundingBox bBox;
        int score;
        bool isDead;

        Player(Model mod); // constructor

        void update(float dt); // update method; runs once per frame

        void shoot(std::vector<Laser> &lasers, Model laserMod, Sound laserSound); // spawns a laser
};