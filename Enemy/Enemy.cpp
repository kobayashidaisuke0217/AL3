#include "Enemy.h"
#include <assert.h>
#include "Player/Player.h"
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
	assert(player_);
	//弾の速度
	const float kBulletSpeed = 1.0f;
	Vector3 playerPos = player_->GetWorldPos();
	Vector3 enemyPos = GetWorldPos();
	Vector3 velocity = Subtract(playerPos, enemyPos);
	velocity = Multiply(kBulletSpeed, Normalise(velocity));
	//生成と初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	bullets_.push_back(newBullet);


}

Vector3 Enemy::GetWorldPos() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
