#pragma once

#include "castbridge.h"
#include <QtCore/private/qjnihelpers_p.h>
#include <QJniEnvironment>

class QJniEnvironment;
class QJniObject;

class CastBridgeAndroid : public CastBridge
{
    Q_OBJECT
    Q_PROPERTY(QString result MEMBER result_ NOTIFY resultChanged)
public:
    explicit CastBridgeAndroid(QObject *parent = nullptr);
    ~CastBridgeAndroid() override;
    int secretValue {0};
signals:
    void resultChanged(QString result);

protected:
    void lowConnect(QString ip, int port, long networkID, QString certificate) override;
    bool lowCreate(bool anotherThread) override;
    bool lowRelease() override;

private:
    QJniEnvironment* env_ = nullptr;
    QJniObject* castHandle_ = nullptr;
    QString result_;
    void stackResult(QString message);

};
