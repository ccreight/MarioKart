#pragma once
#include "Component.h"
#include "Math.h"

class CameraComponent : public Component {

	public:
		CameraComponent(class Actor* owner);
		void Update(float deltaTime);
		Vector3 getIdealPos();
		void SnapToIdeal();

	private:
		class Actor* mOwner;
		const float H_DIST = 60.0f;
		const float V_DIST = 70.0f;
		const float TARGET_DIST = 75.0f;


		const float HORIZ_DIST = 60.0f;
		const float TARGET_OFFSET = 50.0f;
		const float SPRING_CONST = 256.0f;
		float mDampConst = 0.0f;
		Vector3 mCameraPos;
		Vector3 mCameraVeloc;

};