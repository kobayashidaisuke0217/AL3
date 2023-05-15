#include "PlayerBullet.h"
#include<assert.h>
#include "Vector3Calc.h"
void PlayerBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) 
{ assert(model);
	texturehandle_ = TextureManager::Load("black.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void PlayerBullet::Updarte() { worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}

void PlayerBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}

//Vector3 PlayerBullet::Add(Vector3& a, Vector3& b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
