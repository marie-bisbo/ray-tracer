#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable
{
public:
	HittableList() {}
	HittableList(std::shared_ptr<Hittable> object) { Add(object); }

	void Clear() { objects.clear(); }
	void Add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const override;

public:
	std::vector<std::shared_ptr<Hittable>> objects;
};

bool HittableList::Hit(const Ray& ray, double tMin, double tMax, HitRecord& hitRecord) const
{
	HitRecord tempHitRecord;
	bool hitAnything = false;
	auto closestSoFar = tMax;

	for (const auto& object : objects)
	{
		if (object->Hit(ray, tMin, closestSoFar, tempHitRecord))
		{
			hitAnything = true;
			closestSoFar = tempHitRecord.t;
			hitRecord = tempHitRecord;
		}
	}

	return hitAnything;
}
