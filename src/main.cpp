#include "aiws/gui/main_window.hpp"

#include <QApplication>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    aiws::gui::MainWindow window;
    window.show();

    // qDebug() << "Window size:" << window.size();
    // qDebug() << "Window minimum size:" << window.minimumSize();
    // qDebug() << "Window minimum size hint:" << window.minimumSizeHint();

    return app.exec();
}