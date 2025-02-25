
#include "demo/Demos.h"

void colors_draw(Painter &painter, Rectangle screen, double time)
{
    double hue = (int)(time * 80) % 360;

    for (int x = 0; x < screen.width(); x++)
    {
        for (int y = 0; y < screen.height(); y++)
        {
            Color color = HSV(hue, (y / (float)screen.height()), 1);
            painter.plot_pixel(screen.position() + Vec2i(x, y), color);
        }
    }
}
