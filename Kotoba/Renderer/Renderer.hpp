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

        void beginFrame();
        void submit(DrawCommand command);
        void submitBatch(std::vector<DrawCommand> commands);
        void draw();
        void endFrame();

        private:

        struct Impl;
        std::unique_ptr<Impl> impl;
    
    };

}