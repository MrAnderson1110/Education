import QtQuick 2.0

Rectangle {
    id: cell
    property int column: 0
    property int row: 0
    property alias text: txt.text
    property alias textColor: txt.color

    readonly property alias isSelected: p.selected

    signal clicked(var row, var column)

    QtObject {
        id: p
        property bool selected: false
    }

    Text {
        id: txt
        anchors.centerIn: parent
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            p.selected = !p.selected
            cell.clicked(row, column)
        }
    }
}

