#ifndef KLEIN_GUARD
#define KLEIN_GUARD

// p0 -> (e0, e1, e2, e3)
// p1 -> (1, e23, e31, e12)
// p2 -> (e0123, e01, e02, e03)
// p3 -> (e123, e032, e013, e021)

struct plane
{
    vec4 p0;
};

struct line
{
    vec4 p1;
    vec4 p2;
};

struct point
{
    vec4 p3;
};

struct rotor
{
    vec4 p1;
};

struct translator
{
    vec4 p2;
};

struct motor
{
    vec4 p1;
    vec4 p2;
};

rotor rr_mul(in rotor a, in rotor b)
{
    rotor c;
    c.p1 = a.p1.x * b.p1;
    c.p1 -= a.p1.yzwy * b.p1.ywyz;

    vec4 t = a.p1.zyzw * b.p1.zxxx;
    t += a.p1.wwyz * b.p1.wzwy;
    t.x = -t.x;

    c.p1 += t;
    return c;
}

translator tt_mul(in translator a, in translator b)
{
    // (1 + a.p2) * (1 + b.p2) = 1 + a.p2 + b.p2
    translator c;
    c.p2 = a.p2 + b.p2;
    return c;
}

motor mm_mul(in motor a, in motor b)
{
    motor c;
    vec4 a_zyzw = a.p1.zyzw;
    vec4 a_ywyz = a.p1.ywyz;
    vec4 a_wzwy = a.p1.wzwy;
    vec4 c_wwyz = b.p1.wwyz;
    vec4 c_yzwy = b.p1.yzwy;

    c.p1 = a.p1.x * b.p1;
    vec4 t = a_ywyz * c_yzwy;
    t += a_zyzw * b.p1.zxxx;
    t.x = -t.x;
    c.p1 += t;
    c.p1 -= a_wzwy * c_wwyz;

    c.p2 = a.p1.x * b.p2;
    c.p2 += a.p2 * b.p1.x;
    c.p2 += a_ywyz * b.p2.yzwy;
    c.p2 += a.p2.ywyz * c_yzwy;
    t = a_zyzw * b.p2.zxxx;
    t += a_wzwy * b.p2.wwyz;
    t += a.p2.zxxx * b.p1.zyzw;
    t += a.p2.wzwy * c_wwyz;
    t.x = -t.x;
    c.p2 -= t;
    return c;
}

plane rotor_plane(in rotor r, in plane p)
{
    vec4 dc_scale = vec4(1.0, 2.0, 2.0, 2.0);
    vec4 neg_low = vec4(-1.0, 1.0, 1.0, 1.0);

    vec4 t1 = r.p1.zxxx * r.p1.zwyz;
    t1 += r.p1.yzwy * r.p1.yyzw;
    t1 *= dc_scale;

    vec4 t2 = r.p1 * r.p1.xwyz;
    t2 -= (r.p1.wxxx * r.p1.wzwy) * neg_low;
    t2 *= dc_scale;

    vec4 t3 = r.p1 * r.p1;
    t3 -= r.p1.xwyz * r.p1.xwyz;
    t3 += r.p1.xxxx * r.p1.xxxx;
    t3 -= r.p1.xzwy * r.p1.xzwy;

    // TODO: provide variadic rotor-plane application
    plane q;
    q.p0 = t1 * p.p0.xzwy;
    q.p0 += t2 * p.p0.xwyz;
    q.p0 += t3 * p.p0;
    return q;
}

plane motor_plane(in motor m, in plane p)
{
    vec4 dc_scale = vec4(1.0, 2.0, 2.0, 2.0);
    vec4 neg_low = vec4(-1.0, 1.0, 1.0, 1.0);

    vec4 t1 = m.p1.zxxx * m.p1.zwyz;
    t1 += m.p1.yzwy * m.p1.yyzw;
    t1 *= dc_scale;

    vec4 t2 = m.p1 * m.p1.xwyz;
    t2 -= (m.p1.wxxx * m.p1.wzwy) * neg_low;
    t2 *= dc_scale;

    vec4 t3 = m.p1 * m.p1;
    t3 -= m.p1.xwyz * m.p1.xwyz;
    t3 += m.p1.xxxx * m.p1.xxxx;
    t3 -= m.p1.xzwy * m.p1.xzwy;

    vec4 t4 = m.p1.x * m.p2;
    t4 += m.p1.xzwy * m.p2.xwyz;
    t4 += m.p1 * m.p2.x;
    t4 -= m.p1.xwyz * m.p2.xzwy;
    t4 *= vec4(0.0, 2.0, 2.0, 2.0);

    // TODO: provide variadic motor-plane application
    plane q;
    q.p0 = t1 * p.p0.xzwy;
    q.p0 += t2 * p.p0.xwyz;
    q.p0 += t3 * p.p0;
    q.p0 += vec4(dot(t4, p.p0), 0.0, 0.0, 0.0);
    return q;
}

point rotor_point(in rotor r, in point p)
{
    vec4 scale = vec4(0, 2, 2, 2);

    vec4 t1 = r.p1 * r.p1.xwyz;
    t1 -= r.p1.x * r.p1.xzwy;
    t1 *= scale;

    vec4 t2 = r.p1.x * r.p1.xwyz;
    t2 += r.p1.xzwy * r.p1;
    t2 *= scale;

    vec4 t3 = r.p1 * r.p1;
    t3 += r.p1.yxxx * r.p1.yxxx;
    vec4 t4 = r.p1.zwyz * r.p1.zwyz;
    t4 += r.p1.wzwy * r.p1.wzwy;
    t3 -= t4 * vec4(-1.0, 1.0, 1.0, 1.0);

    // TODO: provide variadic rotor-point application
    point q;
    q.p3 = t1 * p.p3.xwyz;
    q.p3 += t2 * p.p3.xzwy;
    q.p3 += t3 * p.p3;
    return  q;
}

point motor_point(in motor m, in point p)
{
    vec4 scale = vec4(0, 2, 2, 2);

    vec4 t1 = m.p1 * m.p1.xwyz;
    t1 -= m.p1.x * m.p1.xzwy;
    t1 *= scale;

    vec4 t2 = m.p1.x * m.p1.xwyz;
    t2 += m.p1.xzwy * m.p1;
    t2 *= scale;

    vec4 t3 = m.p1 * m.p1;
    t3 += m.p1.yxxx * m.p1.yxxx;
    vec4 t4 = m.p1.zwyz * m.p1.zwyz;
    t4 += m.p1.wzwy * m.p1.wzwy;
    t3 -= t4 * vec4(-1.0, 1.0, 1.0, 1.0);

    t4 = m.p1.xzwy * m.p2.xwyz;
    t4 -= m.p1.x * m.p2;
    t4 -= m.p1.xwyz * m.p2.xzwy;
    t4 -= m.p1 * m.p2.x;
    t4 *= scale;

    // TODO: provide variadic motor-point application
    point q;
    q.p3 = t1 * p.p3.xwyz;
    q.p3 += t2 * p.p3.xzwy;
    q.p3 += t3 * p.p3;
    q.p3 += t4 * p.p3.x;
    return  q;
}

point motor_origin(in motor m)
{
    point p;
    p.p3 = m.p1 * m.p2.x;
    p.p3 += m.p1.x * m.p2;
    p.p3 += m.p1.xwyz * m.p2.xzwy;
    p.p3 = m.p1.xzwy * m.p2.xwyz - p.p3;
    p.p3 *= vec4(0.0, 2.0, 2.0, 2.0);
    p.p3.x = 1.0;
    return p;
}

#endif // KLEIN_GUARD