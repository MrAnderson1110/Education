import QtQuick 2.11
import qmlplugins 1.0

BasicGridCell {
    id: cell
    property color selectColor
    property color oddColor
    property color evenColor

    background: Rectangle {
        color: {
            if(selected)
                return selectColor
            else if((cell.rowIndex + cell.columnIndex) % 2)
                return evenColor
            else
                return oddColor
        }
        border.width: 1
        border.color: "black"
    }
}
