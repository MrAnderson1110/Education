import QtQuick 2.11
import QtQml 2.11
import QtQuick.Layouts 1.11

import qmlplugins 1.0

BasicBoard {
    id: root
    property color evenColor: "#8B4513"
    property color oddColor: "#D2B48C"
    property color selectColor: "#629C63"
    property color onFightColor: "#A52A2A"
    property color hoveredColor: "#008080"
    property int generalMargin: 20

    QtObject {
        id: p
        function mapIndexToLetter(index) {
            switch(index) {
            case 0:
                return "A"
            case 1:
                return "B"
            case 2:
                return "C"
            case 3:
                return "D"
            case 4:
                return "E"
            case 5:
                return "F"
            case 6:
                return "G"
            case 7:
                return "H"
            }
        }
    }

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
                    text: p.mapIndexToLetter(index)
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
                    text: 8 - index
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
                GridCell {
                    oddColor: root.oddColor
                    evenColor: root.evenColor
                    selectColor: root.selectColor
                    onFightColor: root.onFightColor
                    hoveredColor: root.hoveredColor

                    Layout.row: index / 8
                    Layout.column: (index + 8) % 8
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    rowIndex: Layout.row
                    columnIndex: Layout.column
                    MouseArea {
                        anchors.fill: parent
                        onClicked: root.clearSelection()
                    }
                }
            }
        }
    }
}

