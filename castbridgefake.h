#pragma once

#include "castbridge.h"

class CastBridgeFake : public CastBridge
{
public:
    explicit CastBridgeFake(QObject *parent = nullptr);

protected:
    bool lowCreate(bool anotherThread) override;
    bool lowRelease() override;
};
