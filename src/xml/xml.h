/*
 * PDF Tools.
 * Copyright (C) 2012-2016 Leonardo Alves da Costa
 * mailto:leonhad AT gmail DOT com
 *
 * PDF Tools is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * PDF Tools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#pragma once

#include "xmltag.h"
#include <string>

class XML
{
    std::shared_ptr<XmlTag> m_root;
    std::vector<XmlTag *> m_last_tag;

    std::string m_version;
    std::string m_charset;

    std::string m_doctype_name;
    std::string m_public_id;
    std::string m_sys_id;

public:
    XML() = default;
    ~XML() = default;

    void StartDocument(const std::string& version, const std::string& charset);
    void SetDoctype(const std::string& name, const std::string& public_id, const std::string& sys_id);
    void AddAttribute(const std::string& id, const std::string& value) const;
    void AddElement(const std::string& value) const;
    void StartTag(const std::string& tag_name);
    void EndTag();
    void EndDocument();

    [[nodiscard]] std::string Content() const;
};
