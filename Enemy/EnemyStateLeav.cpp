#include "EnemyStateLeav.h"
#include "Enemy/Enemy.h"
void EnemyStateLeav::Update(Enemy* enemy_) {
	const Vector3 kCharacterLeaveSpeed = {-0.5f, 0.5f, 0.0f};

	enemy_->Move(kCharacterLeaveSpeed);
}
