#ifndef XMLTAG_H
#define XMLTAG_H

#include <string>
#include <vector>
#include <map>

class XmlTag
{
protected:
    std::string m_name;
    std::vector<XmlTag *> m_children;
    std::map<std::string, std::string> m_atributes;

    XmlTag *m_parent = nullptr;

public:
    XmlTag(std::string name) noexcept;
    virtual ~XmlTag() noexcept;

    std::string name() const noexcept;
    virtual std::string to_XML() const noexcept;
    XmlTag *parent() const noexcept;

    void set_parent(XmlTag *parent) noexcept;
    void add_tag(XmlTag *tag) noexcept;
    void add_attribute(const std::string& id, const std::string& value) noexcept;
};

#endif // XMLTAG_H
