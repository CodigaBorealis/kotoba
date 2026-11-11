#pragma once
#include <memory>
#include <vector>
#include "Types.hpp"

namespace Kotoba{

    struct Window;

    class Renderer{

        public:
        //Commands
/*Used somewhere else
        struct RenderOrder{
            
            RenderOrder() = default;

            constexpr RenderOrder(i32 layer, i32 Zindex, bool visible)
                :
                layer(layer),
                Zindex(Zindex),
                visible(visible)
                {}

            i32 layer{0};
            i32 Zindex{0};
            bool visible{true};
        };
*/

        Renderer(Window& window);
        ~Renderer();

        void beginFrame();//Starts the drawing process
        void submit(DrawCommand command);//Queues a draw command, must be called before the frame starts or after it ends never in between
        void submitBatch(std::vector<DrawCommand> commands);//Submit a batch of draw commands, must be called before the frame starts or after it ends never in between
        void draw();//Draws all the queued commands, commands must be regenerated every frame
        void endFrame();//Finalizes the drawing process

        private:

        struct Impl;
        std::unique_ptr<Impl> impl;
    
    };

}