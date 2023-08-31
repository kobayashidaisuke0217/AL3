#include "Player.h"
#include <cassert>
#include "math/MyMath.h"
#include"ImGuiManager.h"
#include"Grobalvariables/GlovalVariables.h"
Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {

		delete bullet;
	}
	
}

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
	
	
	worldTransformBase_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformLarm_.Initialize();
	worldTransformRarm_.Initialize();
	worldTransformHammer_.Initialize();


		worldtransform3Dreticle_.Initialize();

	uint32_t textureReticle = TextureManager::Load("Reticle.png");

	sprite2DReticle_.reset(
	    Sprite::Create(textureReticle, {640.0f, 300.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f}));


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
	jumpFlag = true;
	jumpMove = 0.1f;
	AtackCountFlag = false;
	atackCount = 0;
	SetCollisionAttribute(CollisionConfig::kCollisionAttributePlayer);
	SetCollisionMask(~CollisionConfig::kCollisionAttributePlayer);
	
}

void Player::Update() {/* worldTransform_.TransferMatrix();*/
	//BehaviorRootUpdate();
	XINPUT_STATE joyState;

	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER&&AtackCountFlag==false) {
		behaviorRequest_ = Behavior::kAttack;
		AtackCountFlag = true;
	}
	if (AtackCountFlag == true) {
		atackCount++;
	}
	if (atackCount >= 10) {
		atackCount = 0;
		AtackCountFlag = false;
	}
	if (jumpFlag == false && joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		JUmpInitialize();
		jumpFlag = true;
	}
	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	for (PlayerBullet* bullet : bullets_) {

		bullet->Updarte();
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
	Setreticle(viewProjection_);
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
	//models_[kModelHammer]->Draw(worldTransformHammer_, view);
	for (PlayerBullet* bullet : bullets_) {

		bullet->Draw(view);
	}
	models_[kModelRarm]->Draw(worldtransform3Dreticle_, view);
}

void Player::DrawUI() { sprite2DReticle_->Draw(); }

void Player::Move() { XINPUT_STATE joystate;

   if (Input::GetInstance()->GetJoystickState(0, joystate)) {
		const float kCharctorSpeed = 0.3f;
	   Vector3 move = {
		   (float)joystate.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
		   (float)joystate.Gamepad.sThumbLY / SHRT_MAX};
		move = Multiply(kCharctorSpeed,Normalise( move));
	   Matrix4x4 rotateMatrix = MakeRotateMatrix(viewProjection_->rotation_);
		move = TransformNormal(move, rotateMatrix);
	   if (worldTransformBase_.translation_.x < -75.0f ||
		   worldTransformBase_.translation_.x > 75.0f) {
			move.x = 0.0f;
			if (worldTransformBase_.translation_.x <= 0.0f) {
				worldTransformBase_.translation_.x = -74.9f;
			} else {

				worldTransformBase_.translation_.x = 74.9f;
			}
	   }
	   if (worldTransformBase_.translation_.z < -50.0f ||
		   worldTransformBase_.translation_.z > 50.0f) {
			move.z = 0.0f;
			if (worldTransformBase_.translation_.z <= 0.0f) {
				worldTransformBase_.translation_.z = -49.9f;
			} else {

				worldTransformBase_.translation_.z = 49.9f;
			}
	   }
	   worldTransformBase_.translation_ = Add(move, worldTransformBase_.translation_);
		worldTransformBody_.translation_ = worldTransformBase_.translation_;
		//worldTransformBase_.rotation_.y = std::atan2(move.x, move.z);
		worldTransformBase_.rotation_.y = viewProjection_->rotation_.y;
		worldTransformBase_.rotation_.z = viewProjection_->rotation_.z;
		worldTransformBody_.rotation_ = worldTransformBase_.rotation_;
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
   if (jumpFlag == true) {

		Jump();
   } else {

		UpdateFloatGimmick();
   }
}

void Player::BehaviorAtackUpdate() {
   if (animationFrame < 5) {
		worldTransformLarm_.rotation_.x -= 0.05f;
		worldTransformRarm_.rotation_.x -= 0.05f;

		
   }  else {
		Atack();
		behaviorRequest_ = Behavior::kRoot;
   }

   animationFrame++;

}

void Player::BehaviorRootInitialize() {
   worldTransformLarm_.rotation_.x = 0.0f;
   worldTransformRarm_.rotation_.x = 0.0f;
   worldTransformHammer_.rotation_.x = 0.0f;
   jumpMove = -0.1f;
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

void Player::Jump() {
  
  
   if (worldTransformBase_.translation_.y > 10.0f) {
		jumpMove = -0.1f;
		
   } else if (worldTransformBase_.translation_.y < -0.1f) {
		/*jumpMove = 0.1f;*/
	   worldTransformBase_.translation_.y = 0.0f;
	   jumpFlag = false;
		
   }
   worldTransformBase_.translation_.y += jumpMove;
   worldTransformBody_.translation_.y = worldTransformBase_.translation_.y;
}

void Player::JUmpInitialize() { jumpMove = 0.1f; }



void Player::Setreticle(const ViewProjection* view) {
   const float kDistancePlayerTo3DReticle = 50.0f;
   Vector3 offset = {0.0f, 0.0f, 1.0f};

   offset = TransformNormal(offset, worldTransformBody_.matWorld_); 
   offset = Multiply(kDistancePlayerTo3DReticle, Normalise(offset));

   worldtransform3Dreticle_.translation_ = Add(GetWorldPos(), offset);
   worldtransform3Dreticle_.UpdateMatrix();

   Vector3 positionReticle = {
	   worldtransform3Dreticle_.matWorld_.m[3][0], worldtransform3Dreticle_.matWorld_.m[3][1],
	   worldtransform3Dreticle_.matWorld_.m[3][2]} /*worldtransform3Dreticle_.translation_*/;

   Matrix4x4 matViewport =
	   MakeViewportMatrix(0.0f, 0.0f, WinApp::kWindowWidth, WinApp::kWindowHeight, 0.0f, 1.0f);

   Matrix4x4 matViewProjectionViewport =
	   Multiply(Multiply(view->matView, view->matProjection), matViewport);
   positionReticle = Transform(positionReticle, matViewProjectionViewport);
   
 ///*  XINPUT_STATE joystate;*/
   Vector2 spritePostition = sprite2DReticle_->GetPosition();
   
		
		sprite2DReticle_->SetPosition({spritePostition.x,spritePostition.y});
   

 
   worldtransform3Dreticle_.UpdateMatrix();
}
void Player::Atack() {
   const float KBulletSped = 1.0f;
   Vector3 velocity(0.0f, 0.0f, KBulletSped);
   
   velocity = Subtract(
	   {worldtransform3Dreticle_.matWorld_.m[3][0], worldtransform3Dreticle_.matWorld_.m[3][1],
	    worldtransform3Dreticle_.matWorld_.m[3][2]},
	   GetWorldPos());
   velocity = Multiply(KBulletSped, Normalise(velocity));
   
   PlayerBullet* newBulllet = new PlayerBullet();
  float bulletoffset = 5.0f;
   
   newBulllet->Initialize(
	   models_[kModelHammer],
	   {
		   worldTransformBase_.translation_.x, worldTransformBase_.translation_.y + bulletoffset , worldTransformBase_.translation_.z
	   },
	   velocity);
   // 弾を登録する
   bullets_.push_back(newBulllet);
  
}
Vector3 Player::GetWorldPos() {
   Vector3 worldPos;
   worldPos.x = worldTransformBase_.matWorld_.m[3][0];
   worldPos.y = worldTransformBase_.matWorld_.m[3][1];
   worldPos.z = worldTransformBase_.matWorld_.m[3][2];
   return worldPos;
}

void Player::OnCollision() {}

 
    
