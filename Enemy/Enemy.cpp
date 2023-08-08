#include "Enemy.h"
#include <assert.h>

Enemy::Enemy() {}
Enemy::~Enemy() { 
}

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	texturehandle_ = TextureManager::Load("black.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	stateArr_[0] = new EnemyStateApproach();
	stateArr_[1] = new EnemyStateLeav();
	//state_ = new EnemyStateApproach();
}

void Enemy::Update() {
	worldTransform_.UpdateMatrix();
	preStateNum_ = stateNum_;
	stateNum_ = stateArr_[stateNum_]->GetNum();
	stateArr_[stateNum_]->Update(this);
}

void Enemy::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}

void Enemy::Move(Vector3 velocity) {

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);
}


