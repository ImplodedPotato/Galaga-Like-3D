#pragma once
#include "raylib.h"
#include <vector> 
#include "Settings.h"
#include "fun.h"

class Laser {
	private:
		Vector3 direction;

	public:
        Vector3 pos;
        Model model;
        BoundingBox bBox;

		Laser(Vector3 pos, Model mod); // constructor

        void update(float dt, std::vector<Laser> &lasers, int index); // update method; runs once per frame

	    void destroy(std::vector<Laser> &lasers, int index); // destoys a laser
}; 