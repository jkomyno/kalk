#include <exception>
#include <QStringList>
#include "view/mainview.h"
#include "view/tabwidget.h"
#include "view/typechoicequestionwidget.h"
#include "view/kalkboardwidget.h"
#include "view/logwidget.h"
#include "kalkviewmanager.h"
#include "settings.h"
#include "../model/kalkmatrixmodel.h"
#include "../model/kalkresultmatrixmodel.h"
#include "../model/resultdestination.h"
#include "lib/linearalgebra/linear_algebra.h"

KalkViewManager::KalkViewManager(TabWidget& tabWidget, LogWidget& logWidget, Settings& settings, QObject* parent) :
    QObject(parent),
    _tabWidget(tabWidget),
    _logWidget(logWidget),
    _typeChoiceQuestionWidget(*_tabWidget.getTypeChoiceQuestionWidget()),
    _kalkBoardWidget(*_tabWidget.getKalkBoardWidget()),
    _settings(settings),
    choicesMap({
                { KalkViewManager::CHOICES::GENERIC_MATRIX, tr("Generic matrix") },
                { KalkViewManager::CHOICES::SQUARE_MATRIX, tr("Square matrix") },
                { KalkViewManager::CHOICES::DIAGONAL_MATRIX, tr("Diagonal matrix") }
               }),
    choicesModel(initStringModelFromMap(choicesMap)),
    boardAMatrix(nullptr),
    boardBMatrix(nullptr)
{
    wireSettings(_settings);
    wireTypeChoiceQuestionWidget();
    wireKalkBoardWidget();
    wireViewManager();
    _settings.parseJSON();
}

KalkViewManager::~KalkViewManager()
{
    delete boardAMatrix;
    delete boardBMatrix;
    delete choicesModel;
}

void KalkViewManager::init()
{
    _typeChoiceQuestionWidget.setChoices(choicesModel);
}

void KalkViewManager::onSettingsSuccess()
{
    _logWidget.onLog("Settings", "Loaded successfully");
    _tabWidget.onSettingsSuccess();
}

void KalkViewManager::handleFirstChoiceDone(int choiceAIndex, int choiceBIndex)
{
    boardAMatrix = newMatrix(choiceAIndex);
    boardBMatrix = newMatrix(choiceBIndex);
    _kalkBoardWidget.init(boardAMatrix,
                          boardBMatrix,
                          _settings.getMinMatrixDimension(),
                          _settings.getMaxMatrixDimension(),
                          _settings.getMinRandomValue(),
                          _settings.getMaxRandomValue(),
                          _settings.getMinTransformValue(),
                          _settings.getMaxTransformValue());
    _logWidget.onLog("First choice", QString("%1, %2").arg(choiceAIndex).arg(choiceBIndex));
}

void KalkViewManager::handleChangeChoiceDone(int choiceAIndex, int choiceBIndex)
{
    _kalkBoardWidget.reinit(newMatrix(choiceAIndex), newMatrix(choiceBIndex));
    _logWidget.onLog("Change choice", QString("%1, %2").arg(choiceAIndex).arg(choiceBIndex));
    _tabWidget.setCurrentIndex(static_cast<int>(TabWidget::TAB_INDEXES::KALK_BOARD));
}

void KalkViewManager::handleChangeDimensionsBoardAClicked(int rows, int columns)
{
    _logWidget.onLog("Board A", QString("Reshape to %1 x %2").arg(rows).arg(columns));
    _kalkBoardWidget.matrixModelA().reshape(rows, columns);
}

void KalkViewManager::handleInfoBoardAClicked()
{
    _logWidget.onLog("Board A", "Show details dialog");
}

void KalkViewManager::handleTransposeBoardAClicked()
{
    _logWidget.onLog("Board A", "Transpose");
    _kalkBoardWidget.matrixModelA().transpose();
}

void KalkViewManager::handleRandomBoardAClicked()
{
    _logWidget.onLog("Board A", "Random");
    _kalkBoardWidget.matrixModelA().random();
}

void KalkViewManager::handleSortBoardAClicked()
{
    _logWidget.onLog("Board A", "Sort");
    _kalkBoardWidget.matrixModelA().sort();
}

void KalkViewManager::handleNegateBoardAClicked()
{
    _logWidget.onLog("Board A", "Negate");
    _kalkBoardWidget.matrixModelA().negate();
}

void KalkViewManager::handleIdentityBoardAClicked()
{
    auto operationName = tr("Identity");
    _logWidget.onLog("Board A", QString("%1").arg(operationName));
    try {
        _kalkBoardWidget.matrixModelA().identity();
    } catch (linear_algebra::exceptions::bad_diagonal_matrix_cast& e) {
        emit onError(operationName, e.what());
    } catch (std::exception& e) {
        emitUnknownException(operationName, e.what());
    }
}

void KalkViewManager::handleIncrementBoardAClicked(int increment)
{
    auto operationName = tr("Increment");
    _logWidget.onLog("Board A", QString("%1 by %2").arg(operationName).arg(increment));
    try {
        _kalkBoardWidget.matrixModelA().increment(increment);
    } catch (std::overflow_error&) {
        emit onError(operationName, tr("An overflow occourred"));
    } catch (std::underflow_error&) {
        emit onError(operationName, tr("An underflow occourred"));
    } catch (std::exception& e) {
        emitUnknownException(operationName, e.what());
    }
}

void KalkViewManager::handleScaleBoardAClicked(int scale)
{
    auto operationName = tr("Scale");
    _logWidget.onLog("Board A", QString("%1 by %2").arg(operationName).arg(scale));
    try {
        _kalkBoardWidget.matrixModelA().scale(scale);
    } catch (std::overflow_error&) {
        emit onError(operationName, tr("An overflow occourred"));
    } catch (std::underflow_error&) {
        emit onError(operationName, tr("An underflow occourred"));
    } catch (std::exception& e) {
        emitUnknownException(operationName, e.what());
    }
}

void KalkViewManager::handleFillBoardAClicked(int fill)
{
    _logWidget.onLog("Board A", QString("Fill with %1").arg(fill));
    _kalkBoardWidget.matrixModelA().fill(fill);
}

void KalkViewManager::handleFillDiagonalBoardAClicked(int fillDiagonal)
{
    auto operationName = tr("Fill diagonal");
    _logWidget.onLog("Board A", QString("%1 with %2").arg(operationName).arg(fillDiagonal));
    try {
        _kalkBoardWidget.matrixModelA().fillDiagonal(fillDiagonal);
    } catch (linear_algebra::exceptions::bad_diagonal_matrix_cast& e) {
        emit onError(operationName, e.what());
    } catch (std::exception& e) {
        emitUnknownException(operationName, e.what());
    }
}

void KalkViewManager::handleChangeDimensionsBoardBClicked(int rows, int columns)
{
    _logWidget.onLog("Board B", QString("Reshape to %1 x %2").arg(rows).arg(columns));
    _kalkBoardWidget.matrixModelB().reshape(rows, columns);
}

void KalkViewManager::handleInfoBoardBClicked()
{
    _logWidget.onLog("Board B", "Show details dialog");
}

void KalkViewManager::handleTransposeBoardBClicked()
{
    _logWidget.onLog("Board B", "Transpose");
    _kalkBoardWidget.matrixModelB().transpose();
}

void KalkViewManager::handleRandomBoardBClicked()
{
    _logWidget.onLog("Board B", "Random");
    _kalkBoardWidget.matrixModelB().random();
}

void KalkViewManager::handleSortBoardBClicked()
{
    _logWidget.onLog("Board B", "Sort");
    _kalkBoardWidget.matrixModelB().sort();
}

void KalkViewManager::handleNegateBoardBClicked()
{
    _logWidget.onLog("Board B", "Negate");
    _kalkBoardWidget.matrixModelB().negate();
}

void KalkViewManager::handleIdentityBoardBClicked()
{
    auto operationName = tr("Identity");
    _logWidget.onLog("Board B", QString("%1").arg(operationName));
    try {
        _kalkBoardWidget.matrixModelB().identity();
    } catch (linear_algebra::exceptions::bad_diagonal_matrix_cast& e) {
        emit onError(operationName, e.what());
    } catch (std::exception& e) {
        emitUnknownException(operationName, e.what());
    }
}

void KalkViewManager::handleIncrementBoardBClicked(int increment)
{
    auto operationName = tr("Increment");
    _logWidget.onLog("Board B", QString("%1 by %2").arg(operationName).arg(increment));
    try {
        _kalkBoardWidget.matrixModelB().increment(increment);
    } catch (std::overflow_error&) {
        emit onError(operationName, tr("An overflow occourred"));
    } catch (std::underflow_error&) {
        emit onError(operationName, tr("An underflow occourred"));
    } catch (std::exception& e) {
        emitUnknownException(operationName, e.what());
    }
}

void KalkViewManager::handleScaleBoardBClicked(int scale)
{
    auto operationName = tr("Scale");
    _logWidget.onLog("Board B", QString("%1 by %2").arg(operationName).arg(scale));
    try {
        _kalkBoardWidget.matrixModelB().scale(scale);
    } catch (std::overflow_error&) {
        emit onError(operationName, tr("An overflow occourred"));
    } catch (std::underflow_error&) {
        emit onError(operationName, tr("An underflow occourred"));
    } catch (std::exception& e) {
        emitUnknownException(operationName, e.what());
    }
}

void KalkViewManager::handleFillBoardBClicked(int fill)
{
    _logWidget.onLog("Board B", QString("Fill with %1").arg(fill));
    _kalkBoardWidget.matrixModelB().fill(fill);
}

void KalkViewManager::handleFillDiagonalBoardBClicked(int fillDiagonal)
{
    auto operationName = tr("Fill diagonal");
    _logWidget.onLog("Board B", QString("%1 with %2").arg(operationName).arg(fillDiagonal));
    try {
        _kalkBoardWidget.matrixModelB().fillDiagonal(fillDiagonal);
    } catch (linear_algebra::exceptions::bad_diagonal_matrix_cast& e) {
        emit onError(operationName, e.what());
    } catch (std::exception& e) {
        emitUnknownException(operationName, e.what());
    }
}

void KalkViewManager::handleAddOperationClicked()
{
    auto operationName = tr("Addition");
    _logWidget.onLog("Operation", "A + B");

    try {
        switch (_kalkBoardWidget.resultDestination()) {
        case RESULT_DESTINATION::TO_A:
            matrixModelA().add(matrixModelB());
            break;
        case RESULT_DESTINATION::TO_B:
            matrixModelB().add(matrixModelA());
            break;
        case RESULT_DESTINATION::TO_WINDOW:
        default:
             matrixModelResult().add(matrixModelA(), matrixModelB());
            _kalkBoardWidget.toggleResultWindow(true);
        }
    } catch (linear_algebra::exceptions::algebric_sum_dimensions& e) {
        // Ideally I'd have to map the library's exception message with a custom I18N'd message
        emit onError(operationName, e.what());
    } catch (std::exception& e) {
        emitUnknownException(operationName, e.what());
    }
}

void KalkViewManager::handleSubtractOperationClicked()
{
    auto operationName = tr("Subtraction");
    _logWidget.onLog("Operation", "A - B");

    try {
        switch (_kalkBoardWidget.resultDestination()) {
        case RESULT_DESTINATION::TO_A:
            matrixModelA().subtract(matrixModelB());
            break;
        case RESULT_DESTINATION::TO_B:
            matrixModelB().subtract(matrixModelA());
            break;
        case RESULT_DESTINATION::TO_WINDOW:
        default:
            matrixModelResult().subtract(matrixModelA(), matrixModelB());
            _kalkBoardWidget.toggleResultWindow(true);
        }
    } catch (linear_algebra::exceptions::algebric_sum_dimensions& e) {
        // Ideally I'd have to map the library's exception message with a custom I18N'd message
        emit onError(operationName, e.what());
    } catch (std::exception& e) {
        emitUnknownException(operationName, e.what());
    }
}

void KalkViewManager::handleMultiplyOperationClicked()
{
    auto operationName = tr("Multiplication");
    _logWidget.onLog("Operation", "A * B");

    try {
        switch (_kalkBoardWidget.resultDestination()) {
        case RESULT_DESTINATION::TO_A:
            matrixModelA().multiply(matrixModelB());
            break;
        case RESULT_DESTINATION::TO_B:
            matrixModelB().multiply(matrixModelA(), false);
            break;
        case RESULT_DESTINATION::TO_WINDOW:
        default:
            matrixModelResult().multiply(matrixModelA(), matrixModelB());
            _kalkBoardWidget.toggleResultWindow(true);
        }
    } catch (linear_algebra::exceptions::multiplication_dimensions& e) {
        // Ideally I'd have to map the library's exception message with a custom I18N'd message
        emit onError(operationName, e.what());
    } catch (std::exception& e) {
        emitUnknownException(operationName, e.what());
    }
}

void KalkViewManager::handleSwapOperationClicked()
{
    auto operationName = tr("Swap");
    _logWidget.onLog("Operation", "Swap A <-> B");

    try {
        matrixModelA().swap(matrixModelB());
    } catch (std::bad_cast& e) {
        // Ideally I'd have to map the library's exception message with a custom I18N'd message
        emit onError(operationName, e.what());
    }
}

void KalkViewManager::wireSettings(Settings& settings)
{
    connect(&settings, SIGNAL(onSuccess()), this, SLOT(onSettingsSuccess()));
    connect(&settings, SIGNAL(onError(QString,QString)), &_logWidget, SLOT(onWarning(QString,QString)));
}

void KalkViewManager::wireViewManager()
{
    connect(this, SIGNAL(onError(QString,QString)), &_kalkBoardWidget, SLOT(showErrorDialog(QString,QString)));
}

void KalkViewManager::wireTypeChoiceQuestionWidget()
{
    connect(&_typeChoiceQuestionWidget, SIGNAL(onFirstChoiceDone(int,int)), this, SLOT(handleFirstChoiceDone(int,int)));
    connect(&_typeChoiceQuestionWidget, SIGNAL(onChangeChoiceDone(int, int)), this, SLOT(handleChangeChoiceDone(int,int)));
}

void KalkViewManager::wireKalkBoardWidget()
{
    connect(&_kalkBoardWidget, SIGNAL(onInit()), &_tabWidget, SLOT(initKalkBoardWidget()));
    wireKalkBoardA();
    wireKalkBoardB();
    wireKalkBoardCommonOperations();
}

void KalkViewManager::wireKalkBoardA()
{
    /* Board A header */
    connect(&_kalkBoardWidget, SIGNAL(onChangeDimensionsBoardAClicked(int,int)), this, SLOT(handleChangeDimensionsBoardAClicked(int,int)));
    connect(&_kalkBoardWidget, SIGNAL(onInfoBoardAClicked()), this, SLOT(handleInfoBoardAClicked()));

    /* Board A transform */
    connect(&_kalkBoardWidget, SIGNAL(onTransposeBoardAClicked()), this, SLOT(handleTransposeBoardAClicked()));
    connect(&_kalkBoardWidget, SIGNAL(onRandomBoardAClicked()), this, SLOT(handleRandomBoardAClicked()));
    connect(&_kalkBoardWidget, SIGNAL(onSortBoardAClicked()), this, SLOT(handleSortBoardAClicked()));
    connect(&_kalkBoardWidget, SIGNAL(onNegateBoardAClicked()), this, SLOT(handleNegateBoardAClicked()));
    connect(&_kalkBoardWidget, SIGNAL(onIdentityBoardAClicked()), this, SLOT(handleIdentityBoardAClicked()));

    connect(&_kalkBoardWidget, SIGNAL(onIncrementBoardAClicked(int)), this, SLOT(handleIncrementBoardAClicked(int)));
    connect(&_kalkBoardWidget, SIGNAL(onScaleBoardAClicked(int)), this, SLOT(handleScaleBoardAClicked(int)));
    connect(&_kalkBoardWidget, SIGNAL(onFillBoardAClicked(int)), this, SLOT(handleFillBoardAClicked(int)));
    connect(&_kalkBoardWidget, SIGNAL(onFillDiagonalBoardAClicked(int)), this, SLOT(handleFillDiagonalBoardAClicked(int)));
}

void KalkViewManager::wireKalkBoardB()
{
    /* Board B header */
    connect(&_kalkBoardWidget, SIGNAL(onChangeDimensionsBoardBClicked(int,int)), this, SLOT(handleChangeDimensionsBoardBClicked(int,int)));
    connect(&_kalkBoardWidget, SIGNAL(onInfoBoardBClicked()), this, SLOT(handleInfoBoardBClicked()));

    /* Board B transform */
    connect(&_kalkBoardWidget, SIGNAL(onTransposeBoardBClicked()), this, SLOT(handleTransposeBoardBClicked()));
    connect(&_kalkBoardWidget, SIGNAL(onRandomBoardBClicked()), this, SLOT(handleRandomBoardBClicked()));
    connect(&_kalkBoardWidget, SIGNAL(onSortBoardBClicked()), this, SLOT(handleSortBoardBClicked()));
    connect(&_kalkBoardWidget, SIGNAL(onNegateBoardBClicked()), this, SLOT(handleNegateBoardBClicked()));
    connect(&_kalkBoardWidget, SIGNAL(onIdentityBoardBClicked()), this, SLOT(handleIdentityBoardBClicked()));

    connect(&_kalkBoardWidget, SIGNAL(onIncrementBoardBClicked(int)), this, SLOT(handleIncrementBoardBClicked(int)));
    connect(&_kalkBoardWidget, SIGNAL(onScaleBoardBClicked(int)), this, SLOT(handleScaleBoardBClicked(int)));
    connect(&_kalkBoardWidget, SIGNAL(onFillBoardBClicked(int)), this, SLOT(handleFillBoardBClicked(int)));
    connect(&_kalkBoardWidget, SIGNAL(onFillDiagonalBoardBClicked(int)), this, SLOT(handleFillDiagonalBoardBClicked(int)));
}

void KalkViewManager::wireKalkBoardCommonOperations()
{
    connect(&_kalkBoardWidget, SIGNAL(onAddOperationClicked()), this, SLOT(handleAddOperationClicked()));
    connect(&_kalkBoardWidget, SIGNAL(onSubtractOperationClicked()), this, SLOT(handleSubtractOperationClicked()));
    connect(&_kalkBoardWidget, SIGNAL(onMultiplyOperationClicked()), this, SLOT(handleMultiplyOperationClicked()));
    connect(&_kalkBoardWidget, SIGNAL(onSwapOperationClicked()), this, SLOT(handleSwapOperationClicked()));
}

KalkMatrixModel& KalkViewManager::matrixModelA() const
{
    return _kalkBoardWidget.matrixModelA();
}

KalkMatrixModel& KalkViewManager::matrixModelB() const
{
    return _kalkBoardWidget.matrixModelB();
}

KalkResultMatrixModel& KalkViewManager::matrixModelResult() const
{
    return _kalkBoardWidget.matrixModelResult();
}

void KalkViewManager::emitUnknownException(const QString& operationName, const QString& message)
{
    emit onError(QString("%1 (%2)").arg(operationName).arg("Unknown"), message);
}

linear_algebra::i_matrix_t* KalkViewManager::newMatrix(int index)
{
    CHOICES keyFromIndex = static_cast<CHOICES>(index);
    auto dimension = _settings.getDefaultSquareDimension();

    switch (keyFromIndex) {
    case CHOICES::SQUARE_MATRIX:
        return new linear_algebra::dense_square_matrix_t(dimension);
    case CHOICES::DIAGONAL_MATRIX:
        return new linear_algebra::dense_diagonal_matrix_t(dimension);
    case CHOICES::GENERIC_MATRIX:
    default:
        auto rows = _settings.getDefaultRowsDimension();
        auto columns = _settings.getDefaultColumnsDimension();
        return new linear_algebra::dense_matrix_t(rows, columns);
    }
}
