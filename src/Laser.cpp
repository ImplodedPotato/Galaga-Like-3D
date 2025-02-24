#include "Laser.h"

Laser::Laser(Vector3 pos, Model mod) : 
    direction({0.0f, 0.0f, -1.0f}), 
    pos((Vector3){pos.x, pos.y, pos.z - 1.0f}), 
    model(mod),
    bBox(GetBoundingBox(mod, pos)) {}

void Laser::update(float dt, std::vector<Laser> &lasers, int index) {
    pos.z += direction.z * LAZER_SPEED * dt;

    bBox = GetBoundingBox(model, pos);

    if (pos.z < -20.0f) {
        destroy(lasers, index);
    }
}

void Laser::destroy(std::vector<Laser> &lasers, int index) {
    lasers.erase(lasers.begin() + index);
}