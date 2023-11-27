#include "castbridge.h"

CastBridge::CastBridge(QObject *parent)
    : QObject{parent}
{

}

void CastBridge::connect(QString ip, int port, long networkID, QString certificate)
{
    lowConnect(ip,port,networkID,certificate);
}

bool CastBridge::create(bool anotherThread) {
    return lowCreate(anotherThread);
}

bool CastBridge::release() {
    return lowRelease();
}
