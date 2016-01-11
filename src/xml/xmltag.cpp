#include "xmltag.h"
#include <sstream>

using namespace std;

XmlTag::XmlTag(string name) noexcept: m_name(name)
{
}

XmlTag::~XmlTag() noexcept
{
    for (XmlTag *tag : m_children) {
        delete tag;
    }
}

string XmlTag::name() const noexcept
{
    return m_name;
}

std::string XmlTag::to_XML() const noexcept
{
    stringstream buffer;
    buffer << "<" << m_name;

    for (const auto &value : m_atributes) {
        buffer << " " << value.first << "=\"" << value.second << "\"";
    }

    buffer << ">\n";

    for (XmlTag *tag : m_children) {
        buffer << tag->to_XML();
    }

    buffer << "</" << m_name << ">";
    return buffer.str();
}

XmlTag *XmlTag::parent() const noexcept
{
    return m_parent;
}

void XmlTag::set_parent(XmlTag *parent) noexcept
{
    m_parent = parent;
}

void XmlTag::add_tag(XmlTag *tag) noexcept
{
    m_children.push_back(tag);
}

void XmlTag::add_attribute(const std::string& id, const std::string& value) noexcept
{
    m_atributes[id] = value;
}
