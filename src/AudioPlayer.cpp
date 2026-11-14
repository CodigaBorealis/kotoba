#include "Kotoba/Audio/AudioPlayer.hpp"
#include "Kotoba/Audio/Types.hpp"
#include "Kotoba/Core/ErrorCode.hpp"
#include "Kotoba/Core/Raylib.hpp"
#include "Kotoba/Core/Exception.hpp"
#include <iterator>
#include <memory>
#include <raylib.h>
#include <vector>
#include <type_traits>

namespace Kotoba{

    struct AudioPlayer::Impl{

        std::vector<Music*> activeMusicStreams{};
        std::vector<AudioCommand> queuedCommands{};
    };

    AudioPlayer::AudioPlayer()
    :
    impl(std::make_unique<Impl>())
    {

        ::InitAudioDevice();
        
    }
    
    AudioPlayer::~AudioPlayer(){

        if(::IsAudioDeviceReady()){

            ::CloseAudioDevice();
        }
    }

    namespace{

        void play(Music* music, const AudioCommand& command, std::vector<Music*>& activeStreams){

            if(!music || !music->isValid()) throw AudioException("Cannot play music resource", ErrorCode::NullPointerException);

            auto it = std::find(activeStreams.begin(), activeStreams.end(), music);;

            if(it != activeStreams.end()) return;

            music->native().looping = command.looping;

            ::PlayMusicStream(music->native());

            activeStreams.push_back(music);
            
        }
        
        void play(Sound* sound, const AudioCommand& command){

            if(!sound || !sound->isValid()) throw AudioException("Cannot play sound resource", ErrorCode::NullPointerException);
            
            ::PlaySound(sound->native());            
        }

        void stop(Music*  music, const AudioCommand& command, std::vector<Music*>& activeStreams){

            if(!music || !music->isValid()) throw AudioException("Cannot stop music resource", ErrorCode::NullPointerException);

            ::StopMusicStream(music->native());

            std::erase(activeStreams, music);
        }
        
        void stop(Sound* sound, const AudioCommand& command){

            if(!sound) throw AudioException("Cannot stop sound resource", ErrorCode::NullPointerException);

            if(!sound->isValid()) throw AudioException("Cannot stop sound resource", ErrorCode::NullPointerException);

            ::StopSound(sound->native());
            
        }

        void volume(Music*  music, const AudioCommand& command){

            if(!music) throw AudioException("Cannot set the volume of a music resource", ErrorCode::NullPointerException);

            if(!music->isValid()) throw AudioException("Cannot set the volume of a music resource", ErrorCode::NullPointerException);

            ::SetMusicVolume(music->native(), command.volume);  
        }
        
        void volume(Sound* sound, const AudioCommand& command){

            if(!sound) throw AudioException("Cannot set the volume of a sound resource", ErrorCode::NullPointerException);

            if(!sound->isValid()) throw AudioException("Cannot set the volume of a sound resource", ErrorCode::NullPointerException);

            ::SetSoundVolume(sound->native(), command.volume);          
        }

        void pitch(Music*  music, const AudioCommand& command){

            if(!music) throw AudioException("Cannot set the pitch of a music resource", ErrorCode::NullPointerException);

            if(!music->isValid()) throw AudioException("Cannot set the pitch of a music resource", ErrorCode::NullPointerException);

            ::SetMusicPitch(music->native(), command.pitch);  
        }
        
        void pitch(Sound* sound, const AudioCommand& command){

            if(!sound) throw AudioException("Cannot set the pitch of a sound resource", ErrorCode::NullPointerException);

            if(!sound->isValid()) throw AudioException("Cannot set the pitch of a sound resource", ErrorCode::NullPointerException);

            ::SetSoundPitch(sound->native(), command.pitch);           
        }

        void pan(Music*  music, const AudioCommand& command){

            if(!music) throw AudioException("Cannot set the pan of a music resource", ErrorCode::NullPointerException);

            if(!music->isValid()) throw AudioException("Cannot set the pan of a music resource", ErrorCode::NullPointerException);

            ::SetMusicPan(music->native(), command.pan);   

        }
        
        void pan(Sound* sound, const AudioCommand& command){

            if(!sound) throw AudioException("Cannot set the pan of a sound resource", ErrorCode::NullPointerException);

            if(!sound->isValid()) throw AudioException("Cannot set the pan of a sound resource", ErrorCode::NullPointerException);

            ::SetSoundPan(sound->native(), command.pan);   
            
        }

        void executeCommand(Sound* sound, const AudioCommand& command){

            switch(command.type){

                case CommandType::Play:

                    play(sound, command);
                    break;
                
                case CommandType::Stop:

                    stop(sound, command);
                    break;
                
                case CommandType::Volume:

                    volume(sound, command);
                    break;

                case CommandType::Pitch:

                    pitch(sound, command);
                    break;

                case CommandType::Pan:

                    pan(sound, command);
                    break;
            }
        }

        void executeCommand(Music* music, const AudioCommand& command, std::vector<Music*>& activeStreams){

            switch(command.type){

                case CommandType::Play:

                    play(music, command, activeStreams);
                    break;
                
                case CommandType::Stop:

                    stop(music, command, activeStreams);
                    break;
                
                case CommandType::Volume:

                    volume(music, command);
                    break;

                case CommandType::Pitch:

                    pitch(music, command);
                    break;

                case CommandType::Pan:

                    pan(music, command);
                    break;
            }
        }
    }

    void AudioPlayer::submit(AudioCommand command){

        impl->queuedCommands.push_back(std::move(command));
    }

    void AudioPlayer::submitBatch(std::vector<AudioCommand> commands){

        impl->queuedCommands.reserve(commands.size() + impl->queuedCommands.size());

        std::move(commands.begin(), commands.end(), std::back_inserter(impl->queuedCommands));
    }


    void AudioPlayer::execute(){
        
        for(const auto& command : impl->queuedCommands){

            std::visit([&command, this](const auto& audio){

                using T = std::decay_t<decltype(audio)>;

                if constexpr(std::is_same_v<T,Sound*>){

                    executeCommand(audio, command);
                    
                }else if constexpr(std::is_same_v<T,Music*>){

                    executeCommand(audio, command, impl->activeMusicStreams);
                }

            }, command.data);
        }

        impl->queuedCommands.clear();

        for(auto it =impl->activeMusicStreams.begin(); it != impl->activeMusicStreams.end();){

            const auto* music = *it;

            if(!music || !music->isValid()){

                it = impl->activeMusicStreams.erase(it);
                continue;
            }

            ::UpdateMusicStream(music->native());

            if(!::IsMusicStreamPlaying(music->native())){

                it = impl->activeMusicStreams.erase(it);

            }else{

                ++it;
            }
        }

    }
}