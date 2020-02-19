!!! danger

    You are currently reading a DRAFT that is available publicly to facilitate collaboration

In the [introduction](../intro), we considered a set of three basis vectors $\ee_1$,
$\ee_2$, and $\ee_3$. In addition, we pontificated a bit on why restricting ourselves to
vectors can cause issues, and argued for the need for a richer structure to match the
richness of the geometry. But how should we go about doing this?

In 3-dimensions, it seems a bit unfair that only "arrows"
can be represented. After all, our world is filled with objects that have area and
volume too. Suppose we wanted to represent a unit area in the x-y plane. Let's give it
a name, say $\ee_{12}$. It seems reasonable that the areas $\ee_{13}$ and $\ee_{23}$.
But wait! Our choice of of index order seems a bit arbitrary. What about $\ee_{21}$,
$\ee_{31}$ and $\ee_{32}$. If we follow our nose a bit, it seems reasonable that the
area represented by $\ee_{12}$ should equal $-\ee_{21}$. After all, they possess opposite
orientations from one another. What about elements with two repeated indices? Like $\ee_{11}$
or $\ee_{33}$? Well, such elements can't reasonably span any area, so let's get back to
how we should handle those in a moment. Like the unit vectors, it seems sensible to allow
us to scale these area-elements with a weight (like $3\ee_{12}$) and add them together
to create areas of arbitrary weight and orientation. So, for example, let's try to add
$\ee_{12} + 2\ee_{23}$. What should its orientation be?

TODO!

For volumes, we have one choice that spans a non-zero volume which is $\ee_{123}$. We
could have also chosen a different basis ordering, which again we'll get back to later.
Let's call our single-index elements _vectors_ as before, the two-index elements _bivectors_,
and the three-index elements _trivectors_.

TODO!
