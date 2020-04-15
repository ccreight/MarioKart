#include "CameraComponent.h"
#include "Actor.h"
#include "VehicleMove.h"
#include "Game.h"
#include "Renderer.h"

CameraComponent::CameraComponent(Actor* owner) : Component(owner){
	mOwner = owner;
	mCameraPos = mOwner->GetPosition();
	mCameraVeloc = Vector3(0, 0, 0);
}

void CameraComponent::Update(float deltaTime) {

	//Vector3 eyeVec = getIdealPos();

	Vector3 idealPos = getIdealPos();

	mDampConst = 2.0f * sqrt(SPRING_CONST);

	Vector3 displacement = mCameraPos - idealPos;
	Vector3 springAcceleration = (-1 * SPRING_CONST * displacement) - mDampConst * mCameraVeloc;
	mCameraVeloc += springAcceleration * deltaTime;
	mCameraPos += mCameraVeloc * deltaTime;

	Vector3 targetVec = mOwner->GetPosition() + mOwner->GetForward() * TARGET_DIST;

	Matrix4 viewMatrix = Matrix4::CreateLookAt(mCameraPos, targetVec, Vector3::UnitZ);
	//Matrix4 viewMatrix = Matrix4::CreateLookAt(idealPos, targetVec, Vector3::UnitZ);
	mOwner->GetGame()->GetRenderer()->SetViewMatrix(viewMatrix);

}

Vector3 CameraComponent::getIdealPos() {

	Vector3 ideal = mOwner->GetPosition() - mOwner->GetForward() * H_DIST + Vector3(0, 0, V_DIST);
	return ideal;

}

void CameraComponent::SnapToIdeal() {

	Vector3 idealPos = getIdealPos();
	Vector3 targetVec = mOwner->GetPosition() + mOwner->GetForward() * TARGET_DIST;

	mCameraPos = idealPos;

	Matrix4 viewMatrix = Matrix4::CreateLookAt(idealPos, targetVec, Vector3::UnitZ);
	mOwner->GetGame()->GetRenderer()->SetViewMatrix(viewMatrix);

}