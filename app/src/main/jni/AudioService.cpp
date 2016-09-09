#include "AudioService.h"
#include "common.h"
#include "FileBuf.h"

AudioService::AudioService() : wavFile(WAVFile(FileBuf::getInstance()->getSound())) {
    SLObjectItf engineObj;
    const SLInterfaceID pIDs[1] = {SL_IID_ENGINE};
    const SLboolean pIDsRequired[1] = {SL_BOOLEAN_TRUE};
    SLresult result = slCreateEngine(
            &engineObj, /*Указатель на результирующий объект*/
            0, /*Количество элементов в массиве дополнительных опций*/
            NULL, /*Массив дополнительных опций, NULL, если они Вам не нужны*/
            1, /*Количество интерфесов, которые должен будет поддерживать создаваемый объект*/
            pIDs, /*Массив ID интерфейсов*/
            pIDsRequired /*Массив флагов, указывающих, необходим ли соответствующий интерфейс. Если указано SL_TRUE, а интерфейс не поддерживается, вызов завершится неудачей, с кодом возврата SL_RESULT_FEATURE_UNSUPPORTED*/
    );
    /*Проверяем результат. Если вызов slCreateEngine завершился неуспехом – ничего не поделаешь*/
    if (result != SL_RESULT_SUCCESS) {
        LOGE("Error after slCreateEngine");
        return;
    }
    /*Вызов псевдометода. Первым аргументом всегда идет аналог this*/
    result = (*engineObj)->Realize(engineObj,
                                   SL_BOOLEAN_FALSE); //Реализуем объект  в синхронном режиме
    /*В дальнейшем я буду опускать проверки результата, дабы не загромождать код*/
    if (result != SL_RESULT_SUCCESS) {
        LOGE("Error after Realize engineObj");
        return;
    }

    SLEngineItf engine;
    result = (*engineObj)->GetInterface(
            engineObj,  /*this*/
            SL_IID_ENGINE, /*ID интерфейса*/
            &engine /*Куда поместить результат*/
    );

    SLObjectItf outputMixObj;
    const SLInterfaceID pOutputMixIDs[] = {};
    const SLboolean pOutputMixRequired[] = {};
    /*Аналогично slCreateEngine()*/
    result = (*engine)->CreateOutputMix(engine, &outputMixObj, 0, pOutputMixIDs,
                                        pOutputMixRequired);
    result = (*outputMixObj)->Realize(outputMixObj, SL_BOOLEAN_FALSE);

    /*Данные, которые необходимо передать в CreateAudioPlayer() для создания буферизованного плеера */
    SLDataLocator_AndroidSimpleBufferQueue locatorBufferQueue = {
            SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 1}; /*Один буфер в очереди*/
/*Информация, которую можно взять из заголовка wav*/
    SLDataFormat_PCM formatPCM = {
            SL_DATAFORMAT_PCM, 1, SL_SAMPLINGRATE_44_1,
            SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_CENTER, SL_BYTEORDER_LITTLEENDIAN
    };
    SLDataSource audioSrc = {&locatorBufferQueue, &formatPCM};
    SLDataLocator_OutputMix locatorOutMix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObj};
    SLDataSink audioSnk = {&locatorOutMix, NULL};
    const SLInterfaceID pIDs_new[1] = {SL_IID_BUFFERQUEUE};
    const SLboolean pIDsRequired_new[1] = {SL_BOOLEAN_TRUE};
/*Создаем плеер*/
    SLObjectItf playerObj;
    result = (*engine)->CreateAudioPlayer(engine, &playerObj, &audioSrc, &audioSnk, 1, pIDs_new,
                                          pIDsRequired_new);
    result = (*playerObj)->Realize(playerObj, SL_BOOLEAN_FALSE);

    SLPlayItf player;
    result = (*playerObj)->GetInterface(playerObj, SL_IID_PLAY, &player);
    result = (*playerObj)->GetInterface(playerObj, SL_IID_BUFFERQUEUE, &bufferQueue);
    result = (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);

    /*Очищаем очередь на случай, если там что-то было. Можно опустить, если хочется, чтобы очередь реально была очередью*/
    (*bufferQueue)->Clear(bufferQueue);
}

void AudioService::push() {
    (*bufferQueue)->Enqueue(bufferQueue, wavFile.ptr(), wavFile.length());
}
