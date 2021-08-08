import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQml 2.11
import QtQuick.Layouts 1.11
import QtQuick.Window 2.11
import qmlplugins 1.0

ApplicationWindow {
    id: root
    height: 640
    width: 640
    minimumHeight: 480
    minimumWidth: minimumHeight

    visible: true
    title: qsTr("Chess")

    background: Rectangle {
        id: back
        color: board.oddColor
        anchors.fill: parent
    }

    ChessBoard {
        id: board
        anchors.fill: parent

        King {
            id: blackKing
            command: BasicPiece.Black
            background: PieceStyle { piece: blackKing }
        }
        Queen {
            id: blackQueen
            command: BasicPiece.Black
            background: PieceStyle { piece: blackQueen }
        }
        Bishop {
            id: blackBishop_1
            command: BasicPiece.Black
            background: PieceStyle { piece: blackBishop_1 }
        }
        Bishop {
            id: blackBishop_2
            command: BasicPiece.Black
            background: PieceStyle { piece: blackBishop_2 }
        }
        Knight {
            id: blackKnight_1
            command: BasicPiece.Black
            background: PieceStyle { piece: blackKnight_1 }
        }
        Knight {
            id: blackKnight_2
            command: BasicPiece.Black
            background: PieceStyle { piece: blackKnight_2 }
        }
        Rook {
            id: blackRook_1
            command: BasicPiece.Black
            background: PieceStyle { piece: blackRook_1 }
        }
        Rook {
            id: blackRook_2
            command: BasicPiece.Black
            background: PieceStyle { piece: blackRook_2 }
        }
        Pawn {
            id: blackRookPawn_1
            command: BasicPiece.Black
            background: PieceStyle { piece: blackRookPawn_1 }
        }
        Pawn {
            id: blackRookPawn_2
            command: BasicPiece.Black
            background: PieceStyle { piece: blackRookPawn_2 }
        }
        Pawn {
            id: blackBishopPawn_1
            command: BasicPiece.Black
            background: PieceStyle { piece: blackBishopPawn_1 }
        }
        Pawn {
            id: blackBishopPawn_2
            command: BasicPiece.Black
            background: PieceStyle { piece: blackBishopPawn_2 }
        }
        Pawn {
            id: blackKnightPawn_1
            command: BasicPiece.Black
            background: PieceStyle { piece: blackKnightPawn_1 }
        }
        Pawn {
            id: blackKnightPawn_2
            command: BasicPiece.Black
            background: PieceStyle { piece: blackKnightPawn_2 }
        }
        Pawn {
            id: blackQueenPawn
            command: BasicPiece.Black
            background: PieceStyle { piece: blackQueenPawn }
        }
        Pawn {
            id: blackKingPawn
            command: BasicPiece.Black
            background: PieceStyle { piece: blackKingPawn }
        }

        King {
            id: whiteKing
            command: BasicPiece.White
            background: PieceStyle { piece: whiteKing }
        }
        Queen {
            id: whiteQueen
            command: BasicPiece.White
            background: PieceStyle { piece: whiteQueen }
        }
        Bishop {
            id: whiteBishop_1
            command: BasicPiece.White
            background: PieceStyle { piece: whiteBishop_1 }
        }
        Bishop {
            id: whiteBishop_2
            command: BasicPiece.White
            background: PieceStyle { piece: whiteBishop_2 }
        }
        Knight {
            id: whiteKnight_1
            command: BasicPiece.White
            background: PieceStyle { piece: whiteKnight_1 }
        }
        Knight {
            id: whiteKnight_2
            command: BasicPiece.White
            background: PieceStyle { piece: whiteKnight_2 }
        }
        Rook {
            id: whiteRook_1
            command: BasicPiece.White
            background: PieceStyle { piece: whiteRook_1 }
        }
        Rook {
            id: whiteRook_2
            command: BasicPiece.White
            background: PieceStyle { piece: whiteRook_2 }
        }
        Pawn {
            id: whiteRookPawn_1
            command: BasicPiece.White
            background: PieceStyle { piece: whiteRookPawn_1 }
        }
        Pawn {
            id: whiteRookPawn_2
            command: BasicPiece.White
            background: PieceStyle { piece: whiteRookPawn_2 }
        }
        Pawn {
            id: whiteBishopPawn_1
            command: BasicPiece.White
            background: PieceStyle { piece: whiteBishopPawn_1 }
        }
        Pawn {
            id: whiteBishopPawn_2
            command: BasicPiece.White
            background: PieceStyle { piece: whiteBishopPawn_2 }
        }
        Pawn {
            id: whiteKnightPawn_1
            command: BasicPiece.White
            background: PieceStyle { piece: whiteKnightPawn_1 }
        }
        Pawn {
            id: whiteKnightPawn_2
            command: BasicPiece.White
            background: PieceStyle { piece: whiteKnightPawn_2 }
        }
        Pawn {
            id: whiteQueenPawn
            command: BasicPiece.White
            background: PieceStyle { piece: whiteQueenPawn }
        }
        Pawn {
            id: whiteKingPawn
            command: BasicPiece.White
            background: PieceStyle { piece: whiteKingPawn }
        }
    }
}
