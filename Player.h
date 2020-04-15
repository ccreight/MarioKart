#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "PlayerMove.h"
#include "CameraComponent.h"
#include "PlayerUI.h"

class Player : public Actor {

	public:
		Player(class Game* game);
		PlayerUI* mUI;

	private:
		const float WIDTH = 100.0f, HEIGHT = 40.0f, DEPTH = 60.0f, SCALE = .75f;
		class Game* mGame;
		MeshComponent* mMesh;
		//CollisionComponent* mCollision;
		PlayerMove* mMove;
		CameraComponent* mCamera;
		

};