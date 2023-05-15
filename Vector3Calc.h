#pragma once
#include "Vector3.h"
#include"matrixCalc.h"
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
Vector3 Add(Vector3 a, Vector3 b);