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
#ifndef PAGELABEL_H
#define PAGELABEL_H

#include <string>

/**
 * Page Type.
 */
enum page_type
{
    /**
     * Arabic type.
     */
    ARABIC,

    /**
     * Roman type in upper case.
     */
    UPCASE_ROMAN,

    /**
     * Roman in lower case.
     */
    LOWCASE_ROMAN,

    /**
     * Letters in upper case.
     */
    UPCASE_LETTERS,

    /**
     * Letters in lower case.
     */
    LOWCASE_LETTERS
};

/**
 * Stores a page label.
 */
class PageLabel
{
private:
    /**
     * The page start number.
     */
    int startNumber;

    /**
     * The page range.
     */
    int range;

    /**
     * The page type.
     */
    page_type type;

    /**
     * The label name.
     */
    std::string name;

public:
    /**
     * Creates a new page label.
     *
     * @param start the page start.
     * @param range the page range.
     * @param type the page type.
     * @param name the label name.
     */
    PageLabel(int start, int range, page_type type, std::string &name);

    /**
     * Gets the page start.
     *
     * @return the page start.
     */
    int Start();

    /**
     * Gets the page range.
     *
     * @return the page range.
     */
    int Range();

    /**
     * Gets the page type.
     *
     * @return the page type.
     */
    page_type Type();

    /**
     * Gets the page name.
     *
     * @return the page name.
     */
    std::string &Name();
};

#endif
