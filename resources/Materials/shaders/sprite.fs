uniform sampler2D texture0;
uniform vec4 color;

varying vec2 vUV;

void w4_main()
{
    //vec4 pixel = texture2D(texture0, vUV);
    //pixel *= color;

    gl_FragColor = texture2D(texture0, vUV) * color;
}
