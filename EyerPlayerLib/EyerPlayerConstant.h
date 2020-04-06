#ifndef EYERPLAYERCONSTANT_H
#define EYERPLAYERCONSTANT_H

#include "EyerCore/EyerCore.hpp"

namespace EyerPlayer {
    class EventTag
    {
    public:
        static const Eyer::EyerString PLAYER;
        static const Eyer::EyerString EVENT_MANAGER;
        static const Eyer::EyerString EVENT_AVREADER;
        static const Eyer::EyerString EVENT_AVDECODER;
        static const Eyer::EyerString EVENT_PLAYER_CTR;
        static const Eyer::EyerString EVENT_AUDIO_PLAYER;


        static const Eyer::EyerString FRAME_QUEUE_PLAYER_VIDEO;
        static const Eyer::EyerString FRAME_QUEUE_PLAYER_AUDIO;
        static const Eyer::EyerString FRAME_QUEUE_DECODER_VIDEO;
    };

    class EventType
    {
    public:
        static const int OPENRequest        = 101;
        static const int OPENResponse       = 201;

        static const int STOPRequest        = 102;
        static const int STOPResponse       = 202;

        static const int UPDATEUIRequest        = 103;
        static const int UPDATEUIResponse       = 203;

        static const int UPDATEAUDIORequest        = 104;
        static const int UPDATEAUDIOResponse       = 204;
    };
}

#endif // EYERPLAYERCONSTANT_H
