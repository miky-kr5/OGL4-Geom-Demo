#version 400

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in float vGeomParamVs[];
in vec4 vColorVs[];

out vec4 vVertexColor;

void main() {
  vec4 normal = vec4(0.0);
  vec4 V = gl_in[2].gl_Position - gl_in[0].gl_Position;
  vec4 W = gl_in[1].gl_Position - gl_in[0].gl_Position;
  normal.x = (V.y * W.z) - (V.z * W.y);
  normal.y = (V.z * W.x) - (V.x * W.z);
  normal.z = (V.x * W.y) - (V.y * W.x);
  normal = normalize(normal);

  for(int k = 0; k < gl_in.length(); k++) {
    gl_Position = gl_in[k].gl_Position + (vGeomParamVs[k] * normal);
    vVertexColor = vColorVs[k];
    EmitVertex();
  }
  EndPrimitive();
}
