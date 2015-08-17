#pragma once

#include "string"
#include "CompositionInfo.hpp"
#include "utils/pugixml/KissPugixml.hpp"
#include "events/EventDispatcher.hpp"

class ProjectInfo : public EventDispatcher {
public:
    ProjectInfo() {
        comps = new vector<CompositionInfo *>;
        version = "1.0";
    }


    string version;
    string name;
    vector<CompositionInfo *> *comps;

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
        comp->idx = comps->size();
        comps->push_back(comp);

        ActionEvent *e = new ActionEvent();
        e->type = ActionEvent::PROJECT_NEW_COMP;
        e->payload = comp;
        disEvent(e);

        return comp;
    }

    bool showCompositionInfo(int idx) {
        if (idx < comps->size()) {
            ActionEvent *e = new ActionEvent();
            e->type = ActionEvent::PROJECT_SHOW_COMP;
            e->payload = comps->at(idx);

                disEvent(e);
            return  true;
        }
        return  false;
    }

    //////////////////////////////////////// open //////////////////////////////////////
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
        forChild(compNode, "compositionInfo", [&](xml_node node) {
            cout << node.first_attribute().name() << node.first_attribute().value() << endl;
            CompositionInfo *compositionInfo = newComposition(node.attribute("name").value(),
                                                              node.attribute("width").as_int(),
                                                              node.attribute("height").as_int(),
                                                              node.attribute("framerate").as_int(),
                                                              node.attribute("duration").as_int());
            compositionInfo->frameWidth = node.attribute("framewidth").as_int();


            forChild(node, "TrackInfo", [&](xml_node trackInfoNode) {
                int trackInfoType = trackInfoNode.attribute("type").as_int();
                string trackName = trackInfoNode.attribute("name").value();

                if (trackInfoType == TrackType::Image) {
                    TrackInfo *trackInfo = compositionInfo->newTrackInfo(trackName,
                                                                         trackInfoNode.attribute("path").value());
                    trackInfo->enable = trackInfoNode.attribute("enable").as_bool();
                    trackInfo->setOpacity(trackInfoNode.attribute("opacity").as_double());

//                    TrackFrameInfo *pre = nullptr;
                    forChild(trackInfoNode, "frame", [&](xml_node node) {
                        trackInfo->newTrackFrameInfo(node.attribute("filename").value(),
                                                     trackInfo->path + node.attribute("filename").value());
                    });

                    BaseEvent *e = new BaseEvent;
                    e->payload = trackInfo;
                    e->type = TrackModelEvent::NEW_TRACK;
                    disEvent(e);
                    compositionInfo->disEvent(e);
                }
                else if (trackInfoType == TrackType::Audio) {
                    AudioTrackInfo *audioTrackInfo = new AudioTrackInfo(trackName);
                    compositionInfo->getTrackInfos()->push_back(audioTrackInfo);
                }
                compositionInfo->updateContentEndFrame();
            });
        });
    }

    ///////////////////////////////// save /////////////////////////////////////////////

    void save(string path) {
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
            addAttr(item, "name", compositionInfo->name.c_str());
            addAttr(item, "framewidth", compositionInfo->frameWidth);
            addAttr(item, "duration", compositionInfo->durationFrame);
            addAttr(item, "framerate", compositionInfo->frameRate);
            addAttr(item, "height", compositionInfo->height);
            addAttr(item, "width", compositionInfo->width);

            /////trackInfo
            for (int j = 0; j < compositionInfo->getTrackInfos()->size(); ++j) {
                buildTrackInfo(compositionInfo->getTrackInfos()->at(j), item);
            }
        }
        doc->save_file(path.c_str());
    }

    void buildTrackInfo(BaseTrackInfo *trackInfo, xml_node item) {
        TrackInfo *imageTrackInfo;
        AudioTrackInfo *audioTrackInfo;
        xml_node trackInfoNode = item.append_child("TrackInfo");
        addAttr(trackInfoNode, "name", trackInfo->name.c_str());
        addAttr(trackInfoNode, "type", trackInfo->type);
        addAttr(trackInfoNode, "enable", trackInfo->enable);
        if (trackInfo->type == TrackType::Image) {
            imageTrackInfo = (TrackInfo *) trackInfo;
            addAttr(trackInfoNode, "opacity", imageTrackInfo->getOpacity());
            addAttr(trackInfoNode, "start", imageTrackInfo->getStartFrame());
            addAttr(trackInfoNode, "end", imageTrackInfo->getEndFrame());
            addAttr(trackInfoNode, "path", imageTrackInfo->path.c_str());
            for (int i = 0; i < imageTrackInfo->trackFrameInfos->size(); ++i) {
                TrackFrameInfo *trackFrameInfo = imageTrackInfo->trackFrameInfos->at(i);
                xml_node frameNode = trackInfoNode.append_child("frame");
                addAttr(frameNode, "start", trackFrameInfo->getStartFrame());
                addAttr(frameNode, "hold", trackFrameInfo->getHoldFrame());
                addAttr(frameNode, "filename", trackFrameInfo->imageInfo->filename.c_str());
            }
        }
        else if (trackInfo->type == TrackType::Audio) {
            audioTrackInfo = (AudioTrackInfo *) trackInfo;
        }
    }
};
