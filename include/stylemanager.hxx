#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QString>

class StyleManager {
public:
    enum Theme {
        Light,
        Dark
    };

    static void applyStyle(Theme theme);
};

#endif // STYLEMANAGER_H
