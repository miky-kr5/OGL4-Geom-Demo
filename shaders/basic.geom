#version 400

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform float fGeomParam;
uniform int iLightsOn;
uniform mat4 mView, mProjection;
uniform mat4 mModel;

in vec4 teColor[];
in vec3 tePatchDistance[];

out vec3 gPatchDistance;
out vec3 gTriDistance;
out vec4 vVertexColor;

void main() {
  vec4 ambient = vec4(0.05, 0.05, 0.05, 1.0);
  vec4 lightDir = normalize(vec4(1.0, 1.0, 0.5, 1.0));
  vec4 bLightColor = vec4(vec3(0.3), 1.0);
  float NdotL, NdotL2;
  vec4 bLight;

  vec4 normal = vec4(0.0);
  vec4 V = gl_in[1].gl_Position - gl_in[0].gl_Position;
  vec4 W = gl_in[2].gl_Position - gl_in[0].gl_Position;
  normal.x = (V.y * W.z) - (V.z * W.y);
  normal.y = (V.z * W.x) - (V.x * W.z);
  normal.z = (V.x * W.y) - (V.y * W.x);
  normal = normalize(normal);
  vec4 mvNormal = mView * mModel * normal;

  if(iLightsOn != 0) {
    NdotL = max(dot(mvNormal, lightDir), 0.0);
    NdotL2 = max(dot(mvNormal, -lightDir), 0.0);
    bLight = bLightColor * NdotL2;
  } else {
    NdotL = 1.0;
    bLight = vec4(0.0);
  }

  gl_Position = gl_in[0].gl_Position + (fGeomParam * normal);
  gl_Position = mProjection * mView * mModel * gl_Position;
  vVertexColor = (NdotL * teColor[0]) + (bLight * teColor[0]) + ambient;
  gPatchDistance = tePatchDistance[0];
  gTriDistance = vec3(1, 0, 0);
  EmitVertex();

  gl_Position = gl_in[1].gl_Position + (fGeomParam * normal);
  gl_Position = mProjection * mView * mModel * gl_Position;
  vVertexColor = (NdotL * teColor[1]) + (bLight * teColor[0]) + ambient;
  gPatchDistance = tePatchDistance[1];
  gTriDistance = vec3(0, 1, 0);
  EmitVertex();

  gl_Position = gl_in[2].gl_Position + (fGeomParam * normal);
  gl_Position = mProjection * mView * mModel * gl_Position;
  vVertexColor = (NdotL * teColor[2]) + (bLight * teColor[0]) + ambient;
  gPatchDistance = tePatchDistance[2];
  gTriDistance = vec3(0, 0, 1);
  EmitVertex();

  EndPrimitive();
}
