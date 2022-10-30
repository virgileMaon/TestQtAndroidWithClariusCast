#include "castbridge.h"

CastBridge::CastBridge(QObject *parent)
    : QObject{parent}
{

}

bool CastBridge::create(bool anotherThread) {
    return lowCreate(anotherThread);
}

bool CastBridge::release() {
    return lowRelease();
}
