#include "EnemyMove.h"
#include <fstream>
#include "CSVHelper.h"
#include "Game.h"

EnemyMove::EnemyMove(class Actor* owner) : VehicleMove(owner) {

	mOwner = owner;

	LoadCSV("Assets/HeightMap/Path.csv");
	mOwner->SetPosition(mPath[0]);

	mNextPos = 1;
	setPedal(true);

}

void EnemyMove::Update(float deltaTime) {

	if ((mOwner->GetPosition() - mPath[mNextPos]).Length() < 40.0f) {
		mNextPos++;
	}

	if (mNextPos >= (signed int)mPath.size()) {
		mNextPos = 0;
	}

	Vector3 v = mPath[mNextPos] - mOwner->GetPosition();
	v.Normalize();

	if (Vector3::Dot(v, mOwner->GetForward()) > .85f) {
		setPedal(true);
	}
	else {
		setPedal(false);
	}

	Vector3 cross = Vector3::Cross(mOwner->GetForward(), v);

	if (cross.z > 0.0f) {
		setTurning(Movement::Right);
	}
	else if (cross.z < -0.0f) {
		setTurning(Movement::Left);
	}
	else {
		setTurning(Movement::None);
	}

	VehicleMove::Update(deltaTime);

}

void EnemyMove::LoadCSV(const std::string& fileName) {

	std::string line = "";
	std::ifstream myfile(fileName);

	if (myfile.is_open())
	{
		getline(myfile, line);

		while (getline(myfile, line))
		{

			if (line == "") {
				continue;
			}

			std::vector<std::string> nums = CSVHelper::Split(line);
			Vector3 pos = mOwner->GetGame()->mMap->CellToWorld(stoi(nums[1]), stoi(nums[2]));

			mPath.push_back(pos);

		}
		myfile.close();
	}

}