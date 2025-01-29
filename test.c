#include <math.h>
#include <stdio.h>

void rotate_xyz(int *x, int *y, int *z, double angle_x, double angle_y, double angle_z)
{
    if (!x || !y || !z)
        return;

    int prev_x = *x;
    int prev_y = *y;
    int prev_z = *z;
    *y = prev_y * cos(angle_x) - prev_z * sin(angle_x);
    *z = prev_y * sin(angle_x) + prev_z * cos(angle_x);

    prev_y = *y;
    prev_z = *z;
    *x = prev_x * cos(angle_y) + prev_z * sin(angle_y);
    *z = -prev_x * sin(angle_y) + prev_z * cos(angle_y);
    prev_x = *x;
    prev_z = *z;
    *x = prev_x * cos(angle_z) - prev_y * sin(angle_z);
    *y = prev_x * sin(angle_z) + prev_y * cos(angle_z);
}

void isometric(int *x, int *y, int z)
{
    if (!x || !y)
        return;

    int prev_x = *x;
    int prev_y = *y;

    *x = (prev_x - prev_y) * cos(0.523599);
    *y = ((prev_x + prev_y) * sin(0.523599) - z);
}

int main()
{
    int x = 10, y = 10, z = 5;
    double angle_x = 0.5;
    double angle_y = 0.3;
    double angle_z = 0.2;

    printf("Before Rotation: x = %d, y = %d, z = %d\n", x, y, z);

    rotate_xyz(&x, &y, &z, angle_x, angle_y, angle_z);
    isometric(&x, &y, z);

    printf("After Rotation & Isometric: x = %d, y = %d\n", x, y);

    return 0;
}

