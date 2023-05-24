#pragma once
#include "Vector3Calc.h"
#include "Model.h"
#include <WorldTransform.h>
class Enemy {
	
public:
	void Initialize(Model* model,const Vector3&position,const Vector3& velocity );
	void Update();
	void Draw(const ViewProjection& view);

	Vector3 GetPos() { return worldTransform_.translation_; }
	void Setpos(const Vector3& pos) { worldTransform_.translation_ = pos; }
	void SetSpeed(const Vector3& speed) { velocity_ = speed; }
	Vector3 GetSpeed() { return velocity_; }

private:
	enum class Phase {
		Approach, // 接近
		Leave,    // 離脱
		start,    // 初期
	};

	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	Vector3 velocity_;
	Phase phase_ = Phase::Approach;

	void Approach();
	void Leave();
};
