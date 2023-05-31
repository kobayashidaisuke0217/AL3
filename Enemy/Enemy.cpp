#include "Enemy.h"
#include <assert.h>

Enemy::Enemy() {}
Enemy::~Enemy() { 
	for (EnemyBullet* bullet : bullets_) {

		delete bullet;
	}
	delete state_; 
	
}

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	texturehandle_ = TextureManager::Load("Enemy.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	state_ = new EnemyStateApproach();
	state_->Initialize(this);
	
}

void Enemy::Update() {
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	worldTransform_.UpdateMatrix();

	state_->Update();
	
	

	for (EnemyBullet* bullet : bullets_) {

		bullet->Updarte();
	}
	

	
}

void Enemy::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
	for (EnemyBullet* bullet : bullets_) {

		bullet->Draw(view);
	}
}

void Enemy::Move(Vector3 velocity) {

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);
}

void Enemy::ChangeEnemyState(EnemyState* enemyState) {
	delete state_;
	state_ = enemyState;
	state_->Initialize(this);
}



void Enemy::Fire() {
	//弾の速度
	Vector3 velocity = {0.0f,0.0f,-1.0f};
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);
	//生成と初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	bullets_.push_back(newBullet);


}
