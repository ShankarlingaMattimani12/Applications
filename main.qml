// import QtQuick 2.15
// import QtQuick.Controls 2.15
// import QtQuick.Layouts 1.15

// ApplicationWindow {
//     visible: true
//     width: 800
//     height: 600
//     title: "Apps Grid by Category"

//     RowLayout {
//         anchors.fill: parent

//         // Left side: category buttons
//         ColumnLayout {
//             Layout.preferredWidth: 150
//             spacing: 10

//             Repeater {
//                 model: categoriesModel
//                 delegate: Button {
//                     text: category
//                     onClicked: appProxyModel.setFilterFixedString(category)
//                 }
//             }

//             Button {
//                 text: "Show All"
//                 onClicked: appProxyModel.setFilterFixedString("")
//             }
//         }

//         // Right side: apps grid
//         GridView {
//             Layout.fillWidth: true
//             Layout.fillHeight: true
//             model: appProxyModel
//             cellWidth: 150
//             cellHeight: 80
//          //   spacing: 10

//             delegate: Rectangle {
//                 width: 140
//                 height: 70
//                 color: "#e0e0e0"
//                 radius: 6
//                 border.width: 1
//                 border.color: "#999"

//                 Text {
//                     anchors.centerIn: parent
//                     text: name
//                 }
//             }
//         }
//     }
// }
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Apps Grid by Category"

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // Left side: category buttons
        Rectangle {
            Layout.preferredWidth: parent.width * 0.25
            Layout.fillHeight: true
            color: "#2c3e50"  // Dark sidebar background

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 8

                Repeater {
                    model: categoriesModel
                    delegate: Button {
                        text: category
                        font.bold: true
                        background: Rectangle {
                            radius: 6
                            color: pressed ? "#1abc9c" : "#34495e"
                        }
                        contentItem: Text {
                            text: category
                            color: "white"
                            font.pixelSize: 30
                            anchors.centerIn: parent
                        }
                        onClicked: appProxyModel.setFilterFixedString(category)
                    }
                }

                Rectangle {
                    height: 1
                    color: "#7f8c8d"
                    Layout.fillWidth: true
                    Layout.margins: 5
                }

                Button {
                    text: "Show All"
                    font.bold: true
                    background: Rectangle {
                        radius: 6
                        color: pressed ? "#1abc9c" : "#34495e"
                    }
                    contentItem: Text {
                        text: "Show All"
                        color: "white"
                        font.pixelSize: 16
                        anchors.centerIn: parent
                    }
                    onClicked: appProxyModel.setFilterFixedString("")
                }
            }
        }

        // Right side: apps grid
        Rectangle {
            Layout.preferredWidth: parent.width * 0.75
            Layout.fillHeight: true
            color: "#ecf0f1" // Light background

            GridView {
                id: appsGrid
                anchors.fill: parent
                anchors.margins: 16
                model: appProxyModel
                cellWidth: 160
                cellHeight: 90
               // spacing: 12

                delegate: Rectangle {
                    width: 150
                    height: 80
                    radius: 10
                    color: "#ffffff"
                    border.width: 1
                    border.color: "#bdc3c7"

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: parent.color = "#dfe6e9"
                        onExited: parent.color = "#ffffff"
                    }

                    Text {
                        anchors.centerIn: parent
                        text: name
                        color: "#2c3e50"
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        wrapMode: Text.Wrap
                    }
                }
            }
        }
    }
}
