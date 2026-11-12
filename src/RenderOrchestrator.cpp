#include "Kotoba/Renderer/RenderOrchestrator.hpp"
namespace Kotoba{

    void RenderOrchestrator::render(Scene& scene){

        auto commands = extractor.collectCommands(scene);

        renderer.submitBatch(commands);

        renderer.beginFrame();
        renderer.draw();
        renderer.endFrame();
    }

}