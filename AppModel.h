#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>
#pragma once

#include <QAbstractListModel>
#include <vector>
struct AppItem {
    QString name;
    QString category;
    QString plugin;
};
class AppModel : public  QAbstractListModel
{

    Q_OBJECT
public:
    explicit AppModel(QObject *parent = nullptr);
    enum Roles {
        NameRole = Qt::UserRole + 1,
        CategoryRole,
        PluginRole
    };

signals:
public:
  // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addApp(const AppItem &item);
    void clear();
    bool loadFromJson(const QString &filePath);

    std::vector<AppItem> m_items;
private:
};

#endif // APPMODEL_H
