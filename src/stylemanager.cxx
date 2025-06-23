#include "stylemanager.hxx"
#include <QApplication>
#include <QFile>
#include <QDebug>

void StyleManager::applyStyle(Theme theme) {
    QString styleFile = (theme == Dark) ? "./assets/styles/dark.qss"
                                        : "./assets/styles/light.qss";

    QFile file(styleFile);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString stylesheet = file.readAll();
        qApp->setStyleSheet(stylesheet);
        qDebug() << "[StyleManager] Applied" << (theme == Dark ? "Dark" : "Light") << "theme.";
    } else {
        qDebug() << "[StyleManager] Failed to load style file:" << styleFile;
    }
}
