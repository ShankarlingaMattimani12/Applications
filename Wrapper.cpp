#include "Wrapper.h"

Wrapper::Wrapper(QObject *parent)
    : QObject{parent}
{
    m_appModel = new AppModel(this);
    m_categoriesModel = new CategoriesModel(this);
    m_filterModel = new QSortFilterProxyModel(this);
    m_filterModel->setSourceModel(m_appModel);
    m_filterModel->setFilterRole(AppModel::CategoryRole);
    m_filterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
}

bool Wrapper::loadFromJson(const QString &path)
{
    bool ok = m_appModel->loadFromJson(path);
    if (ok) {
        // Extract categories dynamically
        QSet<QString> cats;
        for (const auto &app : m_appModel->m_items) cats.insert(app.category);
        m_categoriesModel->setCategories(QStringList(cats.begin(), cats.end()));
    }
    return ok;
}

void Wrapper::setCategoryFilter(const QString &category)
{
    m_filterModel->setFilterFixedString(category);
}

AppModel *Wrapper::appModel() const
{
    return m_appModel;
}

CategoriesModel *Wrapper::categoriesModel() const
{
    return m_categoriesModel;
}

QSortFilterProxyModel *Wrapper::filteredAppModel() const
{
    return m_filterModel;
}
