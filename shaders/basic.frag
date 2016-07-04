#version 400

layout(location = 0) out vec4 vFragColor;

uniform bool uDrawWireFrame;

in vec4 vVertexColor;
in vec3 gTriDistance;
in vec3 gPatchDistance;

float amplify(float d, float scale, float offset)
{
    d = scale * d + offset;
    d = clamp(d, 0, 1);
    d = 1 - exp2(-2*d*d);
    return d;
}

void main(void)
{
  vec3 color = vec3(1.0);

  if(uDrawWireFrame) {
    float d1 = min(min(gTriDistance.x, gTriDistance.y), gTriDistance.z);
    float d2 = min(min(gPatchDistance.x, gPatchDistance.y), gPatchDistance.z);
    color = amplify(d1, 40, -0.5) * amplify(d2, 60, -0.5) * vVertexColor.xyz;
  } else {
    color = vVertexColor.xyz;
  }

  vFragColor = vec4(color, 1.0);
}
