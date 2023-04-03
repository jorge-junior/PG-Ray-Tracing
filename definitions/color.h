struct Color
{
    float r;
    float g;
    float b;
    Color();
    Color(float r, float g, float b);

    bool operator=(const Color &c);
    bool operator!=(const Color &c);
};