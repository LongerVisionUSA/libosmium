#ifndef OSMIUM_OSM_LOCATION_HPP
#define OSMIUM_OSM_LOCATION_HPP

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

#include <cmath>
#include <cstdint>
#include <limits>

#include <boost/operators.hpp>

namespace osmium {

    constexpr int coordinate_precision = 10000000;

    namespace {

        inline int32_t double_to_fix(double c) {
            return round(c * coordinate_precision);
        }

        inline constexpr double fix_to_double(int32_t c) {
            return static_cast<double>(c) / coordinate_precision;
        }

    }

    /**
     * Locations define a place on earth.
     *
     * Locations are stored in 32 bit integers for the x and y
     * coordinates, respectively. This gives you an accuracy of a few
     * centimeters, good enough for OSM use. (The main OSM database
     * uses the same scheme.)
     *
     * An undefined (invalid) Location can be created by calling the
     * constructor without parameters.
     *
     * Coordinates are never checked on whether they are inside bounds.
     */
    class Location : boost::totally_ordered<Location> {

        int32_t m_x;
        int32_t m_y;

    public:

        /// this value is used for a coordinate to mark it as invalid or undefined
        static constexpr int32_t invalid_coordinate = std::numeric_limits<int32_t>::max();

        /**
         * Create undefined Location.
         */
        explicit constexpr Location() :
            m_x(invalid_coordinate),
            m_y(invalid_coordinate) {
        }

        constexpr Location(int32_t x, int32_t y) :
            m_x(x),
            m_y(y) {
        }

        constexpr Location(int64_t x, int64_t y) :
            m_x(x),
            m_y(y) {
        }

        Location(double lon, double lat) :
            m_x(double_to_fix(lon)),
            m_y(double_to_fix(lat)) {
        }

        explicit operator bool() const noexcept {
            return m_x != invalid_coordinate && m_y != invalid_coordinate;
        }

        bool valid() const noexcept {
            return m_x >= -180 * coordinate_precision
                && m_x <=  180 * coordinate_precision
                && m_y >=  -90 * coordinate_precision
                && m_y <=   90 * coordinate_precision;
        }

        constexpr int32_t x() const {
            return m_x;
        }

        constexpr int32_t y() const {
            return m_y;
        }

        Location& x(int32_t x) {
            m_x = x;
            return *this;
        }

        Location& y(int32_t y) {
            m_y = y;
            return *this;
        }

        constexpr double lon() const {
            return fix_to_double(m_x);
        }

        constexpr double lat() const {
            return fix_to_double(m_y);
        }

        Location& lon(double lon) {
            m_x = double_to_fix(lon);
            return *this;
        }

        Location& lat(double lat) {
            m_y = double_to_fix(lat);
            return *this;
        }

    };

    /**
     * Locations are equal if both coordinates are equal.
     */
    inline constexpr bool operator==(const Location& lhs, const Location& rhs) {
        return lhs.x() == rhs.x() && lhs.y() == rhs.y();
    }

    /**
     * Compare two locations by comparing first the x and then the
     * y coordinate.
     * If the location is invalid the result is undefined.
     */
    inline constexpr bool operator<(const Location& lhs, const Location& rhs) {
        return (lhs.x() == rhs.x() && lhs.y() < rhs.y()) || lhs.x() < rhs.x();
    }

} // namespace osmium

#endif // OSMIUM_OSM_LOCATION_HPP
