#pragma once
#include <variant>
#include "Kotoba/Core/Resources.hpp"

namespace Kotoba{

    enum class PlaybackState{

        Stopped,
        Playing,
        Paused
    };

    enum class CommandType{

        Play,
        Stop,
        Volume,
        Pitch,
        Pan
    };

    using AudioVariant = std::variant<Music*, Sound*>;

    struct AudioCommand{

        AudioVariant data{};
        f32 volume{1};
        f32 pitch{1};
        f32 pan{0};
        PlaybackState state{PlaybackState::Stopped};
        CommandType type{CommandType::Play};
        bool looping{false};
    };

}