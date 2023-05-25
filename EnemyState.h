#pragma once
#include "Enemy/Enemy.h"
class Enemy;
class EnemyState {

public:
	virtual ~EnemyState();
	virtual void Update(Enemy* enemy_) = 0;
};
class EnemyStateApproach : public EnemyState {
public:
	void Update(Enemy* enemy_);
};
class EnemyStateLeave : public EnemyState {
public:
	void Update(Enemy* enemy_);
};
