import QtQuick 2.11
import QtQuick.Layouts 1.11

import qmlplugins 1.0

BasicBoard {
    id: board
    property color evenColor: "#8b4513"
    property color oddColor: "#ffe4b5"
    property int generalMargin: 20

    GridLayout {
        rows: 2
        columns: 2
        rowSpacing: 1
        columnSpacing: 1
        anchors.fill: parent
        RowLayout {
            id: rowIndexes
            Layout.column: 2
            Layout.row: 1
            Layout.rightMargin: generalMargin
            spacing: 1
            Repeater {
                model: 8
                Text {
                    Layout.fillWidth: true
                    Layout.preferredHeight: generalMargin
                    color: "black"
                    text: index
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }
            }
        }
        ColumnLayout {
            id: columnIndexes
            spacing: 1
            Layout.column: 1
            Layout.row: 2
            Layout.bottomMargin: generalMargin
            Repeater {
                model: 8
                Text {
                    Layout.fillHeight: true
                    Layout.preferredWidth: generalMargin
                    color: "black"
                    text: index
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                }
            }
        }
        GridLayout {
            id: celles
            columns: 8
            rows: 8
            columnSpacing: 1
            rowSpacing: 1
            Layout.column: 2
            Layout.row: 2
            Layout.rightMargin: generalMargin
            Layout.bottomMargin: generalMargin
            Repeater {
                id: rep
                model: celles.rows * celles.columns
                BasicGridCell {
                    id: cell
                    Layout.row: index / 8
                    Layout.column: (index + 8) % 8
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    rowIndex: Layout.row
                    columnIndex: Layout.column
                    background: Rectangle {
                        anchors.fill: cell
                        color: (cell.rowIndex + cell.columnIndex) % 2 ? evenColor : oddColor
                        border.width: 1
                        border.color: "black"
                    }
                }
            }
        }
    }
}

