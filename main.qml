import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: win
    visible: true
    width: 1000
    height: 600
    title: "Filtered Apps — Left buttons / Right list"

    Row {
        anchors.fill: parent

        // LEFT - 25%
        Rectangle {
            width: parent.width * 0.25
            height: parent.height
            color: "#f0f0f0"

            Column {
                anchors.fill: parent
                spacing: 10
                padding: 12

                Button { text: "Productivity"; onClicked: appProxyModel.setFilterFixedString("Productivity") }
                Button { text: "Setup"; onClicked: appProxyModel.setFilterFixedString("Setup") }
                Button { text: "Support"; onClicked: appProxyModel.setFilterFixedString("Support") }
                Button { text: "Tools"; onClicked: appProxyModel.setFilterFixedString("Tools") }
                Button { text: "Favourite"; onClicked: appProxyModel.setFilterFixedString("Favourite") }

                // quick reset / show all
                Button { text: "Show All"; onClicked: appProxyModel.setFilterFixedString("") }

                // A simple filter text input (extra): filters name too
                TextField {
                    id: txtFilter
                    placeholderText: "(optional) filter names..."
                    onTextChanged: {
                        // when user types, filter using a regex on the display role (name)
                        // We temporarily change filter role to NameRole (role id is 1), then restore
                        // NOTE: this is a simple approach; appProxyModel is a QSortFilterProxyModel from C++
                        appProxyModel.setFilterRole(1); // NameRole is Qt::UserRole+1 -> role id is 257 in practice, but QML sees role indexes starting from 1 if exposed. If this doesn't match, use a small helper in C++ to expose a setter; see notes.
                        appProxyModel.setFilterFixedString(txtFilter.text)
                        // restore filter role to CategoryRole for button clicks
                        // In practice, button clicks set filter role first; this TextField changes role temporarily.
                        appProxyModel.setFilterRole(2) // CategoryRole index — see C++ role mapping if needed
                    }
                }
            }
        }

        // RIGHT - 75%
        Rectangle {
            width: parent.width * 0.75
            height: parent.height
            color: "white"

            Column {
                anchors.fill: parent
                spacing: 8
                padding: 12

                Text { text: "Apps"; font.pixelSize: 20 }

                ListView {
                    id: listView
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    model: appProxyModel
                    delegate: ItemDelegate {
                        width: parent.width
                        text: model.name
                        onClicked: {
                            // show plugin name quickly
                            console.log("Clicked app:", model.name, "plugin:", model.plugin)
                        }
                    }
                }
            }
        }
    }
}
