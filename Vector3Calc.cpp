#include "Vector3Calc.h"

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	return {
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][2],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};
}
Vector3 Add(Vector3 a, Vector3 b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }