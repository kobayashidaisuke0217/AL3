#include "Enemy.h"
#include <assert.h>
void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	texturehandle_ = TextureManager::Load("black.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void Enemy::Update() { 
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

}

void Enemy::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}
