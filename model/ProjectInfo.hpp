#pragma once

#include "string"
#include "CompositionInfo.hpp"
#include "utils/pugixml/pugixml.hpp"

class ProjectInfo {
public:
    ProjectInfo() {
        comps = new vector<CompositionInfo *>;
    }

    string name;
    vector<CompositionInfo *> *comps;

    void save(string path) {

    }

    CompositionInfo *curCompInfo = nullptr;

    CompositionInfo *newComposition(string name, int width, int height, int frameRate, int duration) {
        CompositionInfo *comp = new CompositionInfo();
        comp->name = name;
        comp->width = width;
        comp->height = height;
        comp->frameRate = frameRate;
        comp->durationFrame = duration;
        if (!curCompInfo)
            curCompInfo = comp;
        comps->push_back(comp);
        return comp;
    }

    void saveToXml() {
        auto *doc = new pugi::xml_document();
        pugi::xml_node rootNode = doc->append_child("linanil");
        rootNode.append_attribute("version");
        rootNode.last_attribute().set_value("1.0");


        doc->save_file("test.xml");
    }
};