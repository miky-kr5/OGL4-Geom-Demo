#version 400

uniform mat4 mView, mProjection, mModel;
uniform float fGeomParam;

layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec4 vColor;

out vec4 vColorVs;
out float vGeomParamVs;

void main()
{
	vColorVs = vColor;
	vGeomParamVs = fGeomParam;
	gl_Position = mProjection * mView * mModel * vVertex;
}
