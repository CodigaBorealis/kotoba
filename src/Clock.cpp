#include "Kotoba/Clock/Clock.hpp"
#include "Kotoba/Core/Raylib.hpp"
#include "Kotoba/Core/Exception.hpp"
#include "Kotoba/Core/Types.hpp"
#include <cmath>

namespace Kotoba{

    void Clock::tick(){

        const f32 tick = ::GetFrameTime();

        dTime = Seconds{tick * rate};
        eTime += dTime;

        unscaledDTime = Seconds{tick};
        unscaledETime += unscaledDTime;
    }

    Seconds Clock::deltaTime() const{

        return dTime;
    };

    Seconds Clock::elapsedTime() const{

        return eTime;
    }

    Seconds Clock::unscaledDeltaTime() const{

        return unscaledDTime;
    }

    Seconds Clock::unscaledElapsedTime() const{

        return unscaledETime;
    }

    void Clock::setTimeScale(f32 rate){

        if(!std::isfinite(rate)) throw TimeException("Time scale must be a finite number", ErrorCode::InvalidArgument);
        
        if(rate < 0.0f) throw TimeException("Time scale must be >= 0.0", ErrorCode::InvalidArgument);

        this->rate = rate;
    }
}