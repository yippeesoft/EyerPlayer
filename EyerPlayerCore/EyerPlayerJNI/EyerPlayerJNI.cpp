#include "com_eyer_eyerplayer_EyerPlayerJNI.h"

#include "EyerPlayer/EyerPlayer.hpp"
#include "JniUtil.h"

#include "EyerJNI/EyerJNIEnvManager.h"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    Eyer::EyerJNIEnvManager::jvm = vm;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        EyerLog("JavaVM GetEnv Fail\n");
        return -1;
    }


    // 初始化 MediaCodec 的 class loader
    jclass eyerMediaCodec_ClassLoaderClass = env->FindClass("com/eyer/eyerplayer/codec/EyerMediaCodec");
    if(eyerMediaCodec_ClassLoaderClass == nullptr){
        EyerLog("FFFFF Find EyerMediaCodec Class Fail\n");
    }

    jmethodID eyerMediaCodec_InitMethodId = env->GetMethodID(eyerMediaCodec_ClassLoaderClass, "<init>", "()V");
    if(eyerMediaCodec_InitMethodId == nullptr){
        EyerLog("FFFFF GetMethodID Fail\n");
    }

    jobject eyerMediaCodec = env->NewObject(eyerMediaCodec_ClassLoaderClass, eyerMediaCodec_InitMethodId);
    if(eyerMediaCodec == nullptr){
        EyerLog("FFFFF NewObject Fail\n");
    }

    Eyer::EyerJNIEnvManager::eyerMediaCodec_ClassLoader = env->NewGlobalRef(eyerMediaCodec);

    env->DeleteLocalRef(eyerMediaCodec_ClassLoaderClass);
    env->DeleteLocalRef(eyerMediaCodec);



    EyerLog("JavaVM GetEnv Success\n");
    return JNI_VERSION_1_6;
}

JNIEXPORT jlong JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1init
(JNIEnv * env, jclass)
{
    EyerPlayer::EyerPlayer * player = new EyerPlayer::EyerPlayer();
    return (jlong)player;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1uninit
(JNIEnv *, jclass, jlong playerJNI)
{
    EyerPlayer::EyerPlayer * player = (EyerPlayer::EyerPlayer *)playerJNI;
    delete player;
    return 0;
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1open
(JNIEnv * env, jclass, jlong playerJNI, jstring urlJNI)
{
    char * url = jstringtochar(env, urlJNI);
    EyerPlayer::EyerPlayer * player = (EyerPlayer::EyerPlayer *)playerJNI;
    int ret = player->Open(url);
    free(url);
    return ret;
}


JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1set_1gl_1ctx
(JNIEnv *, jclass, jlong playerJNI, jlong glCtxJNI)
{
    EyerPlayer::EyerPlayer * player = (EyerPlayer::EyerPlayer *)playerJNI;
    Eyer::EyerGLContextThread * glContextThread = (Eyer::EyerGLContextThread *)glCtxJNI;

    return player->BindGLContext(glContextThread);
}

JNIEXPORT jint JNICALL Java_com_eyer_eyerplayer_EyerPlayerJNI_player_1unset_1gl_1ctx
(JNIEnv *, jclass, jlong playerJNI)
{
    EyerPlayer::EyerPlayer * player = (EyerPlayer::EyerPlayer *)playerJNI;

    return player->UnBindGLContext();
}