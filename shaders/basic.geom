#version 400

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform float fGeomParam;
uniform mat4 mView, mProjection;
uniform mat4 mModel;

in vec4 teColor[];
in vec3 tePatchDistance[];

out vec3 gPatchDistance;
out vec3 gTriDistance;
out vec4 vVertexColor;

void main() {
  vec4 normal = vec4(0.0);
  vec4 V = gl_in[1].gl_Position - gl_in[0].gl_Position;
  vec4 W = gl_in[2].gl_Position - gl_in[0].gl_Position;
  normal.x = (V.y * W.z) - (V.z * W.y);
  normal.y = (V.z * W.x) - (V.x * W.z);
  normal.z = (V.x * W.y) - (V.y * W.x);
  normal = normalize(normal);

  gl_Position = gl_in[0].gl_Position + (fGeomParam * normal);
  gl_Position = mProjection * mView * mModel * gl_Position;
  vVertexColor = teColor[0];
  gPatchDistance = tePatchDistance[0];
  gTriDistance = vec3(1, 0, 0);
  EmitVertex();

  gl_Position = gl_in[1].gl_Position + (fGeomParam * normal);
  gl_Position = mProjection * mView * mModel * gl_Position;
  vVertexColor = teColor[1];
  gPatchDistance = tePatchDistance[1];
  gTriDistance = vec3(0, 1, 0);
  EmitVertex();

  gl_Position = gl_in[2].gl_Position + (fGeomParam * normal);
  gl_Position = mProjection * mView * mModel * gl_Position;
  vVertexColor = teColor[2];
  gPatchDistance = tePatchDistance[2];
  gTriDistance = vec3(0, 0, 1);
  EmitVertex();

  EndPrimitive();
}
