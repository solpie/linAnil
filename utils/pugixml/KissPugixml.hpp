#pragma once
//
// Created by manoyuria on 2015/8/12.
//
#include "pugixml.hpp"

using namespace pugi;

template<typename func>

void forChild(xml_node node, const char *childName, func &&f) {
    for (xml_node childNode = node.child(childName); childNode; childNode = childNode.next_sibling(childName))
        f(childNode);
}

template<typename value>

void addAttr(xml_node node, const char *key, value &&v) {
    node.append_attribute(key).set_value(v);
}
