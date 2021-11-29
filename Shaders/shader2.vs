#version 400\n
layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 aTexCoord;
uniform mat4 ModelMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
out vec3 Normals;
out vec3 FragPos;
out vec2 TexCoord;
void main () {
     gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4 (vp, 1.0);
     vec4 a = ModelMatrix * vec4(vp, 1.0f);
     FragPos = a.xyz / a.w;
     Normals = transpose(inverse(mat3(ModelMatrix))) * normal;
     TexCoord = aTexCoord;
}

