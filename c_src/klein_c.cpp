#include "klein.h"

#include <klein/klein.hpp>

kln::plane const& convert(kln_plane const& plane)
{
    return reinterpret_cast<kln::plane const&>(plane);
}

kln_plane const& convert(kln::plane const& plane)
{
    return reinterpret_cast<kln_plane const&>(plane);
}

kln::line const& convert(kln_line const& line)
{
    return reinterpret_cast<kln::line const&>(line);
}

kln_line const& convert(kln::line const& line)
{
    return reinterpret_cast<kln_line const&>(line);
}

kln::point const& convert(kln_point const& point)
{
    return reinterpret_cast<kln::point const&>(point);
}

kln_point const& convert(kln::point const& point)
{
    return reinterpret_cast<kln_point const&>(point);
}

kln::rotor const& convert(kln_rotor const& rotor)
{
    return reinterpret_cast<kln::rotor const&>(rotor);
}

kln_rotor const& convert(kln::rotor const& rotor)
{
    return reinterpret_cast<kln_rotor const&>(rotor);
}

kln::translator const& convert(kln_translator const& translator)
{
    return reinterpret_cast<kln::translator const&>(translator);
}

kln_translator const& convert(kln::translator const& translator)
{
    return reinterpret_cast<kln_translator const&>(translator);
}

kln::motor const& convert(kln_motor const& motor)
{
    return reinterpret_cast<kln::motor const&>(motor);
}

kln_motor const& convert(kln::motor const& motor)
{
    return reinterpret_cast<kln_motor const&>(motor);
}

void kln_plane_init(kln_plane* plane, float a, float b, float c, float d)
{
    plane->p0 = kln::plane{a, b, c, d}.p0_;
}

void kln_line_init(kln_line* line, float a, float b, float c, float d, float e, float f)
{
    kln::line tmp{a, b, c, d, e, f};
    line->p1 = tmp.p1_;
    line->p2 = tmp.p2_;
}

void kln_point_init(kln_point* point, float x, float y, float z)
{
    point->p3 = kln::point{x, y, z}.p3_;
}

kln_point kln_reflect_point(kln_plane const* plane, kln_point const* point)
{
    return convert(convert(*plane)(convert(*point)));
}

kln_line kln_reflect_line(kln_plane const* plane, kln_line const* line)
{
    return convert(convert(*plane)(convert(*line)));
}

kln_plane kln_reflect_plane(kln_plane const* plane1, kln_plane const* plane2)
{
    return convert(convert(*plane1)(convert(*plane2)));
}

kln_point kln_rotate_point(kln_rotor const* rotor, kln_point const* point)
{
    return convert(convert(*rotor)(convert(*point)));
}

kln_line kln_rotate_line(kln_rotor const* rotor, kln_line const* line)
{
    return convert(convert(*rotor)(convert(*line)));
}

kln_plane kln_rotate_plane(kln_rotor const* rotor, kln_plane const* plane)
{
    return convert(convert(*rotor)(convert(*plane)));
}

kln_point
kln_translate_point(kln_translator const* translator, kln_point const* point)
{
    return convert(convert(*translator)(convert(*point)));
}

kln_line kln_translate_line(kln_translator const* translator, kln_line const* line)
{
    return convert(convert(*translator)(convert(*line)));
}

kln_plane
kln_translate_plane(kln_translator const* translator, kln_plane const* plane)
{
    return convert(convert(*translator)(convert(*plane)));
}

kln_point kln_motor_point(kln_motor const* motor, kln_point const* point)
{
    return convert(convert(*motor)(convert(*point)));
}

kln_line kln_motor_line(kln_motor const* motor, kln_line const* line)
{
    return convert(convert(*motor)(convert(*line)));
}

kln_plane kln_motor_plane(kln_motor const* motor, kln_plane const* plane)
{
    return convert(convert(*motor)(convert(*plane)));
}

kln_rotor kln_compose_rotors(kln_rotor const* rotor1, kln_rotor const* rotor2)
{
    return convert(kln::rotor{convert(*rotor2) * convert(*rotor1)});
}

kln_translator kln_compose_translators(kln_translator const* translator1,
                                       kln_translator const* translator2)
{
    return convert(kln::translator{convert(*translator2) * convert(*translator1)});
}

kln_motor kln_compose_rotor_translator(kln_rotor const* rotor,
                                       kln_translator const* translator)
{
    return convert(kln::motor{convert(*translator) * convert(*rotor)});
}

kln_motor kln_compose_translator_rotor(kln_translator const* translator,
                                       kln_rotor const* rotor)
{
    return convert(kln::motor{convert(*rotor) * convert(*translator)});
}

kln_motor kln_compose_motors(kln_motor const* motor1, kln_motor const* motor2)
{
    return convert(kln::motor{convert(*motor2) * convert(*motor1)});
}

kln_line motor_log(kln_motor const* motor)
{
    return convert(kln::line{log(convert(*motor))});
}

kln_motor line_exp(kln_line const* line)
{
    return convert(kln::motor{exp(convert(*line))});
}