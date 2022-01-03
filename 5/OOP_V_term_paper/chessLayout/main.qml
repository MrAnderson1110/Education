import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Layouts 1.11
import QtTest 1.11

Window {
    id: root
    width: chessBorder.implicitWidth
    height: chessBorder.implicitHeight
    minimumHeight: maximumHeight
    maximumHeight: height
    minimumWidth: maximumWidth
    maximumWidth: width
    visible: true
    title: qsTr("Chess Layout")

    Column {
        id: chessBorder
        property int selectedRow: -1
        property int selectedColumn: -1
        property bool hasSelection: false

        RowDelegate {
            id: topCoords
            row: -1
            colorInverce: false
        }

        RowDelegate {
            id: first
            row: 8
            colorInverce: false
        }

        RowDelegate {
            id: sec
            row: 7
            colorInverce: true
        }

        RowDelegate {
            id: third
            row: 6
            colorInverce: false
        }

        RowDelegate {
            id: forth
            row: 5
            colorInverce: true
        }

        RowDelegate {
            id: fifth
            row: 4
            colorInverce: false
        }

        RowDelegate {
            id: sixth
            row: 3
            colorInverce: true
        }

        RowDelegate {
            id: seventh
            row: 2
            colorInverce: false
        }

        RowDelegate {
            id: eightth
            row: 1
            colorInverce: true
        }

        RowDelegate {
            id: bottomCoords
            row: -1
            colorInverce: false
        }
    }
}
