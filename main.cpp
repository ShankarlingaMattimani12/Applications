#include "AppModel.h"
#include "Wrapper.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    AppModel *model = new AppModel();

    // Fill model: 5 categories x 25 apps each
    // const QStringList categories = {"Productivity", "Setup", "Support", "Tools", "Favourite"};
    // for (const QString &cat : categories) {
    //     for (int i = 1; i <= 25; ++i) {
    //         AppItem it;
    //         it.name = QString("%1 App %2").arg(cat).arg(i);
    //         it.category = cat;
    //         it.plugin = QString("%1 Plugin %2").arg(cat).arg(i);
    //         model->addApp(it);
    //     }
    // }
    Wrapper wrapper;
    // Path to JSON file in project directory
    QString jsonPath = /*QCoreApplication::applicationDirPath() +*/ "/home/shankar/QtTrsin/AppExample/Data.json";
    if (!wrapper.loadFromJson(jsonPath)) {
        qWarning() << "Failed to load apps from" << jsonPath;
    }

    // Proxy model for filtering
     CategoriesModel *categoriesModel = new CategoriesModel(); // Categories from JS
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(model);
    // set filterRole to the model's category role (note: use enum value)

    proxy->setFilterRole(AppModel::CategoryRole);
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);

    QQmlApplicationEngine engine;
      engine.rootContext()->setContextProperty("categoriesModel", categoriesModel);
    engine.rootContext()->setContextProperty("wrapper", &wrapper);
    engine.rootContext()->setContextProperty("appModel", model);

    engine.rootContext()->setContextProperty("categoriesModel", wrapper.categoriesModel());
    engine.rootContext()->setContextProperty("appProxyModel", wrapper.filteredAppModel());


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
