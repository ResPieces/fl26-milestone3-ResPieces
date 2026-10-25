#include "aiws/gui/main_window.hpp"

#include <QApplication>
#include <QMessageBox>
#include <QDebug>

void confirm_exit(QWidget *parent)
{
    const auto result = QMessageBox::question(
        parent,
        "Exit",
        "Are you sure you want to exit?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No);

    if (result == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    aiws::gui::MainWindow window;
    window.set_exit_callback(&confirm_exit);
    window.show();

    // qDebug() << "Window size:" << window.size();
    // qDebug() << "Window minimum size:" << window.minimumSize();
    // qDebug() << "Window minimum size hint:" << window.minimumSizeHint();

    return app.exec();
}