/*
 * PDF Tools.
 * Copyright (C) 2012-2016 Leonardo Alves da Costa
 * mailto:leonhad AT gmail DOT com
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#ifndef GENERICEXCEPTION_H
#define GENERICEXCEPTION_H

#include <stdexcept>
#include <string>

class GenericException : public std::exception
{
private:
    const std::string m_msg;

public:
    GenericException(std::string msg) noexcept;
    GenericException(GenericException &&ex) noexcept;
    virtual ~GenericException() noexcept = default;

    virtual const char* what() const noexcept override;
};

#endif
