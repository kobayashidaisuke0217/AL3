#pragma once
#include "Enemy/Enemy.h"
class Enemy;
class EnemyState {
	

protected:
	Enemy* enemy_;

public:
	void Update();
};
class EnemyStateApproach:public EnemyState {
public:
	static void Update();
};
class EnemyStateleave:public EnemyState {
public:
	static void Update();
};
