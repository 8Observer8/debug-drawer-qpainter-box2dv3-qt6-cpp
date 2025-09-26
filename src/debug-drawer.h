#include <box2d/box2d.h>
#include <QPainter>

void drawSolidPolygon(b2Transform transform, const b2Vec2* vertices,
    int vertexCount, float radius, b2HexColor color, void* context);
void drawSolidCircle(b2Transform transform, float radius,
    b2HexColor color, void* context);
