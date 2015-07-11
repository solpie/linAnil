#pragma once
//
// Created by manoyuria on 2015/7/11.
//

#ifndef LINANIL_VSROOT_HPP
#define LINANIL_VSROOT_HPP

#endif //LINANIL_VSROOT_HPP

#include "vs/VsObjContainer.hpp"
#include "Performance.hpp"
#include "view/TrackArea.hpp"
class VsRoot : public VsObjContainer {
public:
    VsRoot() {
        for (int i = 0; i < 12; i++) {
            char file[128];
            snprintf(file, 128, "test/thumb/image%d.jpg", i+1);
            images[i] = nvgCreateImage(VS_CONTEXT, file, 0);
            if (images[i] == 0) {
                printf("Could not load %s.\n", file);
//                return -1;
            }
        }


        perfFps = new Performance();
        perfFps->x = 5;
        perfFps->y = 5;
        perfFps->initGraph(GRAPH_RENDER_FPS, "Frame Time");
        addChild(perfFps);

        perfCpu = new Performance();
        perfCpu->x = perfFps->x + perfFps->width + 5;
        perfCpu->y = 5;
        perfCpu->initGraph(GRAPH_RENDER_MS, "CPU Time");
        addChild(perfCpu);
    }

    virtual void render() override;

private:
    Performance *perfFps;
    int images[12];
    Performance *perfCpu;
};

void VsRoot::render() {
    drawThumbnails(VS_CONTEXT, 365, 30, 160, 300, images, 12, glfwGetTime());
    VsObjContainer::render();
}
