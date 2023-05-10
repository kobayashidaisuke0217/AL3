#include "Player.h"
#include <cassert>
#include "matrixCalc.h"
#include "ImGuiManager.h"
Vector3 Player::Add(Vector3 add1, Vector3 add2) {
	
	return {add1.x + add2.x, add1.y + add2.y, add1.z + add2.z};
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
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	//worldTransform_.TransferMatrix();
}
void Player::Draw(ViewProjection view) { model_->Draw(worldTransform_, view, textureHandle_);
}