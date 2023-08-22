#include "Enemy.h"
#include "math/MyMath.h"
void Enemy::Initialize(const std::vector<Model*>& models) {
	BaseCharactor::Initialize(models);
	worldTransform_.translation_.z = 30.0f;
}

void Enemy::Update() {
	const float kCharctorSpeed = 0.3f;
	Vector3 velocity{0.0f, 0.0f, kCharctorSpeed};
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);
	worldTransform_.rotation_.y += 0.05f;
	BaseCharactor::Update();
}

void Enemy::Draw(const ViewProjection& view) { BaseCharactor::Draw(view); }
