#include "BaseCharactor.h"

void BaseCharactor::Initialize(const std::vector<Model*>& models,const Vector3& pos ) {
	models_ = models;
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
}

void BaseCharactor::Update() { worldTransform_.UpdateMatrix(); }

void BaseCharactor::Draw(const ViewProjection& view) {
	for (Model* model : models_) {
		model->Draw(worldTransform_, view);
	}
}
