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

        BasicPiece {
            id: blackKing
            command: BasicPiece.Black
            type: BasicPiece.King
            background: PieceStyle { piece: blackKing }
        }
        BasicPiece {
            id: blackQueen
            command: BasicPiece.Black
            type: BasicPiece.Queen
            background: PieceStyle { piece: blackQueen }
        }
        BasicPiece {
            id: blackBishop_1
            command: BasicPiece.Black
            type: BasicPiece.Bishop
            background: PieceStyle { piece: blackBishop_1 }
        }
        BasicPiece {
            id: blackBishop_2
            command: BasicPiece.Black
            type: BasicPiece.Bishop
            background: PieceStyle { piece: blackBishop_2 }
        }
        BasicPiece {
            id: blackKnight_1
            command: BasicPiece.Black
            type: BasicPiece.Knight
            background: PieceStyle { piece: blackKnight_1 }
        }
        BasicPiece {
            id: blackKnight_2
            command: BasicPiece.Black
            type: BasicPiece.Knight
            background: PieceStyle { piece: blackKnight_2 }
        }
        BasicPiece {
            id: blackRook_1
            command: BasicPiece.Black
            type: BasicPiece.Rook
            background: PieceStyle { piece: blackRook_1 }
        }
        BasicPiece {
            id: blackRook_2
            command: BasicPiece.Black
            type: BasicPiece.Rook
            background: PieceStyle { piece: blackRook_2 }
        }
        BasicPiece {
            id: blackRookPawn_1
            command: BasicPiece.Black
            type: BasicPiece.Pawn
            background: PieceStyle { piece: blackRookPawn_1 }
        }
        BasicPiece {
            id: blackRookPawn_2
            command: BasicPiece.Black
            type: BasicPiece.Pawn
            background: PieceStyle { piece: blackRookPawn_2 }
        }
        BasicPiece {
            id: blackBishopPawn_1
            command: BasicPiece.Black
            type: BasicPiece.Pawn
            background: PieceStyle { piece: blackBishopPawn_1 }
        }
        BasicPiece {
            id: blackBishopPawn_2
            command: BasicPiece.Black
            type: BasicPiece.Pawn
            background: PieceStyle { piece: blackBishopPawn_2 }
        }
        BasicPiece {
            id: blackKnightPawn_1
            command: BasicPiece.Black
            type: BasicPiece.Pawn
            background: PieceStyle { piece: blackKnightPawn_1 }
        }
        BasicPiece {
            id: blackKnightPawn_2
            command: BasicPiece.Black
            background: PieceStyle { piece: blackKnightPawn_2 }
        }
        BasicPiece {
            id: blackQueenPawn
            command: BasicPiece.Black
            type: BasicPiece.Pawn
            background: PieceStyle { piece: blackQueenPawn }
        }
        BasicPiece {
            id: blackKingPawn
            command: BasicPiece.Black
            type: BasicPiece.Pawn
            background: PieceStyle { piece: blackKingPawn }
        }

        BasicPiece {
            id: whiteKing
            command: BasicPiece.White
            type: BasicPiece.King
            background: PieceStyle { piece: whiteKing }
        }
        BasicPiece {
            id: whiteQueen
            command: BasicPiece.White
            type: BasicPiece.Queen
            background: PieceStyle { piece: whiteQueen }
        }
        BasicPiece {
            id: whiteBishop_1
            command: BasicPiece.White
            type: BasicPiece.Bishop
            background: PieceStyle { piece: whiteBishop_1 }
        }
        BasicPiece {
            id: whiteBishop_2
            command: BasicPiece.White
            type: BasicPiece.Bishop
            background: PieceStyle { piece: whiteBishop_2 }
        }
        BasicPiece {
            id: whiteKnight_1
            command: BasicPiece.White
            type: BasicPiece.Knight
            background: PieceStyle { piece: whiteKnight_1 }
        }
        BasicPiece {
            id: whiteKnight_2
            command: BasicPiece.White
            type: BasicPiece.Knight
            background: PieceStyle { piece: whiteKnight_2 }
        }
        BasicPiece {
            id: whiteRook_1
            command: BasicPiece.White
            type: BasicPiece.Rook
            background: PieceStyle { piece: whiteRook_1 }
        }
        BasicPiece {
            id: whiteRook_2
            command: BasicPiece.White
            type: BasicPiece.Rook
            background: PieceStyle { piece: whiteRook_2 }
        }
        BasicPiece {
            id: whiteRookPawn_1
            command: BasicPiece.White
            type: BasicPiece.Pawn
            background: PieceStyle { piece: whiteRookPawn_1 }
        }
        BasicPiece {
            id: whiteRookPawn_2
            command: BasicPiece.White
            type: BasicPiece.Pawn
            background: PieceStyle { piece: whiteRookPawn_2 }
        }
        BasicPiece {
            id: whiteBishopPawn_1
            command: BasicPiece.White
            type: BasicPiece.Pawn
            background: PieceStyle { piece: whiteBishopPawn_1 }
        }
        BasicPiece {
            id: whiteBishopPawn_2
            command: BasicPiece.White
            type: BasicPiece.Pawn
            background: PieceStyle { piece: whiteBishopPawn_2 }
        }
        BasicPiece {
            id: whiteKnightPawn_1
            command: BasicPiece.White
            type: BasicPiece.Pawn
            background: PieceStyle { piece: whiteKnightPawn_1 }
        }
        BasicPiece {
            id: whiteKnightPawn_2
            command: BasicPiece.White
            type: BasicPiece.Pawn
            background: PieceStyle { piece: whiteKnightPawn_2 }
        }
        BasicPiece {
            id: whiteQueenPawn
            command: BasicPiece.White
            type: BasicPiece.Pawn
            background: PieceStyle { piece: whiteQueenPawn }
        }
        BasicPiece {
            id: whiteKingPawn
            command: BasicPiece.White
            type: BasicPiece.Pawn
            background: PieceStyle { piece: whiteKingPawn }
        }
    }
}
