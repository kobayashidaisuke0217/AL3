#pragma once
#include "Vector3.h"
#include"matrixCalc.h"
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);
Vector3 Add(Vector3 a, Vector3 b);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);
Vector3 Multiply(float scalar, const Vector3& v);
float Dot(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
Vector3 Normalise(const Vector3& v);