#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mGame(game)
	,mState(ActorState::Active)
	,mPosition(Vector3::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
{
	game->AddActor(this);

}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	std::vector<Component*> temp = mComponents;

	for (unsigned int i = 0; i < temp.size(); i++) {
		delete temp[i];
	}

	mComponents.clear();

}

Vector3 Actor::GetForward() {

	// Calculates the forward position
	Vector3 position = Vector3(cos(mRotation), sin(mRotation), 0.0f);
	return position;

}

void Actor::Update(float deltaTime)
{
	// Updates active actors
	if (mState == ActorState::Active) {
		for (unsigned int x = 0; x < mComponents.size(); x++) {
			mComponents[x]->Update(deltaTime);
		}
		OnUpdate(deltaTime);
	}

	float arr1[4][4] = { {mScale, 0, 0, 0},
						{0, mScale, 0, 0},
						{0, 0, mScale, 0},
						{0, 0, 0, 1} };

	Matrix4 scaleMatrix = Matrix4(arr1);

	float arr2[4][4] = { {1, 0, 0, 0},
						{0, 1, 0, 0},
						{0, 0, 1, 0},
						{mPosition.x, mPosition.y, mPosition.z, 1} };

	Matrix4 translateMatrix = Matrix4(arr2);

	float arr3[4][4] = { {cos(mRotation), sin(mRotation), 0, 0},
						{-1 * sin(mRotation), cos(mRotation), 0, 0},
						{0, 0, 1, 0},
						{0, 0, 0, 1} };

	Matrix4 rotateMatrix = Matrix4(arr3);

	mWorldTransform = scaleMatrix * rotateMatrix * translateMatrix;

}

void Actor::OnUpdate(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
	// Processes input for active actors
	if (mState == ActorState::Active) {
		for (unsigned int x = 0; x < mComponents.size(); x++) {
			mComponents[x]->ProcessInput(keyState);
		}
		OnProcessInput(keyState);
	}

}

void Actor::OnProcessInput(const Uint8* keyState)
{
}

void Actor::AddComponent(Component* c)
{
	mComponents.emplace_back(c);
	std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
		return a->GetUpdateOrder() < b->GetUpdateOrder();
	});
}
