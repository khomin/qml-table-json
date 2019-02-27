import QtQuick.Layouts 1.1
import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.1


ApplicationWindow {
    width: 800
    height: 800

    visible: true
    title: "test_application"

    Connections {
        target: test_application

        onConnectToHostOk: {}
        onConnectToHostError: {
            messageError.text = qsTr("Ошибка соединения");
            messageError.setInformativeText(errorMessage);
            messageError.open();
        }
        onParceResponceError: {
            messageError.text = qsTr("Ошибка разбора");
            messageError.open();
        }
    }

        TableView {
            anchors.fill: parent
            model: tableDataModel

            rowDelegate: Rectangle {
               height: 25
               SystemPalette {
                  id: myPalette;
                  colorGroup: SystemPalette.Active
               }
               color: {
                  var baseColor = styleData.alternate?myPalette.alternateBase:myPalette.base
                  return styleData.selected?myPalette.highlight:baseColor
               }
            }

            itemDelegate: Item {
                id:tableItem
                height: 25
                Rectangle {
                    anchors.fill: parent
                    color: model.isCoordinate ? (parseInt(styleData.value) >= 0 ? "green" : "red") : "transparent"
                    radius: 90
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: styleData.textColor
                        elide: styleData.elideMode
                        text: styleData.value
                    }
                }
            }

            TableViewColumn {
                role: "columnKey"
                title: "ColumnKey"
            }

            TableViewColumn {
                role: "columnValue"
                title: "columnValue"
            }
        }

        MessageDialog {
            id: messageError
            icon: StandardIcon.Information
            title: qsTr("Error")
        }
    }
