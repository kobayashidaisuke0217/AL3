#include "Player.h"
#include <cassert>
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
	const float kCharacterSpeed = 0.2f;
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
}
void Player::Draw(ViewProjection view) { model_->Draw(worldTransform_, view, textureHandle_); }