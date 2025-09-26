#include "mainwindow.h"

#include <QPainter>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Qt, QPainter, Box2D v3.1.0");
    resize(800, 600);

    // Create a collider line drawer for debugging
    m_debugDrawer = b2DefaultDebugDraw();
    m_debugDrawer.drawShapes = true;
    m_debugDrawer.DrawSolidPolygonFcn = drawSolidPolygon;
    m_debugDrawer.DrawSolidCircleFcn = drawSolidCircle;

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2) { 0.f, 10.f };
    m_worldId = b2CreateWorld(&worldDef);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = (b2Vec2) { 50.f / m_ppm, 350.f / m_ppm };
    b2BodyId groundBodyId = b2CreateBody(m_worldId, &groundBodyDef);
    b2Polygon groundShape = b2MakeBox(200.f / 2.f / m_ppm, 40.f / 2.f / m_ppm);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2ShapeId groundShapeId = b2CreatePolygonShape(groundBodyId, &groundShapeDef, &groundShape);

    b2BodyDef boxBodyDef = b2DefaultBodyDef();
    boxBodyDef.position = (b2Vec2) { 70.f / m_ppm, 100.f / m_ppm };
    boxBodyDef.type = b2_dynamicBody;
    b2BodyId boxBodyId = b2CreateBody(m_worldId, &boxBodyDef);
    b2Polygon boxShape = b2MakeBox(40.f / 2.f / m_ppm, 40.f / 2.f / m_ppm);
    b2ShapeDef boxShapeDef = b2DefaultShapeDef();
    b2ShapeId boxShapeId = b2CreatePolygonShape(boxBodyId, &boxShapeDef, &boxShape);

    // Timer triggers every 16 ms (~60 FPS)
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimeout);
    timer->start(16);
}

MainWindow::~MainWindow() {}

void MainWindow::onTimeout()
{
    b2World_Step(m_worldId, 0.016, 5);
    update(); // schedule repaint
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Provide QPainter to debug drawer
    m_debugDrawer.context = &painter;

    // Let Box2D call the draw functions
    b2World_Draw(m_worldId, &m_debugDrawer);
}
