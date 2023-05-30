#include "EnemyState.h"

EnemyState::~EnemyState() {}

void EnemyStateApproach::Update() {
	if (--enemy->fireTimer <= 0) {
		enemy->Fire();
		enemy->fireTimer = enemy->kFireInterval;
	}
	const Vector3 kCharacterApproachSpeed = {0.0f, 0.0f, -0.1f};

	enemy->Move(kCharacterApproachSpeed);
	if (enemy->GetPos().z <= -15.0f) {
		enemy->ChangeEnemyState(new EnemyStateLeave());
	}
}

void EnemyStateApproach::Initialize(Enemy* enemy_) { enemy = enemy_; 
enemy->fireTimer = enemy->kFireInterval;
}

void EnemyStateLeave::Update() {
	const Vector3 kCharacterLeaveSpeed = {-0.1f, 0.1f, 0.0f};

	enemy->Move(kCharacterLeaveSpeed);
}

void EnemyStateLeave::Initialize(Enemy* enemy_) { enemy = enemy_; }
