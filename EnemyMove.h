#pragma once
#include "VehicleMove.h"
#include "Math.h"
#include <vector>
#include <string>

class EnemyMove : public VehicleMove {

	public:
		EnemyMove(class Actor* owner);
		void Update(float deltaTime);

	private:
		class Actor* mOwner;
		std::vector<Vector3> mPath;
		int mNextPos;

		void LoadCSV(const std::string& fileName);

};