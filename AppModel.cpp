#include "AppModel.h"
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include<QJsonArray>
AppModel::AppModel(QObject *parent)
    :  QAbstractListModel{parent}
{}
int AppModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return static_cast<int>(m_items.size());
}

QVariant AppModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return {};
    int row = index.row();
    if (row < 0 || row >= (int)m_items.size()) return {};
    const AppItem &it = m_items[row];
    switch (role) {
    case NameRole: return it.name;
    case CategoryRole: return it.category;
    case PluginRole: return it.plugin;
    case Qt::DisplayRole: return it.name;
    default: return {};
    }
}

QHash<int, QByteArray> AppModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[CategoryRole] = "category";
    roles[PluginRole] = "plugin";
    return roles;
}

void AppModel::addApp(const AppItem &item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items.push_back(item);
    endInsertRows();
}

void AppModel::clear()
{
    beginResetModel();
    m_items.clear();
    endResetModel();
}
bool AppModel::loadFromJson(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return false;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (!doc.isObject()) return false;
    QJsonObject obj = doc.object();
    if (!obj.contains("apps") || !obj["apps"].isArray()) return false;

    beginResetModel();
    m_items.clear();

    QJsonArray arr = obj["apps"].toArray();
    for (auto v : arr) {
        if (!v.isObject()) continue;
        QJsonObject appObj = v.toObject();
        AppItem item;
        item.name = appObj["name"].toString();
        item.category = appObj["category"].toString();
        //item.plugin = appObj["plugin"].toString();
        m_items.push_back(item);
    }

    endResetModel();
    return true;
}
