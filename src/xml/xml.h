#ifndef XML_H
#define XML_H

#include "xmltag.h"
#include <string>

class XML {
private:
    XmlTag *m_root = nullptr;
    XmlTag *m_last_tag = nullptr;
    std::string m_version;
    std::string m_charset;

    std::string m_doctype_name;
    std::string m_public_id;
    std::string m_sys_id;

public:
    XML() noexcept;
    ~XML() noexcept;
    
    void start_document(const std::string& version, const std::string& charset) noexcept;
    void add_doctype(const std::string& name, const std::string& public_id, const std::string& sys_id) noexcept;
    void add_attribute(const std::string& id, const std::string& value) noexcept;
    void add_element(const std::string& value) noexcept;
    void start_tag(const std::string& tag_name) noexcept;
    void end_tag() noexcept;
    void end_document() noexcept;
    const std::string content() const noexcept;
};

#endif
