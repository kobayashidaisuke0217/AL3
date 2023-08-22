#pragma once
#include<Charactor/BaseCharactor.h>
class Enemy:public BaseCharactor {
public:
	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(const ViewProjection& viewProjection) override;
};
