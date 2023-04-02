struct point3
{
    float location[3];
    const float &operator[](int index) const {};
};

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

vec3 operator*(const vec3 &v, float x){};
vec3 operator*(float x, const vec3 &v){};

point3 operator+(const point3 &p, const vec3 &v){};
point3 operator+(const vec3 &v, const point3 &p){};

vec3 operator-(const point3 &p1, const point3 &p2){};