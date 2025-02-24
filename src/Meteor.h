#pragma once
#include "raylib.h"
#include "Player.h"
#include "Laser.h"
#include "Timer.h"
#include "Settings.h"
#include "raymath.h"
#include <vector>

class Meteor {
	private:
		Vector3 direction;
		float speed;
		float scale;
        Vector2 flashAmount;
		Texture tex;
		Timer timer;
	public:
		Vector3 pos;
		float radius;
		Model model;
        Shader shader;

		Meteor(); // constructor

		Meteor(Texture tex); // constructor, with a texture
		
		void update(float dt, Texture *texs); // updates the meteor; runs once per frame

		void CheckPlayerCollision(Player &player); // checks if the player and meteor are colliding, then deals with it; runs once per frame

		void CheckLaserCollision(std::vector<Laser> &lasers, Player &player, Sound explosion); // checks if any lasers and a meteor are colliding, then deals with it; runs once per frame

		void Destroy(); // destroys the meteor
};