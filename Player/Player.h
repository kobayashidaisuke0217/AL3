#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include"PlayerBullet.h"
#include <list>
#include "Manager/Collider/Collider.h"
#include "Manager/Collider/CollisionConfig.h"
class Player : public Collider {
public:
	~Player();
	void Initialize(Model* model, uint32_t textureHandle, Vector3 pos);

	void Update();

	void Draw(ViewProjection view);
	
	Vector3 GetWorldPos() override;
	void OnCollision() override;

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }
	void Setparent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }
	

private:
	int count = 0;
	std::list<PlayerBullet*> bullets_;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	PlayerBullet* bullet_ = nullptr;
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;


	void Atack();
};
