#include "Player.h"
#include <cassert>
#include "math/MyMath.h"
#include"ImGuiManager.h"
#include"Grobalvariables/GlovalVariables.h"

void Player::Initialize(const std::vector<Model*>& models)  { 
	
	BaseCharactor::Initialize(models);
	models_[kModelHead] = models[kModelHead];
	models_[kModelBody] = models[kModelBody];
	models_[kModelLarm] = models[kModelLarm];
	models_[kModelRarm] = models[kModelRarm];
	models_[kModelHammer] = models[kModelHammer];
	input_ = Input::GetInstance();
	SetParent(&GetWorldTransformBody());
	//worldTransform_.Initialize();
	InitializeFloatGimmick();
	/*worldTransformHead_.translation_ = {0.0f, 1.0f, 0.0f};
	worldTransformLarm_.translation_ = {-0.2f, 1.0f, 0.0f};
	worldTransformRarm_.translation_ = {0.2f, 1.0f, 0.0f};*/
	
	worldTransformBase_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformLarm_.Initialize();
	worldTransformRarm_.Initialize();
	worldTransformHammer_.Initialize();
	GlovalVariables* globalVariables{};
	globalVariables = GlovalVariables::GetInstance();

	const char* groupName = "Player";
	GlovalVariables::GetInstance()->CreateGroup(groupName);
	globalVariables->AddItem(groupName, "Test", 90.0f);
	globalVariables->AddItem(groupName, "Head Translation", worldTransformHead_.translation_);
	globalVariables->AddItem(groupName, "Body Translation", worldTransformBody_.translation_);
	globalVariables->AddItem(groupName, "Larm Translation", worldTransformLarm_.translation_);
	globalVariables->AddItem(groupName, "Rarm Translation", worldTransformRarm_.translation_);
	ApplyGlobalVariables();
}

void Player::Update() {/* worldTransform_.TransferMatrix();*/
	//BehaviorRootUpdate();
	XINPUT_STATE joyState;

	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		behaviorRequest_ = Behavior::kAttack;
	}
	if (behaviorRequest_) {
		behavior_ = behaviorRequest_.value();
		switch (behavior_) {
		case Behavior::kRoot:
		default:
			BehaviorRootInitialize();
			break;
		case Behavior::kAttack:
			BehaviorAtackInitialize();
			break;
		
		}
		behaviorRequest_ = std::nullopt;
	}
	switch (behavior_) {
	case Behavior::kRoot:
	default:
		BehaviorRootUpdate();
		break;
	case Behavior::kAttack:
		BehaviorAtackUpdate();
		break;
	}
	ModelUpdateMatrix();
	ImGui::Begin("Player");
	ImGui::DragFloat3("Head", &worldTransformHead_.translation_.x,0.1f);
	ImGui::DragFloat3("Body", &worldTransformBody_.translation_.x, 0.1f);
	ImGui::DragFloat3("LArm", &worldTransformLarm_.translation_.x, 0.1f);
	ImGui::DragFloat3("RArm", &worldTransformRarm_.translation_.x, 0.1f);
	ImGui::DragFloat3("Base", &worldTransformBase_.translation_.x, 0.1f);
	ImGui::DragFloat3("Hammer", &worldTransformHammer_.translation_.x, 0.1f);
	ImGui::End();
}
void Player::Draw(const ViewProjection& view) { 
	models_[kModelBody]->Draw(worldTransformBody_, view);
	models_[kModelHead]->Draw(worldTransformHead_, view);
	models_[kModelLarm]->Draw(worldTransformLarm_, view);
	models_[kModelRarm]->Draw(worldTransformRarm_, view);
	models_[kModelHammer]->Draw(worldTransformHammer_, view);
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
   worldTransformHammer_.parent_ = parent;
}

void Player::ModelUpdateMatrix() { 
	worldTransformBase_.UpdateMatrix();
   worldTransformBody_.UpdateMatrix();
   worldTransformHead_.UpdateMatrix();
   worldTransformRarm_.UpdateMatrix();
   worldTransformLarm_.UpdateMatrix();
   worldTransformHammer_.UpdateMatrix();
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

void Player::BehaviorRootUpdate() {
   Move();
   UpdateFloatGimmick();
}

void Player::BehaviorAtackUpdate() {
   if (animationFrame < 10) {
		worldTransformLarm_.rotation_.x -= 0.05f;
		worldTransformRarm_.rotation_.x -= 0.05f;

		worldTransformHammer_.rotation_.x -= 0.05f;
   } else if (worldTransformHammer_.rotation_.x <= 2.0f * (float)M_PI / 4) {
		worldTransformLarm_.rotation_.x += 0.1f;
		worldTransformRarm_.rotation_.x += 0.1f;

		worldTransformHammer_.rotation_.x += 0.1f;
   } else {
		behaviorRequest_ = Behavior::kRoot;
   }

   animationFrame++;

}

void Player::BehaviorRootInitialize() {
   worldTransformLarm_.rotation_.x = 0.0f;
   worldTransformRarm_.rotation_.x = 0.0f;
   worldTransformHammer_.rotation_.x = 0.0f;

   InitializeFloatGimmick();

   worldTransformBody_.Initialize();
   worldTransformHead_.Initialize();
   worldTransformLarm_.Initialize();
   worldTransformRarm_.Initialize();
   worldTransformHammer_.Initialize();
}

void Player::BehaviorAtackInitialize() {
   worldTransformLarm_.rotation_.x = (float)M_PI;
   worldTransformRarm_.rotation_.x = (float)M_PI;
   worldTransformHammer_.rotation_.x = 0.0f;
   animationFrame = 0;
}

void Player::ApplyGlobalVariables() {
   GlovalVariables* globalVariables= GlovalVariables::GetInstance();

   const char* groupName = "Player";

   worldTransformHead_.translation_ =
	   globalVariables->GetVector3Value(groupName, "Head Translation");
   worldTransformBody_.translation_ =
	   globalVariables->GetVector3Value(groupName, "Body Translation");

    worldTransformLarm_.translation_ =
	   globalVariables->GetVector3Value(groupName, "Larm Translation");
   worldTransformRarm_.translation_ =
	   globalVariables->GetVector3Value(groupName, "Rarm Translation");
}

 
    
