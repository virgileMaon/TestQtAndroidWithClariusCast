#pragma once

#include "castbridge.h"

class QJniEnvironment;
class QJniObject;

class CastBridgeAndroid : public CastBridge
{
public:
    explicit CastBridgeAndroid(QObject *parent = nullptr);
    ~CastBridgeAndroid() override;

protected:
    bool lowCreate(bool anotherThread) override;
    bool lowRelease() override;

private:
    QJniEnvironment* env_ = nullptr;
    QJniObject* castHandle_ = nullptr;

};
