#include "Enemy.h"
#include "math/MyMath.h"
#include"Player/Player.h"
#include"GameScene.h"
void Enemy::Initialize(const std::vector<Model*>& models,const Vector3& pos) {
	BaseCharactor::Initialize(models, pos);
	models_[kModelBody] = models[kModelBody];
	models_[1] = models[1];
	worldTransform_.translation_ = pos;
	
	worldTransform_.Initialize();
	SetCollisionAttribute(CollisionConfig::kCollisionAttributeEnemy);
	SetCollisionMask(~CollisionConfig::kCollisionAttributeEnemy);
	isAlive_ = true;
	count = 0;
	SetRadius(2.0f);
}

void Enemy::Update() {
	count++;
	if (count >= 60) {
		Fire();
		count = 0;
	}
	Vector3 Rotate = Subtract(player_->GetWorldPos(), GetWorldPos());

	worldTransform_.rotation_.y = std::atan2(Rotate.x, Rotate.z);
	float RotateXZ = Length({Rotate.x, 0.0f, Rotate.z});
	// X軸回り
	worldTransform_.rotation_.x = std::atan2(-Rotate.y, RotateXZ);

	BaseCharactor::Update();
}

void Enemy::Draw(const ViewProjection& view) {
	if (isAlive_ == true) {

		models_[kModelBody]->Draw(worldTransform_, view);
	}
}

Vector3 Enemy::GetWorldPos() {
	Vector3 worldPos;
	worldTransform_.UpdateMatrix();
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::OnCollision() { 
	isAlive_ = false;

}

void Enemy::Fire() {
	assert(player_);
	// 弾の速度
	const float kBulletSpeed = 1.0f;
	Vector3 playerPos = player_->GetWorldPos();
	Vector3 enemyPos = this->GetWorldPos();
	Vector3 velocity = Subtract(playerPos, enemyPos);
	velocity = Normalise(velocity);
	velocity.x *= kBulletSpeed;
	velocity.y *= kBulletSpeed;
	velocity.z *= kBulletSpeed;
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->SetPlayer(player_);
	// 生成と初期化
	newBullet->Initialize(models_[1], worldTransform_.translation_, velocity);

	gameScene_->AddEnemyBullet(newBullet);
}
