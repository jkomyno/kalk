#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <tuple>

class QString;
class QFile;
class QDir;
class QJsonObject;
struct QJsonParseError;

class Settings final : public QObject
{
    Q_OBJECT
    using JSONObjectError = std::tuple<QJsonObject, QJsonParseError>;

public:
    using value_type = int;
    using MinMaxTuple = std::tuple<value_type, value_type>;

    explicit Settings(const QString& filename, QObject *parent = nullptr);
    explicit Settings(const Settings& other) = delete;
    Settings& operator=(const Settings& other) = delete;

    void parseJSON();

    value_type getMinMatrixDimension() const { return minMatrixDimension; }
    value_type getMaxMatrixDimension() const { return maxMatrixDimension; }
    value_type getDefaultRowsDimension() const { return defaultRowsDimension; }
    value_type getDefaultColumnsDimension() const { return defaultColumnsDimension; }
    value_type getDefaultSquareDimension() const { return defaultSquareDimension; }
    value_type getMinRandomValue() const { return minRandomValue; }
    value_type getMaxRandomValue() const { return maxRandomValue; }
    value_type getMinTransformValue() const { return minTransformValue; }
    value_type getMaxTransformValue() const { return maxTransformValue; }

signals:
    void onSuccess();
    void onError(const QString& title, const QString& message);

private:
    QString filename_;
    value_type minMatrixDimension;
    value_type maxMatrixDimension;
    value_type defaultRowsDimension;
    value_type defaultColumnsDimension;
    value_type defaultSquareDimension;
    value_type minRandomValue;
    value_type maxRandomValue;
    value_type minTransformValue;
    value_type maxTransformValue;

    value_type getValueFromJSON(const QJsonObject& obj, const QString& option);
    MinMaxTuple getMinMaxValueFromJSON(const QJsonObject& obj, const QString& option);
    QString readJSONFile();
    QString readJSONFromInternalResource();
    QDir openConfigDir();
    void writeDefaultSettings(QFile& stdConfigFile, const QString& settings);
    void emitError(const QString& s1, const QString& s2);

    static JSONObjectError getJSONObject(const QString& rawJSON);
};

#endif // SETTINGS_H
