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

#include <memory>
#include <vector>
#include <string>

class Outline
{
    std::vector<std::shared_ptr<Outline>> m_children;
    std::string m_title;
    int m_id;
    int m_generation;
    double m_x;
    double m_y;

public:
    Outline();
    ~Outline() = default;

    void AddChild(const std::shared_ptr<Outline>& child);
    void SetDestination(int id, int generation);
    void SetLocation(double x, double y);
    void SetTitle(const std::string& title);

    [[nodiscard]] int Id() const;
    [[nodiscard]] int Generation() const;
    const std::string& Title();

    [[nodiscard]] size_t Size() const;
    std::shared_ptr<Outline> Child(size_t index);
};
