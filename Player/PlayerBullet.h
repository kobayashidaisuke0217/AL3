#pragma once
#include "Manager/Collider/Collider.h"
#include "Manager/Collider/CollisionConfig.h"
#include "Model.h"
#include "WorldTransform.h"
class PlayerBullet : public Collider {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Updarte();

	void Draw(const ViewProjection& view);

	bool isDead() const { return isDead_; }

	void OnCollision() override;

	Vector3 GetWorldPos() override;

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	Vector3 velocity_;
	static const int32_t kLifeTime = 30 * 100;

	int32_t deathTimer_ = kLifeTime;

	bool isDead_ = false;
};