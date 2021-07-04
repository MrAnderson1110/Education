import QtQuick 2.0

Row {
    id: root
    property int row: 0
    property int cellHeight: 60
    property int cellWidth: 60
    property bool colorInverce: false
    property color evenColor: "#8b4513"
    property color oddColor: "#ffe4b5"
    property color selectedColor: "#808000"

    QtObject {
        id: p
        property string realOddColor: colorInverce ? evenColor : oddColor
        property string realEvenColor: colorInverce ? oddColor : evenColor
        property string coordColor: oddColor
        property string textColor: evenColor
    }

    Repeater {
        id: rowRepeater
        model: 10
        Cell {
            row: root.row
            column: index
            height: row < 0 ? cellHeight / 2 : cellHeight
            width: index === 0 || index === 9 ? cellWidth / 2 : cellWidth
            color: {
                if(index === 0 || index === 9)
                    return p.coordColor
                else if(row < 0)
                    return p.coordColor
                else if(chessBorder.hasSelection) {
                    console.log("current:", row, index, "selected:", chessBorder.selectedRow, chessBorder.selectedColumn)
                    if(row === chessBorder.selectedRow && index === chessBorder.selectedColumn)
                        return selectedColor
                    else if((row === chessBorder.selectedRow + 2 || row === chessBorder.selectedRow - 2)
                            && (index === chessBorder.selectedColumn + 1 || index === chessBorder.selectedRow - 1))
                        return selectedColor
                    else if((row === chessBorder.selectedRow + 1 || row === chessBorder.selectedRow - 1)
                            && (index === chessBorder.selectedColumn + 2 || index === chessBorder.selectedColumn - 2))
                        return selectedColor
                    else index % 2 ? p.realOddColor : p.realEvenColor

                }
                else
                    return index % 2 ? p.realOddColor : p.realEvenColor
            }
            textColor: p.textColor
            text: {
                if(row < 0 && index !== 0 && index !== 9)
                    return index
                else if(index === 0 || index === 9) {
                    return chooseColor(row)
                }
                else
                    return ""
            }

            ColorizedImage {
                anchors.fill: parent
                visible: row === 5 && index === 5 || row === 2 && index === 2
                color: index % 2 ? "black" : "white"
                source: "qrc:/resources/knight.svg"
            }

            onClicked: {
                if(chessBorder.selectedColumn === column && chessBorder.selectedRow === row || !chessBorder.hasSelection)
                    chessBorder.hasSelection = !chessBorder.hasSelection
                chessBorder.selectedColumn = column
                chessBorder.selectedRow = row
                //                console.log(row, column)
            }
        }
    }

    function chooseColor(row) {
        switch (row) {
        case 1:
            return "A"
        case 2:
            return "B"
        case 3:
            return "C"
        case 4:
            return "D"
        case 5:
            return "E"
        case 6:
            return "F"
        case 7:
            return "G"
        case 8:
            return "H"
        default:
            return ""
        }
    }
}
