#include "EnemyState.h"

EnemyState::~EnemyState() {

}

EnemyStateApproach::~EnemyStateApproach() {
	for (TimeCall* timeCall : timecalls_) {

		delete timeCall;
	}
}

void EnemyStateApproach::Update() {
	timecalls_.remove_if([](TimeCall* timecall) {
		if (timecall->IsFinish()) {
			delete timecall;
			return true;
		}
		return false;
	});
	for (TimeCall*timecall:timecalls_) {
		timecall->Update();
	}
		
	const Vector3 kCharacterApproachSpeed = {0.0f, 0.0f, 0.0f};

	enemy->Move(kCharacterApproachSpeed);
	if (enemy->GetPos().z <= -15.0f) {
		enemy->ChangeEnemyState(new EnemyStateLeave());
	}
}

void EnemyStateApproach::Initialize(Enemy* enemy_) { enemy = enemy_; 
enemy->fireTimer = enemy->kFireInterval;
	FireAndReset();
}

void EnemyStateApproach::FireAndReset() { 
	
	enemy->Fire();

	timecalls_.push_back(
	    new TimeCall(std::bind(&EnemyStateApproach::FireAndReset, this), enemy->kFireInterval));
}

void EnemyStateLeave::Update() {
	const Vector3 kCharacterLeaveSpeed = {-0.1f, 0.1f, 0.0f};

	enemy->Move(kCharacterLeaveSpeed);
}

void EnemyStateLeave::Initialize(Enemy* enemy_) { enemy = enemy_; }
