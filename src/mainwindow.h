#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <box2d/box2d.h>
#include "debug-drawer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTimeout();

private:
    void paintEvent(QPaintEvent *) override;

private:
    float m_ppm = 30.f; // Pixels per meter
    b2WorldId m_worldId;
    b2DebugDraw m_debugDrawer;
    int x;
};

#endif // MAINWINDOW_H
