#include <QString>
#include <QDir>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardPaths>
#include "settings.h"

Settings::Settings(const QString& filename, QObject* parent) :
    QObject(parent),
    filename_(filename)
{}

void Settings::parseJSON()
{
    QString rawJSON = readJSONFile();
    if (rawJSON.isEmpty()) return;

    QJsonObject jsonObject;
    QJsonParseError jsonError;
    std::tie(jsonObject, jsonError) = getJSONObject(rawJSON);
    if (jsonError.error != QJsonParseError::NoError) {
        emitError("Couldn't parse JSON file", "");
        return;
    }

    minMatrixDimension = getValueFromJSON(jsonObject, "minMatrixDimension");
    maxMatrixDimension = getValueFromJSON(jsonObject, "maxMatrixDimension");
    defaultRowsDimension = getValueFromJSON(jsonObject, "defaultRowsDimension");
    defaultColumnsDimension = getValueFromJSON(jsonObject, "defaultColumnsDimension");
    defaultSquareDimension = getValueFromJSON(jsonObject, "defaultSquareDimension");

    std::tie(minRandomValue, maxRandomValue) = getMinMaxValueFromJSON(jsonObject, "random");
    std::tie(minTransformValue, maxTransformValue) = getMinMaxValueFromJSON(jsonObject, "transform");

    emit onSuccess();
}

Settings::value_type Settings::getValueFromJSON(const QJsonObject& obj, const QString& option)
{
    return obj[option].toInt();
}

Settings::MinMaxTuple Settings::getMinMaxValueFromJSON(const QJsonObject& obj, const QString& option)
{
   auto nestedJSON = obj[option].toObject();
   auto min = getValueFromJSON(nestedJSON, "min");
   auto max = getValueFromJSON(nestedJSON, "max");
   return std::make_tuple(min, max);
}

QString Settings::readJSONFile()
{
    auto defaultSettings = readJSONFromInternalResource();
    QDir configDir = openConfigDir();
    auto path = configDir.filePath(filename_);
    QFile stdFile(path);
    if (stdFile.exists()) {
        if (!stdFile.open(QFile::ReadOnly | QFile::Text)) {
            emitError(tr("Couldn't open"), path);
            return defaultSettings;
        }
        QString settings = stdFile.readAll();
        stdFile.close();
        return settings;
    } else {
        writeDefaultSettings(stdFile, defaultSettings);
        return defaultSettings;
    }
}

QString Settings::readJSONFromInternalResource()
{
    QDir resourceDir(":/json");
    if (!resourceDir.exists()) {
        emitError(tr("Internal resource path is missing:"), resourceDir.canonicalPath());
        return "";
    }

    auto path = resourceDir.filePath(filename_);
    QFile resourceFile(path);
    if (!resourceFile.open(QFile::ReadOnly | QFile::Text)) {
        emitError(tr("Couldn't open internal resource"), path);
        return "";
    }

    return resourceFile.readAll();
}

QDir Settings::openConfigDir()
{
    QDir configDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    if (configDir.dirName().isEmpty()) {
        emitError(tr("Couldn't open configuration directory"), configDir.dirName());
    } else {
        if (!configDir.exists()) {
            QDir dir;
            dir.mkpath(configDir.path());
        }
    }
    return configDir;
}

void Settings::writeDefaultSettings(QFile& stdConfigFile, const QString& settings)
{
    auto length = settings.length();
    auto stdFileName = stdConfigFile.fileName();
    if (!stdConfigFile.open(QFile::WriteOnly | QFile::Text)) {
        emitError(tr("Couldn't open file to write:"), stdFileName);
    }
    auto bytesWritten = stdConfigFile.write(settings.toLocal8Bit().constData(), length);
    if (bytesWritten != length) {
        emitError(tr("Couldn't write settings to file:"), stdFileName);
        stdConfigFile.remove();
    }
    stdConfigFile.close();
}

void Settings::emitError(const QString& s1, const QString& s2)
{
     emit onError(tr("Settings"), QString("%1 %2").arg(s1).arg(s2));
}

Settings::JSONObjectError Settings::getJSONObject(const QString& rawJSON)
{
    QJsonParseError jsonError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(rawJSON.toUtf8(), &jsonError);
    QJsonObject jsonObject = jsonDocument.object();

    return std::make_tuple(jsonObject, jsonError);
}
