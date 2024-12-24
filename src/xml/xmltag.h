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

#include <string>
#include <vector>
#include <map>
#include <memory>

class XmlTag
{
protected:
    std::string m_name;
    std::vector<std::shared_ptr<XmlTag>> m_children;
    std::map<std::string, std::string> m_attributes;

public:
    explicit XmlTag(std::string name);
    virtual ~XmlTag() = default;

    [[nodiscard]] std::string Name() const;
    [[nodiscard]] virtual std::string ToXML() const;
    [[nodiscard]] std::weak_ptr<XmlTag> Parent() const;

    void AddTag(XmlTag* tag);
    void AddAttribute(const std::string& id, const std::string& value);
};

