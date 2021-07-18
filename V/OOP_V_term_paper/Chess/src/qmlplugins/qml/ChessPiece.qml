import QtQuick 2.11
import QtQml 2.11

import qmlplugins 1.0

BasicPiece {
    id: root
    property color whiteColor: "white"
    property color blackColor: "black"

    background: ColorizedImage {
        id: img
        color: root.command === BasicPiece.White ? whiteColor : blackColor
        source: p.__mapTypeToIconSource(root.type)
    }

    QtObject {
        id: p

        function __mapTypeToIconSource(type) {
            switch(type) {
            case BasicPiece.King:
                return "./resources/king.svg"
            case BasicPiece.Queen:
                return "./resources/queen.svg"
            case BasicPiece.Bishop:
                return "./resources/bishop.svg"
            case BasicPiece.Knight:
                return "./resources/knight.svg"
            case BasicPiece.Rook:
                return "./resources/rook.svg"
            case BasicPiece.Pawn:
                return "./resources/pawn.svg"
            }
        }
    }     

    MoveManipulator {
        id: moveManiupulator
        anchors.fill: parent
        piece: root
        onStarted: root.startMove()
        onFinsihed: root.finishMove()
        onMoved: root.move(geometry)
    }
}
