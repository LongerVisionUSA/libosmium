#ifndef OSMIUM_OSM_BOUNDS_HPP
#define OSMIUM_OSM_BOUNDS_HPP

/*

This file is part of Osmium (http://osmcode.org/osmium).

Copyright 2013 Jochen Topf <jochen@topf.org> and others (see README).

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <osmium/osm/location.hpp>
#include <ostream>

namespace osmium {

    class Bounds {

        osmium::Location m_bottom_left;
        osmium::Location m_top_right;

    public:

        Bounds() :
            m_bottom_left(),
            m_top_right() {
        }

        /**
         * Extend the bounding box by the given location. If the location
         * is undefined, the bounding box is unchanged.
         */
        Bounds& extend(const Location& location) {
            if (location) {
                if (m_bottom_left) {
                    if (location.x() < m_bottom_left.x()) {
                        m_bottom_left.x(location.x());
                    }
                    if (location.x() > m_top_right.x()) {
                        m_top_right.x(location.x());
                    }
                    if (location.y() < m_bottom_left.y()) {
                        m_bottom_left.y(location.y());
                    }
                    if (location.y() > m_top_right.y()) {
                        m_top_right.y(location.y());
                    }
                } else {
                    m_bottom_left = location;
                    m_top_right = location;
                }
            }
            return *this;
        }

        explicit operator bool() const noexcept {
            return static_cast<bool>(m_bottom_left);
        }

        bool valid() const noexcept {
            return bottom_left().valid() && top_right().valid();
        }

        /**
         * Bottom-left location.
         */
        Location bottom_left() const {
            return m_bottom_left;
        }

        /**
         * Top-right location.
         */
        Location top_right() const {
            return m_top_right;
        }

    }; // class Bounds

} // namespace osmium

#endif // OSMIUM_OSM_BOUNDS_HPP
