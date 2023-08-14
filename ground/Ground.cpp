#include "Ground.h"
#include <cassert>
void Ground::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {100.0f, 100.0f, 100.0f};
	
}

void Ground::Update() { worldTransform_.UpdateMatrix(); }

void Ground::Draw(const ViewProjection& viewPrijection) {
	model_->Draw(worldTransform_, viewPrijection);
}
