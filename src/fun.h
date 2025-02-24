#pragma once
#include "raylib.h"
#include "raymath.h"

BoundingBox GetBoundingBox(Model model, Vector3 pos); // gets the BoundingBox of a given model with it's position