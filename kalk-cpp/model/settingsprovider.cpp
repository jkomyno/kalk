#include <QString>
#include "settings.h"
#include "settingsprovider.h"

static QString SETTINGS_FILE = "settings.json";
std::unique_ptr<Settings> SettingsProvider::instanceSettings = nullptr;

/**
 * \brief SettingsProvider::getSettings returns Settings as a Singleton class
 */
Settings& SettingsProvider::getSettings()
{
    if (instanceSettings == nullptr) {
        instanceSettings = std::unique_ptr<Settings>(new Settings(SETTINGS_FILE));
    }

    return *instanceSettings;
}
