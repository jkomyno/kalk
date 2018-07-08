#ifndef KALKVIEWMANAGER_H
#define KALKVIEWMANAGER_H

#include <QObject>
#include <QStringListModel>
#include <map>
#include "lib/linearalgebra/linear_algebra.fwd.h"

class TabWidget;
class LogWidget;
class TypeChoiceQuestionWidget;
class KalkBoardWidget;
class QStringList;
class QStringListModel;
class KalkMatrixModel;
class KalkResultMatrixModel;
class Settings;

class KalkViewManager final : public QObject
{
    Q_OBJECT
public:
    explicit KalkViewManager(TabWidget& tabWidget, LogWidget& logWidget, Settings& settings, QObject *parent = nullptr);
    ~KalkViewManager();
    void init();

    enum CHOICES {
        GENERIC_MATRIX = 0,
        SQUARE_MATRIX,
        DIAGONAL_MATRIX,
        VECTOR
    };

signals:
    void onError(const QString& title, const QString& error);

public slots:
    void onSettingsSuccess();

    void handleFirstChoiceDone(int choiceAIndex, int choiceBIndex);
    void handleChangeChoiceDone(int choiceAIndex, int choiceBIndex);

    /* Board A header */
    void handleChangeDimensionsBoardAClicked(int rows, int columns);
    void handleInfoBoardAClicked();

     /* Board A transform */
    void handleTransposeBoardAClicked();
    void handleRandomBoardAClicked();
    void handleSortBoardAClicked();
    void handleNegateBoardAClicked();
    void handleIdentityBoardAClicked();

    void handleIncrementBoardAClicked(int increment);
    void handleScaleBoardAClicked(int scale);
    void handleFillBoardAClicked(int fill);
    void handleFillDiagonalBoardAClicked(int fillDiagonal);

    /* Board A header */
    void handleChangeDimensionsBoardBClicked(int rows, int columns);
    void handleInfoBoardBClicked();

     /* Board A transform */
    void handleTransposeBoardBClicked();
    void handleRandomBoardBClicked();
    void handleSortBoardBClicked();
    void handleNegateBoardBClicked();
    void handleIdentityBoardBClicked();

    void handleIncrementBoardBClicked(int increment);
    void handleScaleBoardBClicked(int scale);
    void handleFillBoardBClicked(int fill);
    void handleFillDiagonalBoardBClicked(int fillDiagonal);

    /* Common operations */
    void handleAddOperationClicked();
    void handleSubtractOperationClicked();
    void handleMultiplyOperationClicked();
    void handleSwapOperationClicked();

private:
    TabWidget& _tabWidget;
    LogWidget& _logWidget;
    TypeChoiceQuestionWidget& _typeChoiceQuestionWidget;
    KalkBoardWidget& _kalkBoardWidget;
    Settings& _settings;

    std::map<CHOICES, QString> choicesMap;
    QStringListModel* choicesModel;

    linear_algebra::i_matrix_t* boardAMatrix;
    linear_algebra::i_matrix_t* boardBMatrix;

    void wireSettings(Settings& settings);
    void wireViewManager();
    void wireTypeChoiceQuestionWidget();
    void wireKalkBoardWidget();
    void wireKalkBoardA();
    void wireKalkBoardB();
    void wireKalkBoardCommonOperations();

    KalkMatrixModel& matrixModelA() const;
    KalkMatrixModel& matrixModelB() const;
    KalkResultMatrixModel& matrixModelResult() const;

    void emitUnknownException(const QString& operationName, const QString& message);

    template <typename T>
    static QStringListModel* initStringModelFromMap(const std::map<T, QString>& stringMap) {
        QStringList stringList;
        stringList.reserve(static_cast<int>(stringMap.size()));
        for (auto item : stringMap) {
            stringList.push_back(item.second);
        }
        return new QStringListModel(stringList);
    }

    linear_algebra::i_matrix_t* newMatrix(int index);
};

#endif // KALKVIEWMANAGER_H
