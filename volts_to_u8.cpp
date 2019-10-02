#include <algorithm>
#include <inttypes.h>

// assume 5V max and clamp to [-5,5]

constexpr double datastep = 1.0 / 64000.0;
constexpr double audiostep = 1.0 / 22050.0;

double interpolate(double v0, double t0, double v1, double t1, double t)
{
    float a1 = (t - t0) / (t1 - t0);
    float a0 = 1.0 - a1;

    return a0 * v0 + a1 * v1;
}

int main(int argc, char **argv)
{
    char line[512];

    double t = 0.0;
    double nextaudio = 0.0;
    double oldv = 0.0;
    double oldt = 0.0;

    while(fgets(line, sizeof(line), stdin) == line) {
        if(line[0] != '#') { // Skip comments
            double v;
            sscanf(line, "%lg", &v);

            while(nextaudio < t) {
                double interpolated = interpolate(oldv, oldt, v, t, nextaudio);
                double clamped = std::clamp(interpolated, -5.0, 5.0);
                uint8_t u = (uint8_t)((clamped + 5.0) / 10.0 * 255.999);
                fputc(u, stdout);
                nextaudio += audiostep;
            }

            oldv = v;
            oldt = t;
            t += datastep;
        }
    }
}
