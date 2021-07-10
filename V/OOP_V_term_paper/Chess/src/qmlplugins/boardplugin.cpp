#include "boardplugin.h"

#include <QtQml>

#include <ChessBoard>
#include <IPiece>
#include <BasicPiece>
#include <BasicPawn>

void BoardPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("qmlplugins"));

    qmlRegisterType<ChessBoard>(uri, 1, 0, "ChessBoard");

    qmlRegisterUncreatableType<IPiece>(uri, 1, 0, "IPiece", "must be create from C++ only");
    qmlRegisterType<BasicPiece>(uri, 1, 0, "BasicPiece");
    qmlRegisterType<BasicPawn>(uri, 1, 0, "BasicPawn");
}
