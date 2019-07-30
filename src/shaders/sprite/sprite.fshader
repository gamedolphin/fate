$input TexCoords

#include <bgfx_shader.sh>

uniform sampler2D image;
uniform vec3 spriteColor;

void main() {
     gl_FragColor = mul(vec4(spriteColor, 1.0), texture2D(image, TexCoords));
}