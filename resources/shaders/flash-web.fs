#version 100

precision highp float;

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform sampler2D texture0;
uniform vec2 flash;

void main() {
    vec4 texelColor = texture2D(texture0, fragTexCoord);
    gl_FragColor = mix(texelColor, vec4(1.0, 1.0, 1.0, texelColor.a), flash.x);
}