import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQml 2.11
import QtQuick.Layouts 1.11
import QtQuick.Window 2.11
import qmlplugins 1.0

ApplicationWindow {
    id: root
    height: 640
    minimumHeight: 480
    minimumWidth: height
    maximumWidth: minimumWidth

    visible: true
    title: qsTr("Hello World")

    background: Rectangle {
        id: back
        color: board.oddColor
        anchors.fill: parent
    }

    ChessBoard {
        id: board
    }
}
