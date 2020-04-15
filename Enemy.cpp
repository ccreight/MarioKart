#include "Enemy.h"
#include "Game.h"
#include "Renderer.h"

Enemy::Enemy(class Game* game) : Actor(game) {
	
	mGame = game;

	mMesh = new MeshComponent(this);
	mMesh->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Kart.gpmesh"));
	mMesh->SetTextureIndex(4);

	SetScale(SCALE);
	mMove = new EnemyMove(this);

}