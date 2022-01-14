#version 330 core

layout (location = 0) in vec3 in_v3Position;
layout (location = 1) in vec3 in_v3Color;
layout (location = 2) in vec2 in_v2TextureCoord;
layout (location = 3) in vec3 in_v3Normal;

out vec3 m_v3Color;
out vec2 m_v2TextureCoord;
out vec3 m_v3Normal;
out vec3 m_v3CurrentPosition;

uniform mat4 uni_mat4CameraMatrix;
uniform mat4 uni_mat4Model;

void main()
{
	m_v3CurrentPosition = vec3(uni_mat4Model * vec4(in_v3Position, 1.0f));
	gl_Position = uni_mat4CameraMatrix * vec4(m_v3CurrentPosition, 1.0);

	m_v3Color = in_v3Color;
	m_v2TextureCoord = in_v2TextureCoord;
	m_v3Normal = in_v3Normal;
}