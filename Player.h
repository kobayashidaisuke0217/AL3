#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include""
class Player {
public:
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection view);
	Vector3 operator+(Vector3 obj) { return {this->worldTransform_.translation_.x + obj.x,
	this->worldTransform_.translation_.y+obj.y,
		this->worldTransform_.translation_.z+obj.z
	};
	}
	Vector3 Add(Vector3 add1, Vector3 add2);
	private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;
};
