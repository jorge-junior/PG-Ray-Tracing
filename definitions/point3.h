struct point3
{
    float location[3];
    const float &operator[](int index) const {};
};