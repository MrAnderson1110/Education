#include "boardplugin.h"

#include <QtQml>

#include <BasicBoard>
#include <BasicGridCell>
#include <PieceStrategy>

typedef PieceStrategy<BasicPiece::King> King;
typedef PieceStrategy<BasicPiece::Queen> Queen;
typedef PieceStrategy<BasicPiece::Bishop> Bishop;
typedef PieceStrategy<BasicPiece::Knight> Knight;
typedef PieceStrategy<BasicPiece::Rook> Rook;
typedef PieceStrategy<BasicPiece::Pawn> Pawn;

void BoardPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("qmlplugins"));

    qmlRegisterType<BasicBoard>(uri, 1, 0, "BasicBoard");
    qmlRegisterType<BasicGridCell>(uri, 1, 0, "BasicGridCell");

    qmlRegisterUncreatableType<BasicPiece>(uri, 1, 0, "BasicPiece", "must be created from C++ only");
    qmlRegisterType<King>(uri, 1, 0, "King");
    qmlRegisterType<Queen>(uri, 1, 0, "Queen");
    qmlRegisterType<Bishop>(uri, 1, 0, "Bishop");
    qmlRegisterType<Knight>(uri, 1, 0, "Knight");
    qmlRegisterType<Rook>(uri, 1, 0, "Rook");
    qmlRegisterType<Pawn>(uri, 1, 0, "Pawn");
}
