#include "VehicleMove.h"
#include "Actor.h"
#include "Game.h"
#include <fstream>
#include "CSVHelper.h"
#include <iostream>

VehicleMove::VehicleMove(class Actor* actor) : Component(actor, 50){

	mOwner = actor;
	mIsAccelerating = false;
	mTurning = Movement::None;
	mVelocity = Vector3::Zero;
	mAngularVelocity = 0.0f;
	mTimeAccelerating = 0.0f;

	LoadCheckpoints("Assets/HeightMap/Checkpoints.csv");

}

void VehicleMove::Update(float deltaTime) {

	if (mLastCheckpoint == 0) {
		OnLapChange(mCurrentLap);
	}

	float AccelerationMagnitude = 0.0f;

	if (mIsAccelerating) {

		mTimeAccelerating += deltaTime;

		if (mTimeAccelerating > ACCEL_RAMP_TIME) {
			mTimeAccelerating = ACCEL_RAMP_TIME;
		}

		AccelerationMagnitude = Math::Lerp(MIN_LINEAR_ACCEL, MAX_LINEAR_ACCEL, mTimeAccelerating / ACCEL_RAMP_TIME);

		mVelocity += mOwner->GetForward() * AccelerationMagnitude * deltaTime;

	}

	else {
		mTimeAccelerating = 0.0f;
	}

	// Update position
	mOwner->SetPosition(mOwner->GetPosition() + mVelocity * deltaTime);

	// Apply linear drag to the velocity
	if (mIsAccelerating) {
		mVelocity *= LINEAR_DRAG_COEFF_NO_ACCEL;
	}
	else {
		mVelocity *= LINEAR_DRAG_COEFF;
	}

	float TurnFactor = 0.0f;

	if (mTurning == Movement::Left) {
		TurnFactor = -1.0f;
	}
	else if (mTurning == Movement::Right) {
		TurnFactor = 1.0f;
	}

	Vector3 pos = mOwner->GetPosition();

	if (mTurning != Movement::None) {
		mAngularVelocity += ANGULAR_ACCEL * TurnFactor * deltaTime;
		mOwner->SetRotation(mOwner->GetRotation() + mAngularVelocity * deltaTime);
	}
	//if (mOwner->GetGame()->mMap->isOnTrack(pos.x, pos.y)){
		mAngularVelocity *= ANGULAR_DRAG_COEFF;
	//}

	if (mOwner->GetGame()->mMap->isOnTrack(pos.x, pos.y)) {
		float z = Math::Lerp(pos.z, mOwner->GetGame()->mMap->GetHeight(pos.x, pos.y), .1f);
		mOwner->SetPosition(Vector3(pos.x, pos.y, z));
	}

	Checkpoint c = mCheckpoints[mLastCheckpoint + 1];
	std::pair<int, int> loc = mOwner->GetGame()->mMap->WorldToCell(pos.x, pos.y);

	if (c.mMaxX == c.mMinX && abs(loc.first - c.mMaxX) < 1) {
		if (loc.second <= c.mMaxY && loc.second >= c.mMinY) {
			mLastCheckpoint++;
		}
	}
	else if (c.mMaxY == c.mMinY && abs(loc.second - c.mMaxY) < 1) {
		if (loc.first <= c.mMaxX && loc.first >= c.mMinX) {
			mLastCheckpoint++;
		}
	}
	
	if (mLastCheckpoint == mCheckpoints.size() - 1) {
		mLastCheckpoint = -1;
		mCurrentLap++;
	}

	if (!mMusicChanged && mCurrentLap >= 4 && mLastCheckpoint == 0) {
		Mix_FadeOutChannel(mOwner->GetGame()->GetChannel(), 250);
		Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/FinalLap.wav"), 0);
		Mix_FadeInChannel(mOwner->GetGame()->GetChannel(), mOwner->GetGame()->GetSound("Assets/Sounds/MusicFast.ogg"), -1, 4000);
		mMusicChanged = true;
	}

}

void VehicleMove::LoadCheckpoints(const std::string& fileName) {

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
			Checkpoint c = Checkpoint(stof(nums[1]), stof(nums[3]), stof(nums[2]), stof(nums[4]));

			mCheckpoints.push_back(c);

		}
		myfile.close();
	}

}

float VehicleMove::distToCheck() {

	Checkpoint c = mCheckpoints[mLastCheckpoint + 1];

	
	if (c.mMaxX == c.mMinX) {
		int averageY = (int)((c.mMaxY + c.mMinY) / 2);
		return (mOwner->GetPosition() - mOwner->GetGame()->mMap->CellToWorld((int)c.mMaxX, averageY)).Length();
	}

	else {
		int averageX = (int)((c.mMaxX + c.mMinX) / 2);
		return (mOwner->GetPosition() - mOwner->GetGame()->mMap->CellToWorld((int)c.mMaxY, averageX)).Length();
	}

}