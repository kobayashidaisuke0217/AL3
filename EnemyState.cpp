#include "EnemyState.h"

void EnemyState::Update() {


}

void EnemyStateApproach::Update() {
	enemy_->Setpos(Add(enemy_->GetPos(),enemy_->GetSpeed()));
	if (enemy_->GetPos() .z< -15.0f) {

		phase_ = Phase::Leave;
	}
}

void EnemyStateleave::Update() {

}
