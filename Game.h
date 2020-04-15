#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "Player.h"
#include "HeightMap.h"
#include "Enemy.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	Mix_Chunk* GetSound(const std::string& fileName);

	class Renderer* GetRenderer() {	return mRenderer; }

	Player* GetPlayer() {
		return mPlayer;
	}

	int GetChannel() {
		return mChannel;
	}

	HeightMap* mMap = nullptr;
	Enemy* mEnemy = nullptr;
	Player* mPlayer = nullptr;

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	const float WINDOW_WIDTH = 1024.0f, WINDOW_HEIGHT = 768.0f;

	std::unordered_map<std::string, Mix_Chunk*> mSounds;

	// All the actors in the game
	std::vector<class Actor*> mActors;

	class Renderer* mRenderer = nullptr;

	Uint32 mTicksCount;
	bool mIsRunning;

	
	Actor* mTrack = nullptr;
	MeshComponent* mTrackMesh = nullptr;

	float mTimeSinceStart = 8.5f;
	bool mActivated = false;

	int mChannel = 0;


};
