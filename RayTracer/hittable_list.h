#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H
#include <vector>
#include "common.h"
#include "hittable.h"
using std::shared_ptr;
using std::make_shared;

class hittable_list :public hittable {
	public:
		std::vector<shared_ptr<hittable>> objects;
		hittable_list(){}
        hittable_list(shared_ptr<hittable_list> object);

        void clear();
        void add(shared_ptr<hittable> object);

		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double time0, double time1, aabb& output)const override;
};
#endif // !HITTABLE_LIST_H