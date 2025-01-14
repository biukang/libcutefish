#include "wallpaper.h"

Wallpaper::Wallpaper(QObject *parent)
    : QObject(parent)
    , m_interface("org.cutefish.Settings",
                  "/Theme", "org.cutefish.Theme",
                  QDBusConnection::sessionBus(), this)
{
    if (m_interface.isValid()) {
        connect(&m_interface, SIGNAL(wallpaperChanged(QString)), this, SLOT(onPathChanged(QString)));
        connect(&m_interface, SIGNAL(darkModeDimsWallpaerChanged()), this, SIGNAL(dimsWallpaperChanged()));
    }
}

QString Wallpaper::path() const
{
    return m_interface.property("wallpaper").toString();
}

bool Wallpaper::dimsWallpaper() const
{
    return m_interface.property("darkModeDimsWallpaer").toBool();
}

void Wallpaper::onPathChanged(QString path)
{
    Q_UNUSED(path);

    emit pathChanged();
}
