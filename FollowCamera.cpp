#include "FollowCamera.h"
#include"MyMath.h"
#include"ImGuiManager.h"
void FollowCamera::Initialize() { viewprojection_.Initialize();
	input_ = Input::GetInstance();
}

void FollowCamera::Update() {
	
	Move();
	Rotate();
	viewprojection_.UpdateViewMatrix();
	viewprojection_.TransferMatrix();
}

void FollowCamera::SetTarget(const WorldTransform* target) {

	target_ = target; }

void FollowCamera::Move() {
	if (target_) {

		Vector3 offset = {0.0f, 2.0f, -10.0f};

		Matrix4x4 rotateMatrix = MakeRotateMatrix(viewprojection_.rotation_);

		offset = TransformNormal(offset, rotateMatrix);
		viewprojection_.translation_ = Add(target_->translation_, offset);
		viewprojection_.translation_.y += 0.5f;
	}
}

void FollowCamera::Rotate() {
	XINPUT_STATE joystate;

	if (Input::GetInstance()->GetJoystickState(0, joystate)) {
		const float kRotateSpeed = 0.02f;
		viewprojection_.rotation_.y += (float)joystate.Gamepad.sThumbRX / SHRT_MAX * kRotateSpeed;
		/*if (viewprojection_.rotation_.x <= 0.15f && viewprojection_.rotation_.x >= -0.15f) {
			
			viewprojection_.rotation_.x +=
			    (float)joystate.Gamepad.sThumbRY / SHRT_MAX * (kRotateSpeed * -1.0f);
		} else {
			
		}*/
	}
	/*if (viewprojection_.rotation_.x <= -0.15f) {
		viewprojection_.rotation_.x = -0.15f;
	} 
	if (viewprojection_.rotation_.x >= 0.15f) {
		viewprojection_.rotation_.x = 0.15f;
	}*/
	
	
}
