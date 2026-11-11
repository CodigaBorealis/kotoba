#pragma once
#include "Kotoba/Core/Concepts.hpp"
#include "Kotoba/Audio/Types.hpp"
 
namespace Kotoba{

    /*
    *Represents a component that can have an audio resource
    */

    struct AudioComponent{

        constexpr AudioComponent() = default;
            
        u64 resourceID{0};

        bool shouldPlay{true};
        bool looping{false};
        float volume{1.0f};

        bool playRequested{true};
    };   

    /*
    *Represents a component that can control the playback state
    */

    struct AudioPlaybackComponent{

        PlaybackState state{PlaybackState::Stopped};
    };

    /*
    *Represents a component that can control the volume of an audio component
    */

    struct AudioVolumeComponent{

        f32 volume{1};
    };
    /*
    *Represents a component that can control the pitch of an audio component
    */

    struct AudioPitchComponent{

        f32 pitch{1};
    };

    /*
    *Represents a component that can loop an audio component
    */

    struct AudioLoopComponent{

        bool looping{false};
    };

    /*
    *Represents a component that can control the paning of an audio component
    */

    struct AudioPanComponent{

        bool looping{false};
    };
    template<> inline constexpr bool IsComponent<AudioComponent> = true;
    template<> inline constexpr bool IsComponent<AudioPlaybackComponent> = true;
    template<> inline constexpr bool IsComponent<AudioVolumeComponent> = true;
    template<> inline constexpr bool IsComponent<AudioPitchComponent> = true;
    template<> inline constexpr bool IsComponent<AudioLoopComponent> = true;

}