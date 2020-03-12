#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Hierarchy;
class Inspector;
class RenderWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void DeleteObjects();

public slots:
    void OnNewSceneClicked();
    void OnSaveClicked();
    void OnOpenClicked();
    void OnExitClicked();
    void OnAboutClicked();

private:
    Ui::MainWindow *ui_main_window;

    Hierarchy *hierarchy;

    Inspector *inspector;

    RenderWidget *renderWidget;

};

#endif // MAINWINDOW_H
