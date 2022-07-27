#include "cub3d.h"

void rot_vec(double *v ,double a, double * res)
{
    double tmp[2];
    
    tmp[0] = v[0];
    tmp[1] = v[1];
    res[0] = cos(a) * tmp[0] - sin(a) * tmp[1];
    res[1] = sin(a) * tmp[0] + cos(a) * tmp[1];
}

double vec_cross(double *v1, double *v2)
{
    return (v1[0] * v2[1] - v1[1] * v2[0]);
}

void sub_vec(double *v1, double *v2, double *res)
{    
    res[0] = (v2[0] - v1[0]);
    res[1] = (v2[1] - v1[1]);
}

void add_vec(double *v1, double *v2,double *res)
{
    res[0] = (v2[0] + v1[0]);
    res[1] = (v2[1] + v1[1]);
}


void scale_vec_by(double *v, double c, double *res)
{
    res[0] = v[0] * c;
    res[1] = v[1] * c;
}

double dot(double *v1, double *v2)
{
    return (v1[0]*v2[0] + v1[1]*v2[1]);
}

double get_ord_angle(double *v1)
{
    double  unit_vector_1[2]; 
    double  unit_vector_2[2]; 
    int     sign;
    double  v2[2];

    v2[0] = 0;
    v2[1] = 1;
    if (hypot(v1[0],v1[1]) && hypot(v2[0],v2[1]))
    {
        scale_vec_by(v1, 1 / hypot(v1[0],v1[1]), unit_vector_1);
        scale_vec_by(v2, 1 / hypot(v2[0],v2[1]), unit_vector_2);
        if (vec_cross(v1, v2) < 0)
            return (-1 *  acos(dot(unit_vector_1, unit_vector_2)));
        return (acos(dot(unit_vector_1, unit_vector_2)));
        
    }
    return (0);

}

double get_abs_angle(double *v1)
{
    double  unit_vector_1[2]; 
    double  unit_vector_2[2]; 
    int     sign;
    double  v2[2];

    v2[0] = 1;
    v2[1] = 0;
    if (hypot(v1[0],v1[1]) && hypot(v2[0],v2[1]))
    {
        scale_vec_by(v1, 1 / hypot(v1[0],v1[1]), unit_vector_1);
        scale_vec_by(v2, 1 / hypot(v2[0],v2[1]), unit_vector_2);
        if (vec_cross(v1, v2) < 0)
            return (-1 *  acos(dot(unit_vector_1, unit_vector_2)));
        return (acos(dot(unit_vector_1, unit_vector_2)));
        
    }
    return (0);
}

double get_angle(double *v1, double *v2)
{
    double  unit_vector_1[2]; 
    double  unit_vector_2[2]; 
    int     sign;

    if (hypot(v1[0],v1[1]) && hypot(v2[0],v2[1]))
    {
        scale_vec_by(v1, 1 / hypot(v1[0],v1[1]), unit_vector_1);
        scale_vec_by(v2, 1 / hypot(v2[0],v2[1]), unit_vector_2);
        if (vec_cross(v1, v2) < 0)
            return (-1 *  acos(dot(unit_vector_1, unit_vector_2)));
        return (acos(dot(unit_vector_1, unit_vector_2)));
        
    }
    return (0);
}

void scale_vec_to(double *v, double c, double *res)
{
    double x_unit[2];
    double tmp[2];

    x_unit[0] = 1;
    x_unit[1] = 0;
    tmp[0] = v[0];
    tmp[1] = v[1];
    res[0] = c * cos(get_angle(x_unit, tmp));
    res[1] = c * sin(get_angle(x_unit, tmp));
}






