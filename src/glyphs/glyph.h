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
#ifndef GLYPH_H
#define GLYPH_H

#include <vector>

class Html;
class Context;

class Glyph
{
private:
    std::vector<Glyph *> m_childs;

protected:
    Context *m_context;
    Glyph *m_last_glyph;

public:
    Glyph();
    virtual ~Glyph();
    void add_child(Glyph *glyph);
    void execute(Html *document, Context *context);

    virtual void do_glyph(Html *);
    virtual void start_glyph(Html *);
    virtual void end_glyph(Html *);

    void set_last(Glyph *glyph);
};

#endif
