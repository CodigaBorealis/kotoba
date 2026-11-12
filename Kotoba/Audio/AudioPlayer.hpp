#pragma once

#include "Kotoba/Audio/Types.hpp"
#include <memory>
#include <vector>
namespace Kotoba{

    class AudioPlayer{

        public:

        AudioPlayer();
        
        ~AudioPlayer();
        
        void submit(AudioCommand command);
        void submitBatch(std::vector<AudioCommand> commands);

        void execute();

        private:

        struct Impl;

        std::unique_ptr<Impl> impl;
    };

}