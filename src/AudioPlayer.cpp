#include "Kotoba/Audio/AudioPlayer.hpp"
#include "Kotoba/Audio/Types.hpp"
#include "Kotoba/Core/ErrorCode.hpp"
#include "Kotoba/Core/Raylib.hpp"
#include "Kotoba/Core/Exception.hpp"
#include <iterator>
#include <raylib.h>
#include <vector>

namespace Kotoba{

    struct AudioPlayer::Impl{

        std::vector<std::shared_ptr<Music>> activeMusicStreams{};
        std::vector<AudioCommand> queuedCommands{};
    };

    AudioPlayer::AudioPlayer(){

        ::InitAudioDevice();
        
    }
    
    AudioPlayer::~AudioPlayer(){

        if(::IsAudioDeviceReady()){

            ::CloseAudioDevice();
        }
    }

    namespace{

        void play(std::shared_ptr<Music> music, const AudioCommand& command){

            if(!music) throw AudioException("Cannot play music resource", ErrorCode::NullPointerException);

            if(!music->isValid()) throw AudioException("Cannot play music resource", ErrorCode::NullPointerException);
            
            ::PlayMusicStream(music->native());
        }
        
        void play(std::shared_ptr<Sound> sound, const AudioCommand& command){

            if(!sound) throw AudioException("Cannot play sound resource", ErrorCode::NullPointerException);

            if(!sound->isValid()) throw AudioException("Cannot play sound resource", ErrorCode::NullPointerException);
            
            ::PlaySound(sound->native());
            
        }

        void stop(std::shared_ptr<Music> music, const AudioCommand& command){

            if(!music) throw AudioException("Cannot stop music resource", ErrorCode::NullPointerException);

            if(!music->isValid()) throw AudioException("Cannot stop music resource", ErrorCode::NullPointerException);

            ::StopMusicStream(music->native());
        }
        
        void stop(std::shared_ptr<Sound> sound, const AudioCommand& command){

            if(!sound) throw AudioException("Cannot stop sound resource", ErrorCode::NullPointerException);

            if(!sound->isValid()) throw AudioException("Cannot stop sound resource", ErrorCode::NullPointerException);

            ::StopSound(sound->native());
            
        }

        void volume(std::shared_ptr<Music> music, const AudioCommand& command){

            if(!music) throw AudioException("Cannot set the volume of a music resource", ErrorCode::NullPointerException);

            if(!music->isValid()) throw AudioException("Cannot set the volume of a music resource", ErrorCode::NullPointerException);

            ::SetMusicVolume(music->native(), command.volume);  
        }
        
        void volume(std::shared_ptr<Sound> sound, const AudioCommand& command){

            if(!sound) throw AudioException("Cannot set the volume of a sound resource", ErrorCode::NullPointerException);

            if(!sound->isValid()) throw AudioException("Cannot set the volume of a sound resource", ErrorCode::NullPointerException);

            ::SetSoundVolume(sound->native(), command.volume);          
        }

        void pitch(std::shared_ptr<Music> music, const AudioCommand& command){

            if(!music) throw AudioException("Cannot set the pitch of a music resource", ErrorCode::NullPointerException);

            if(!music->isValid()) throw AudioException("Cannot set the pitch of a music resource", ErrorCode::NullPointerException);

            ::SetMusicPitch(music->native(), command.pitch);  
        }
        
        void pitch(std::shared_ptr<Sound> sound, const AudioCommand& command){

            if(!sound) throw AudioException("Cannot set the pitch of a sound resource", ErrorCode::NullPointerException);

            if(!sound->isValid()) throw AudioException("Cannot set the pitch of a sound resource", ErrorCode::NullPointerException);

            ::SetSoundPitch(sound->native(), command.pitch);           
        }

        void pan(std::shared_ptr<Music> music, const AudioCommand& command){

            if(!music) throw AudioException("Cannot set the pan of a music resource", ErrorCode::NullPointerException);

            if(!music->isValid()) throw AudioException("Cannot set the pan of a music resource", ErrorCode::NullPointerException);

            ::SetMusicPan(music->native(), command.pan);   

        }
        
        void pan(std::shared_ptr<Sound> sound, const AudioCommand& command){

            if(!sound) throw AudioException("Cannot set the pan of a sound resource", ErrorCode::NullPointerException);

            if(!sound->isValid()) throw AudioException("Cannot set the pan of a sound resource", ErrorCode::NullPointerException);

            ::SetSoundPan(sound->native(), command.pan);   
            
        }

        void executeCommand(std::shared_ptr<Sound> sound, const AudioCommand& command){

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

        void executeCommand(std::shared_ptr<Music> music, const AudioCommand& command){

            switch(command.type){

                case CommandType::Play:

                    play(music, command);
                    break;
                
                case CommandType::Stop:

                    stop(music, command);
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

            std::visit([&command](const auto& audio){

                executeCommand(audio, command);

            }, command.data);
        }

        impl->queuedCommands.clear();

        for(const auto& music : impl->activeMusicStreams){

            if(!music || !music->isValid()) continue;

            ::UpdateMusicStream(music->native());
        }
    }
}