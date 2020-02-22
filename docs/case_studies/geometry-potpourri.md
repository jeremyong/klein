In this miniature article, we're going to walk through a number of common geometric tasks
such as finding intersections, computing distances, performing rotations, etc. For each task, we'll
showcase not only the Klein code that would produce the desired result, but also show mathematically
how it can be computed by hand.

!!! danger

    In this article, I make very little effort to explain why an operation is defined a certain way or explain some of the deeper underlying mathematics. This article was written because it's often helpful to see how computation is done first, and perform some calculations by hande as well gain some intuition before taking a closer look at the theory.

## Multivectors

!!! info

    Klein API: [kln::entity](../../api/kln_entity)

In this section, we look at all the various operations and elements that show up in $\PGA$.
A common question that people run into when getting exposed to GA for the first time is, "why are
their so many operations?" The best answer is that, well, geometry has a lot of operations! More
than can be captured easily with just the dot product and cross product you're likely familiar with.
This section just gets you acquainted with the mechanics of $\PGA$, but to glean more geometric
intuition, _all_ the sections afteward will focus on concrete examples (plane distance to point,
meeting to points to make a line, projecting a line onto a plane, rotating a point about a line,
reflecting a point through a plane, etc). You'll find that for a bit of upfront complexity presented
here, what's gained is a satisfying degree of uniformity in all the geometry that comes later.

### PGA Basis and Geometric Product

!!! info

    Klein API: `operator*`

    Written as two elements adjacent to each other ($ab$).

Let's get used to some basis elements and operations first.
In $\mathbf{P}(\mathbb{R}^*_{3, 0, 1})$ (also known as PGA), we have four grade-1 vector basis
elements, $\ee_0$, $\ee_1$, $\ee_2$, and $\ee_3$.
Let's define the square of these vectors in the following manner.
The first element squares to $0$ ($\ee_0 \ee_0 =
0$) while the latter 3 elements square to $1$ ($\ee_1\ee_1 = \ee_2\ee_2 = \ee_3\ee_3 = 1$).
As we now immediately have a means to create $1$, we can generate all the numbers this way,
so let's declare $1$ as our grade-0 basis element.
When we write elements adjacent to one another as in $\ee_1\ee_1$, the operation being represented
here is the _geometric product_. In code, the geometric product is expressed as the multiplication
(`*`) operator. So far, we've written down what the geometric product does when the
elements multiply against themselves. Next, we need to describe what happens when we take the
geometric product between different elements.

Mixed products of the basis vectors produce the basis bivectors, which can themselves be used in
linear combinations to produce general bivectors. Bivectors that can be written as the product of
two vectors may be referred to as _blades_ or _simple bivectors_. The products between basis vectors
are all blades by definition. As shorthand, we combine subscripts as shown
below:

$$
\begin{aligned}
\ee_1\ee_0 &= \ee_{10} \\
\ee_1\ee_2 &= \ee_{12} \\
\ee_3\ee_0 &= \ee_{30} \\
&\dots
\end{aligned}
$$

At the moment, we would have $4\times 3 = 12$ basis bivectors if defined this way, but we impose a
relation on them that relates basis bivectors that contain the same subscripts. Namely, the product
of two vectors is minus the product of the two vectors with the order interchanged.

$$
\begin{aligned}
\ee_{01} &= -\ee_{10} \\
\ee_{02} &= -\ee_{20} \\
\ee_{03} &= -\ee_{30} \\
\ee_{12} &= -\ee_{21} \\
\ee_{31} &= -\ee_{13} \\
\ee_{23} &= -\ee_{32} \tag{1}
\end{aligned}
$$

For reasons that will become clear in a future writeup, we'll select the blades on the left hand side of $(1)$ to be the
_canonical 2-blades_ in PGA. There is some choice index order selection as will be explained later,
but the order here is used to match existing literature and so that computations later are made more
convenient.

Now that we know we can swap the order of the multiplication by basis vectors by introducing a sign,
we can compute things like $\ee_{01}\ee_0$.

$$
\begin{aligned}
\ee_{01}\ee_0 &= \ee_0\ee_1\ee_0 \\
&= -\ee_0\ee_0\ee_1 \\
&= 0
\end{aligned}
$$

Another example (that doesn't vanish):

$$
\begin{aligned}
\ee_{20}\ee_2 &= \ee_2\ee_0\ee_2 \\
&= -\ee_2\ee_2\ee_0 \\
&= -\ee_0
\end{aligned}
$$

The same algorithm can be used to produce the 4 trivectors:

$$
\begin{aligned}
\ee_{123} &= \ee_{12}\ee_3 = -\ee_{132} = \ee_{312} \\
\ee_{021} &= \ee_{02}\ee_1 = -\ee_{201} = \ee_{210} \\
\ee_{013} &= \ee_{01}\ee_3 = -\ee_{031} = \ee_{301} \\
\ee_{032} &= \ee_{03}\ee_2 = -\ee_{302} = \ee_{320}
\end{aligned}
$$

Not all permutations were listed, but just a few so you can gain familiarity with swapping indices
and introducing signs or removing them as ncessary. The last element we haven't touched on is the
pseudoscalar $\ee_{0123}$. The pseudoscalar is so named because while it does not have grade zero,
it is uniquely identified within its grade to within a permutation of its indices (compared to, say,
the grade-2 elements of which there are six distinct members).
Note that there is no way in which we can introduce an element with grade
higher than this, and so our $16$ algebra elements (1 scalar, 4 vector, 6 bivector, 4 trivector, and
1 pseudoscalar) are fully described. Linear combinations can be made from all of these elements to
produce a general multivector. To take the geometric product between general multivectors, we
leverage the fact that the geometric product obeys the distributive law.

$$
\begin{aligned}
(4\ee_1 - 2\ee_{32})(3\ee_{012} + \ee_{10}) &= 4\ee_1(3\ee_{012} + \ee_{10}) - 2\ee_{32}(3\ee_{012}
+ \ee_{10}) \\
&= 12\ee_1\ee_{012} + 4\ee_1\ee_{10} - 6\ee_{32}\ee_{012} - 2\ee_{32}\ee_{10} \\
&= -12\ee_{02} + 4\ee_0 - 6\ee_{301} - 2\ee_{3210} \\
&= 4\ee_0 - 12\ee_{02} - 6\ee_{013} - 2\ee_{0123}
\end{aligned}
$$

In the last step, we simply took the time to sort the resulting terms by grade and also performed
swaps as necessary to write terms with the canonical subscript ordering.

!!! tip "Exercises"

    1. Write down two vectors whose product is $-\ee_{01} + 2\ee_{13}$.
    2. The geometric product is neither commutative, nor anticommutative. Find examples that demonstrate this fact.
    3. Not every bivector can be written down as the product of two vectors. Find an example that demonstrates this fact.

### The Symmetric Inner Product

!!! info

    Klein API: `operator|`

    Written as $a \cdot b$.

The _symmetric inner product_ (inner product for short) is similar to the geometric product except
it _is always grade decreasing_ such that the final grade is the absolute value of the difference of
the operand grades. If the grade of the element resulting from a geometric product
would have been greater than this difference, the inner product extinguishes it to zero. In other
words, all indices must contract for the inner product to produce a non-zero value (note that if the
degenerate element contracts, a zero is produced anyways).
Before, we
saw that the geometric product can decrease the grade in
the event that indices match (which contracts the result to $1$ or $0$ depending). The easy way to
perform a symmetric product is to perform the geometric product as normal but discard terms produced
that produce the undesired grade. For example, $\ee_1\cdot \ee_1 = 1$ but $\ee_1\cdot
\ee_2 = 0$.
For a more nuanced example, $\ee_{12}\cdot\ee_{02}$ is _also_ $0$ because the $1$ index did not contract.
Note that we write the symmetric inner product as $\cdot$ in equation form, but in code,
it is expressed via the pipe (`|`) operator. As with the geometric product, the symmetric inner
product obeys the distributive law. Here's an example mirroring an example above but using the inner
product instead of the geometric product:

$$
\begin{aligned}
(4\ee_1 - 2\ee_{32})\cdot (3\ee_{012} + \ee_{10}) &= 4\ee_1\cdot(3\ee_{012} + \ee_{10}) -
2\ee_{32}\cdot (3\ee_{012} + \ee_{10}) \\
&= -12 \ee_{02} + 4\ee_0 \\
&= 4\ee_0 - 12\ee_{02}
\end{aligned}
$$

In addition, because of our "rule" that the inner product can only decrease grade, the inner product
between any quantity and a scalar quantity must be zero.

!!! tip "Exercises"

    1. Can the symmetric inner product ever produce the pseudoscalar? Why or why not?
    2. Explain why $\ee_0 \cdot \ee_{012}$ is $0$ and not $\ee_{12}$.
    3. The symmetric inner product not always commutative! Provide a counterexample for the inner product between other grades. When is it commutative?

### The Exterior Product

!!! info

    Klein API: `operator^`

    Written as $a\wedge b$.

The _exterior product_ (also known as the _wedge_ product or the _outer_ product) is similar to the
geometric product except it always extinguishes results upon contraction.
Thus, the result of an exterior product either has grade equal to the sum of the grades of its operands, or it
is exactly zero. The exterior product is represented in equations with a $\wedge$ symbol, and in
code, is represented with a caret (`^`) operator. The exterior product obeys the laws of distributivity as with the other products,
so let's return to our familiar example:

$$
\begin{aligned}
(4\ee_1 - 2\ee_{32})\wedge (3\ee_{012} + \ee_{10}) &= 4\ee_1\wedge(3\ee_{012} + \ee_{10}) -
2\ee_{32}\wedge (3\ee_{012} + \ee_{10}) \\
&= -2\ee_{3210} \\
&= -2\ee_{0123}
\end{aligned}
$$

!!! tip "Exercises"

    1. The geometric product **between vectors** (grade-1) is the sum of the inner product and the exterior product. Prove this by explicitly expanding out the geometric product between two general vectors.
    2. The geometric product is **not** generally the sum of the inner product and the exterior product. Why is that?
    3. The exterior product isn't generally anti-commutative! Find counterexamples demonstrating this fact.

### The Poincaré Dual Map

!!! info

    Klein API: `operator!`

    Written as $\JJ(a)$.

To perform the regressive product in the next section, we need a map that is _grade-reversing_. That
is, we need a map that takes multivectors $v$ to multivectors $v^*$ such that the grade of $v$ is
equal to $4$ minus the grade of $v^*$ (and vice versa). For example, vectors should be mapped to
trivectors, bivectors to bivectors, and the scalar to the pseudoscalar. In addition, this map needs
to be an involution (two application of the map is the identity). Here, a map is provided but note
that several such maps are possible. The nice property of the map provided here is that the
application of the map is just a coordinate tuple reversal without any sign changes. The mechanism for how this basis
was chosen is elegant but will be the subject of a different article. By convention, the dual
map is written as $\JJ$ in expressions.

$$
\begin{aligned}
    \JJ(1) = \ee_{0123}&,\quad \JJ(\ee_{0123}) = 1 \\
    \JJ(\ee_0) = \ee_{123}&,\quad \JJ(\ee_{123}) = \ee_0 \\
    \JJ(\ee_1) = \ee_{032}&,\quad \JJ(\ee_{032}) = \ee_1 \\
    \JJ(\ee_2) = \ee_{013}&,\quad \JJ(\ee_{013}) = \ee_2 \\
    \JJ(\ee_3) = \ee_{021}&,\quad \JJ(\ee_{021}) = \ee_3 \\
    \JJ(\ee_{01}) = \ee_{23}&,\quad \JJ(\ee_{23}) = \ee_{01} \\
    \JJ(\ee_{02}) = \ee_{31}&,\quad \JJ(\ee_{31}) = \ee_{02} \\
    \JJ(\ee_{03}) = \ee_{12}&,\quad \JJ(\ee_{12}) = \ee_{03}
\end{aligned}
$$

!!! tip "Exerices"

    1. Double check that all elements in the algebra are accounted for above.
    2. The dual map is a unary operator that can be distributed across each term in a multivector sum. For example, $\JJ(\ee_1 + 2\ee_{02}) = \ee_{032} + 2\ee_{31}$. Verify that the map is still an involution (that is, two applications of $\JJ$ should map back to the original argument).

### Regressive Product

!!! info

    Klein API: `operator&`

    Written as $a\vee b$.

The _regressive product_ (written as $\vee$ and expressed as the `&` operator in code) is defined in
terms of the dual map and the exterior product like so:

$$
a \vee b = \JJ(\JJ(a)\wedge\JJ(b))
$$

!!! danger "TODO: provide examples/exercises"

## Planes

!!! info

    [kln::plane](../../api/kln_plane)

A plane $p$ _is the manifestation of a reflection_. It is often helpful not to think of a plane as a
"set of points" in PGA as will be evident when we look at rotations and translations later.

### Examples

Let's look at some simple examples first.

#### Planes through the origin

The plane represented implicitly by $x = 0$ appears in PGA simply as the vector $\ee_1$. Similarly,
the planes $y = 0$ and $3z = 0$ correspond to $\ee_2$ and $3\ee_3$ respectively. It's easy to see that
planes like $x + 3y - z = 0$ can be represented by taking linear combinations of $\ee_1$, $\ee_2$
and $\ee_3$. In this case, the plane we just created would be represented as $\ee_1 + 3\ee_2 -
\ee_3$.

```c++
// Plane x = 0
kln::plane p1{1.f, 0.f, 0.f, 0.f};

// Plane y = 0
kln::plane p2{0.f, 1.f, 0.f, 0.f};

// Plane 3z = 0
kln::plane p3{0.f, 0.f, 3.f, 0.f};

// Plane x + 3y - z = 0
kln::plane p4{1.f, 3.f, -1.f, 0.f};

// Equivalent to p4
kln::plane p5 = p1 + 3.f * p2 - p3 / 3.f;
```

#### Planes away from the origin

To shift a plane from the origin, we can add a multiple of the degenerate vector $\ee_0$. This
vector is different from the other vectors in a very important way as we will see soon.

The plane $2x + 1 = 0$ is represented as $\ee_0 + 2\ee_1$.

```c++
// Plane 2x + 1 = 0
kln::plane p6{2.f, 0.f, 0.f, 1.f};
```

Other planes like to the one above can be constructed similarly.

#### Angles between planes

The angle between planes is given by the inner product which produces the cosine of the angle
between them as you would expect.

Suppose we have two planes $3\ee_0 + \ee_1 + \ee_3$ and $\ee_0 + \ee_3$. The first plane we recognize as
$x + z - 3 = 0$, a plane parallel to the y-axis that passes through the points
$(0, y, 3)$ and $(3, y, 0)$ for any value of $y$. The second plane the plane $z + 1 = 0$ which is
parallel to the $xy$-plane and intercepts the $z$-axis one unit below the origin. The angle between
them is computed as:

$$
\begin{aligned}
    (3\ee_0 + \ee_1 + \ee_3) \cdot (\ee_0 + \ee_3) &= 3\ee_0\cdot\ee_0 + \ee_1\cdot\ee_0 +
     \ee_3\cdot\ee_0 + \\
     &\quad\quad 3\ee_0 \cdot \ee_3 + \ee_1\cdot\ee_3 + \ee_3 \cdot\ee_3 \\
    &= 1
\end{aligned}
$$
