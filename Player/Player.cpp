#include "Player.h"
#include <cassert>
#include "ImGuiManager.h"
#include"Vector3Calc.h"
Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {

		delete bullet;
	}
}

void Player::Atack() {
	if (input_->PushKey(DIK_SPACE)) {
		if (count == 0) {

			const float KBulletSped = 1.0f;
			Vector3 velocity(0,0,KBulletSped);
			velocity = TransformNormal(velocity, worldTransform_.matWorld_);
			PlayerBullet* newBulllet = new PlayerBullet();
			newBulllet->Initialize(model_, worldTransform_.translation_, velocity);
			// 弾を登録する
			bullets_.push_back(newBulllet);
			count++;
		}
	} else {

		count = 0;
	}
}

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void Player::Update() {
	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	worldTransform_.TransferMatrix();
	Vector3 move = {0, 0, 0};
	// キャラクターの移動量
	const float kCharacterSpeed = 0.3f;
	float imputFloat3[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	
	// デバッグ
	ImGui::Begin("Debug");
	ImGui::SliderFloat3("player", imputFloat3, -30.0f, 30.0f);
	ImGui::End();
	worldTransform_.translation_.x = imputFloat3[0];
	worldTransform_.translation_.y = imputFloat3[1];
	worldTransform_.translation_.z = imputFloat3[2];

	const float kRotSpeed = 0.02f; 
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	// 移動限界
	const float kMoveLimiX = 30.0f;
	const float kMoveLimiY = 18.0f;


	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimiX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimiX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimiY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimiY);
	
	
	worldTransform_.translation_=Add(worldTransform_.translation_, move);
	worldTransform_.UpdateMatrix();
	
	Atack();
	for (PlayerBullet* bullet : bullets_) {
	
	bullet->Updarte();
	}
}
void Player::Draw(ViewProjection view) {
	model_->Draw(worldTransform_, view, textureHandle_);
	for (PlayerBullet* bullet : bullets_) {

	bullet->Draw(view);
	}
}

Vector3 Player::GetWorldPos() { 
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos; }
