#include "resource_dir.h"
#include "raymath.h"
#include "Settings.h"
#include "fun.h"
#include "Timer.h"
#include "Player.h"
#include "Laser.h"
#include "Meteor.h"
#include <iostream>

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame(void *args);

typedef struct Game {
	Player player;
	Camera camera;
	std::vector<Laser> lasers;
	Texture MeteorTexs[4];
	Meteor meteors[NUMBER_OF_METEORS];
	Music music;
	Sound explosion;
	Sound laserSound;
	Image darkImg;
	Model laserMod;
	Font font;
	bool debug;
	
	Game():
	player(LoadModel("models/ship.glb")), 
	camera(),
	lasers(),
	MeteorTexs(),
	meteors(),
	music(LoadMusicStream("audio/music.wav")),
	explosion(LoadSound("audio/explosion.wav")),
	laserSound(LoadSound("audio/laser.wav")),
	darkImg(LoadImage("textures/dark.png")),
	laserMod(LoadModel("models/laser.glb")),
	font(LoadFontEx("font/Stormfaze", FONT_SIZE, 0, 0)),
	debug(false) {
		camera.position = {-5.0f, 8.0f, 6.0f};
		camera.target = {0.0f, 0.0f, -1.0f};
		camera.up = {0.0f, 1.0f, 0.0f};
		camera.fovy = 45.0f;
		camera.projection = CAMERA_PERSPECTIVE;
		std::array<std::string, 4> textures = {"red", "green", "orange", "purple"};
		for (int i = 0; i < 4; i++) {
			MeteorTexs[i] = LoadTexture(("textures/" + textures[i] + ".png").c_str());
		}
		for (int i = 0; i < NUMBER_OF_METEORS; i++) {
			meteors[i] = Meteor(MeteorTexs[GetRandomValue(0, 3)]);
		}
	};

	~Game() {
		UnloadModel(player.model);
		UnloadModel(laserMod);
		for (Meteor &meteor : meteors) {
			UnloadModel(meteor.model);
			UnloadShader(meteor.shader);
		}
		UnloadMusicStream(music);
		UnloadSound(explosion);
		UnloadSound(laserSound);
		for (Texture &tex : MeteorTexs) {
			UnloadTexture(tex);
		}
		UnloadImage(darkImg);
		UnloadFont(font);
	};
} Game;

int main() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "3D Galaga");
    InitAudioDevice();
    SearchAndSetResourceDir("resources");

    Game game;

    PlayMusicStream(game.music);

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop_arg(UpdateDrawFrame, &game, 0, 1);
    #else
    
    while (!WindowShouldClose()) {
        UpdateDrawFrame(&game);
    }

    #endif
    CloseAudioDevice();
    CloseWindow();
    return 0;
}

void UpdateDrawFrame(void *args) {
    Game *game = (Game *)args;
    UpdateMusicStream(game->music);

	float dt = GetFrameTime();

	if (!game->player.isDead) {
		game->player.update(dt);

		if (IsKeyPressed(KEY_SPACE)) {
			game->player.shoot(game->lasers, game->laserMod, game->laserSound);
		}

		for (int i = 0; i < game->lasers.size(); i++) {
			game->lasers[i].update(dt, game->lasers, i);
		}

		for (Meteor &meteor : game->meteors) {
			meteor.update(dt, game->MeteorTexs);
			meteor.CheckPlayerCollision(game->player);
			meteor.CheckLaserCollision(game->lasers, game->player, game->explosion);
		}
	} else {
		if (IsKeyPressed(KEY_ENTER)) {
			game->player = Player(game->player.model);
			for (Laser &laser : game->lasers) {
				laser.destroy(game->lasers, 0);
			}
			for (Meteor &meteor : game->meteors) {
				UnloadModel(meteor.model);
				meteor = Meteor(game->MeteorTexs[GetRandomValue(0, 3)]);
			}
		}
	}

	if (IsKeyPressed(KEY_GRAVE)) {
		game->debug = !game->debug;
	}
	

	BeginDrawing();
	ClearBackground(BLACK);
	BeginMode3D(game->camera);

	DrawModel(game->player.model, game->player.pos, 1.0f, WHITE);
	if (game->debug) {
		DrawBoundingBox(game->player.bBox, RED);
	}

	for (int i = 0; i < game->lasers.size(); i++) {
		DrawModel(game->laserMod, game->lasers[i].pos, 1.0f, WHITE);
		if (game->debug) {
			DrawBoundingBox(game->lasers[i].bBox, RED);
		}
	}

	for (Meteor &meteor : game->meteors) {
		DrawModel(meteor.model, meteor.pos, 1.0f, WHITE);
	}

	EndMode3D();

	DrawTextEx(game->font, TextFormat("Score: %d", game->player.score), (Vector2){ GetScreenWidth() / 2.0f - 150.0f, GetScreenHeight() / 9.0f }, FONT_SIZE, FONT_PADDING, WHITE);

	if (game->player.isDead) {
		DrawTextEx(game->font, "Your DEAD!!!", (Vector2){ GetScreenWidth() / 2.0f - 225.0f, GetScreenHeight() / 5.0f }, FONT_SIZE, FONT_PADDING, RED);
		DrawTextEx(game->font, "Press RETURN to retry.", (Vector2){ GetScreenWidth() / 2.0f - 425.0f, GetScreenHeight() / 3.0f }, FONT_SIZE, FONT_PADDING, WHITE);
	}

	DrawFPS(0, 0);
	EndDrawing();
}