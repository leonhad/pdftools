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

#include <stdexcept>
#include <string>

/**
 * Exception used in application.
 */
class GenericException : public std::exception
{
    /**
     * The exception message.
     */
    const std::string m_msg;

public:
    /**
     * Creates a new instance.
     *
     * @param msg the exception message.
     */
    explicit GenericException(const char *msg);

    /**
     * Creates a new instance.
     *
     * @param msg the exception message.
     */
    explicit GenericException(std::string  msg);

    /**
     * Creates a new instance.
     *
     * @param ex the original exception.
     */
    GenericException(GenericException &&ex) noexcept;

    /**
     * Destroy the instance.
     */
    ~GenericException() override = default;

    /**
     * Gets the exception message.
     *
     * @return the exception message.
     */
    [[nodiscard]] const char* what() const noexcept override;
};
