// madoodia@gmail.com
// (C) 2019
// All rights reserved.
// ------------------

#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "material.h"

class Sphere : public Hitable
{
public:
	vec3 center;
	float radius;
	Material* material;
public:
	Sphere() {}
	Sphere(vec3 cen, float r, Material* mat) : center(cen), radius(r), material(mat) {}
	virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const;
};

bool Sphere::hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const
{
	vec3 oc = ray.origin() - center;
	float a = dot(ray.direction(), ray.direction());
	float b = dot(oc, ray.direction());
	float c = dot(oc, oc) - radius * radius;
	float discreminant = b * b - a * c;
	if(discreminant > 0.0)
	{
		float temp = (-b - sqrt(b * b - a * c)) / a;
		if(temp <tMax && temp > tMin)
		{
			record.t = temp;
			record.p = ray.pFunction(record.t);
			record.normal = (record.p - center) / radius;
			record.matPtr = material;
			return true;
		}
		temp = (-b + sqrt(b * b - a * c)) / a;
		if(temp <tMax && temp > tMin)
		{
			record.t = temp;
			record.p = ray.pFunction(record.t);
			record.normal = (record.p - center) / radius;
			record.matPtr = material;
			return true;
		}
	}
	return false;
}

#endif // SPHERE_H