#version 330 core
in vec3 OutColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main () {
    //FragColor = vec4(OutColor, 1.0);
    //FragColor = texture(ourTexture, TexCoord) * vec4(OutColor, 1.0);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}
