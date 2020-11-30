Klein is header only, so you may use it by adding the contents of the `public`
directory to your include path. If you use [cmake](https://cmake.org/), you
may opt to link the `klein` target interface. If you have CMake 3.15 or later,
you can use the following snippet to easily fetch Klein into your build tree:

```cmake
include(FetchContent)

# This tracks the latest commit on the master branch of the Klein
# repository. Instead of `origin/master`, you can specify a specific
# commit hash or tag.
FetchContent_Declare(
    klein
    GIT_REPOSITORY https://github.com/jeremyong/Klein.git
    GIT_TAG origin/master
)
FetchContent_MakeAvailable(klein)

# Now, you can use target_link_libraries(your_lib PUBLIC klein::klein)
# If you can target SSE4.1 (~97% market penetration), you can link against
# the target klein::klein_sse42 instead.
```

The primary "catch-all" header provided can be included using `#include <klein/klein.hpp>`.
The `klein.hpp` header includes the following:

| File                    | Purpose                                                           |
| ----------------------- | ----------------------------------------------------------------- |
| `direction.hpp`         | Defines the `direction` class.                                    |
| `dual.hpp`              | Defines the `dual` class.                                         |
| `plane.hpp`             | Defines the `plane` class.                                        |
| `point.hpp`             | Defines the `point` class.                                        |
| `line.hpp`              | Defines the `line`, `branch`, and `ideal_line` classes.           |
| `rotor.hpp`             | Defines the `rotor` class.                                        |
| `translator.hpp`        | Defines the `translator` class.                                   |
| `motor.hpp`             | Defines the `motor` class.                                        |
| `geometric_product.hpp` | Defines the geometric product between all supported entities.     |
| `meet.hpp`              | Defines the exterior product between all supported entities.      |
| `join.hpp`              | Defines the regressive product between all supported entities.    |
| `inner_product.hpp`     | Defines the inner product between all supported entities.         |
| `project.hpp`           | Defines the `project` function to project between entities.       |
| `exp_log.hpp`           | Defines the `exp` and `log` functions between supported entities. |
| `util.hpp`              | Defines various mathematical constants and helper routines.       |

Here's a simple snippet to get you started:

```c++
#include <klein/klein.hpp>

// Create a rotor representing a pi/2 rotation about the z-axis
// Normalization is done automatically
rotor r{kln::pi * 0.5f, 0.f, 0.f, 1.f};

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
mat4x4 m_matrix = m.as_mat4x4();
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
    line motor_step = log(b * ~a);

    // exp(log(m)) = exp(t*log(m) + (1 - t)*log(m))
    // = exp(t*(log(m))) * exp((1 - t)*log(m))
    motor_step *= t;

    // The exponential of the step here can be cached if the blend occurs
    // with fixed steps toward the final motor. Compose the interpolated
    // result with the start motor to produce the intermediate blended
    // motor.
    return exp(motor_step) * a;
}
```
