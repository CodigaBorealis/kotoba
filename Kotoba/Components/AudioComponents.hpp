#pragma once
#include "Kotoba/Core/Concepts.hpp"
#include "Kotoba/Audio/Types.hpp"
 
namespace Kotoba{

    /*
    *Represents a component that can have a Music resource
    */

    struct MusicComponent{
            
        ResourceID resourceID{0};
    };   
    
    /*
    *Represents a component that can have a Sound resource
    */

    struct SoundComponent{

        ResourceID resourceID{0};
    };

    /*
    *Represents a component that can play audio
    */

    struct AudioPlaybackComponent{

        PlaybackState state{PlaybackState::Stopped};
        bool looping{false};
        bool shouldPlay{true};

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

    /*
    *Represents a component that can control the paning of an audio component
    */

    struct AudioPanComponent{

        f32 pan{0};
    };
    template<> inline constexpr bool IsComponent<MusicComponent> = true;
    template<> inline constexpr bool IsComponent<SoundComponent> = true;
    template<> inline constexpr bool IsComponent<AudioPlaybackComponent> = true;
    template<> inline constexpr bool IsComponent<AudioVolumeComponent> = true;
    template<> inline constexpr bool IsComponent<AudioPitchComponent> = true;
    template<> inline constexpr bool IsComponent<AudioPanComponent> = true;

}