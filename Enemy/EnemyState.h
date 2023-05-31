#pragma once
#include "Enemy/Enemy.h"
#include"TimeCall.h"
class Enemy;
class EnemyState {

public:
	virtual ~EnemyState();
	virtual void Update() = 0;
	virtual void Initialize(Enemy* enemy_) = 0;

protected:
	Enemy* enemy;
	std::list<TimeCall*> timecalls_;
	
};
class EnemyStateApproach : public EnemyState {
public:
	~EnemyStateApproach();
	void Update();
	void Initialize(Enemy* enemy_);

private:
	void FireAndReset();
	
};
class EnemyStateLeave : public EnemyState {
public:
	void Update();
	void Initialize(Enemy* enemy_);
};
