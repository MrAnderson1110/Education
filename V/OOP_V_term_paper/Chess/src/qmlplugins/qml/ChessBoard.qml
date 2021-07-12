import QtQuick 2.11
import QtQuick.Layouts 1.11
import qmlplugins 1.0

BasicBoard {
    id: board
    anchors.fill: parent
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
            spacing: 1
            Repeater {
                model: 8
                Text {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 20
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
            Repeater {
                model: 8
                Text {
                    Layout.fillHeight: true
                    Layout.preferredWidth: 20
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
                        color: (index + 1) % 2 ? "red" : "green"
                        border.width: 1
                        border.color: "black"
                    }
                }
            }
        }
    }
}

