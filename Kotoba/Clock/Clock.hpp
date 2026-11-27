#pragma once
#include "Kotoba/Core/Types.hpp"
namespace Kotoba{

    class Clock{

        public:

        Seconds deltaTime() const;
        Seconds elapsedTime() const;
        Seconds unscaledDeltaTime() const;
        Seconds unscaledElapsedTime() const;

        void setTimeScale(f32 rate);

        private:

        friend class Engine;
        
        void tick();

        Seconds dTime{0.0f};
        Seconds eTime{0.0f};
        Seconds unscaledDTime{0.0f};
        Seconds unscaledETime{0.0f};

        f32 rate{1.0};
    };

}