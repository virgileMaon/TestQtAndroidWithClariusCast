#include "castbridgefake.h"

CastBridgeFake::CastBridgeFake(QObject *parent)
    : CastBridge{parent}
{

}

bool CastBridgeFake::lowCreate(bool anotherThread) { return true; }
bool CastBridgeFake::lowRelease() { return true; }

