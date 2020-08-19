const vs_src = `
    attribute vec4 a_pos;
    uniform mat4 u_mvp;
    uniform mat4 u_proj;

    void main() {
        gl_Position = u_proj * u_mvp * a_pos;
    }
`;

const fs_src = `
    void main() {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
`

function init_canvas(cv) {
    const gl = cv.getContext('webgl');

    gl.clearColor(0, 0, 0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);
}

function load_default(gl) {
    const prog = link_program(gl, vs_src, fs_src);
    if (!prog) {
        return null;
    }

    return {
        prog,
        a_pos: gl.getAttribLocation(prog, 'a_pos'),
        u_mvp: gl.getAttribLocation(prog, 'u_mvp'),
        u_proj: gl.getAttribLocation(prog, 'u_proj'),
    }
}

function load_shader(gl, type, source) {
    const shader = gl.createShader(type);
    gl.shaderSource(shader, source);
    gl.compileShader(shader);
    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
        console.error(gl.getShaderInfoLog(shader));
        gl.deleteShader(shader);
        return null;
    }
    return shader;
}

function link_program(gl, vs, fs) {
    const vert = load_shader(gl, gl.VERTEX_SHADER, vs);
    const frag = load_shader(gl, gl.VERTEX_SHADER, fs);

    const prog = gl.createProgram();
    gl.attachShader(prog, vert);
    gl.attachShader(prog, frag);
    gl.linkProgram(prog);

    if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
        console.error(gl.getProgramInfoLog(prog));
        gl.deleteShader(vert);
        gl.deleteShader(frag);
        return null;
    }

    return prog;
}