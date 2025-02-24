#include "Meteor.h"

Meteor::Meteor() {}

// private:
// 		Vector3 direction;
// 		float speed;
// 		float scale;
//         Vector2 flashAmount;
// 		Texture tex;
// 		Timer timer;
// 	public:
// 		Vector3 pos;
// 		float radius;
// 		Model model;
//         Shader shader;

Meteor::Meteor(Texture tex):
    direction((Vector3){0.0f, 0.0f, 1.0f}), 
    speed((float)GetRandomValue(METEOR_SPEED_RANGE.x, METEOR_SPEED_RANGE.y) / 10.f),
    scale((float)GetRandomValue(10, 20) / 10.0f),
    flashAmount((Vector2){ 1.0f, 0.0f }),
    tex(tex),
    timer(),
    pos((Vector3){(float)GetRandomValue(-100, 125) / 10.0f, (float)GetRandomValue(-scale, scale) / 10.0f, (float)GetRandomValue(-200, -600) / 10.0f}),
    radius(scale),
    model(LoadModelFromMesh(GenMeshSphere(radius, 16, 16))),
    shader() {
        #if defined(PLATFORM_WEB)
            shader = LoadShader(NULL, "shaders/flash-web.fs");
        #else
            shader = LoadShader(NULL, "shaders/flash.fs");
        #endif
        SetMaterialTexture(&model.materials[0], MATERIAL_MAP_ALBEDO, tex);
        model.materials[0].shader = shader;
        scale = 1.0f;
    }

void Meteor::update(float dt, Texture *texs) {
    pos.z += direction.z * speed * dt;

    if (timer.active) {
        timer.update();
        scale -= 2.0f * dt;
        radius = scale;
        model.transform = MatrixScale(scale, scale, scale);
    }
    
    if (pos.z > 8.0f) {
        UnloadModel(model);
        *this = Meteor(texs[GetRandomValue(0, 3)]);
    }
}

void Meteor::CheckPlayerCollision(Player &player) {
    if (CheckCollisionBoxSphere(player.bBox, pos, radius) && !timer.active) {
        player.isDead = true;
    }
}

void Meteor::CheckLaserCollision(std::vector<Laser> &lasers, Player &player, Sound explosion) {
    for (int i = 0; i < lasers.size(); i++) {
        if (CheckCollisionBoxSphere(lasers[i].bBox, pos, radius)) {
            if (timer.active) {
                return;
            }
            lasers[i].destroy(lasers, i);
            SetShaderValue(shader, GetShaderLocation(shader, "flash"), &flashAmount, SHADER_UNIFORM_VEC2);
            player.score++;
            PlaySound(explosion);
            Timer death(0.5, false, true, [this]() {
                Destroy();
            });
            timer = death;
        }
    }
}

void Meteor::Destroy() {
    UnloadModel(model);
    *this = Meteor(tex);
    timer.active = false;
}