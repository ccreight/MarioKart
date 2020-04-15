#pragma once
#include "VehicleMove.h"

class PlayerMove : public VehicleMove {

	public:
		PlayerMove(class Player* owner);
		void Update(float deltaTime);
		void ProcessInput(const Uint8* keyState);
		void OnLapChange(int newLap);

	private:
		class Player* mOwner;

};