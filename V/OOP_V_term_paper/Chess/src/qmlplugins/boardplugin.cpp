#include "boardplugin.h"

#include <QtQml>

#include <BasicBoard>
#include <BasicGridCell>

void BoardPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("qmlplugins"));

    qmlRegisterType<BasicBoard>(uri, 1, 0, "BasicBoard");
    qmlRegisterType<BasicGridCell>(uri, 1, 0, "BasicGridCell");
}
