!!! danger "DRAFT"

    This case study is a WIP

One of the most direct applications of Geometric Algebra is to model a hierarchy of kinematic
chains, also referred to as a skeleton. Let's breakdown how we might model a skeleton and its
animation data with Klein.

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

![tpose](../../img/tpose.png){: style="width:50%;height:50%;text-align:center"}

!!! tip "What are motors again?"

    If you're used to working primarily with matrices, quaternions, and dual quaternions
    don't be too put off by the terminology. A _motor_ is isomorphic to the dual quaternions
    but embedded in a "fuller" algebra with a richer structure. In practice, anywhere you
    would have needed a rotation plus a translation, or a dual quaternion, a motor is often
    a suitable choice.

As we mentioned, joints are part of
a skeletal hierarchy, so we need a way to reference the parent joint. The representation I prefer is
to store a negative offset to the parent joint, so given a joint `j`, its parent would be `*(&j - parent_offset)`. We can easily identify the root bone as having an offset of zero when encoded this
way. Another trick used here is to use the additional padding we have left in the structure to store
the size of the joint's "group" which includes itself and all of its children. A joint that is a
leaf of the skeletal hierarchy will have a `group_size` of 1.

!!! todo

    Illustrate this data structure

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
        joint_positions[i] = instance.world_location;
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
than is reasonable.

// TODO: keyframe blending
