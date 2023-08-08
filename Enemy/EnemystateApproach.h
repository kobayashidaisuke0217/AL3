#pragma once
#include"Enemy/EnemyState.h"
class EnemyStateApproach:public EnemyState {
public:
	void Update(Enemy* enemy_) override;
};
