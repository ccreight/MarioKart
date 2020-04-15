#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "EnemyMove.h"

class Enemy : public Actor {

	public:
		Enemy(class Game* game);

	private:
		class Game* mGame;
		MeshComponent* mMesh;
		EnemyMove* mMove;

		const float SCALE = .75f;

};