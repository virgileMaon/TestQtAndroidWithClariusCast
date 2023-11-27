#pragma once

#include <QObject>

class CastBridge : public QObject
{
    Q_OBJECT
public:
    explicit CastBridge(QObject *parent = nullptr);

public slots:
    void connect(QString ip, int port, long networkID, QString certificate);
    bool create(bool anotherThread);
    bool release();

protected:
    virtual void lowConnect(QString ip, int port, long networkID, QString certificate) = 0;
    virtual bool lowCreate(bool anotherThread) = 0;
    virtual bool lowRelease() = 0;

};
