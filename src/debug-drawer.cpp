#include "debug-drawer.h"
#include <QColor>

static const float PPM = 50.0f; // or use your m_ppm

void drawSolidPolygon(b2Transform transform, const b2Vec2 *vertices,
                      int vertexCount, float /*radius*/, b2HexColor color, void *context)
{
    QPainter *painter = static_cast<QPainter*>(context);
    if (!painter) return;

    QPolygonF polygon;
    for (int i = 0; i < vertexCount; ++i) {
        // Apply transform
        b2Vec2 v = b2TransformPoint(transform, vertices[i]);
        // Convert to pixels
        polygon << QPointF(v.x * PPM, v.y * PPM);
    }

    QColor qcolor((color >> 16) & 0xFF,
                  (color >> 8) & 0xFF,
                  color & 0xFF);

    painter->setPen(Qt::black);
    painter->setBrush(qcolor);
    painter->drawPolygon(polygon);
}

void drawSolidCircle(b2Transform transform, float radius,
                     b2HexColor color, void *context)
{
    QPainter *painter = static_cast<QPainter*>(context);
    if (!painter) return;

    b2Vec2 center = transform.p;

    QColor qcolor((color >> 16) & 0xFF,
                  (color >> 8) & 0xFF,
                  color & 0xFF);

    painter->setPen(Qt::black);
    painter->setBrush(qcolor);
    painter->drawEllipse(QPointF(center.x * PPM, center.y * PPM),
                         radius * PPM, radius * PPM);
}
