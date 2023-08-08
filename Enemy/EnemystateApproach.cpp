#include "EnemystateApproach.h"
#include"Enemy/Enemy.h"
void EnemyStateApproach::Update(Enemy* enemy_) {
	const Vector3 kCharacterApproachSpeed = {0.0f, 0.0f, -0.5f};

	enemy_->Move(kCharacterApproachSpeed);
	if (enemy_->GetPos().z <= -15.0f) {
		StateNum = 1;
		//enemy_->ChangeEnemyState(new EnemyStateLeave());
	}
}