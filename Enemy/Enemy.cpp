#include "Enemy.h"
#include <assert.h>

Enemy::Enemy() {

}
Enemy::~Enemy() { delete state_; }

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	texturehandle_ = TextureManager::Load("black.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	state_ = new EnemyStateApproach();
}

void Enemy::Update() { 
	worldTransform_.UpdateMatrix();

	state_->Update(this);
	

}

void Enemy::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}

void Enemy::Move(Vector3 speed) {

	worldTransform_.translation_ = Add(worldTransform_.translation_,speed);
}

void Enemy::ChangeEnemyState(EnemyState* enemyState) { delete state_;
	state_ = enemyState;

}

