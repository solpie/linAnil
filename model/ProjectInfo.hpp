#pragma once

#include "string"
#include "CompositionInfo.hpp"
#include "utils/pugixml/pugixml.hpp"

#define addAttri(name, value) append_attribute(name).set_value(value)
using namespace pugi;

class ProjectInfo {
public:
    ProjectInfo() {
        comps = new vector<CompositionInfo *>;
        version = "1.0";
    }

    string version;
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
        auto *doc = new xml_document();
        xml_node rootNode = doc->append_child("linanil");
        rootNode.append_attribute("version");
        rootNode.last_attribute().set_value(version.c_str());

        //////setting
        xml_node settingNode = rootNode.append_child("setting");
        xml_node extTool = settingNode.append_child("PaintApp");
        extTool.append_attribute("name");
        extTool.last_attribute().set_value("CSP");

        extTool.append_attribute("path");
        extTool.last_attribute().set_value(
                "\"C:\\Program Files\\CELSYS\\CLIP STUDIO\\CLIP STUDIO PAINT\\CLIPStudioPaint.exe\"");
        /////Composition
        xml_node compNode = rootNode.append_child("composition");
        for (int i = 0; i < comps->size(); ++i) {
            CompositionInfo *compositionInfo = comps->at(i);
            xml_node item = compNode.append_child("compositionInfo");
            item.addAttri("name", compositionInfo->name.c_str());
            item.addAttri("framewidth", compositionInfo->frameWidth);
            item.addAttri("duration", compositionInfo->durationFrame);
            item.addAttri("framerate", compositionInfo->frameRate);
            item.addAttri("height", compositionInfo->height);
            item.addAttri("width", compositionInfo->width);

            /////trackInfo
            for (int j = 0; j < compositionInfo->getTrackInfos()->size(); ++j) {
                buildTrackInfo(compositionInfo->getTrackInfos()->at(j), item);
            }
        }
        doc->save_file("test.xml");
    }

    void buildTrackInfo(BaseTrackInfo *trackInfo, xml_node item) {
        TrackInfo *imageTrackInfo;
        AudioTrackInfo *audioTrackInfo;
        xml_node trackInfoNode = item.append_child("TrackInfo");
        trackInfoNode.addAttri("name", trackInfo->name.c_str());
        trackInfoNode.addAttri("type", trackInfo->type);
        trackInfoNode.addAttri("enable", trackInfo->enable);
        if (trackInfo->type == TrackType::Image) {
            imageTrackInfo = (TrackInfo *) trackInfo;
            trackInfoNode.addAttri("opacity", imageTrackInfo->getOpacity());
            trackInfoNode.addAttri("start", imageTrackInfo->getStartFrame());
            trackInfoNode.addAttri("end", imageTrackInfo->getEndFrame());
            for (int i = 0; i < imageTrackInfo->trackFrameInfos->size(); ++i) {
                TrackFrameInfo *trackFrameInfo = imageTrackInfo->trackFrameInfos->at(i);
                xml_node frameNode = trackInfoNode.append_child("frame");
                frameNode.addAttri("start", trackFrameInfo->getStartFrame());
                frameNode.addAttri("hold", trackFrameInfo->getHoldFrame());
            }
        }
        else if (trackInfo->type == TrackType::Audio) {
            audioTrackInfo = (AudioTrackInfo *) trackInfo;
        }
    }
};
