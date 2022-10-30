#pragma once

#include <QObject>

class CastBridge : public QObject
{
    Q_OBJECT
public:
    explicit CastBridge(QObject *parent = nullptr);

public slots:

    bool create(bool anotherThread);
    bool release();

protected:

    virtual bool lowCreate(bool anotherThread) = 0;
    virtual bool lowRelease() = 0;

};
