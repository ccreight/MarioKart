#pragma once
#include "Component.h"
#include "Math.h"
#include <vector>
#include <string>

enum class Movement {

	Left,
	Right,
	None

};

class Checkpoint {

	public:
		Checkpoint(float minx, float miny, float maxx, float maxy) {
			mMinX = minx;
			mMinY = miny;
			mMaxX = maxx;
			mMaxY = maxy;
		}

		float mMinX, mMinY, mMaxX, mMaxY;

};

class VehicleMove : public Component {

	public:
		VehicleMove(class Actor* actor);
		void Update(float deltaTime);

		void setPedal(bool accel) {
			mIsAccelerating = accel;
		}

		void setTurning(Movement m) {
			mTurning = m;
		}

		void LoadCheckpoints(const std::string& fileName);

		virtual void OnLapChange(int newLap) {}

		int mCurrentLap = 1;
		int mLastCheckpoint = -1;

		class Actor* getOwner() {
			return mOwner;
		}

		std::vector<Checkpoint> getCheckpoints() {
			return mCheckpoints;
		}

		float distToCheck();

	private:
		class Actor* mOwner;
		bool mIsAccelerating;
		Movement mTurning;
		Vector3 mVelocity;
		float mAngularVelocity;
		float mTimeAccelerating;

		const float MIN_LINEAR_ACCEL = 500.0f;
		const float MAX_LINEAR_ACCEL = 750.0f;
		const float ACCEL_RAMP_TIME = 2.0f;
		const float ANGULAR_ACCEL = Math::Pi * 4.0f;
		const float LINEAR_DRAG_COEFF = .9f;
		const float LINEAR_DRAG_COEFF_NO_ACCEL = .975f;
		const float ANGULAR_DRAG_COEFF = .9f;

		std::vector<Checkpoint> mCheckpoints;
		bool mMusicChanged = false;

};