#pragma once
#include "Model.h"
#include "Manager/Collider/Collider.h"
class Player;
class EnemyBullet : public Collider {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Updarte();

	void Draw(const ViewProjection& view);

	bool isDead() const { return isDead_; }
	void SetPlayer(Player* player) { player_ = player; }
	void OnCollision() override;
	Vector3 GetWorldPos() override;

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	Vector3 velocity_;
	static const int32_t kLifeTime = 10*20;

	int32_t deathTimer_ = kLifeTime;
	Player* player_;


	bool isDead_ = false;
};
