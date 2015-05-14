#include "resourceloader.h"
const QString ResourceLoader:: CONFIG_PATH = "config.cfg";
const QString ResourceLoader:: FONT_PATH = ":/fonts/Munro.ttf";
const QString ResourceLoader:: FONT_NAME = "Munro";
const QString ResourceLoader:: STYLE_PATH = ":/stylesheets/stylesheets/button.qss";
const QString ResourceLoader::PACMAN_TEXTURE_PATH = ":/textures/textures/pacman-sprite.png";
const double ResourceLoader::GLOBAL_TIMER_TIME = 50;
const double ResourceLoader::AGENT_TIMER_TIME = 5;
const int ResourceLoader::WALL_PEN_WIDTH = 26;
const QString ResourceLoader::SCARRIED_GHOST_TEXTURE_PATH = ":/textures/textures/scarried.png";
const QString ResourceLoader::SCORE_LIST_PATH = "score.lst";
const QString ResourceLoader::LAYOUTS_PATH = "layouts";
QString ResourceLoader::STYLE;

const std::vector<QString> ResourceLoader::GHOST_TEXTURES_PATH =
    { ":/textures/textures/1",
      ":/textures/textures/2",
      ":/textures/textures/3",
      ":/textures/textures/4"};

 void ResourceLoader::loadFont()
 {
     QFontDatabase::addApplicationFont(FONT_PATH);
 }

 void ResourceLoader::loadStyle()
 {
     QFile style(STYLE_PATH); //move to resouce loader
     style.open(QFile::ReadOnly);
     STYLE = QLatin1String(style.readAll());
 }

 void ResourceLoader::load()
 {
     loadFont();
     loadStyle();
 }
