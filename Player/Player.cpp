#include "Player.h"
#include <cassert>
#include "math/MyMath.h"
#include"ImGuiManager.h"

void Player::Initialize(const std::vector<Model*>& models)  { 
	
	BaseCharactor::Initialize(models);
	models_[kModelHead] = models[kModelHead];
	models_[kModelBody] = models[kModelBody];
	models_[kModelLarm] = models[kModelLarm];
	models_[kModelRarm] = models[kModelRarm];
	input_ = Input::GetInstance();
	SetParent(&GetWorldTransformBody());
	//worldTransform_.Initialize();
	InitializeFloatGimmick();
	worldTransformHead_.translation_ = {0.0f, 1.0f, 0.0f};
	worldTransformLarm_.translation_ = {-0.2f, 1.0f, 0.0f};
	worldTransformRarm_.translation_ = {0.2f, 1.0f, 0.0f};
	
	worldTransformBase_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformLarm_.Initialize();
	worldTransformRarm_.Initialize();

}

void Player::Update() {/* worldTransform_.TransferMatrix();*/
	Move();
	UpdateFloatGimmick();
	ModelUpdateMatrix();
	ImGui::Begin("Player");
	ImGui::DragFloat3("Head", &worldTransformHead_.translation_.x,0.1f);
	ImGui::DragFloat3("Body", &worldTransformBody_.translation_.x, 0.1f);
	ImGui::DragFloat3("LArm", &worldTransformLarm_.translation_.x, 0.1f);
	ImGui::DragFloat3("RArm", &worldTransformRarm_.translation_.x, 0.1f);
	ImGui::DragFloat3("Base", &worldTransformBase_.translation_.x, 0.1f);
	ImGui::End();
}
void Player::Draw(const ViewProjection& view) { 
	models_[kModelBody]->Draw(worldTransformBody_, view);
	models_[kModelHead]->Draw(worldTransformHead_, view);
	models_[kModelLarm]->Draw(worldTransformLarm_, view);
	models_[kModelRarm]->Draw(worldTransformRarm_, view);

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
	   worldTransformBase_.translation_ = Add(move, worldTransformBase_.translation_);
		worldTransformBody_.translation_ = worldTransformBase_.translation_;
		worldTransformBody_.rotation_.y = std::atan2(move.x, move.z);
   }
   
}

void Player::SetParent(const WorldTransform* parent) {
   worldTransformBase_.parent_ = parent;
   worldTransformHead_.parent_ = parent;
   worldTransformRarm_.parent_ = parent;
   worldTransformLarm_.parent_ = parent;
}

void Player::ModelUpdateMatrix() { 
	worldTransformBase_.UpdateMatrix();
   worldTransformBody_.UpdateMatrix();
   worldTransformHead_.UpdateMatrix();
   worldTransformRarm_.UpdateMatrix();
   worldTransformLarm_.UpdateMatrix();
}

void Player::InitializeFloatGimmick() { floatingParametor_ = 0.0f; }

void Player::UpdateFloatGimmick() {
    uint16_t T = 120;

    float step = 2.0f * (float)M_PI / T;
float floatingAmplitude = 0.3f;

   floatingParametor_ += step;
   floatingParametor_ = (float)std::fmod(floatingParametor_, 2.0f * M_PI);

    

   worldTransformBody_.translation_.y = std::sin(floatingParametor_) * floatingAmplitude+0.2f;

   worldTransformLarm_.rotation_.x = std::sin(floatingParametor_) * 0.75f;
   worldTransformRarm_.rotation_.x = std::sin(floatingParametor_) * 0.75f;
   
}
