#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringListModel>

#include "controller.h"
#include "datahandlertest.h"
#include "tablemodel.h"
#include "chartmodel.h"

//int main(int argc, char *argv[]) // original
//{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    Controller controller;
//    engine.rootContext()->setContextProperty("controller",&controller);
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

//    return app.exec();
//}

static QObject *registerChartModel(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    ChartModel *model = new ChartModel();
    return model;
}

int main(int argc, char *argv[])
{
    // TESTS
    DataHandlerTest tester;
    tester.test_all();
    tester.test_tags();
    // -----
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    // For chartview
    qmlRegisterSingletonType<ChartModel>("qt.chart", 1, 0, "ChartModel", registerChartModel);

    QQmlApplicationEngine engine;

    // Tableview model
    TableModel tbmodel;
    engine.rootContext()->setContextProperty("tablemodel",&tbmodel);
    //

    // Combobox 2
    QStringListModel racesStrList;
    engine.rootContext()->setContextProperty("rctagmodel",&racesStrList);

    // Controller
    Controller controller(&tbmodel,&racesStrList);
    engine.rootContext()->setContextProperty("controller",&controller);
    //

    // Combobox year model
    auto years = controller.getEveryYear();
    QStringList yearList;
    for(auto year : years)
    {
        yearList.append(year);
    }
    engine.rootContext()->setContextProperty("yearsModel", QVariant::fromValue(yearList));
    //


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
