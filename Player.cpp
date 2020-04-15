#include "Player.h"
#include "Game.h"
#include "Renderer.h"

Player::Player(class Game* game) : Actor(game) {

	mGame = game;

	mMesh = new MeshComponent(this);
	mMesh->SetMesh(mGame->GetRenderer()->GetMesh("Assets/Kart.gpmesh"));
	mMesh->SetTextureIndex(2);

	SetScale(.75);

	/*mCollision = new CollisionComponent(this);
	mCollision->SetSize(WIDTH, HEIGHT, DEPTH);*/

	mMove = new PlayerMove(this);
	mCamera = new CameraComponent(this);

	mCamera->SnapToIdeal();

	mUI = new PlayerUI(this);

}