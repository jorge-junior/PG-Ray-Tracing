#include <iostream>
#include <vector>
#include "lodepng.cpp"

using namespace std;

int main()
{
    // Create a vector of RGBA pixels
    vector<unsigned char> image(256 * 256 * 4);

    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            int index = (y * 256 + x) * 4;
            image[index + 0] = 0;   // R channel
            image[index + 1] = 0;   // G channel
            image[index + 2] = 255; // B channel
            image[index + 3] = 255; // Alpha channel
        }
    }
    cout << image[0] << endl;

    // Save the image as a PNG file
    unsigned error = lodepng::encode("image.png", image, 256, 256);
    if (error)
    {
        cout << "PNG encoder error: " << lodepng_error_text(error) << endl;
        return 1;
    }

    cout << "Image saved to 'image.png'" << endl;
    return 0;
}
