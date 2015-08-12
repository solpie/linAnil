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

    void open(string path) {
        auto *doc = new xml_document();//::load_file(path);
        xml_parse_result result = doc->load_file(path.c_str());
        if (result) {
            cout << "XML [" << path << "] parsed without errors, version value: [" <<
            doc->child("linanil").attribute("version").value() << "]\n\n";
        }
        else {
            std::cout << "XML [" << path << "] parsed with errors, version value: [" <<
            doc->child("linanil").attribute("version").value() << "]\n";
            std::cout << "Error description: " << result.description() << "\n";
            std::cout << "Error offset: " << result.offset << " (error at [..." << (result.offset) << "]\n\n";
        }
        xml_node linanilNode = doc->child("linanil");


        xml_node settingNode = linanilNode.child("setting");
        for (xml_node node = settingNode.child("PaintApp"); node; node = node.next_sibling("PaintApp")) {
            cout << node.first_attribute().name() << node.first_attribute().value() << endl;
        }

        xml_node compNode = linanilNode.child("composition");
        for (xml_node node = compNode.child("compositionInfo"); node; node = node.next_sibling("compositionInfo")) {
            cout << node.first_attribute().name() << node.first_attribute().value() << endl;
//            CompositionInfo *comp = projInfo->newComposition("comp1", 1280, 720, 24, 300);

            CompositionInfo *compositionInfo = newComposition(node.attribute("name").value(),
                                                              node.attribute("width").as_int(),
                                                              node.attribute("height").as_int(),
                                                              node.attribute("framerate").as_int(),
                                                              node.attribute("duration").as_int()
            );

            for (xml_node trackInfoNode = node.child("TrackInfo");
                 trackInfoNode; trackInfoNode = trackInfoNode.next_sibling("TrackInfo")) {
                int trackInfoType = trackInfoNode.attribute("type").as_int();
                string trackName = trackInfoNode.attribute("name").value();

                if (trackInfoType == TrackType::Image) {
                    TrackInfo *trackInfo = new TrackInfo(trackName);
                    trackInfo->name = trackInfoNode.attribute("name").value();
                    trackInfo->enable = trackInfoNode.attribute("enable").as_bool();
                    trackInfo->setOpacity(trackInfoNode.attribute("opacity").as_double());
                    trackInfo->path = trackInfoNode.attribute("path").value();
                    compositionInfo->getTrackInfos()->push_back(trackInfo);
                    readTrackInfo(trackInfoNode, trackInfo);
                    BaseEvent *e = new BaseEvent;
                    e->payload = trackInfo;
                    Evt_ins.disEvent(TrackModelEvent::NEW_TRACK, e);
                }
                else if (trackInfoType == TrackType::Audio) {
                    AudioTrackInfo *audioTrackInfo = new AudioTrackInfo(trackName);
                    compositionInfo->getTrackInfos()->push_back(audioTrackInfo);
                }

            }
        }
    }

    void readTrackInfo(xml_node trackInfoNode, TrackInfo *trackInfo) {
        TrackFrameInfo *pre = nullptr;
        for (xml_node node = trackInfoNode.child("frame"); node;
             node = trackInfoNode.next_sibling("frame")) {
            TrackFrameInfo *trackFrameInfo = new TrackFrameInfo;
            ImageInfo *imageInfo = ImageLoader()._().load(trackInfo->path + node.attribute("filename").value());
            imageInfo->filename = node.attribute("filename").value();
            trackFrameInfo->imageInfo = imageInfo;
            pre = trackFrameInfo->setPre(pre);
            if (!trackInfo->getHeadTrackFrameInfo())
                trackInfo->setHead(trackFrameInfo);
            trackFrameInfo->setStartFrame(node.attribute("start").as_int());
            trackFrameInfo->setHoldFrame(node.attribute("hold").as_int());
            trackInfo->trackFrameInfos->push_back(trackFrameInfo);
        }
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
        doc->save_file("c:\\test.xml");
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
            trackInfoNode.addAttri("path", imageTrackInfo->path.c_str());
            for (int i = 0; i < imageTrackInfo->trackFrameInfos->size(); ++i) {
                TrackFrameInfo *trackFrameInfo = imageTrackInfo->trackFrameInfos->at(i);
                xml_node frameNode = trackInfoNode.append_child("frame");
                frameNode.addAttri("start", trackFrameInfo->getStartFrame());
                frameNode.addAttri("hold", trackFrameInfo->getHoldFrame());
                frameNode.addAttri("filename", trackFrameInfo->imageInfo->filename.c_str());
            }
        }
        else if (trackInfo->type == TrackType::Audio) {
            audioTrackInfo = (AudioTrackInfo *) trackInfo;
        }
    }
};
