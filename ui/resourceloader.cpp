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
 const QString ResourceLoader::START_SOUND_PATH = "qrc:/sounds/sound/pacman_beginning.wav";
 const QString ResourceLoader::EAT_FOOD_SOUND_PATH = "qrc:/sounds/sound/pacman_chomp.waw";
 const QString ResourceLoader::EAT_GHOST_SOUND_PATH = "qrc:/sounds/sound/pacman_eatghost.wav";
 const QString ResourceLoader::WIN_SOUND_PATH = "qrc:/sounds/sound/pacman_intermission.wav";
 const QString ResourceLoader::LOSE_SOUND_PATH = "qrc:/sounds/sound/pacman_death.wav";
 const QString ResourceLoader::EAT_CAPS_SOUND_PATH= "qrc:/sounds/sound/pacman_eatfruit.wav";
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
