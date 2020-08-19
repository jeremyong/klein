# Basic Skeletal Animation with Geometric Algebra

## Intro

One of the most direct applications of Geometric Algebra is to model a hierarchy of kinematic
chains, also referred to as a skeleton. Most tutorials and material you'll find in books and online
for this subject matter will be expressed in terms of the quaternion and dual-quaternion algebra. So
here, let's break down how we might model a skeleton and its
animation data with Geometric Algebra with simple code snippets using [Klein](https://www.github.com/jeremyong/klein).

## Data Modeling

First, let's model the data in a `joint` structure. A joint is an individually controllable set of degrees of freedom in our
skeleton (your elbow or shoulder is a good example), and we'll assume for the moment that all joints
in our skeleton can rotate the attached bone but not extend it or twist it in place (these are known
as "prismatic" and "cylindrical joints" respectively).

```c++
struct joint
{
    kln::motor  inv_bind_pose;
    uint8_t     parent_offset;
    uint8_t     group_size;
};
```

??? info "Joints! Not Bones!"

    Often in the industry, you may hear people say "bones" but this is honestly a misnomer. The transforms applied during animation act on joints, and the bones are just occupying the space between the joints as it were.

Typically, when an animator rigs a character, it's done when the character is positioned in what is
known as a "bind pose" or "T-pose." After all, associating vertices of a skinned mesh with nearby
joints isn't very practical if all the joints are collapsed to the origin.
As a result, it's common to cache on the joint itself, a means to transform the joint out of the bind
pose. In our case, we'll use a motor called the `inv_bind_pose`.

!!! note "A familiar face rocking the T-pose"

    <figure style="text-align:center">
        <img src="../../img/tpose.png" style="width:50%;height:50%" alt="T-Pose">
    </figure>

!!! tip "What are motors again?"

    If you're used to working primarily with matrices, quaternions, and dual quaternions
    don't be too put off by the terminology. A _motor_ is isomorphic to the dual quaternions
    but embedded in a "fuller" algebra with a richer structure. In practice, anywhere you
    would have needed a rotation plus a translation, or a dual quaternion, a motor is often
    a suitable choice.

    If you have rotation data and translation data from an external data source, you can easily convert it to a motor by constructing a [rotor](http://localhost:8000/api/kln_rotor/#structkln_1_1rotor) and a [translator](http://localhost:8000/api/kln_translator/#structkln_1_1translator) and taking the product to produce a [motor](http://localhost:8000/api/kln_motor/).

As we mentioned, joints are part of
a skeletal hierarchy, so we need a way to reference the parent joint. The representation I prefer is
to store a negative offset to the parent joint, so given a joint `j`, its parent would be `*(&j - parent_offset)`. We can easily identify the root bone as having an offset of zero when encoded this
way. Another trick used here is to use the additional padding we have left in the structure to store
the size of the joint's "group" which includes itself and all of its children. A joint that is a
leaf of the skeletal hierarchy will have a `group_size` of 1.

The joints themselves reside in a skeleton, so let's just use the simplest arrangement we can think of.

```c++
struct skeleton
{
    joint*       joints;
    char const** joint_names;
    uint16_t     size;
};
```

Here, joints are stored on the skeleton as a single allocation with `size` elements. Its common to
refer to joints by name for both debugging and authorship, but since the joint names aren't needed
at runtime, we'll store them in a separately allocated array.

Now, all we've done is established a nice representation of the skeletal hierarchy, but we haven't
done any animation yet! To do this, we're going to need to store a sequence of _poses_ (also known
as an animation clip). Each pose
will encode a transform for every joint in our skeleton. Then, by interpolating from pose to pose,
we'll have our first rudimentary animation system. Here's what our `pose` structure could be modeled
as:

```c++
struct pose
{
    kln::motor* joint_poses; // Array of poses for each joint
    // NOTE: some engines allow animators to include scale data with each joint
    // pose, but we'll ignore that for the time being.
};

struct clip
{
    pose*    poses;        // Array of poses
    uint16_t size;         // Number of poses in the animation clip
    uint16_t timestamps;   // Array of timestamps for each skeletal pose
    uint32_t timestamp_us; // Conversion from timestamp to microseconds
};
```

Again, we use the `kln::motor` to model the position of a joint. Typically, the rotation/translation
of each joint in a pose is encoded _relative to the parent joint_. Why? Because the relative
encoding allows us to mix and match animations on different parts of the skeleton, or perturb
various joint transforms depending on gameplay. For example, suppose we want to allow a character to
play its reload animation, while adding an additional twist at the hip as the player turns the
camera. This type of emergent pose is much easier to tackle when we can use the joint poses of the
reload animation clip directly, and simply apply the additional transform of the hip rotation.

## Forward Kinematics

Now that we have our `clip` containing an array of `pose` objects, we can now animate an instance of
our skeleton! First, let's do this without any interpolation.

At a given pose (keyframe), we start at the root joint, apply its transform to itself, then to all
its children, and then we repeat this process for all the other joints.

```c++
struct skeleton_instance
{
    // All positions here are in world coordinate space
    kln::point* joint_positions;
    kln::point  world_location;
};

void animate_keyframe(skeleton const& parent,
                      skeleton_instance& instance,
                      pose const& target)
{
    // We need to write out the final transforms to the instance of the parent
    // skeleton. The clip is the set of joint poses we need to apply.

    // First, initialize the position of every joint to the world location
    for (uint16_t i = 0; i != parent.size; ++i)
    {
        instance.joint_positions[i] = instance.world_location;
    }

    // Locomoting the world location of the instance according to the animation
    // clip is known as "root motion" animation and is a relatively common
    // technique, although it does have some tradeoffs outside the scope of this
    // tutorial.

    // For each joint, apply its corresponding joint pose motor to every
    // position in its group.
    for (uint16_t i = 0; i != parent.size; ++i)
    {
        // To apply the joint pose motor, we use the call operator. Here, we
        // use the overload that is efficient when applying the same motor to
        // a set of different positions.
        target.joint_poses[i](
            &instances.joint_positions[i], // Position input
            &instances.joint_positions[i], // Position output
            parent.joints[i].group_size);  // Count
    }
}
```

And in just a few lines of code, we have a "stepping" version of our animation system. Of course,
there's a big problem with what we have so far. To get smooth animations, we'd need more keyframes
than is reasonable. Before getting to that though, let's consider why we opted to apply a joint pose
motor $N$ times across $N$ joint positions in a single call as opposed to $N$ separate calls.
To see why, we'll need to look at the expanded motor conjugation operation $mP\widetilde{m}$ for
some motor $m$ and point $P$.

??? question "Conjugation?"

    Often, you may hear the term "conjugate" used as a noun. For example, the complex conjugate of $a + bi\mkern1mu$ is $a - bi\mkern1mu$.
    However, the term is also used frequently to mean a "sandwich multiplication" such as $pq\widetilde{p}$.
    Those familiar with quaternions will recognize this as the application of a quaternion $q$ to a point $p$.
    Conjugation is used through Geometric Algebra because the fundamental action is reflection through a plane (produced by a conjugation with a vector quantity).
    Rotations and translations are modeled as two reflections, and so their action manifests itself as a conjugation by a bivector quantity.

First, let's give variable names to all the coordinates of a point $P$:

$$P \equiv a_0\ee_{123} + a_1\ee_{021} + a_2\ee_{013} + a_3\ee_{023}$$

and the motor $m$:

$$
    \begin{aligned}
        m \equiv b_0 &+ b_1 \ee_{12} + b_2 \ee_{31} + b_3 \ee_{23} \\
        &+ c_1 \ee_{01} + c_2 \ee_{02} + c_3 \ee_{03} + c_0 \ee_{0123}
    \end{aligned}
$$

Here, we've labeled the coefficients with prefixes $b$ and $c$ to distinguish between
elements that contain the degenerate $\ee_0$ from those that don't. With these definitions,
the group action of the motor is performed via conjugation as follows:

$$
    \begin{aligned}
        mP\widetilde{m} = &a_0 (b_0^2 + b_1^2 + b_2^2 + b_3^2) \ee_{123} + \\
        \\
        + (2&a_0(b_3 c_2 - b_0 c_3 - b_2 c_1 - b_1 c_0) + \\
        2&a_2(b_1 b_2 - b_0 b_3) + \\
        2&a_3(b_0 b_2 + b_1 b_3) + \\
        &a_1(b_0^2 + b_1^2 - b_2^2 - b_3^2)) \ee_{021} + \\
        \\
        + (2&a_0(b_1 c_1 - b_0 c_2 - b_3 c_3 - b_2 c_0) + \\
         2&a_3(b_2 b_3 - b_0 b_1) + \\
         2&a_1(b_0 b_3 + b_1 b_2) + \\
         &a_2(b_0^2 + b_2^2 - b_1^2 - b_3^2)) \ee_{013} + \\
        \\
        + (2&a_0(b_2 c_3 - b_0 c_1 - b_1 c_2 - b_3 c_0) + \\
         2&a_1(b_1 b_3 - b_0 b_2) + \\
         2&a_2(b_0 b_1 +  b_2 b_3) + \\
         &a_3(b_0^2 + b_3^2 - b_1^2 - b_2^2)) \ee_{032}
    \end{aligned}
$$

Now, this is admittedly a mouthful, but if you stare at it long enough, some patterns should emerge.
First, note that the result could be factorized in such a way that $a_0$, $a_1$, $a_2$, and $a_3$
don't need to participate in the computation until the very end. This is an optimization
opportunity! All the arithmetic for the terms involving factors of $b$ and $c$ can be computed once
and reused for each point $P$.

Internally, Klein uses a template variable to determine if it should loop over an array of entities
when applying the motor and this optimization is done automatically, provided the code is written as
above. If the motor is applied to a single entity (as in `m(p)`), that will be equivalent to the
application of a dual-quaternion, so still not slow by any means, but still, the optimization
mentioned above is often too good to pass up. To see the exact SSE code where this is optimization is
made, feel free to refer to the Klein code
[here](https://github.com/jeremyong/klein/blob/master/public/klein/detail/sandwich.hpp) (search for
the function `sw312` which means "sandwich partition 3 with partitions 1 and 2").

??? question "Why did you label the motor coefficients with $b$s and $c$s"

    The answer to this is that the $c$ coefficients which were attached to basis elements with an ideal component $\ee_0$ produce a _translational_ effect. If you look at the expanded motor conjugation above and set $c_0 = c_1 = c_2 = c_3 = 0$, a number of terms drop out and you'll be left with a purely rotational action. A rotor (aka a quaternion)! In fact, the code internally shares a bunch of code this way and the extraneous code when no translation is desired is optimized out at compile time.

OK, now we have code that will apply compute the joint pose positions in a global coordinate space
given a specified pose. In practice though, an arbitrary time sample in our animation clip could be
requested. In particular, we may need to render a pose _between_ two keyframes. How should we go
about doing this?

## Normalized Interpolation

What we need is a mechanism for interpolating between two motors, say, $m_1$ and $m_2$.
There are at least two ways of performing this interpolation, a fast and moderately accurate way,
and a slower but truly accurate way. By "accurate" here, what we mean is that given a parameter $t
\in [0, 1]$ that maps $m$ to $m_1$ when $t = 0$ and maps $m$ to $m_2$ when $t = 1$,
the speed of a particle moving along the path taken by $m$ is constant.

The reason why a simple linear interpolation such as $m = m_1 (1 - t) + m_2 t$ doesn't work
is because the norm of $m$ must be $1$ to represent a rigid-body transform. It's easy to prove that
the norm of an $m$ produced this way from two normalized motors isn't normalized in general.
Let's compute the norm directly:

$$
    \begin{aligned}
        m &\equiv m_1 (1 - t) + m_2 t \\
        \\
        m\widetilde{m} &= \left(m_1 (1 - t) + m_2 t\right) \left(\widetilde{m}_1 (1 - t) + \widetilde{m}_2 t\right) \\
        &= m_1\widetilde{m}_1 (1-t)^2 + (m_2\widetilde{m}_1 + m_1\widetilde{m}_2)t(1-t) + m_2\widetilde{m}_2t \\
        &= 1 - t + t^2 + (m_2\widetilde{m}_1 + m_1\widetilde{m}_2)t(1-t)
    \end{aligned}
$$

If $t = 0$ or $t = 1$, then no interpolation happened at all, and we can see that the expression
above works out to $1$ as we'd expect.
Otherwise, we can see that the norm of a linearly interpolated motor is
$1$ if and only if $m_2\widetilde{m}_1 + m_1\widetilde{m}_2 = 1$ which is not true in general.

To correct for this, a "fast and dirty" approach is to just linearly interpolate anyways, but then
normalize the result so that we at least we're guaranteed to end up with a rigid body transform.
This is commonly referred to as `nlerp`, and a function that does this might look like the
following:

```c++
// NOTE: t is expected to be between 0 and 1
kln::motor nlerp(kln::motor const& m1, kln::motor const& m2, float t)
{
    return ((1 - t) * m1 + t * m2).normalize();
}
```

Not much to it! The main benefit of something like nlerp is that it is fast and requires no
transcendental functions except a single fast Newton-Raphson square root to normalize the result.

## The Exp and Log Map

??? warning "Math Alert"

    The contents of this section are slightly more math heavy and less programming heavy. It's useful knowledge to know, but if its a bit much and you just want a smooth constant speed interpolation, you can safely skip to the next section where we simply apply the techniques learned here in a provided API. Don't be intimidated though! I, the author, sincerely wish that the material here is presented in a way that can be grasped even if unfamiliar given a little bit of patience.

What if we wanted to maintain constant velocity around the curve? We can accomplish this by
linearizing the transition motor. Let's step back for a second. Motors _are_ the result of
an exponential map, but to see why this might be plausible, let's look at complex numbers first as
they are likely more familiar. Recall Euler's formula:

$$ e^{i\mkern1mu \theta} = \cos \theta + i\mkern1mu \sin \theta $$

The reason this works is because if we Taylor expand the LHS:

$$
e^{i\mkern1mu \theta} = 1 + i\mkern1mu\theta - \frac{\theta^2}{2} - \frac{i\mkern1mu \theta^3}{6} + \dots = \left(1 - \frac{\theta^2}{2} + \dots\right) + i\mkern1mu\left(\theta - \frac{\theta^3}{6} + \dots\right)
$$

we seemingly miraculously end up with a well defined rotation, recognized on the RHS of Euler's formula. The $i\mkern1mu$ is the key
ingredient. Because the square of $i\mkern1mu$ is $-1$, repeated multiplication of $i\mkern1mu$
doesn't grow to infinity. Instead, it "rotates" with a well-defined periodicity. Suppose I had two
rotations $r_1$ and $r_2$ as below:

$$
\begin{aligned}
    r_1 &\equiv \cos{\theta_1} + i\mkern1mu \sin{\theta_1} \\
    r_2 &\equiv \cos{\theta_2} + i\mkern1mu \sin{\theta_2}
\end{aligned}
$$

and suppose I want a rotation that takes me halfway between $r_1$ to $r_2$. How would we produce such a rotation?
The answer is obvious. We simply produce a rotation that's the average of $\theta_2$ and $\theta_1$
(assuming that we bisect the shorter arc between them). Then, the desired rotation is simply given
as

$$ \cos{\frac{\theta_1 + \theta_2}{2}} + i\mkern1mu\sin{\frac{\theta_1 + \theta_2}{2}} $$

This was easy because of the _form_ I expressed $r_1$ and $r_2$ to you. The angles we needed to
blend between was in plain sight! What if the rotation was given as $\alpha + i\mkern1mu \beta$
instead? Well, in this case, we can retrieve the angle by taking the _logarithm_ of the rotation.
Let's do this precisely. Suppose now that the rotations are given as follows:

$$
\begin{aligned}
    r_1 &\equiv \alpha_1 + i\mkern1mu \beta_1 \\
    r_2 &\equiv \alpha_2 + i\mkern1mu \beta_2
\end{aligned}
$$

and again we are asked to find the rotation $r$ halfway between $r_1$ and $r_2$. The first thing we
can realize is identify a new quantity I'm just going to call $r_\delta$. Suppose that $r_\delta$
represents the rotation halfway _between_ $r_1$ and $r_2$. That is:

$$ r_\delta^2 r_1 = r_2 $$

Then, we can multiply both sides by $r_1^\dagger$ (the complex conjugate of $r_1$) to isolate
$r_\delta$ on the LHS. Solving for $r_\delta$ can proceed as follows:

$$
\begin{aligned}
    r_\delta^2 r_1 &= r_2 \\
    r_\delta^2 r_1 r_1^\dagger &= r_2 r_1^\dagger \\
    2 \ln\left|r_\delta\right| &= \ln\left|r_2 r_1^\dagger\right| \tag{1} \\
    r_\delta &= \exp{\left(\frac{1}{2}\ln\left|r_2 r_1^\dagger\right|\right)}
\end{aligned}
$$

$$
    r_\delta r_1 = \exp{\left(\frac{1}{2}\ln\left|r_2 r_1^\dagger\right|\right)} r_1 \tag{2}
$$

In the last step, we right multiplied by $r_1$ (our starting rotation) since $r_\delta$ was the
halfway rotation _between_ $r_1$ and $r_2$. Hopefully, taking the natural logarithm of a complex
number isn't two scary. After all, we know that $r_1$ and $r_2$ have corresonding angles $\theta_1$
and $\theta_2$ (defined as the arctangents of their $\alpha$ and $\beta$ components) along with polar forms that make simplifying the RHS above easy.

$$
\begin{aligned}
    r_\delta r_1 &= \exp{\left(\frac{1}{2}\ln\left|r_2 r_1^\dagger\right|\right)} r_1 \\
    &= \exp{\left(\frac{1}{2}\ln\left|e^{i\mkern1mu \theta_2}\right|\ln\left|e^{-i\mkern1mu \theta_1}\right|\right)} r_1 \\
    &= \exp{\left(\frac{i\mkern1mu (\theta_2 - \theta_1)}{2}\right)} \exp{(i\mkern1mu \theta_1)} \\
&= \cos{\frac{\theta_1 + \theta_2}{2}} + i\mkern1mu\sin{\frac{\theta_1 + \theta_2}{2}}
\end{aligned}
$$

Different path but same result! Now, this might seem needlessly complicated to achieve what could
have been done more easily by reading off the angles, but this is only because converting complex
numbers to their polar representations is relatively easy. The angle can be determined by taking the
arctangent of the ratio of the imaginary and real component. The _most important step_ to appreciate
in the second method we used above, is the part where we divide both sides by $2$ (see the equation
marked $(1)$ above). The exponent there was our desired subdivision (we wanted
to split the arc in two, so the incremental rotation ended up being squared to take us from $r_1$ to
$r_2$). If we wanted to subdivide the arc into $n$ segments, we would have needed a power of $n$. By
taking the logarithm of both sides, we _linearized_ the rotation so that we could simply _divide_
our arc in the correct number of subdivisions.

For a motor in 3D projective geometric algebra, there **is** a closed-form solution for the
logarithm which means we can apply the same trick as above!
In fact, we technically also don't yet know how to exponentiate the logarithm of a motor, but Klein
provides implementations of both the exp and log functions taking bivectors to motors and vice versa
that we can use.
The derivation for both is a bit involved
to flesh out here, but code demonstrating how this is done can be referred to
[here](https://github.com/jeremyong/klein/blob/master/public/klein/detail/exp_log.hpp) (a fuller
derivation will be the subject of a future post).
Taking the journey above as inspiration, given two motors $m_1$ and $m_2$, we have a recipe for blending
between them smoothly. First, we multiply $m_2$ by $\widetilde{m}_1$ (the reversion operator is the
Geometric Algebra analogue of the complex conjugate). This gives us $m_2\widetilde{m}_1$ which is
the motor that takes $m_1$ to $m_2$. Next we take the logarithm of $m_2\widetilde{m}_1$, divide the
logarithm by the number of segments in our interpolation, re-exponentiate, and finally multiply by
$m_1$ to produce the interpolated result. If this was difficult to follow, feel free to refer again
to the process we went through for complex numbers above. The RHS of equation $(2)$ is _precisely_
what we want after substituting $r$s for $m$s.

!!! question "Huh? This doesn't look like the slerp I'm familiar with"

    Chances are, you're used to seeing slerp in the following form (credit: [wikipedia](https://en.wikipedia.org/wiki/Slerp)):

    $$\frac{[\sin{(1 - t)\phi]}}{\sin\phi}p_1 + \frac{\sin{[t\phi]}}{\sin\phi}p_2$$

    The derivation used with exponentials and logarithms is completely equivalent but it might take some staring (or pencil and paper) to work out why that is so. The key lies in realizing that the formula given here uses $\phi$ which is angle of the arc subtended by the two points of the arc
    (computed by the inner product $p_1 \cdot p_2$). This angle _already_ captures the information provided by the logarithm and the sine ratios after reconstitute the non-linearized map as opposed to exponentiation.

    The issue with this formula is that it doesn't generalize well to dual-quaternions or motors because the angle of the subtended arc isn't quite as easy to compute.

## Spherical Interpolation

We can now implement our motor blend function as follows:

```c++
// Blend between two motors with a parameter t in the range [0, 1]
kln::motor slerp(kln::motor const& a, kln::motor const& b, float t)
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

Voilà. A motor slerp, also known as a "dual quaternion slerp." Now, you may be thinking, isn't this
slower? The answer is yes, `log` and `exp` both require transcendentals after all. However, the
choice between slerp and nlerp isn't necessarily as cut and dry as you may think. First, higher
quality interpolation can mean that fewer keyframes are needed to produce the
desired result. Second, as is evident in the code snippet above, the logarithm (called `motor_step`)
can be _cached_ if the motors do not change from frame to frame. This effectively cuts the cost of
the slerp in half at the cost of some memory.

With this blend function, we can now sample our animation clip at any time.

```c++
// Given a skeleton, an instance of the skeleton, a clip, and a timestamp,
// transform the instance to the correct pose sampled from the clip.
void animate_sample(skeleton const& parent,
                    skeleton_instance& instance,
                    clip const& active_clip,
                    skeleton_instance const& instance,
                    int32_t timestamp_ms,
                    // scratch is a mutable pose with sufficient memory
                    // to hold our interpolated joint poses.
                    pose& scratch)
{
    pose*  previous;
    pose*  next;
    float* t;
    // This function isn't provided, but it takes a clip and timestamp
    // and produces the poses that straddle the requested time and the
    // interpolation parameter.
    query_pose_endpoints(clip, timestamp, &previous, &next, &t);

    for (uint16_t i = 0; i != parent.size; ++i)
    {
        // This could use slerp or nlerp if we wanted. A possible
        // implementation of this slerp function was given above.
        scratch.joint_poses[i] = slerp(
            previous->joint_poses[i],
            next->joint_poses[i],
            *t
        );
    }

    // Reuse our keyframe forward kinematic routine from above
    animate_keyframe(parent, instance, scratch);
}
```

Of course, there are myriad optimizations that should jump out to us from the implementation
given here, but as a starting point and considering how few lines of code we used, it's not bad in
my opinion! Example optimizations include caching the logarithms from the previous frame, or
reworking the code above so that all the temporary interpolated results do not need to reside in
memory at once. The code provided here was written thusly in the interest of remaining terse.

??? question "What about `inv_bind_pose`??"

    We defined this `kln::motor` on our `joint` and never used it. "What gives?" you might ask. Well, we didn't use it because we didn't need to transform to the joint's local coordinate space. This will be needed for skinning which will be the subject of a future tutorial. I'm impressed you noticed this (if you did)!

## Conclusion

We have developed from the ground up the barebones making of an animation library. To be anything
close to resembly a production library, it would need animation blending, vertex skinning/morphing,
animation retargeting, and a whole host of other features, but at the very least, it should have
been illustrative in the basic underpinnings of modeling kinematic motion with Geometric Algebra and
Klein. Of course, there's much more to geometry than rigid motion, so stay tuned for future
write-ups on collision detection and a whole host of other topics!

Feedback? Questions? Comments? Suggestions on what you'd like to see next? Feel free to drop by our [discord](https://discord.gg/gkbfnNy) and say hi!
