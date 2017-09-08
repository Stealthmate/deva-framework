#version 450
#extension GL_ARB_separate_shader_objects : enable
layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec3 inColor;

layout(binding=0) uniform TestUni {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) out vec3 fragColor;

vec3 pos[3] = vec3[](
    vec3(-0.5, 0.0, 0.0),
    vec3(0.0, 0.5, 0.0),
    vec3(0.5, 0.0, 0.0)
);

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    gl_Position = inPosition * ubo.model * ubo.view * ubo.proj;
    //fragColor = inPosition.xyz;
    fragColor = vec3(0.5, inPosition.w, 0.f);
    //fragColor = inColor;
}
