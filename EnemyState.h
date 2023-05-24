#pragma once
#include "Enemy/Enemy.h"
class EnemyState {
protected:
	Enemy* enemy_;

public:
	void Update();
};
class EnemyStateApproach:public EnemyState {
public:
	void Update();
};
class EnemyStateleave:public EnemyState {
public:
	void Update();
};
