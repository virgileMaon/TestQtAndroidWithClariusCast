#include "castbridgeandroid.h"

#include <QDebug>

#define __ANDROID__ 1
#ifdef __ANDROID__

#include <QtCore/private/qandroidextras_p.h>

void onTestCallBack(JNIEnv*, jobject, jboolean value, jlong obj) {
     CastBridgeAndroid *instance = reinterpret_cast<CastBridgeAndroid*>(obj);
     qDebug()<<"<<callback instance " << instance;
     qDebug()<<"<<onTestCallBack c++ " << value <<", secret value : " << instance->secretValue;
}


CastBridgeAndroid::CastBridgeAndroid(QObject *parent)
    : CastBridge{parent}
{
    env_ = new QJniEnvironment();
}
CastBridgeAndroid::~CastBridgeAndroid() {

    if (castHandle_) delete castHandle_;
    delete env_;

}




void CastBridgeAndroid::lowConnect(QString ip, int port, long networkID, QString certificate)
{
    qDebug()<<"<<lowConnect ";
    stackResult("lowConnect");

    if (!castHandle_)
        lowCreate(false);
    auto jip = QJniObject::fromString(ip);
    auto jcertificate = QJniObject::fromString(certificate);

    /*
    auto succeeded = castHandle_->callMethod<jboolean>("connect",
                                                       "(Ljava/lang/String;IJLjava/lang/String;)Z", jip.object(), port, networkID, jcertificate.object());
    */

    /*
    auto callback = [](QString& data){
        qDebug()<<"<<callback " << data;
    };
    */

    JNINativeMethod methods[]{
                              { "onConnected", "(ZJ)V", reinterpret_cast<void*>(onTestCallBack) }
    };
    jclass javaClass = env_->findClass("test/cast/CastWrapper");
    qDebug()<<" sizeof(methods) " <<  sizeof(methods) << ", sizeof(methods[0])" << sizeof(methods[0]);

    const int result = env_->registerNativeMethods(javaClass, methods, 1);

    qDebug()<<"<<registerNativeMethods " << result;
    secretValue = 132;

    jlong obj = reinterpret_cast<jlong>(this);


    auto succeeded = castHandle_->callMethod<jboolean>("test","(Ljava/lang/String;IJJ)Z",jip.object(),port, networkID, obj);
    qDebug()<<"<<this " << this;
    qDebug()<<"<<succeeded " << succeeded;

    stackResult(QString("succeeded?") + QChar(succeeded));

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

#else

CastBridgeAndroid::CastBridgeAndroid(QObject *parent)
    : CastBridge{parent}
{

}
CastBridgeAndroid::~CastBridgeAndroid() {



}

void CastBridgeAndroid::lowConnect(QString ip, int port, long networkID, QString certificate)
{
    qDebug()<<"<<lowConnect " << result_;
    stackResult("lowConnect");
}

bool CastBridgeAndroid::lowCreate(bool anotherThread) {
    return false;
}
bool CastBridgeAndroid::lowRelease() {
    return false;
}

#endif
void CastBridgeAndroid::stackResult(QString message){
    result_ = message + "\n" + result_;
    emit resultChanged(result_);
}
