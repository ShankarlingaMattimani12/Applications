#include "CategoriesModel.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

CategoriesModel::CategoriesModel(QObject *parent)
    : QAbstractListModel(parent)
{
    loadFromJson(":/data/categories.json");
}

QHash<int, QByteArray> CategoriesModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[CategoryRole] = "category";
    return roles;
}

int CategoriesModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return m_categories.count();
}

QVariant CategoriesModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_categories.size())
        return QVariant();

    if (role == CategoryRole)
        return m_categories.at(index.row());

    return QVariant();
}

void CategoriesModel::setCategories(const QStringList &cats) {
    qDebug() << "size ----"<<m_categories.size();
    beginResetModel();
    m_categories = cats;
    endResetModel();
    qDebug() << "size 111----"<<m_categories.size();

}

void CategoriesModel::loadFromJson(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open" << filePath;
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return;
    }

    if (!doc.isObject()) {
        qWarning() << "Invalid JSON format";
        return;
    }

    QJsonObject rootObj = doc.object();
    if (!rootObj.contains("categories") || !rootObj["categories"].isArray()) {
        qWarning() << "No categories array found";
        return;
    }

    QStringList categoriesList;
    QJsonArray catArray = rootObj["categories"].toArray();
    for (const QJsonValue &val : catArray) {
        if (val.isString())
            categoriesList << val.toString();
    }

    setCategories(categoriesList);
}
