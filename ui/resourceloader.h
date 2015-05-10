#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H
#include <QString>
#include <QPixmap>
#include <QFont>
#include <vector>
#include <QFontDatabase>
#include <QFile>
struct ResourceLoader
{
    static const QString CONFIG_PATH;
    static const QString FONT_PATH;
    static const QString FONT_NAME;
    static const QString STYLE_PATH;
    static  QString STYLE;
    static const std::vector<QString> GHOST_TEXTURES_PATH;
    static const QString PACMAN_TEXTURE_PATH;
    static const QString SCARRIED_GHOST_TEXTURE_PATH;
    static const double GLOBAL_TIMER_TIME;
    static const double AGENT_TIMER_TIME;
    static const int WALL_PEN_WIDTH;
    static const QString SCORE_LIST_PATH;
    static const QString LAYOUTS_PATH;
    static void loadFont();
    static void loadStyle();
    static void load();
};

#endif // RESOURCELOADER_H
