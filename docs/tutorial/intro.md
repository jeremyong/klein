!!! danger

    You are currently reading a DRAFT that is available publicly to facilitate collaboration

<script src="../../js/tutorial.js"></script>

This guide is meant to be a gentle intro to Projective Geometric Algebra,
also referred to as $\mathbf{P}(\mathbb{R}^*_{3, 0, 1})$. It assumes no
knowledge of quaternions and dual-quaternions, but if you have some familiarity
of either, you may find yourself armed with a new appreciation for them. Also not assumed
is any knowledge of abstract algebra, or any specific algebra closely related to Geometric
Algebra (e.g. exterior algebra, Clifford Algebra, etc.).

The emphasis first is on just getting familiarity with the notation and the various
operations and what they do. The [references](../../references) page on the left contains
some excellent references if you prefer a bottom up approach. Here though, the goal will
be to build your intuition primarily through examples, and then introduce the formalism
afterwards.

!!! tip

    Grab a pen and paper! You are expected to work out a number of expressions by hand
    and _see_ for yourself that the formulae behave as advertised. Further, drawing pictures
    is _very_ important to maintain the linkage between the algebra and the geometry.

We're going to go straight to 3D, so hang on tight. Let's start with three perfectly
ordinary basis vectors, $\ee_1$, $\ee_2$ and $\ee_3$. Now, normally when we think about
vectors, we imagine that they have some length and direction. In this case, let's have
$\ee_1$ point in the x-direction, $\ee_2$ point in the y-direction, $\ee_3$ point in the
z-direction, and give all of them unit length. Each one of these basis vectors can be
scaled by a weight, and we can take linear combinations of them to create any vector
in our 3D space. So far, everything behaves just like your good ol' 3D vector space.

Now, let's pause and consider for a moment what our vector space might be lacking. With
vectors alone, we can certainly come up with ways to represent all sorts of things.
Sometimes, vectors are arrows from the origin. Other times, we use vectors to mean the
point terminated at by that arrow. Still other times, a vector is used to represent a
plane through the origin by encoding the normal to the plane. In a way, vectors are
somewhat encumbered due to the need to represent _all_ the various entities in geometry
one way or another. But even if we try, we'll find that there are still aspects of geometry
that we can't reasonably or easily represent with vectors. For example, what if the
plane didn't go through the origin? I suppose we could use two vectors, one for the normal,
and one to describe a point in the plane. What about a rotation? Maybe we use a vector
for the axis, and the length includes the angle. Translations? Maybe the vector points in the
direction of the translation and the length encodes the displacement. Do you see
an issue with the way things are going with this thought exercise? All of these
interpretations of what a "vector" is are not mutually compatible with one another! We
certainly can't add a vector intended to be used as a rotation axis and a vector intended
to be used as a plane normal and expect to have a consistent interpretation of the result.
All of them need to be treated distinctly and live "in their own space" as it were, with
very delicate code to keep the invisible boundaries between them uncrossed.

Needless to say, mathematically, the situation described above leaves much to be desired.
What we'd like is an algebra (aka the Geometric Algebra) that could describe all the entities
we need (points, lines, planes, rotations, translations, to name a few) in a _unifying_
framework glued by an operation which has a sensible meaning when its operands are any
of the listed entities (aka the geometric product). To make this a reality though, we're
going to need to move past our vector space and limited set of operations to an algebra
that is much richer. This algebra (the Geometric Algebra) will have more operations than
you're used to, and more "things" than you're used to, but that's to be expected. After all,
geometry is far richer than just arrows emanating from the origin. Embracing the additional
structure is in some sense, akin to embracing the reality that is geometry itself, and
acknowledge that the algebra is going to need to play some catch up to describe the
geometry more aptly. So, then, aside from vectors, what else do we need? In the next
section, we'll describe the exterior algebra as a stepping stone to geometric algebra,
so see you there!
