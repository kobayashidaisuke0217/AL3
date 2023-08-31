#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <Model.h>
#include <vector>

enum ModelParts { kModelBody, kModelHead, kModelLarm, kModelRarm, kModelHammer };

class BaseCharactor {
public:
	virtual void Initialize(const std::vector<Model*>& models, const Vector3& pos);

	virtual void Update();

	virtual void Draw(const ViewProjection& view);

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

protected:
	std::vector<Model*> models_;
	WorldTransform worldTransform_;
};
