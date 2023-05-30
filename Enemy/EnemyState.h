#pragma once
#include "Enemy/Enemy.h"
class Enemy;
class EnemyState {

public:
	virtual ~EnemyState();
	virtual void Update() = 0;
	virtual void Initialize(Enemy* enemy_) = 0;

protected:
	Enemy* enemy;
};
class EnemyStateApproach : public EnemyState {
public:
	void Update();
	void Initialize(Enemy* enemy_);



};
class EnemyStateLeave : public EnemyState {
public:
	void Update();
	void Initialize(Enemy* enemy_);
};
