#include "Player.h"
#include <cassert>
void Player::Initialize(Model* model) { 
	assert(model);
	model_ = model;
	input_ = Input::GetInstance();
	worldTransform_.Initialize();
}

void Player::Update() { worldTransform_.TransferMatrix();
	Move();
}
void Player::Draw(ViewProjection view) { 
	model_->Draw(worldTransform_, view);

}

void Player::Move() { XINPUT_STATE joystate;

   if (Input::GetInstance()->GetJoystickState(0, joystate)) {
		const float kCharctorSpeed = 0.3f;
	   Vector3 move = {
		   (float)joystate.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
		   (float)joystate.Gamepad.sThumbLY / SHRT_MAX};
		move = Multiply(kCharctorSpeed,Normalise( move));
	   Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);
		move = TransformNormal(move, rotateMatrix);
	   worldTransform_.translation_ = Add(move, worldTransform_.translation_);
		worldTransform_.rotation_.y = std::atan2(move.x, move.z);
   }
   worldTransform_.UpdateMatrix();
}
