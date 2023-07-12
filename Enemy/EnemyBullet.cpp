#include "EnemyBullet.h"
#include "Vector3Calc.h"
#include <assert.h>
#include "Player/Player.h"
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	assert(model);
	texturehandle_ = TextureManager::Load("enemyBullet.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {0.5f, 0.5f, 3.0f};
	velocity_ = velocity;
	// Y軸回り
	worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	float velociteXZ = Length({velocity_.x, 0.0f, velocity_.z});
	// X軸回り
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, velociteXZ);
}

void EnemyBullet::Updarte() {
	Vector3 toPlayer = Subtract(player_->GetWorldPos(), worldTransform_.translation_);
	toPlayer = Normalise(toPlayer);
	velocity_ = Normalise(velocity_);
	velocity_ = Slerp(0.1f, velocity_, toPlayer);

	// Y軸回り
	worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	float velociteXZ = Length({velocity_.x, 0.0f, velocity_.z});
	// X軸回り
	worldTransform_.rotation_.x = std::atan2(-velocity_.y, velociteXZ);

	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}
void EnemyBullet::OnCollision() { isDead_ = true; }

Vector3 EnemyBullet::GetWorldPos() { 
Vector3 worldPos;
	
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
