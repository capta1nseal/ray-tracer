#include "frame.hpp"


#include <vector>
#include <ostream>
#include <string>
#include <sstream>
#include <cmath>

#include "raymath/vec3.hpp"
#include "raymath/vec3functions.hpp"


Frame::Frame(unsigned int initWidth, unsigned int initHeight)
    : width(initWidth), height(initHeight)
{
    if (width == 0) width = 1;
    if (height == 0) height = 1;

    accessCountBuffer.resize(width * height, 0);
    frame.resize(width * height, Vec3<double>(0.0, 0.0, 0.0));
}

void Frame::add(unsigned int x, unsigned int y, const Vec3<double>& newValue)
{
    if (x > width - 1 or y > height - 1) return;

    accessCountBuffer[y * width + x]++;
    frame[y * width + x] += newValue;
}

Vec3<double> Frame::at(unsigned int x, unsigned int y) const
{
    if (x > width - 1 or y > height - 1) return {0.0, 0.0, 0.0};
    return frame[y * width + x] * 1.0 / static_cast<double>(accessCountBuffer[y * width + x]);
}

std::string asString(int number)
{
    std::stringstream stringstream;
    stringstream << number;
    return stringstream.str();
}

char valueToChar(double value)
{
    std::vector<double> values{0.0, 0.0751, 0.0829, 0.0848, 0.1227, 0.1403, 0.1559, 0.185, 0.2183, 0.2417, 0.2571, 0.2852, 0.2902, 0.2919, 0.3099, 0.3192, 0.3232, 0.3294, 0.3384, 0.3609, 0.3619, 0.3667, 0.3737, 0.3747, 0.3838, 0.3921, 0.396, 0.3984, 0.3993, 0.4075, 0.4091, 0.4101, 0.42, 0.423, 0.4247, 0.4274, 0.4293, 0.4328, 0.4382, 0.4385, 0.442, 0.4473, 0.4477, 0.4503, 0.4562, 0.458, 0.461, 0.4638, 0.4667, 0.4686, 0.4693, 0.4703, 0.4833, 0.4881, 0.4944, 0.4953, 0.4992, 0.5509, 0.5567, 0.5569, 0.5591, 0.5602, 0.5602, 0.565, 0.5776, 0.5777, 0.5818, 0.587, 0.5972, 0.5999, 0.6043, 0.6049, 0.6093, 0.6099, 0.6465, 0.6561, 0.6595, 0.6631, 0.6714, 0.6759, 0.6809, 0.6816, 0.6925, 0.7039, 0.7086, 0.7235, 0.7302, 0.7332, 0.7602, 0.7834, 0.8037, 0.9999};

    unsigned int nearestIndex = 0;
    double nearestOpacityDifference = 2.0;

    for (int i = values.size() - 1; i > -1; i--)
    {
        double difference = std::abs(value - values[i]);
        if (difference < nearestOpacityDifference)
        {
            nearestOpacityDifference = difference;
            nearestIndex = i;
        }
    }

    return " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@"[nearestIndex];
}

std::ostream& operator<<(std::ostream& os, const Frame& frame)
{
    unsigned int width = frame.getWidth();
    unsigned int height = frame.getHeight();

    double gamma = 2.5;

    std::string boldCode = "\033[1m";
    std::string foreGroundCode = "\033[38;2;0;0;0m";
    std::string backGroundCode = "\033[48;2;0;0;0m";
    std::string resetCode = "\033[0m";

    std::string output = "";

    // 8-bit RGB colour representation.
    std::string red8, green8, blue8;

    double brightness;
    double charFactor;

    Vec3<double> accumulatedColor;

    for (int y = height - 1; y > -1; y--)
    {
        for (int x = 0; x < width; x++)
        {
            accumulatedColor = frame.at(x, y);

            brightness = std::clamp(mean(accumulatedColor), 0.0, 1.0);
            charFactor = std::pow(brightness, 1.0 / gamma);

            red8 = asString(std::min(static_cast<int>(accumulatedColor.x * 255), 255));
            green8 = asString(std::min(static_cast<int>(accumulatedColor.y * 255), 255));
            blue8 = asString(std::min(static_cast<int>(accumulatedColor.z * 255), 255));

            // TODO implement some drawing method taking advantage of coloured characters over the background colour.
            // foreGroundCode = "\033[38;2;" + red8 + ";" + green8 + ";" + blue8 + "m";
            backGroundCode = "\033[48;2;" + red8 + ";" + green8 + ";" + blue8 + "m";

            output += backGroundCode + " ";
        }
        output += resetCode + "\n" + boldCode + backGroundCode;
    }

    output += resetCode;

    os << output;

    return os;
}
