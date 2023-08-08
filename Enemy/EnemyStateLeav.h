#pragma once
#include "Enemy/EnemyState.h"
class EnemyStateLeav:public EnemyState {
public:
	void Update(Enemy* enemy_)override;
};
