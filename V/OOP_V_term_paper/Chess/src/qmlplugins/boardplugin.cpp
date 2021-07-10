#include "boardplugin.h"

#include <QtQml>

#include <ChessBoard>
#include <IPiece>
#include <King>
#include <Queen>
#include <Knife>
#include <Bishop>
#include <Rook>
#include <Pawn>

void BoardPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("qmlplugins"));

    qmlRegisterType<ChessBoard>(uri, 1, 0, "ChessBoard");

    qmlRegisterUncreatableType<IPiece>(uri, 1, 0, "IPiece", "must be create from C++ only");
    qmlRegisterType<King>(uri, 1, 0, "King");
    qmlRegisterType<Queen>(uri, 1, 0, "Queen");
    qmlRegisterType<Knife>(uri, 1, 0, "Knife");
    qmlRegisterType<Bishop>(uri, 1, 0, "Bishop");
    qmlRegisterType<Rook>(uri, 1, 0, "Rook");
    qmlRegisterType<Pawn>(uri, 1, 0, "Pawn");

}
