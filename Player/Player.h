#pragma once
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include"PlayerBullet.h"
#include <list>
#include "Manager/Collider/Collider.h"
#include "Manager/Collider/CollisionConfig.h"
#include <Sprite.h>
class Player : public Collider {
public:
	~Player();
	void Initialize(Model* model, uint32_t textureHandle, Vector3 pos);

	void Update(const ViewProjection view);

	void Draw(const ViewProjection view);
	void DrawUI();
	Vector3 GetWorldPos() override;
	void OnCollision() override;

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }
	void Setparent(const WorldTransform* parent) { worldTransform_.parent_ = parent; } 
	void SetViewProjection(const ViewProjection& view) { viewProjection_ = view; }

private:
	int count = 0;
	std::list<PlayerBullet*> bullets_;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;
	PlayerBullet* bullet_ = nullptr;
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;
	WorldTransform worldtransform3Dreticle_;

	Sprite* sprite2DReticle_ = nullptr;
	void Atack();
	void Setreticle(const ViewProjection view);
};
