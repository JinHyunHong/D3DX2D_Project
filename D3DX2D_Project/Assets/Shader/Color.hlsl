struct VertexInput
{
    float4 position : POSITION0;
    float4 color : COLOR0;
};

struct PixelInput
{
    float4 position : SV_POSITION0;
    float4 color : COLOR0;
};

cbuffer CameraBuffer : register(b0) // ->  0 ~ 13 // 4096 * 16byte
{
    matrix view;
    matrix proj;
};

cbuffer TransformBuffer : register(b1) // ->  0 ~ 13 // 4096 * 16byte
{
    matrix world;
};

cbuffer ColorBuffer : register(b2) // ->  0 ~ 13 // 4096 * 16byte
{
    float4 color;
};


PixelInput VS(VertexInput input)
{
    // 1 x 4            4 x 4  -----> 1 x 4
    //1, 2, 3, 1   *    0000
    //                  0000
    //                  0000
    //                  0000

    PixelInput output;
    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, proj);

    output.color = input.color;
 
    return output;
}

float4 PS(PixelInput input) : SV_Target
{
    // Pixel Shader가 반환하는 색상은 1.0f가 최대값이다.
    // 현재 format이 DXGI_FORMAT_R8G8B8A8_UNORM 
    // + color를 하면 1.0f를 넘겨버린다. Pixel Shader가 반환하는 색상은 1.0f가 최대이다. 그래서 색상을 곱해준다.
    // 그러나 *를 하면 된다. 대신 intersect_color = D3DXCOLOR(1, 1, 1, 1) 기본으로 가져야한다.
    // 0, 0, 0, 0으로 하면 곱하면 다 0이 되서 검정색이 나옴
    // 만일 충돌해서 intersect_color가 1.0f, 0.f, 0.f, 1.0f 가 되면 곱하면 특정색깔만 남길수 있다.
    
    // return input.color * color;
    return input.color;
}