import QtQuick 2.11
import QtQuick.Window 2.11
import qmlplugins 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ChessBoard {
        King {}
        Queen {}
        Knife {}
        Bishop {}
        Rook {}
        Pawn { type: IPiece.Knife }
    }
}
