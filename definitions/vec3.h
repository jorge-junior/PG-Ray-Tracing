struct vec3
{
    float direction[3];

    const float &operator[](int index) const {};

    static float dot(const vec3 &v1, const vec3 &v2){};

    static float dot(const point3 &v1, const vec3 &v2){};

    static float dot(const vec3 &v1, const point3 &v2){};

    static float dot(const point3 &v1, const point3 &v2){};

    static vec3 cross(const vec3 &v1, const vec3 &v2){};
};