#include "PlayerBullet.h"
#include<assert.h>
void PlayerBullet::Initialize(Model* model, const Vector3& position) 
{ assert(model);
	texturehandle_ = TextureManager::Load("black.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void PlayerBullet::Updarte() { worldTransform_.UpdateMatrix(); }

void PlayerBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}
