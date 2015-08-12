#pragma once
//
// Created by manoyuria on 2015/8/12.
//
#include "pugixml.hpp"

#define addAttri(name, value) append_attribute(name).set_value(value)
using namespace pugi;

template<typename func>

void forChild(xml_node node, const char *childName, func &&f) {
    for (xml_node childNode = node.child(childName); childNode; childNode = childNode.next_sibling(childName))
        f(childNode);
}
