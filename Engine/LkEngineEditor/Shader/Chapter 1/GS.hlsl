#include "Common.hlsli"

[maxvertexcount(9)]
void GS(triangle VertexOut input[3], inout TriangleStream<VertexOut> output)
{
    VertexOut vertexes[6];
    int i;
    [unroll]
    for (i = 0; i < 3; ++i)
    {
        vertexes[i] = input[i];
        vertexes[i + 3].posH = (input[i].posH + input[(i + 1) % 3].posH) / 2.0f;
    }

    [unroll]
    for (i = 0; i < 3; ++i)
    {
        output.Append(vertexes[i]);
        output.Append(vertexes[3 + i]);
        output.Append(vertexes[(i + 2) % 3 + 3]);
        output.RestartStrip();

    }
}