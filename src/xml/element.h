#ifndef ELEMENT_H
#define ELEMENT_H

#include "xmltag.h"

class Element : public XmlTag
{
public:
    Element(std::string element) noexcept;
    virtual ~Element() noexcept;

    virtual std::string to_XML() const noexcept override;
};

#endif // ELEMENT_H
