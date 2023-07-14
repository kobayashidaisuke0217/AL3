#pragma once
#include "EnemyState.h"
#include "Model.h"
#include "MyMath.h"
#include <WorldTransform.h>
#include "EnemyBullet.h"
#include "Manager/Collider/Collider.h"
#include "Manager/Collider/CollisionConfig.h"
class GameScene;
class Player;
class EnemyState;
class Enemy:public Collider {

public:
	Enemy();
	~Enemy();
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& view);

	Vector3 GetPos() { return worldTransform_.translation_; }
	void Setpos(const Vector3& pos) { worldTransform_.translation_ = pos; }
	void Move(Vector3 velocity);
	Vector3 GetSpeed() { return velocity_; }
	void ChangeEnemyState(EnemyState* enemyState);

	void Fire();
	void OnCollision() override;
	Vector3 GetWorldPos() override;
	//発射間隔
	static const int kFireInterval = 60;
	int32_t fireTimer;
	void SetPlayer(Player* player) { player_ = player; }
	
	//const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	bool isDead() const { return isDead_; }

private:
	EnemyState* state_;
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	Vector3 velocity_;
	bool isDead_ = false;
	/* std::list<EnemyBullet*> bullets_;*/
	
	Player* player_ = nullptr;
	 GameScene* gameScene_ = nullptr;
};
