#include "PlayerBullet.h"
#include "math/MyMath.h"
#include <assert.h>
#include "ImGuiManager.h"
void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.UpdateMatrix();
	velocity_ = velocity;
	SetCollisionAttribute(CollisionConfig::kCollisionAttributePlayer);
	SetCollisionMask(~CollisionConfig::kCollisionAttributePlayer);
}

void PlayerBullet::Updarte() {
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
		
	}
	ImGui::Begin("aa");
	ImGui::DragFloat3("pos", &worldTransform_.translation_.x, 0.1f);
	ImGui::End();
}

void PlayerBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view);
}

void PlayerBullet::OnCollision() { isDead_ = true; }

Vector3 PlayerBullet::GetWorldPos() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}