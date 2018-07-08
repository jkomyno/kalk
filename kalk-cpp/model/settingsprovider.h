#ifndef SETTINGSPROVIDER_H
#define SETTINGSPROVIDER_H

#include <memory>

class Settings;

class SettingsProvider final
{
public:
    SettingsProvider() = default;
    explicit SettingsProvider(const SettingsProvider& other) = delete;
    SettingsProvider& operator=(const SettingsProvider& other) = delete;

    static Settings& getSettings();

private:
    // since this pointer is static, I have no control over it,
    // thus I must use a smart pointer in order to avoid memory leaks
    static std::unique_ptr<Settings> instanceSettings;
};

#endif // SETTINGSPROVIDER_H
