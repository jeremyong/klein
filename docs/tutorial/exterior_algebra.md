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
orientations from one another.

<DIV ID="bivector"></DIV>
<SCRIPT>
/*
window.addEventListener('load',()=>{
    Algebra(3,0,1,()=>{
    // rotation helper and Lathe function.     
    var rot = (a,P)=>Math.cos(a)+Math.sin(a)*P.Normalized,
        lathe=(X,n,P,m)=>[...Array(n+1)].map((x,i)=>rot(i/n*Math.PI*(m||1),P)>>>X),

    // wrap takes X, a double array of points, and generates triangles.
        wrap=(X)=>{
          var u=X.length-1,v=X[0].length-1; X=[].concat.apply([],X);
          var P=[],vp=v+1; for(var i=0;i<u*vp;i+=vp)for(var j=0;j<v;j++)P.push([i+j,i+j+1,vp+i+j],[i+j+1,vp+i+j,vp+i+j+1]);
          return P.map(x=>x.map(x=>X[x]));
        },

    // Basic primitives constructed by Lathing points, line segments, etc.
        cylinder = (r=1,h=1,x=32)=>wrap(lathe([!1e0,!(1e0+r*1e3),!(1e0+r*1e3+h*1e1),!(1e0+h*1e1)],x,1e23)),
        torus    = (r=.3,r2=.25,x=32,y=16)=>wrap(lathe((1+r*.5e03)>>>lathe(!(1e0+r2*(1e1+1e3)/2**.5),y,1e13),x,1e23)),
        sphere   = (r=1,x=32,y=16)=>wrap(lathe(lathe(!(1e0+r*1e1),y,1e13,.5),x,1e23)),
        cone     = (r=1,h=1,x=64)=>wrap(lathe([!1e0,!(1e0+r*1e3),!(1e0+h*1e1)],x,1e23)),
        arrow    = ()=>[/*...cone(.075,0),*/...cone(.075,.2),...cylinder(.03,-1)],

    // A selection of these objects.
        objs=[arrow(),arrow()].map(x=>({data:x}));

    // Render and rotate them using the webGL2 previewer.
      var c=document.getElementById('bivector').appendChild( this.graph(()=>{
        var time = Math.PI/2+-.5*Math.sin(performance.now()/1000);
        var time2 = Math.PI/2+-.5*Math.sin(performance.now()/2134);
        var t1 = objs[0].transform = rot(time,1e13)*rot(-0.1,1e12)*(1-.5e01);
        var t2 = objs[1].transform = rot(time2,1e12+.5e23)*rot(-0.1,1e12)*(1-.5e01);
        return [0xbbaaffaa,...objs, 0xff0000, [1e123,t1>>>1e123,t2>>>1e123]]
      },{gl:1,alpha:1,animate:1,camera:(1-.7e03)*Math.E**(Math.PI/4*1e13),grid:1}));
      c.style.width='100%'; c.style.height='250px'; c.style.background='transparent';
    });

});
\*/
</SCRIPT>

What about elements with two repeated indices? Like $\ee_{11}$
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
