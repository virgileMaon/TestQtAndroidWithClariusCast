#include "castbridgeandroid.h"

#include <QDebug>
#include <QtCore/private/qandroidextras_p.h>
#include <QtCore/private/qjnihelpers_p.h>
#include <QJniEnvironment>
CastBridgeAndroid::CastBridgeAndroid(QObject *parent)
    : CastBridge{parent}
{
    env_ = new QJniEnvironment();
}
CastBridgeAndroid::~CastBridgeAndroid() {
    if (castHandle_) delete castHandle_;
    delete env_;
}

bool CastBridgeAndroid::lowCreate(bool anotherThread) {
    qDebug()<<">>cast.create " << (anotherThread ? "from another thread" : "from same thread");
    if (!castHandle_) {
        jclass javaClass = env_->findClass("test/cast/CastWrapper");
        if (javaClass == NULL) {
            qWarning() << "WARNING: Failed to find class "
                                  "test/cast/Test";
            return false;
        }
        castHandle_ = new QJniObject(javaClass,"(Z)V", anotherThread);
    }
    QJniObject ctx = QNativeInterface::QAndroidApplication::context();

    auto succeeded = castHandle_->callMethod<jboolean>("createCast",
                                 "(Landroid/content/Context;)Z",
                                 ctx.object());

    qDebug()<<"<<cast.create "<<succeeded;
    return succeeded;
}
bool CastBridgeAndroid::lowRelease() {
    if (!castHandle_) return false;
    qDebug()<<">>cast.release";

    auto succeeded = castHandle_->callMethod<jboolean>("releaseCast",
                                 "()Z");

    delete castHandle_;
    castHandle_ = nullptr;
    qDebug()<<"<<cast.release "<<succeeded;
    return succeeded;
}
