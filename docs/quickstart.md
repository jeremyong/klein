Klein is header only, so you may use it by adding the contents of the `public`
directory to your include path. If you use [cmake](https://cmake.org/), you
may opt to link the `klein` target interface.

The primary "catch-all" header provided can be included using `#include <klein/klein.hpp>`.
If you wish, individual headers in the top level `public/klein` folder may be included
to reduce the included code footprint.

The `klein.hpp` header includes the following:

- `klein/direction.hpp`
- `klein/line.hpp`
- `klein/mat4x4.hpp`
- `klein/motor.hpp`
- `klein/plane.hpp`
- `klein/point.hpp`
- `klein/rotor.hpp`
- `klein/translator.hpp`

Here's a simple snippet to get you started:

```c++
#include <klein/klein.hpp>
// Minimal headers needed for this example are:
// #include <klein/motor.hpp>
// #include <klein/point.hpp>
// #include <klein/rotor.hpp>

// Create a rotor representing a pi/2 rotation about the z-axis
// Normalization is done automatically
rotor r{M_PI * 0.5f, 0.f, 0.f, 1.f};

// Create a translator that represents a translation of 1 unit
// in the yz-direction. Normalization is done automatically.
translator t{1.f, 0.f, 1.f, 1.f};

// Create a motor that combines the action of the rotation and
// translation above.
motor m = r * t;

// Construct a point at position (1, 0, 0)
point p1{1, 0, 0};

// Apply the motor to the point. This is equivalent to the conjugation
// operator m * p1 * ~m where * is the geometric product and ~ is the
// reverse operation.
point p2 = m(p1);

// We could have also written p2 = m * p1 * ~m but this will be slower
// because the call operator eliminates some redundant or cancelled
// computation.
// point p2 = m * p1 * ~m;

// We can access the coordinates of p2 with p2.x(), p2.y(), p2.z(),
// and p2.w(), where p.2w() is the homogeneous coordinate (initialized
// to one). It is recommended to localize coordinate access in this way
// as it requires unpacking storage that may occupy an SSE register.

// Rotors and motors can produce 4x4 transformation matrices suitable
// for upload to a shader or for interoperability with code expecting
// matrices as part of its interface. The matrix returned in this way
// is a column-major matrix
mat4x4 m_matrix = m.as_matrix();
```

The spherical interpolation (aka slerp) employed to produce smooth incremental
rotations/transformations in the quaternion algebra is available in Klein
using the exp and log functions as in the snippet below.

```c++
// Blend between two motors with a parameter t in the range [0, 1]
kln::motor blend_motors(kln::motor const& a, kln::motor const& b, float t)
{
    // Starting from a, the motor needed to get to b is b * ~a.
    // To perform this motion continuously, we can take the principal
    // branch of the logarithm of b * ~a, and subdivide it before
    // re-exponentiating it to produce a motor again.

    // In practice, this should be cached whenever possible.
    line motor_step = (b * ~a).log();

    // exp(log(m)) = exp(t*log(m) + (1 - t)*log(m))
    // = exp(t*(log(m))) * exp((1 - t)*log(m))
    motor_step *= t;

    // The exponential of the step here can be cached if the blend occurs
    // with fixed steps toward the final motor. Compose the interpolated
    // result with the start motor to produce the intermediate blended
    // motor.
    return motor_step.exp() * a;
}
```