// VertexInput과 InputLayout(IA 단계) 타입이 다르면 에러가 난다.
struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

struct PixelInput
{
    float4 position : SV_POSITION0;
    float2 uv : TEXCOORD0;
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

// keyframe 정보를 받아오기 위해 constantbuffer을 만든다.
cbuffer AnimationBuffer : register(b2)
{
    float2 sprite_offset; //keyframe이 가지고 있는 offset
    float2 sprite_size; //keyframe이 가지고 있는 size 
    float2 texture_size; //텍스쳐의 최종 크기
    float is_animated; // 애니메이션이 없는지 있는지
    float padding;
    float4 color_key;
}

PixelInput VS(VertexInput input)
{
    // 1 x 4            4 x 4  -----> 1 x 4
    //1, 2, 3, 1   *    0000
    //                  0000
    //                  0000
    //                  0000

    /*
        우리는 여기서 스프라이트이미지(아틀라스) 1장을 받고
        특정 부분만 툭떼서 사용할 것이다.(UV로)
    
        UV를 조작해야함
    */
    PixelInput output;
    
    // 이거 하는 이유는.. 액터 생성시에 따로 사이즈를 줄 필요가 없다. 그렇게 주면 결국 이미지가 짤려서 고정되서 나온다.
    // 이미지는 각 크기가 다르다. 그래서 이미지 사이즈를 크기로 만든다. 이미지 크기대로 출력될 수 있도록
    // 원래는 이렇게 하지만, hlsl에선 이렇게 할 필요가 없다.
    //output.position = float4(input.position.x * sprite_size.x, input.position.y * sprite_size.y, 0.0f, 1.0f)
    //hlsl에서는 float4의 데이터도 간편하게 float3, float2, float형태로 바꿔 사용할 수 있다.
    // 이렇게 가능 float 2끼리 곱하기가 가능하다.
    // 편한 수식 가능
    // input.xxxx 등 가능...
    // 이렇게 곱해주면 그 크기만큼 값을 가지게 된다.
    // 여러 문제가 있어서 보통은 shader를 분리하는 것이 좋다.(뭔말이냐하면은 텍스쳐용 shader와 애니메이션용 shader 컬러용 shader로 분할해서
    // Meshrenderer에서는 shader의 경로를 파라미터로 받아 외부에서 처리하는 것이 좋다.)
    output.position = float4(input.position.xy * sprite_size, 0.0f, 1.0f);
    
    output.position = mul(output.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, proj);

    // 0 ~ 1인 uv 좌표를 조정
    output.uv = input.uv;
    // 원래 크기대로 늘려줌
    output.uv *= sprite_size / texture_size; // 정규화된 크기가 나옴(소수점 단위로) ex ) 200 / 1000 = 0.2 이걸 원본 크기에 * 0.2 해주면 그 크기만큼 된다.
    // 특정 오프셋만큼 이동
    output.uv += sprite_offset / texture_size;

    return output;
}

Texture2D source_texture : register(t0);
SamplerState samp        : register(s0); //16 -> 0 ~ 15

float4 PS(PixelInput input) : SV_Target
{
    if(is_animated)
    {
        float4 color = 0.0f;

        color = source_texture.Sample(samp, input.uv);
        
        if (any(color_key))
        {
            float4 color_key_normal = color_key / 255;
            if (abs(color_key_normal.r - color.r) < 0.01)
                   discard;
            
            return color;
        }
        
        else
            return color;
    }
    
    // Shader가 작동하고 있는지 확인하고 싶은 경우 특정 색이 찍히도록 코드르 작성하고
    // 실행시켜 확인한다. - visualstudio의 GPU profiling 기능을 사용해도 좋다.
    else
        return float4(1, 0, 0, 1);
}