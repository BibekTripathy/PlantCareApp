#include "stylemanager.hxx"
#include <QApplication>
#include <QFile>
#include <QDebug>

void StyleManager::applyStyle(Theme theme) {
    QString darkStyle = R"(
        /* Global */
        QWidget {
            background-color: #121212;
            color: #E0E0E0;
            font-family: "Segoe UI", "Noto Sans", sans-serif;
            font-size: 14px;
        }

        /* Buttons */
        QPushButton {
            background-color: #1E1E1E;
            color: #FFFFFF;
            border: 1px solid #555555;
            padding: 6px 12px;
            border-radius: 10px;
        }
        QPushButton:hover {
            background-color: #2A2A2A;
        }
        QPushButton:pressed {
            background-color: #3A3A3A;
        }

        /* LineEdit and TextEdit */
        QLineEdit, QTextEdit {
            background-color: #1E1E1E;
            color: #FFFFFF;
            border: 1px solid #555555;
            border-radius: 10px;
            padding: 4px;
        }

        /* Labels */
        QLabel {
            color: #E0E0E0;
            border: 1px solid #555555;
            padding: 2px 6px;
            border-radius: 10px;
        }

        /* Scrollbars */
        QScrollBar:vertical, QScrollBar:horizontal {
            background: transparent;
            width: 12px;
            margin: 0px;
        }
        QScrollBar::handle {
            background: #444;
            border-radius: 10px;
        }
        QScrollBar::handle:hover {
            background: #666;
        }
        QScrollBar::add-line, QScrollBar::sub-line {
            background: none;
        }

        /* ComboBoxes */
        QComboBox {
            background-color: #1E1E1E;
            color: #FFFFFF;
            border: 1px solid #555555;
            padding: 4px;
            border-radius: 10px;
        }
        QComboBox QAbstractItemView {
            background-color: #1E1E1E;
            color: #FFFFFF;
            border: 1px solid #3A3A3A;
            border-radius: 10px;
        }

        /* Menu Bar */
        QMenuBar {
            background-color: #1E1E1E;
            color: #FFFFFF;
            border-bottom: 1px solid #333;
        }
        QMenuBar::item {
            background: transparent;
            padding: 6px 12px;
        }
        QMenuBar::item:selected {
            background: #2A2A2A;
            border-radius: 10px;
        }
        QMenuBar::item:pressed {
            background: #3A3A3A;
        }

        /* Menus */
        QMenu {
            background-color: #1E1E1E;
            color: #FFFFFF;
            border: 1px solid #444;
            padding: 4px;
            border-radius: 10px;
        }
        QMenu::item {
            padding: 6px 12px;
            border-radius: 10px;
        }
        QMenu::item:selected {
            background-color: #2A2A2A;
        }
        QMenu::item:disabled {
            color: #666666;
        }
    )";

    QString lightStyle = R"(
        /* Global */
        QWidget {
            background-color: #F5F5F5;
            color: #2E2E2E;
            font-family: "Segoe UI", "Noto Sans", sans-serif;
            font-size: 14px;
        }

        /* Buttons */
        QPushButton {
            background-color: #E0E0E0;
            color: #2E2E2E;
            border: 1px solid #888888;
            padding: 6px 12px;
            border-radius: 10px;
        }
        QPushButton:hover {
            background-color: #D5D5D5;
        }
        QPushButton:pressed {
            background-color: #C0C0C0;
        }

        /* Inputs */
        QLineEdit, QTextEdit {
            background-color: #FFFFFF;
            color: #2E2E2E;
            border: 1px solid #888888;
            border-radius: 10px;
            padding: 4px;
        }

        /* Labels */
        QLabel {
            color: #2E2E2E;
            border: 1px solid #888888;
            padding: 2px 6px;
            border-radius: 10px;
        }

        /* Scrollbars */
        QScrollBar:vertical, QScrollBar:horizontal {
            background: transparent;
            width: 12px;
            margin: 0px;
        }
        QScrollBar::handle {
            background: #AAAAAA;
            border-radius: 10px;
        }
        QScrollBar::handle:hover {
            background: #888888;
        }
        QScrollBar::add-line, QScrollBar::sub-line {
            background: none;
        }

        /* ComboBoxes */
        QComboBox {
            background-color: #FFFFFF;
            color: #2E2E2E;
            border: 1px solid #888888;
            padding: 4px;
            border-radius: 10px;
        }
        QComboBox QAbstractItemView {
            background-color: #FFFFFF;
            color: #2E2E2E;
            border: 1px solid #CCCCCC;
            border-radius: 10px;
        }

        /* Menu Bar */
        QMenuBar {
            background-color: #E0E0E0;
            color: #2E2E2E;
            border-bottom: 1px solid #B0B0B0;
        }
        QMenuBar::item {
            background: transparent;
            padding: 6px 12px;
        }
        QMenuBar::item:selected {
            background: #D0D0D0;
            border-radius: 10px;
        }
        QMenuBar::item:pressed {
            background: #C0C0C0;
        }

        /* Menus */
        QMenu {
            background-color: #FFFFFF;
            color: #2E2E2E;
            border: 1px solid #CCCCCC;
            padding: 4px;
            border-radius: 10px;
        }
        QMenu::item {
            padding: 6px 12px;
            border-radius: 10px;
        }
        QMenu::item:selected {
            background-color: #EEEEEE;
        }
        QMenu::item:disabled {
            color: #AAAAAA;
        }
    )";

    if (theme == Dark) {
        qApp->setStyleSheet(darkStyle);
        qDebug() << "[StyleManager] Applied Dark theme.";
    } else {
        qApp->setStyleSheet(lightStyle);
        qDebug() << "[StyleManager] Applied Light theme.";
    }
}

