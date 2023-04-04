#include "mmdvm.h"
#include <oboe/Oboe.h>

extern "C"
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT jshortArray JNICALL
Java_cz_okdmr_mmdvm_MainActivity_decode(JNIEnv *env, jobject thiz, jbyteArray a) {
    if (!globalPlayer) {
        globalPlayer = new OboePlayer();
    }
    jshortArray result;
    result = env->NewShortArray(160);
    if (result == NULL) {
        return NULL;
    }

    jbyte *byte_array = env->GetByteArrayElements(a, NULL);
    unsigned const char *char_array = (unsigned char *) byte_array;

    env->ReleaseByteArrayElements(a, byte_array, 0);

    short* decoded = globalPlayer->decodeAmbeSamples(char_array);


    int i;
    jshort fill[160];
    for (i = 0; i < 160; i++) {
        fill[i] = decoded[i];
    }

    env->SetShortArrayRegion(result, 0, 160, fill);

    return result;


}