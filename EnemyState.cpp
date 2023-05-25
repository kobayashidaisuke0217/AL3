#include "EnemyState.h"

EnemyState::~EnemyState() {}

void EnemyStateApproach::Update(Enemy* enemy_) {
	const Vector3 kCharacterApproachSpeed = {0.0f, 0.0f, -0.5f};

	enemy_->Move(kCharacterApproachSpeed);
	if (enemy_->GetPos().z <= -15.0f) {
		enemy_->ChangeEnemyState(new EnemyStateLeave());
	}
}

void EnemyStateLeave::Update(Enemy* enemy_) {
	const Vector3 kCharacterLeaveSpeed = {-0.5f, 0.5f, 0.0f};

	enemy_->Move(kCharacterLeaveSpeed);
}
