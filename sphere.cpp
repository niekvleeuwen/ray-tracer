#include "sphere.h"

Sphere::Sphere(Vec _center, double _radius, material *_mat){
    center = _center;
    radius = _radius;
    mat = _mat;
}

// Calculate the distance between a sphere and a ray between given t min and t max
bool Sphere::hit(const Ray& ray, double t_min, double t_max, hit_record& rec) const {
     /*
        Calculate the discrimant of the following equation using the ABC formula
        dot((P-C),(P-C)) = r^2
        dot((p(t) - C), (p(t) - C)) = r^2
        dot((A + t * B - C), (A + t * B - C)) = r^2
        t^2 * dot(B,B) + 2t * dot(B, A - C) + dot(A - C, A - C) - R^2 = 0
    */
    Vec origin_minus_center = ray.origin - center;
    double a = dot(ray.getDirection(), ray.getDirection());
    double b = dot(origin_minus_center, ray.getDirection());
    double c = dot(origin_minus_center, origin_minus_center) - radius*radius;
    double discriminant = b*b - a*c;
        if(discriminant > 0){
        double d = (-b - sqrt(discriminant))/a;
        if (d < t_max && d > t_min) {
            rec.t = d;
            rec.p = ray.point(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat;
            return true;
        }
        d = (-b + sqrt(discriminant)) / a;
        if (d < t_max && d > t_min) {
            rec.t = d;
            rec.p = ray.point(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat;
            return true;
        }
    }
    return false;
}
