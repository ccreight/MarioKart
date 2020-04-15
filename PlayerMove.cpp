#include "PlayerMove.h"
#include <SDL/SDL.h>
#include "Game.h"
#include "Renderer.h"
#include "Actor.h"
#include "Player.h"
#include <iostream>

PlayerMove::PlayerMove(Player* owner) : VehicleMove(owner) {

	mOwner = owner;
	mOwner->SetPosition(mOwner->GetGame()->mMap->CellToWorld(39, 58));

}

void PlayerMove::Update(float deltaTime) {

	VehicleMove::Update(deltaTime);

}


void PlayerMove::ProcessInput(const Uint8* keyState) {

	if (keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP]) {
		setPedal(true);
	}
	else {
		setPedal(false);
	}

	if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) {
		setTurning(Movement::Left);
	}
	else if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) {
		setTurning(Movement::Right);
	}
	else {
		setTurning(Movement::None);
	}

}

void PlayerMove::OnLapChange(int newLap) {

	if (newLap >= 5) {

		Mix_FadeOutChannel(mOwner->GetGame()->GetChannel(), 250);

		if (mOwner->GetGame()->mPlayer->GetComponent<VehicleMove>()->mCurrentLap >= 5) {
			mOwner->mUI->SetRaceState(PlayerUI::Won);
			Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Won.wav"), 0);
		}
		else {
			mOwner->mUI->SetRaceState(PlayerUI::Lost);
			Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Lost.wav"), 0);
		}

		mOwner->GetGame()->mPlayer->SetState(ActorState::Paused);
		mOwner->GetGame()->mEnemy->SetState(ActorState::Paused);

	}

	mOwner->mUI->OnLapChange(newLap);

}