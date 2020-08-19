// File: klein.h
// Purpose: Klein C interface, suitable for binding to other languages

#pragma once

#if __cplusplus
extern "C"
{
#endif

#include <xmmintrin.h>

    typedef struct
    {
        /// LSB (e0, e1, e2, e3) MSB
        __m128 p0;
    } kln_plane;

    /// For lines, the scalar component and pseudoscalar components should be
    /// exactly zero.
    typedef struct
    {
        /// LSB (1, e12, e31, e23) MSB
        __m128 p1;

        /// LSB (e0123, e01, e02, e03) MSB
        __m128 p2;
    } kln_line;

    /// For directions, the e123 coordinate should be exactly zero. Directions
    /// are modeled as points at infinity (i.e. ideal points)
    typedef struct
    {
        /// LSB (e123, e021, e013, e032) MSB
        __m128 p3;
    } kln_direction;

    /// The point at cartesian coordinate $(x, y, z)$ corresponds to the
    /// multivector:
    /// $$\mathbf{e}_{123} + x\mathbf{e}_{032} + y\mathbf{e}_{013} +\
    /// z\mathbf{e}_{021}$$
    typedef struct
    {
        /// LSB (e123, e021, e013, e032) MSB
        __m128 p3;
    } kln_point;

    typedef struct
    {
        /// LSB (1, e12, e31, e23) MSB
        __m128 p1;
    } kln_rotor;

    typedef struct
    {
        /// LSB (e0123, e01, e02, e03) MSB
        __m128 p2;
    } kln_translator;

    typedef struct
    {
        /// LSB (1, e12, e31, e23) MSB
        __m128 p1;

        /// LSB (e0123, e01, e02, e03) MSB
        __m128 p2;
    } kln_motor;

    // INITIALIZATION ROUTINES

    /// Initialize a given plane to the quantity $a\mathbf{e}_1 + b\mathbf{e}_2 +\
    /// c\mathbf{e}_3 + d\mathbf{e}_0$.
    void kln_plane_init(kln_plane* plane, float a, float b, float c, float d);

    /// A line is specifed by 6 coordinates which correspond to the line's
    /// [Plücker
    /// coordinates](https://en.wikipedia.org/wiki/Pl%C3%BCcker_coordinates).
    /// The coordinates specified in this way correspond to the following
    /// multivector:
    ///
    /// $$a\mathbf{e}_{01} + b\mathbf{e}_{02} + c\mathbf{e}_{03} +\
    /// d\mathbf{e}_{12} + e\mathbf{e}_{31} + f\mathbf{e}_{23}$$
    void kln_line_init(kln_line* line,
                       float a,
                       float b,
                       float c,
                       float d,
                       float e,
                       float f);

    /// Initialize a given point to the quantity $\mathbf{e}_{123} + x\mathbf{e}_{023} +\
    /// y\mathbf{e}_{031} + z\mathbf{e}_{012}$.
    void kln_point_init(kln_point* point, float x, float y, float z);

    // VARIOUS GROUP ACTIONS

    /// Reflect point through plane
    kln_point kln_reflect_point(kln_plane const* plane, kln_point const* point);

    /// Reflect line through plane
    kln_line kln_reflect_line(kln_plane const* plane, kln_line const* line);

    /// Reflect plane2 through plane1
    kln_plane kln_reflect_plane(kln_plane const* plane1, kln_plane const* plane2);

    /// Apply rotor to point
    kln_point kln_rotate_point(kln_rotor const* rotor, kln_point const* point);

    /// Apply rotor to line
    kln_line kln_rotate_line(kln_rotor const* rotor, kln_line const* line);

    /// Apply rotor to plane
    kln_plane kln_rotate_plane(kln_rotor const* rotor, kln_plane const* line);

    /// Apply a translator to a point
    kln_point kln_translate_point(kln_translator const* translator,
                                  kln_point const* point);

    /// Apply a translator to a line
    kln_line
    kln_translate_line(kln_translator const* translator, kln_line const* line);

    /// Apply a translator to a plane
    kln_plane kln_translate_plane(kln_translator const* translator,
                                  kln_plane const* plane);

    /// Apply motor to point
    kln_point kln_motor_point(kln_motor const* motor, kln_point const* point);

    /// Apply motor to line
    kln_line kln_motor_line(kln_motor const* motor, kln_line const* line);

    /// Apply motor to plane
    kln_plane kln_motor_plane(kln_motor const* motor, kln_plane const* plane);

    // GROUP ACTION COMPOSITION

    /// Compose two rotors (rotor2 * rotor1)
    kln_rotor
    kln_compose_rotors(kln_rotor const* rotor1, kln_rotor const* rotor2);

    /// Compose two translators (translator2 * translator1)
    kln_translator kln_compose_translators(kln_translator const* translator1,
                                           kln_translator const* translator2);

    /// Compose a rotor and a translator to create a motor (translator * rotor)
    kln_motor kln_compose_rotor_translator(kln_rotor const* rotor,
                                           kln_translator const* translator);

    /// Compose a translator and a rotor to create a motor (translator * rotor)
    kln_motor kln_compose_translator_rotor(kln_translator const* translator,
                                           kln_rotor const* rotor);

    /// Compose two motors (motor2 * motor1)
    kln_motor
    kln_compose_motors(kln_motor const* motor1, kln_motor const* motor2);

    // MISCELLANEOUS

    /// Motor logarithm
    kln_line motor_log(kln_motor const* motor);

    /// Bivector exponential
    kln_motor line_exp(kln_line const* line);

#if __cplusplus
}
#endif